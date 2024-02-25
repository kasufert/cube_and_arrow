#pragma once
#include "header.hpp"
#include <functional>

class Shape
{
    GLuint vao = 0;
    Buffer vbo;
    Buffer ibo;
public:
    Transform transform;
    Texture tex;
    Shape();
    Shape(const ShapeData& sd);
    Shape(std::function<ShapeData(void)> shapeMaker);
    void Draw(glm::mat4 worldToProj, Shader& shader);
};