#include <GL/glut.h>
#include <stdio.h>

#define MAX_LINES 50


typedef struct {
    float x1, y1, x2, y2;
} Line;

Line lines[MAX_LINES];
int numLines;
float xmin, ymin, xmax, ymax;

// Liang–Barsky
int liangBarskyClip(float x1, float y1, float x2, float y2,
                    float *cx1, float *cy1, float *cx2, float *cy2)
{
    float dx = x2 - x1;
    float dy = y2 - y1;
    float p[4], q[4];
    float u1 = 0.0, u2 = 1.0;

    p[0] = -dx; q[0] = x1 - xmin;
    p[1] = dx;  q[1] = xmax - x1;
    p[2] = -dy; q[2] = y1 - ymin;
    p[3] = dy;  q[3] = ymax - y1;

    for (int i = 0; i < 4; i++) {
        if (p[i] == 0) {
            if (q[i] < 0)
                return 0; // Line is parallel and outside
        } else {
            float r = q[i] / p[i];
            if (p[i] < 0) {
                if (r > u2)
                    return 0;
                else if (r > u1)
                    u1 = r;
            } else if (p[i] > 0) {
                if (r < u1)
                    return 0;
                else if (r < u2)
                    u2 = r;
            }
        }
    }

    *cx1 = x1 + u1 * dx;
    *cy1 = y1 + u1 * dy;
    *cx2 = x1 + u2 * dx;
    *cy2 = y1 + u2 * dy;
    return 1;
}

void drawRectangle(float xmin, float ymin, float xmax, float ymax)
{
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_LINE_LOOP);
        glVertex2f(xmin, ymin);
        glVertex2f(xmax, ymin);
        glVertex2f(xmax, ymax);
        glVertex2f(xmin, ymax);
    glEnd();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    drawRectangle(xmin, ymin, xmax, ymax);


    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_LINES);
    for (int i = 0; i < numLines; i++) {
        glVertex2f(lines[i].x1, lines[i].y1);
        glVertex2f(lines[i].x2, lines[i].y2);
    }
    glEnd();


    glColor3f(0.0, 1.0, 0.0);
    glBegin(GL_LINES);
    for (int i = 0; i < numLines; i++) {
        float cx1, cy1, cx2, cy2;
        if (liangBarskyClip(lines[i].x1, lines[i].y1, lines[i].x2, lines[i].y2,
                            &cx1, &cy1, &cx2, &cy2)) {
            glVertex2f(cx1, cy1);
            glVertex2f(cx2, cy2);
        }
    }
    glEnd();

    glFlush();
}

void init()
{
    glClearColor(0.1, 0.1, 0.1, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
}

int main(int argc, char **argv)
{
    printf("Enter clipping window (xmin ymin xmax ymax): ");
    scanf("%f %f %f %f", &xmin, &ymin, &xmax, &ymax);

    printf("Enter number of line segments (max %d): ", MAX_LINES);
    scanf("%d", &numLines);

    for (int i = 0; i < numLines; i++) {
        printf("Enter x1 y1 x2 y2 for line %d: ", i + 1);
        scanf("%f %f %f %f", &lines[i].x1, &lines[i].y1, &lines[i].x2, &lines[i].y2);
    }

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Liang-Barsky Line Clipping (User Input)");

    init();
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}


//Enter clipping window (xmin ymin xmax ymax): -0.5 -0.5 0.5 0.5
//Enter number of line segments (max 50): 3
//Enter x1 y1 x2 y2 for line 1: -0.8 -0.8 0.8 0.8
//Enter x1 y1 x2 y2 for line 2: -0.7 0.2 0.9 0.2
//Enter x1 y1 x2 y2 for line 3: -0.3 -0.3 0.3 0.3
