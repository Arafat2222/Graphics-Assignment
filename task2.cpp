#include <GL/glut.h>
#include <math.h>
#include <stdio.h>

#define PI 3.1415926535898


void drawCircle(float cx, float cy, float radius, float thickness, float r, float g, float b)
{
    int segments = 360;
    float angle;

    glLineWidth(thickness);  // Set thickness
    glColor3f(r, g, b);      // Set color

    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < segments; i++)
    {
        angle = 2 * PI * i / segments;
        float x = cx + cos(angle) * radius;
        float y = cy + sin(angle) * radius;
        glVertex2f(x, y);
    }
    glEnd();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    float cx = 0.0f, cy = 0.0f;  // Center of circles
    int numCircles = 18;
    float maxRadius = 0.8f;
    float minRadius = 0.05f;
    float radiusStep = (maxRadius - minRadius) / numCircles;

    float baseThickness = 1.0f;

    for (int i = 0; i < numCircles; i++)
    {
        float radius = minRadius + i * radiusStep;
        float thickness = baseThickness + i * 0.3f;


        float r = (float)i / numCircles;
        float g = 0.2f;
        float b = 1.0f - (float)i / numCircles;

        drawCircle(cx, cy, radius, thickness, r, g, b);
    }

    glFlush();
}

void init()
{
    glClearColor(0.1, 0.1, 0.1, 1.0); // Background color
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0); // Set coordinate system
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Concentric Circles with Color Gradient");

    init();
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}
