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

Buffer::Buffer(Buffer&& other)
{
    id = other.id;
    target = other.target;
    size = other.size;
    count = other.count;
    other.id = 0;
}

Buffer& Buffer::operator=(Buffer&& other)
{
    id = other.id;
    target = other.target;
    size = other.size;
    count = other.count;
    other.id = 0;
    return *this;
}

Buffer::~Buffer()
{
    if (id != 0)
    {
        GLCALL(glDeleteBuffers(1, &id));
    }
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
