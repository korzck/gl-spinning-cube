#include <GL/glew.h>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include "vertexBuffer.h"
#include "indexBuffer.h"

static std::string loadShader(const std::string& file)
{
    std::ifstream stream(file);
    std::stringstream shader;
    shader << stream.rdbuf();
    return shader.str();
}

static unsigned int compileShader(const std::string& source, unsigned int type)
{
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE)
    {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)alloca(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);
        std::cout << "failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << std::endl;
        std::cout << message << std::endl;
        glDeleteShader(id);
        return 0;
    }

    return id;
}

static unsigned int createShader(const std::string& vertexShader, const std::string& fragmentShader)
{
    unsigned int program = glCreateProgram();
    unsigned int vs = compileShader(vertexShader, GL_VERTEX_SHADER);
    unsigned int fs = compileShader(fragmentShader, GL_FRAGMENT_SHADER);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);
    
    glDeleteShader(vs);
    glDeleteShader(fs);
    
    return program;
}


class Shader
{
private:
    unsigned int m_shader;
public:
    unsigned int indecesCount;
    indexBuffer m_ib;
    vertexBuffer m_vb;
    Shader(float* points, unsigned int pointsCount, unsigned int* indeces, unsigned int indecesCount, unsigned int coordsSpan, std::string vertexShaderFile, std::string fragmentShaderFile) : indecesCount(indecesCount)
    {
        m_vb = vertexBuffer(points, pointsCount * sizeof(float));

        glVertexAttribPointer(0, coordsSpan, GL_FLOAT, GL_FALSE, sizeof(float) * coordsSpan, 0); 
        glEnableVertexAttribArray(0);

        m_ib = indexBuffer(indeces, indecesCount);

        m_shader = createShader(loadShader(vertexShaderFile), loadShader(fragmentShaderFile));
    }
    ~Shader()
    {
        glDeleteProgram(m_shader);
    }
    unsigned int getShader()
    {
        return m_shader;
    }
};