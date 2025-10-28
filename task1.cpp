
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include<stdio.h>
#include<math.h>

int x1_cor, y1_cor, x2_cor, y2_cor;
int lineWidth = 1;


void plotPixel(int x, int y)
{
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}



void bresenhamLine(int x1, int y1, int x2, int y2)
{
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);



    int sx = -1;
    if( x2 > x1){
        sx = 1;
    }
    int sy = -1;
    if( y2 > y1){
        sy = 1;
    }

    int err = dx - dy;

    while (1)
    {
        plotPixel(x1, y1);

        if (x1 == x2 && y1 == y2)
            break;

        int e2 = 2 * err;

        if (e2 > -dy)
        {
            err -= dy;
            x1 += sx;
        }

        if (e2 < dx)
        {
            err += dx;
            y1 += sy;
        }
    }
}


void bresenhamThickLine(int x1, int y1, int x2, int y2, int width)
{

    float dx = x2 - x1;
    float dy = y2 - y1;
    float len = sqrt(dx * dx + dy * dy);


    float offsetX = -(dy / len);
    float offsetY = (dx / len);



    int halfWidth = width / 2;

    for (int i = -halfWidth; i <= halfWidth; i++)
    {
        int x1_off = x1 + round(i * offsetX);
        int y1_off = y1 + round(i * offsetY);
        int x2_off = x2 + round(i * offsetX);
        int y2_off = y2 + round(i * offsetY);

        bresenhamLine(x1_off, y1_off, x2_off, y2_off);
    }
}


void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1.0, 1.0, 1.0);
    if (lineWidth <= 1)
        bresenhamLine(x1_cor, y1_cor, x2_cor, y2_cor);
    else
        bresenhamThickLine(x1_cor, y1_cor, x2_cor, y2_cor, lineWidth);

    glFlush();
}


void init(void)
{
    glClearColor(0.0, 0.0, 0.0, 0.0); // Black background
    glColor3f(1.0, 1.0, 1.0);         // White drawing color
    gluOrtho2D(0, 500, 0, 500);       // 2D coordinate system
}


int main(int argc, char **argv)
{
    printf("Enter x1, y1, x2, y2: ");
    scanf("%d %d %d %d", &x1_cor, &y1_cor, &x2_cor, &y2_cor);

    printf("Enter line width (1 for standard): ");
    scanf("%d", &lineWidth);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Bresenham's Line Drawing Algorithm");
    init();
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}
