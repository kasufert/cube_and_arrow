#pragma once
#include "header.hpp"

struct ShapeData
{
    Vertex* verts = NULL;
    GLuint numVerts = 0;
    GLsizeiptr vertsSize() const {
        return numVerts * sizeof(Vertex);
    }
    GLushort* indices = NULL;
    GLuint numIndices = 0;
    GLsizeiptr indsSize() const {
        return numIndices * sizeof(GLushort);
    }

    inline void cleanup() {
        delete[] verts;
        delete[] indices;
        fmt::print("Heap free'd vertex and index array\n");
    }

    inline void setVerts(Vertex* data, size_t sze) {
        numVerts = sze / sizeof(Vertex);
        verts = new Vertex[numVerts];
        memcpy_s(verts, sze, data, sze);
    }

    inline void setInds(GLushort* data, size_t sze) {
        numIndices = sze / sizeof(GLushort);
        indices = new GLushort[numIndices];
        memcpy_s(indices, sze, data, sze);
    }
};