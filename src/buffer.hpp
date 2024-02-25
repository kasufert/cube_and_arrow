#pragma once
#include "header.hpp"

class Buffer {
public:
    GLuint id = 0;
    GLenum target = 0;
    GLsizeiptr size = 0;
    uint count = 0;
    Buffer();
    Buffer(GLenum target, GLsizeiptr size, void* data, GLenum usage, uint count);
    Buffer(const Buffer& other) = delete;
    Buffer& operator=(const Buffer& other) = delete;
    Buffer(Buffer&& other);
    Buffer& operator=(Buffer&& other);
    ~Buffer();
    void bind();
    void edit(void* newData, GLenum newUsage);
    void unbind();
};