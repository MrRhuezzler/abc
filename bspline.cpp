// #include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <windows.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <cmath>

int MOUSE_X = 0;
int MOUSE_Y = 0;

static void resize(int width, int height)
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, width, height, 0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int STATE = 0; // 1 => Movement, 0 => Stop

float radiusOfHighlight = 25.0f;
int highlighted = -1;
int k = 3; // Order of B Spline
std::vector<float> knots;
std::vector<std::pair<float, float>> controlPoints = {

};

double uinc = 0.001;

int delta(double u)
{
    int m = controlPoints.size();
    for (int i = 0; i <= m + k - 1; i++)
    {
        if (u >= knots[i] && u < knots[i + 1])
            return i;
    }
    return -1;
}

std::pair<float, float> bspline(double u, int d)
{

    std::pair<float, float> *c = new std::pair<float,
                                               float>[controlPoints.size()];
    for (int i = 0; i <= k - 1; i++)
    {
        c[i] = controlPoints[d - i];
    }

    for (int r = k; r >= 2; r--)
    {
        int i = d;
        for (int s = 0; s <= r - 2; s++)
        {
            double u_i = knots[i];
            double u_ir1 = knots[i + r - 1];
            double omega = (u - u_i) / (u_ir1 - u_i);
            c[s].first = omega * c[s].first + (1 - omega) * c[s + 1].first;
            c[s].second = omega * c[s].second + (1 - omega) * c[s + 1].second;
            i--;
        }
    }

    std::pair<float, float> result = c[0];
    delete[] c;
    return result;
}

void generateKnots()
{
    knots.clear();

    for (int i = 0; i < k; i++)
        knots.push_back(0);

    int middle = controlPoints.size() - k;
    for (int i = 0; i < middle; i++)
        knots.push_back(double(i + 1) / (middle + 1));

    for (int i = 0; i < k; i++)
        knots.push_back(1);
}

static void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3d(1, 0, 0);

    generateKnots();

    glBegin(GL_LINE_STRIP);
    glColor3f(1.0f, 1.0f, 1.0f);
    for (double u = knots[k - 1] + uinc; u <=
                                         knots[controlPoints.size()];
         u += uinc)
    {
        int d = delta(u);
        if (controlPoints.size() >= d)
        {
            std::pair<float, float> point = bspline(u, d);
            glVertex2f(point.first, point.second);
        }
    }
    glEnd();

    glPushAttrib(GL_POINT_SIZE);
    glPointSize(5);
    glBegin(GL_POINTS);
    for (int i = 0; i < controlPoints.size(); i++)
    {
        auto p = controlPoints[i];
        if (highlighted == i)
            glColor3f(1.0f, 1.0f, 0.0f);
        else
            glColor3f(1.0f, 0.0f, 0.0f);
        glVertex2f(p.first, p.second);
    }
    glEnd();
    glPopAttrib();

    glFlush();
}

static void key(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 27:
    case 'q':
        exit(0);
        break;
    case 'd':
        if (highlighted == -1)
            break;
        controlPoints.erase(controlPoints.begin() + highlighted);
        break;
    }

    glutPostRedisplay();
}

static void handleMouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        if (highlighted == -1)
            return;
        if (STATE == 1)
            STATE = 0;
        else
            STATE = 1;
    }
    else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
    {
        controlPoints.push_back(std::make_pair<float, float>(MOUSE_X, MOUSE_Y));
    }
}

static float sqauredDistanceBetween(std::pair<float, float> p1,
                                    std::pair<float, float> p2)
{
    return pow(p1.first - p2.first, 2.0f) + pow(p1.second - p2.second, 2.0f);
}

static void handleMouseMove(int x, int y)
{
    MOUSE_X = x;
    MOUSE_Y = y;

    if (STATE == 0)
    {
        highlighted = -1;
        for (int i = 0; i < controlPoints.size(); i++)
        {
            if (sqauredDistanceBetween(controlPoints[i],
                                       std::make_pair(MOUSE_X, MOUSE_Y)) < radiusOfHighlight)
            {
                highlighted = i;
            }
        }
    }

    if (highlighted == -1)
        return;
    if (STATE == 1)
    {
        controlPoints[highlighted].first = MOUSE_X;
        controlPoints[highlighted].second = MOUSE_Y;
    }
}

static void idle(void)
{
    glutPostRedisplay();
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(10, 10);
    glutInitDisplayMode(GLUT_RGBA | GLUT_SINGLE);

    glutCreateWindow("B Spline");

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
