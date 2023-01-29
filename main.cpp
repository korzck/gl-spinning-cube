#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <cmath>
#include "shader.h"

float transform[4][4];

void rotate(float a, float b, float c)
{
    a = a * M_PI / 180;
    b = b * M_PI / 180;
    c = c * M_PI / 180;
    transform[0][0] =  cosf(a)*cosf(b);
    transform[1][0] =  sinf(a)*cosf(b);
    transform[2][0] = -sinf(b); 

    transform[0][1] = cosf(a)*sinf(b)*sinf(c)-sinf(a)*cosf(c);
    transform[1][1] = sinf(a)*sinf(b)*sinf(c)+cosf(a)*cosf(c);
    transform[2][1] = cosf(b)*sinf(c);

    transform[0][2] = cosf(a)*sinf(b)*cosf(c)+sinf(a)*sinf(c);
    transform[1][2] = sinf(a)*sinf(b)*cosf(c)-cosf(a)*sinf(c);
    transform[2][2] = cosf(b)*cosf(c);

    transform[3][0] = 0.0f; transform[0][3] = 0.0f; 
    transform[3][1] = 0.0f; transform[1][3] = 0.0f;
    transform[3][2] = 0.0f; transform[2][3] = 0.0f;
                            transform[3][3] = 1.0f;
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
        -0.5f, -0.5f,  0.5f, 
         0.5f, -0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
        -0.5f, -0.5f, -0.5f, 
         0.5f, -0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
        -0.5f,  0.5f, -0.5f,
    };

    float semiaxes[] {
        -0.5f, -0.5f,  0.0f, 
         0.5f, -0.5f,  0.0f,
         0.5f,  0.5f,  0.0f,
        -0.5f,  0.5f,  0.0f,
    };

    unsigned int indeces [] = {
        0, 1, 2, 
        2, 3, 0,

        4, 5, 6,
        6, 7, 4,

        0, 4, 7,
        7, 3, 0,

        1, 5, 6,
        6, 2, 1,

        2, 3, 7,
        7, 6, 2,

        0, 1, 5,
        5, 4, 0
        
    };
    
    Shader shader(position, 24, indeces, 36, 3, "vertex.glsl", "fragment.glsl");
    
    
    
    
    glUseProgram(shader.getShader());    
    


    unsigned int transformLocation = glGetUniformLocation(shader.getShader(), "transform");
    // unsigned int transformLocation2 = glGetUniformLocation(shader2.getShader(), "transform");
    float param = 0.0f;
    float inc = 1.0f;
    while (!glfwWindowShouldClose(window))
    {
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        param += inc;
        rotate(0, param, 30);
        glUniformMatrix4fv(transformLocation, 1, GL_TRUE, &transform[0][0]);
        // glUniformMatrix4fv(transformLocation2, 1, GL_TRUE, &transform[0][0]);

        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    glfwTerminate();
    return 0;
}