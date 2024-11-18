#pragma once
#include <string>
#include <vector>

class Model
{
public:
    Model(const std::string &filepath);
    ~Model();

    void Render();
    const std::vector<float>& GetVertices() const { return vertices; }

private:
    float GetFloat(std::string input);
    int GetInt(std::string input);

private:
    void RegisterMesh(const std::string &filepath);
    std::vector<float> vertices;
    int vertSize;
};