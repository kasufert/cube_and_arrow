#pragma once
#include "buffer.hpp"



Buffer::Buffer()
{
}

Buffer::Buffer(GLenum target, GLsizeiptr size, void* data, GLenum usage, uint count) : target(target), count(count), size(size)
{
    GLCALL(glGenBuffers(1, &id));
    GLCALL(glBindBuffer(target, id));
    GLCALL(glBufferData(target, size, data, usage));
}

void Buffer::bind()
{
    GLCALL(glBindBuffer(target, id));
}

void Buffer::edit(void* newData, GLenum newUsage)
{
    GLCALL(glBindBuffer(target, id));
    GLCALL(glBufferData(target, size, newData, newUsage));
}

void Buffer::unbind()
{
    GLCALL(glBindBuffer(target, 0));
}
