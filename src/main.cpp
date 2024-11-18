#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <imgui.h>
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <string>
#include <vector>
#include <iostream>
#include <cmath>

float vertices[16 * 6] = {
    -4.0, -4.0, 0.5, 0.55, 0.24, 0.09,
    -4.0,  4.0, 0.5, 0.55, 0.24, 0.09,
     4.0,  4.0, 0.5, 0.55, 0.24, 0.09,
     4.0, -4.0, 0.5, 0.55, 0.24, 0.09,

    -4.5, -4.5, 0.5, 0.55, 0.24, 0.09,
    -4.5,  4.5, 0.5, 0.55, 0.24, 0.09,
     4.5,  4.5, 0.5, 0.55, 0.24, 0.09,
     4.5, -4.5, 0.5, 0.55, 0.24, 0.09,
      
    -5.0, -5.0, 0.0, 0.55, 0.24, 0.09,
    -5.0,  5.0, 0.0, 0.55, 0.24, 0.09,
     5.0,  5.0, 0.0, 0.55, 0.24, 0.09,
     5.0, -5.0, 0.0, 0.55, 0.24, 0.09,

    -4.0, -4.0, 0.5, 0.803, 0.522, 0.247,
    -4.5, -4.5, 0.5, 0.545, 0.271, 0.075,
    -4.5,  4.5, 0.5, 0.545, 0.271, 0.075,
    -4.0,  4.0, 0.5, 0.803, 0.522, 0.247,
};

unsigned int indices[16] = {
    0, 1, 2, 3,
    4, 5, 6, 7,
    8, 9, 10, 11,
    12, 13, 14, 15,
};

glm::vec3 translation_vector = {0.0f, 0.0f, 5.0f};
glm::vec3 scale_vector = {0.2f, 0.2f, 0.2f};
glm::vec3 rotation_vector = {0.0f, 0.8f, 1.6f};

float zoomOut = 1.0f;
float aspect_ratio;

class Camera
{
public:
    glm::vec3 position;
    glm::vec3 target;
    glm::vec3 up;

    float fov;
    float nearClip, farClip;
    float aspectRatio;

    Camera(glm::vec3 pos, glm::vec3 tgt, glm::vec3 upDir, float fovDeg, float aspect, float near, float far)
        : position(pos), target(tgt), up(upDir), fov(fovDeg), nearClip(near), farClip(far), aspectRatio(aspect) {}

    glm::mat4 getViewMatrix() {
        return glm::lookAt(position, target, up);
    }

    glm::mat4 getProjectionMatrix() {
        return glm::perspective(glm::radians(fov), aspect_ratio, nearClip, farClip);
    }
};

Camera camera(
    glm::vec3(0.0f, 0.0f, 10.0f),  // Position
    glm::vec3(0.0f, 0.0f, 0.0f),   // Target
    glm::vec3(0.0f, 1.0f, 0.0f),   // Up direction
    45.0f,                         // FOV
    aspect_ratio,                  // Aspect ratio
    1.0f,                          // Near clip
    20.0f                          // Far clip
);

void print_matrix(glm::mat4 mat)
{
    for (int i=0; i<4; i++)
    {
        for (int j=0; j<4; j++)
        {
            std::cout << mat[i][j] << " ";
        }
        std::cout << "\n";
    }
}

void initialization()
{
    glEnable(GL_BLEND);
    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CW);
    glCullFace(GL_BACK);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_DEPTH_TEST);
}

void keyFunction(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

void renderChessBoard()
{
    std::string vertexSource = R"(
        #version 330 core
        layout(location = 0) in vec3 position;
        layout(location = 1) in vec3 color;

        out vec3 fragColor;

        uniform mat4 model;
        uniform mat4 view;
        uniform mat4 projection;

        void main()
        {
            gl_Position = projection * view * model * vec4(position, 1.0);
            fragColor = color;
        }
    )";
    std::string fragmentSource = R"(
        #version 330 core
        in vec3 fragColor;
        out vec4 color;

        void main()
        {
            color = vec4(fragColor, 1.0);
        }
    )";

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    const GLchar *source = (const GLchar *)vertexSource.c_str();
    glShaderSource(vertexShader, 1, &source, 0);
    glCompileShader(vertexShader);

    GLint isCompiled = 0;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
    if(isCompiled == GL_FALSE)
    {
        GLint maxLength = 0;
        glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);
        std::vector<GLchar> infoLog(maxLength);
        glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);
        glDeleteShader(vertexShader);
        return;
    }

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    source = (const GLchar *)fragmentSource.c_str();
    glShaderSource(fragmentShader, 1, &source, 0);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
    if (isCompiled == GL_FALSE)
    {
        GLint maxLength = 0;
        glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);
        std::vector<GLchar> infoLog(maxLength);
        glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);
        glDeleteShader(fragmentShader);
        glDeleteShader(vertexShader);
        return;
    }

    GLuint program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);
    
    GLint isLinked = 0;
    glGetProgramiv(program, GL_LINK_STATUS, (int *)&isLinked);
    if (isLinked == GL_FALSE)
    {
        GLint maxLength = 0;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);
        std::vector<GLchar> infoLog(maxLength);
        glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);
        glDeleteProgram(program);
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);	
        return;
    }

    glDetachShader(program, vertexShader);
    glDetachShader(program, fragmentShader);

    // ==================

    glUseProgram(program);
    GLuint VAO, VBO, IBO;

    // Set up vertex array
    glCreateVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // Set up vertex buffer
    glCreateBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Position attribute (location 0)
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));

    glGenBuffers(1, &IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glm::mat4 model = glm::toMat4(glm::quat(rotation_vector)) * glm::scale(glm::mat4(1.0f), scale_vector);
    glUniformMatrix4fv(glGetUniformLocation(program, "model"), 1, GL_FALSE, glm::value_ptr(model));

    glm::mat4 projection = camera.getProjectionMatrix();
    glUniformMatrix4fv(glGetUniformLocation(program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

    glm::mat4 view = camera.getViewMatrix();
    glUniformMatrix4fv(glGetUniformLocation(program, "view"), 1, GL_FALSE, glm::value_ptr(view));
    
    glBindVertexArray(VAO);
    glDrawElements(GL_QUADS, 16, GL_UNSIGNED_INT, nullptr);
    glUseProgram(0);
}

void displayFunction() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.2f, 0.2f, 0.2f, 0.8f);
    renderChessBoard();
}

void initImGui(GLFWwindow *window)
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();

    if (!ImGui_ImplOpenGL3_Init("#version 410")) {
        std::cerr << "ImGui OpenGL3 Init failed!\n";
        return;
    }

    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable; 

    ImGui_ImplGlfw_InitForOpenGL(window, true);
}

void renderImGui()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ImGui::Begin("Debug Console");
    ImGui::DragFloat3("Object Rotation", glm::value_ptr(rotation_vector), 0.1f, 0.0f, 5.0f);
    ImGui::DragFloat("Zoom out", &zoomOut, 0.1f, 1.0f, 10.0f);
    ImGui::End();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

int main()
{
    GLFWwindow* window;

    if (!glfwInit())
        return -1;

    window = glfwCreateWindow(1500, 1000, "3D Chess Game", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        return -1;
    }

    initialization();
    glfwSetKeyCallback(window, keyFunction);

    initImGui(window);

    

    while (!glfwWindowShouldClose(window))
    {        
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        aspect_ratio = (float)display_w / (float)display_h;

        displayFunction();
        renderImGui();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }


    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}