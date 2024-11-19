cmake_minimum_required(VERSION 3.28)
project(chess)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

# Set C++ standard version
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 17)
endif()

if(NOT CMAKE_CXX_STANDARD MATCHES "^(17|20)$")
	message(FATAL_ERROR "CMAKE_CXX_STANDARD must be set to 17 or 20")
endif()

# Prevent unnecessary re-linking on Linux 
if(NOT DEFINED CMAKE_LINK_DEPENDS_NO_SHARED AND UNIX AND NOT APPLE)
	set(CMAKE_LINK_DEPENDS_NO_SHARED ON)
endif()

# Add executable files
add_executable(${PROJECT_NAME}
    src/EntryPoint.cpp
    src/Core/Debug/Logging.cpp
    src/Core/Debug/ImGuiLayer.cpp
    src/Core/Window/Window.cpp
    src/Core/Render/Model.cpp
    src/Core/Render/Renderer.cpp
    src/Core/Render/RendererAPI.cpp
    src/Core/Render/Camera.cpp
    src/Core/Render/Shader.cpp
    src/Core/Game/Game.cpp
    src/Backends/OpenGL/OpenGLRenderer.cpp
    src/Backends/OpenGL/OpenGLShader.cpp

    vendor/glad/src/glad.c
    vendor/imgui/imgui.cpp
    vendor/imgui/imgui_demo.cpp
	vendor/imgui/imgui_draw.cpp
	vendor/imgui/imgui_tables.cpp
	vendor/imgui/imgui_widgets.cpp
    vendor/imgui/backends/imgui_impl_opengl3.cpp
    vendor/imgui/backends/imgui_impl_glfw.cpp
)

# Add included directories
include_directories(${PROJECT_NAME}
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    vendor/glad/include
    vendor/imgui
    vendor/imgui/backends
    vendor/spdlog/include
    libs/glfw-build/install/include
	libs/glm-build/install/include
)

# Set policy to modern GLVND and find OpenGL
if (POLICY CMP0072)
    cmake_policy(SET CMP0072 NEW)
endif()

# Set prefix cmake path
list(APPEND CMAKE_PREFIX_PATH libs/glfw-build/install/lib/cmake/glfw3)
list(APPEND CMAKE_PREFIX_PATH libs/glm-build/install/share/glm)

# Find the required packages
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(glm CONFIG REQUIRED)

# Link the libraries to the target
target_link_libraries(${PROJECT_NAME} glfw glm::glm ${OPENGL_LIBRARIES})