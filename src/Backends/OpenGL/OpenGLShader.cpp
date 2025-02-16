#include <glad/glad.h>
#include "Backends/OpenGL/OpenGLShader.h"
#include "Core/Debug/Logging.h"
#include "Core/Debug/Assert.h"
#include <glm/gtc/type_ptr.hpp>
#include <fstream>


OpenGLShader::OpenGLShader(const std::string &name, const std::string &filepath)
    :m_Name(name)
{
    std::string source = ReadFile(filepath);
    auto shaderSources = PreProcess(source);
    Compile(shaderSources);   
}

OpenGLShader::OpenGLShader(const std::string &name, const std::string& vertexSrc, const std::string &fragmentSrc)
    :m_Name(name)
{
    std::unordered_map<GLenum, std::string> sources;
    sources[GL_VERTEX_SHADER] = vertexSrc;
    sources[GL_FRAGMENT_SHADER] = fragmentSrc;
    Compile(sources);   
}

OpenGLShader::~OpenGLShader()
{
    glDeleteProgram(m_ShaderID);
}

std::string OpenGLShader::ReadFile(const std::string &filepath)
{
    std::string result;
    std::fstream fin(filepath, std::ios::in | std::ios::binary);
    if (fin)
    {
        fin.seekg(0, std::ios::end);
        result.resize(fin.tellg());
        fin.seekg(0, std::ios::beg);
        fin.read(&result[0], result.size());
        fin.close();
    }
    else
    {
        ERROR("Could not open file path: {0}", filepath);
    }
    return result;
}

std::unordered_map<GLenum, std::string> OpenGLShader::PreProcess(const std::string &source)
{
    std::unordered_map<GLenum, std::string> shaderSources;
    const char* typeToken = "#type";
    size_t typeTokenLength = strlen(typeToken);
    size_t pos = source.find(typeToken, 0);

    while (pos != std::string::npos)
    {
        size_t eol = source.find_first_of("\r\n", pos);
        ASSERT(eol != std::string::npos, "Syntax error");
        size_t begin = pos + typeTokenLength + 1;
        std::string type = source.substr(begin, eol - begin);
        ASSERT(Utils::ShaderTypeFromString(type), "Invalid shader type specified");
        size_t nextLinePos = source.find_first_not_of("\r\n", eol);
        pos = source.find(typeToken, nextLinePos);
        shaderSources[Utils::ShaderTypeFromString(type)] = source.substr(nextLinePos, pos - (nextLinePos == std::string::npos ? source.size() - 1 : nextLinePos));
    }
    return shaderSources;
}

void OpenGLShader::Compile(const std::unordered_map<GLenum, std::string> &shaderSources)
{
    GLuint program = glCreateProgram();    
    ASSERT(shaderSources.size() <= 2, "Only support 2 shaders for now");

    std::array<GLenum, 2> glShaderIDs; 
    int glShaderIDIndex = 0;

    
    for (auto &kv : shaderSources)
    {
        GLenum type = kv.first;
        const std::string& source = kv.second;
        GLuint shader = glCreateShader(type);

        const GLchar* sourceCStr = source.c_str();
        glShaderSource(shader, 1, &sourceCStr, 0);
        glCompileShader(shader);

        GLint isCompiled = 0;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
        if (isCompiled == GL_FALSE)
        {
            GLint maxLength = 0;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

            std::vector<GLchar> infoLog(maxLength);
            glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

            glDeleteShader(shader);

            ERROR("{0}", infoLog.data());
            WARN("Shader failed at {0}", glShaderIDIndex);
            ASSERT(false, "Shader compilation failure at!");
            exit(-1);
        }
        glAttachShader(program, shader);
        glShaderIDs[glShaderIDIndex++] = shader;
    }

    m_ShaderID = program;
    glLinkProgram(program);

    GLint isLinked = 0;
    glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);
    
    if (isLinked == GL_FALSE)
    {
        GLint maxLength = 0;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

        std::vector<GLchar> infoLog(maxLength);
        glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

        
        glDeleteProgram(program);
        for (auto id : glShaderIDs) 
        {
            glDeleteShader(id);
        }

        ERROR("{0}", infoLog.data());
        ASSERT(false, "Shader program link failure!");
        return;
    }

    for (auto id : glShaderIDs)
    {
        glDetachShader(program, id);
    }
}

void OpenGLShader::Bind() const 
{
    glUseProgram(m_ShaderID);  
}

void OpenGLShader::UnBind() const
{
    glUseProgram(0);
}

void OpenGLShader::SetInt(const std::string &name, int value)
{
    UploadUniformInt(name, value);
}

void OpenGLShader::SetIntArray(const std::string &name, int* values, uint32_t count)
{
    UploadUniformIntArray(name, values, count);
}

void OpenGLShader::SetFloat(const std::string &name, float value)
{
    UploadUniformFloat(name, value);
}

void OpenGLShader::SetFloat2(const std::string &name, const glm::vec2 &value)
{
    UploadUniformFloat2(name, value);
}

void OpenGLShader::SetFloat3(const std::string &name, const glm::vec3 &value)
{
    UploadUniformFloat3(name, value);
}

void OpenGLShader::SetFloat4(const std::string &name, const glm::vec4 &value)
{
    UploadUniformFloat4(name, value);
}

void OpenGLShader::SetMat4(const std::string &name, const glm::mat4 &value)
{
    UploadUniformMat4(name, value);
}

void OpenGLShader::UploadUniformInt(const std::string &name, int value)
{
    GLint location = glGetUniformLocation(m_ShaderID, name.c_str());
    glUniform1i(location, value);
}

void OpenGLShader::UploadUniformIntArray(const std::string &name, int* values, uint32_t count)
{
    GLint location = glGetUniformLocation(m_ShaderID, name.c_str());
    glUniform1iv(location, count, values);
}

void OpenGLShader::UploadUniformFloat(const std::string &name, float value)
{
    GLint location = glGetUniformLocation(m_ShaderID, name.c_str());
    glUniform1f(location, value);
}

void OpenGLShader::UploadUniformFloat2(const std::string &name, const glm::vec2 &value)
{
    GLint location = glGetUniformLocation(m_ShaderID, name.c_str());
    glUniform2f(location, value.x, value.y);
}

void OpenGLShader::UploadUniformFloat3(const std::string &name, const glm::vec3 &value)
{
    GLint location = glGetUniformLocation(m_ShaderID, name.c_str());
    glUniform3f(location, value.x, value.y, value.z);
}

void OpenGLShader::UploadUniformFloat4(const std::string &name, const glm::vec4 &value)
{
    GLint location = glGetUniformLocation(m_ShaderID, name.c_str());
    glUniform4f(location, value.x, value.y, value.z, value.w);
}

void OpenGLShader::UploadUniformMat3(const std::string &name, const glm::mat3 &matrix)
{
    GLint location = glGetUniformLocation(m_ShaderID, name.c_str());
    glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}

void OpenGLShader::UploadUniformMat4(const std::string &name, const glm::mat4 &matrix)
{
    GLint location = glGetUniformLocation(m_ShaderID, name.c_str());
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}