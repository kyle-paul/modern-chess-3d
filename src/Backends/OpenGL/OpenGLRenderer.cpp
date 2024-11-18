#include "Backends/OpenGL/OpenGLRenderer.h"
#include "Core/Debug/Logging.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

void OpenGLRenderer::Init()
{
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        ERROR("Could not initialize GLAD as OpenGL API!");
        exit(-1);
    }

    glEnable(GL_BLEND);
    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CW);
    glCullFace(GL_BACK);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_DEPTH_TEST);
}