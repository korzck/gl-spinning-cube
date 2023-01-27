#include <GL/glew.h>
#include<GL/gl.h>
#include <GLFW/glfw3.h>
#include <iostream>

static unsigned int compileShader(const std::string& source, unsigned int type)
{
    unsigned int id = glCreateShader(GL_ARRAY_BUFFER);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);
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

    glewInit();

    window = glfwCreateWindow(640, 480, "Main", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    glewInit();

    float pos[6] = {
        -0.5f, -0.5f, 0.0f, 0.5f, 0.5f, -0.5f 
    };

    unsigned int buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, 6*sizeof(float), pos, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float)*2, 0); 
    glEnableVertexArrayAttrib(0, 0);

    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}