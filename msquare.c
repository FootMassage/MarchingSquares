#include <GL/freeglut.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

#define WIDTH 640
#define HEIGHT 480

// float field[][];
struct vector
{
    float x;
    float y;
};
void init()
{
    glClearColor(0, 0, 0, 0);
}
float map(float i, int res, char type)
{

    return type == 'w' ? ((2 * i) / ((WIDTH / res))) - 1 : ((2 * i) / ((HEIGHT / res))) - 1;
}
float mapFull(float i, int res, char type)
{

    return type == 'w' ? ((2 * i) / ((WIDTH))) - 1 : ((2 * i) / ((HEIGHT))) - 1;
}

int getState(int a, int b, int c, int d)
{
    return a * 8 + b * 4 + c * 2 + d;
}
void drawFromVector(struct vector a, struct vector b)
{
    glColor3f(1, 1, 1);
    glBegin(GL_LINES);
    glVertex2f(a.x, a.y);
    glVertex2f(b.x, b.y);
    glEnd();
}
void drawLines(int state, struct vector a, struct vector b, struct vector c, struct vector d)
{
    switch (state)
    {
    case 1:
        drawFromVector(c, d);
        break;
    case 2:
        drawFromVector(c, b);
        break;
    case 3:
        drawFromVector(d, b);
        break;
    case 4:
        drawFromVector(a, b);
        break;
    case 5:
        drawFromVector(a, b);
        drawFromVector(d, c);
        break;
    case 6:
        drawFromVector(a, c);
        break;
    case 7:
        drawFromVector(a, d);
        break;
    case 8:
        drawFromVector(a, d);
        break;
    case 9:
        drawFromVector(a, c);
        break;
    case 10:
        drawFromVector(a, d);
        drawFromVector(b, c);
        break;
    case 11:
        drawFromVector(a, b);
        break;
    case 12:
        drawFromVector(d, b);
        break;
    case 13:
        drawFromVector(b, c);
        break;
    case 14:
        drawFromVector(d, c);
        break;
    default:
        break;
    }
}

void draw()
{
    int res = 10;
    int cols = (WIDTH / res) + 1;
    int rows = (HEIGHT / res) + 1;
    float field[cols][rows];

    struct vector a, b, c, d;

    for (int i = 0; i < cols; i++)
    {
        for (int j = 0; j < rows; j++)
        {
            field[i][j] = rand() % 2;
        }
    }

    glPolygonMode(GL_FRONT, GL_FILL);
    glPointSize(2);
    for (int i = 0; i < cols; i++)
    {
        for (int j = 0; j < rows; j++)
        {

            if (field[i][j] == 1)
            {
                glColor3f(0, 1, 0);
            }
            else
            {
                glColor3f(1.0, 0, 0.5);
            }
            float mapdi = map((float)i, res, 'w');
            float mapdj = map((float)j, res, 'h');
            glBegin(GL_POINTS);
            glVertex2f(mapdi, mapdj);
            glEnd();

            float x = i * res;
            float y = j * res;
            a.x = mapFull(x + (res / 2), res, 'w');
            a.y = mapdj;
            b.x = mapFull(x + res, res, 'w');
            b.y = mapFull(y + ((float)res / 2), res, 'h');
            c.x = mapFull(x + ((float)res / 2), res, 'w');
            c.y = mapFull(y + res, res, 'h');
            d.x = mapdi;
            d.y = mapFull(y + ((float)res / 2), res, 'h');

            // testing lines
            int state = getState((int)field[i][j], (int)field[i + 1][j], (int)field[i + 1][j + 1], (int)field[i][j + 1]);
            drawLines(state, a, b, c, d);
        }
    }
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    draw();

    glutSwapBuffers();
}
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH) - WIDTH) / 2, (glutGet(GLUT_SCREEN_HEIGHT) - HEIGHT) / 2);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutCreateWindow("Marching Squares");

    init();
    glutDisplayFunc(display);

    glutMainLoop();
}