#include "Core/Render/Model.h"
#include "Core/Render/Renderer.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <cstring>
#include <cstdlib>
#include <iostream>

namespace Utils
{
    std::vector<std::string> Split(std::string &str, char delimiter)
    {
        std::vector<std::string> split;
        int prev = -1; int i = 0;
        
        for (i = 0; i < str.size(); i++)
        {
            if (str[i] == delimiter)
            {
                split.push_back(str.substr(prev + 1, i - prev - 1));
                prev = i;
            }
        }
        if(i == str.size() && prev != i - 1) 
            split.push_back(str.substr(prev + 1));

        return split;
    }
}

Model::Model(const std::string &filepath)
{
    RegisterMesh(filepath);
}

void Model::Init()
{
    VA = VertexArray::Create();
    VB = VertexBuffer::Create(vertices.data(), vertices.size() * sizeof(float));
    VB->SetLayout({
        { ShaderDataType::Float3, "a_position", false },
        { ShaderDataType::Float2, "a_texture",  false },
        { ShaderDataType::Float3, "a_normals",  false },
    });
    VA->AddVertexBuffer(VB);
}

Model::~Model()
{
    vertices.clear();
}

void Model::Render()
{
    Renderer::Draw(VA, false, vertices.size() / 8);
}

void Model::RegisterMesh(const std::string &filepath)
{
    std::vector<float> pos;
    std::vector<float> norm;
    std::vector<float> tex;

    std::ifstream fin;
	std::string input;
    std::vector<std::string> split;

    fin.open(filepath);
    if (fin)
    {
        while(getline(fin, input))
        {
            split = Utils::Split(input, ' ');
            if (split.size() == 0) continue;

            if (split[0] == "v")
            {
                pos.push_back(GetFloat(split[1]));
                pos.push_back(GetFloat(split[2]));
                pos.push_back(GetFloat(split[3]));
            }
            else if (split[0] == "vt")
            {
                tex.push_back(GetFloat(split[1]));
                tex.push_back(GetFloat(split[2]));
            }
            else if (split[0] == "vn")
            {
                norm.push_back(GetFloat(split[1]));
                norm.push_back(GetFloat(split[2]));
                norm.push_back(GetFloat(split[3]));
            }
            else if (split[0] == "f")
            {
                std::vector<std::string> faces; int index;
                for (int i = 1; i <= 3; i++)
                {
                    faces = Utils::Split(split[i], '/');

                    index = 3 * (GetInt(faces[0]) - 1);
                    vertices.push_back(pos[index]);
                    vertices.push_back(pos[index + 1]);                   
                    vertices.push_back(pos[index + 2]);

                    index = 2 * (GetInt(faces[1]) - 1);
                    vertices.push_back(tex[index]);
                    vertices.push_back(tex[index + 1]);

                    index = 3 * (GetInt(faces[2]) - 1);
                    vertices.push_back(norm[index]);
                    vertices.push_back(norm[index + 1]);
                    vertices.push_back(norm[index + 2]);
                }
            }
        }
    }
}


float Model::GetFloat(std::string input)
{
    std::istringstream ssinput(input);
	float check;

	ssinput >> check;
	return check;
}

int Model::GetInt(std::string input)
{
    std::istringstream ssinput(input);
	int check;

	ssinput >> check;
	return check;
}