#include<GL/freeglut.h>
#include<GL/glew.h>

static void RenderSceneCB()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glutSwapBuffers();
}

static void InitializeGlutCallbacks()
{
    glutDisplayFunc(RenderSceneCB);
}


int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA);
    glutInitWindowSize(1024, 768);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Tutorial 01");

    InitializeGlutCallbacks();

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    glutMainLoop();
    
    return 0;
}