#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>
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

int main()
{
    GLFWwindow* window;
    if (!glfwInit())
        return -1;

    window = glfwCreateWindow(640, 480, "Main", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    glewInit();

    std::cout << glGetString(GL_VERSION) << std::endl;
    
    float position[] = {
        -0.5f, -0.5f, 
         0.5f, -0.5f,
         0.5f,  0.5f,
        -0.5f,  0.5f 
    };

    unsigned int indeces [] = {
        0, 1, 2
    };

    unsigned int vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    vertexBuffer vb(position, 4 * 2 * sizeof(float));

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0); 

    indexBuffer ib(indeces, 3);

    unsigned int shader = createShader(loadShader("vertex.glsl"), loadShader("fragment.glsl"));

    unsigned int colorLocation = glGetUniformLocation(shader, "uColor");
    unsigned int scaleLocation = glGetUniformLocation(shader, "scale");
    glUseProgram(shader);

    float r = 0.01f;
    float red = 0.0f;
    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        red+=r;
        glUniform4f(colorLocation, red, 0.4f, 0.5f, 1.0f);
        glUniform1f(scaleLocation, sinf(red));

        ib.bind();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

        if (red > 1.0f)
            r = -0.01f;
        else if (red < 0.0f)
            r = 0.01f;

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    glfwTerminate();
    return 0;
}