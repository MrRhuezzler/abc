#include <bits/stdc++.h>
#include <windows.h>
#include <GL/glut.h>
#include <stdlib.h>

int MOUSE_X = 0;
int MOUSE_Y = 0;

static void resize(int width, int height)
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, width, 0, height);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity() ;
}

static void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3d(1,0,0);
    glFlush();
}

static void key(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 27 :
        case 'q':
            exit(0);
            break;
    }

    glutPostRedisplay();
}

static void handleMouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {

    }
    else if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
    {

    }
}

static void handleMouseMove(int x, int y) {
    MOUSE_X = x;
    MOUSE_Y = y;
}

static void idle(void)
{
    glutPostRedisplay();
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGBA | GLUT_SINGLE);

    glutCreateWindow("STARTER");

    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutKeyboardFunc(key);
    glutMouseFunc(handleMouse);
    glutMotionFunc(handleMouseMove);
    glutPassiveMotionFunc(handleMouseMove);
    glutIdleFunc(idle);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glClearColor(0, 0, 0, 1);
    glutMainLoop();

    return EXIT_SUCCESS;
}
