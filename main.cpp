#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <cmath>
#include "shader.h"

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
    
    Shader shader(position, 8, indeces, 3, 2, "vertex.glsl", "fragment.glsl");
    
    glUseProgram(shader.getShader());
    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    glfwTerminate();
    return 0;
}