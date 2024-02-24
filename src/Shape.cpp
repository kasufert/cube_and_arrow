#pragma once
#include "Shape.hpp"



Shape::Shape(const ShapeData& sd)
{
    GLCALL(glGenVertexArrays(1, &vao));
    GLCALL(glBindVertexArray(vao));

    vbo = Buffer(GL_ARRAY_BUFFER, sd.vertsSize(), sd.verts, GL_STATIC_DRAW, sd.numVerts);
    ibo = Buffer(GL_ELEMENT_ARRAY_BUFFER, sd.indsSize(), sd.indices, GL_STATIC_DRAW, sd.numIndices);

    // VBO
    vbo.bind();
    GLCALL(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), 0)); // POSITION
    GLCALL(glEnableVertexAttribArray(0));
    GLCALL(glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (const void*)(3 * sizeof(float)))); // COLOR
    GLCALL(glEnableVertexAttribArray(1));
    GLCALL(glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (const void*)(7 * sizeof(float)))); // TEXCOORDS
    GLCALL(glEnableVertexAttribArray(2));

    // IBO
    ibo.bind();


    // Cleanup
    GLCALL(glBindVertexArray(0));
    GLCALL(glBindBuffer(GL_ARRAY_BUFFER, 0));
    GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));

    transform = Transform();
}

Shape::Shape()
{
}

void Shape::Draw(glm::mat4 worldToProjection, Shader& shader)
{
    GLCALL(glBindVertexArray(vao));
    ibo.bind();
    glm::mat4 mat = worldToProjection * transform.matrix();
    shader.set("uCompleteMatrix", mat);
    GLCALL(glDrawElements(GL_TRIANGLES, ibo.count, GL_UNSIGNED_SHORT, 0));

    // Cleanup
    GLCALL(glBindVertexArray(0));
    ibo.unbind();
}

Shape::Shape(std::function<ShapeData(void)> shapeMaker)
{
    ShapeData sd = shapeMaker();
    *this = Shape(sd);
    sd.cleanup();
}
