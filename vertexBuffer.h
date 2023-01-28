#pragma once
#include <GL/glew.h>

class vertexBuffer
{
private:
    unsigned int m_buffer;
public:
    vertexBuffer(void* data, unsigned int size)
    {
        glGenBuffers(1, &m_buffer);
        glBindBuffer(GL_ARRAY_BUFFER, m_buffer);
        glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
    }
    ~vertexBuffer()
    {
        glDeleteBuffers(1, &m_buffer);
    }
    void bind() const
    {
        glBindBuffer(1, m_buffer);
    }
    void unbind() const
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
};
