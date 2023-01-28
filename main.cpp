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
        0, 3, 2
    };
    float n = 0;
    float moving[4][4];
    moving[0][0] = 1.0f; moving[0][1] = 0.0f; moving[0][2] = 0.0f; moving[0][3] = n;
    moving[1][0] = 0.0f; moving[1][1] = 1.0f; moving[1][2] = 0.0f; moving[1][3] = 0.0f;
    moving[2][0] = 0.0f; moving[2][1] = 0.0f; moving[2][2] = 1.0f; moving[2][3] = 0.0f;
    moving[3][0] = 0.0f; moving[3][1] = 0.0f; moving[3][2] = 0.0f; moving[3][3] = 1.0f;
    

    vertexBuffer vb(position, 4 * 2 * sizeof(float));

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0); 

    indexBuffer ib(indeces, 3);

    unsigned int shader = createShader(loadShader("vertex.glsl"), loadShader("fragment.glsl"));

    unsigned int colorLocation = glGetUniformLocation(shader, "uColor");
    unsigned int scaleLocation = glGetUniformLocation(shader, "scale");
    unsigned int movingLocation = glGetUniformLocation(shader, "moving");
    glUseProgram(shader);
    glUniform4f(colorLocation, 0.5f, 0.5f, 0.5f, 1.0f);

    float increment = 0.01f;
    float param = 0.0f;
    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        n = sinf(param) - 0.5f;
        // moving[0][3] = n;
        glUniformMatrix4fv(movingLocation, 1, GL_TRUE, &moving[0][0]);
        glUniform1f(scaleLocation, 4 * fabs(n));
        
        

        ib.bind();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
        param += increment;
        if (param > 1.0f)
            increment = -0.01f;
        else if (param < 0.0f)
            increment = 0.01f;
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    glfwTerminate();
    return 0;
}