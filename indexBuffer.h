#pragma once
#include <GL/glew.h>

class indexBuffer
{
public:
    unsigned int m_buffer;
    unsigned int m_count;
    indexBuffer()
    {}
    indexBuffer(unsigned int* data, unsigned int count) : m_count(count)
    {
        glGenBuffers(1, &m_buffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_buffer);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW);
    }
    ~indexBuffer()
    {
        glDeleteBuffers(1, &m_buffer);
    }
    void operator=(indexBuffer a)
    {
        this->m_buffer = a.m_buffer;
        a.m_buffer = 0;
    }
    void bind() const
    {
        glBindBuffer(1, m_buffer);
    }
    void unbind() const
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
    inline unsigned int getCount() const
    {
        return m_count;
    }
};
