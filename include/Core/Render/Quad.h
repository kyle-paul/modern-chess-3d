#pragma once
#include "Core/Render/Shader.h"
#include "Core/Render/VertexArray.h"
#include "Core/Render/Buffer.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>

class Quad
{
public:
    Quad();
    ~Quad();
    void Init();
    void Render(const std::shared_ptr<Shader> &shad, const glm::vec3 &position, const  int &type=-1);

private:
    float vertices [4 * 3] = {
        0.0f, 0.0f, 0.5f,
        0.0f, 1.0f, 0.5f,
        1.0f, 1.0f, 0.5f,
        1.0f, 0.0f, 0.5f,
    };

    std::shared_ptr<VertexArray> QuadVA;
    std::shared_ptr<VertexBuffer> QuadVB;
};