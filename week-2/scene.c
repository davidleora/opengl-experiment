#include <GL/glut.h>

void drawFloor()
{
    glColor3f(0.2f, 0.8f, 0.2f);
    glBegin(GL_QUADS);
    glVertex3f(-10.0f, 0.0f, -10.0f);
    glVertex3f(-10.0f, 0.0f, 10.0f);
    glVertex3f(10.0f, 0.0f, 10.0f);
    glVertex3f(10.0f, 0.0f, -10.0f);
    glEnd();
}

void drawHouse()
{
    glTranslatef(0.0f, 0.0f, 0.0f);

    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glVertex3f(-1.0f, 0.0f, -1.0f);
    glVertex3f(-1.0f, 2.0f, -1.0f);
    glVertex3f(1.0f, 2.0f, -1.0f);
    glVertex3f(1.0f, 0.0f, -1.0f);
    glEnd();

    glBegin(GL_QUADS);
    glVertex3f(-1.0f, 0.0f, 1.0f);
    glVertex3f(-1.0f, 2.0f, 1.0f);
    glVertex3f(1.0f, 2.0f, 1.0f);
    glVertex3f(1.0f, 0.0f, 1.0f);
    glEnd();

    glBegin(GL_QUADS);
    glVertex3f(-1.0f, 0.0f, -1.0f);
    glVertex3f(-1.0f, 0.0f, 1.0f);
    glVertex3f(1.0f, 0.0f, 1.0f);
    glVertex3f(1.0f, 0.0f, -1.0f);
    glEnd();

    glBegin(GL_QUADS);
    glVertex3f(-1.0f, 2.0f, -1.0f);
    glVertex3f(-1.0f, 2.0f, 1.0f);
    glVertex3f(1.0f, 2.0f, 1.0f);
    glVertex3f(1.0f, 2.0f, -1.0f);
    glEnd();

    glBegin(GL_QUADS);
    glVertex3f(-1.0f, 0.0f, -1.0f);
    glVertex3f(-1.0f, 2.0f, -1.0f);
    glVertex3f(-1.0f, 2.0f, 1.0f);
    glVertex3f(-1.0f, 0.0f, 1.0f);
    glEnd();

    glBegin(GL_QUADS);
    glVertex3f(1.0f, 0.0f, -1.0f);
    glVertex3f(1.0f, 2.0f, -1.0f);
    glVertex3f(1.0f, 2.0f, 1.0f);
    glVertex3f(1.0f, 0.0f, 1.0f);
    glEnd();
}
