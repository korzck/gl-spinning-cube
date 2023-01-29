#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <cmath>
#include "shader.h"

void rotate(float a, float b, float c, float (&matrix3fv)[4][4])
{
    a = a * M_PI / 180;
    b = b * M_PI / 180;
    c = c * M_PI / 180;
    matrix3fv[0][0] =  cosf(b)*cosf(c);
    matrix3fv[1][0] =  sinf(b)*cosf(c);
    matrix3fv[2][0] = -sinf(b); 

    matrix3fv[0][1] = sinf(a)*sinf(b)*cosf(c)-cosf(a)*sinf(c);
    matrix3fv[1][1] = sinf(a)*sinf(b)*sinf(c)+cosf(a)*cosf(c);
    matrix3fv[2][1] = sinf(a)*cosf(b);

    matrix3fv[0][2] = cosf(a)*sinf(b)*cosf(c)+sinf(a)*sinf(c);
    matrix3fv[1][2] = cosf(a)*sinf(b)*sinf(c)-sinf(a)*cosf(c);
    matrix3fv[2][2] = cosf(a)*cosf(b);

    matrix3fv[3][0] = 0.0f; matrix3fv[0][3] = 0.0f; 
    matrix3fv[3][1] = 0.0f; matrix3fv[1][3] = 0.0f;
    matrix3fv[3][2] = 0.0f; matrix3fv[2][3] = 0.0f;
                            matrix3fv[3][3] = 1.0f;
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

    unsigned int indeces [] = {
        0, 1, 2, 2, 3, 0
    };
    
    float rot[4][4];
    for(int i =0; i < 4; i++)
    {    
        for(int j =0; j < 4; j++)
        {
            std::cout << rot[i][j] << " ";
        }
        std::cout << '\n';
    }
    Shader shader(position, 24, indeces, 6, 3, "vertex.glsl", "fragment.glsl");
    unsigned int transformLocation = glGetUniformLocation(shader.getShader(), "transform");
    glUseProgram(shader.getShader());
    float param = 0.0f;
    float inc = 1.0f;
    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        param += inc;
        rotate(param, 0, 0, rot);
        glUniformMatrix4fv(transformLocation, 1, GL_TRUE, &rot[0][0]);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    glfwTerminate();
    return 0;
}