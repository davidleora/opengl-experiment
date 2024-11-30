#include <GL/glut.h>
#include <stdbool.h>
#include <stdio.h>

extern void drawFloor();
extern void drawHouse();

bool keyStates[256] = {false};
float cameraX = 0.0f;
float cameraZ = 0.0f;

void renderText(float x, float y, const char *text)
{
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0.0, 800.0, 0.0, 800.0);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glRasterPos2f(x, y);
    for (const char *c = text; *c != '\0'; c++)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
    }

    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
}

void init()
{
    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
    glEnable(GL_DEPTH_TEST);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(45.0, 1.0, 1.0, 100.0);

    glMatrixMode(GL_MODELVIEW);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();

    glTranslatef(cameraX, 0.0f, cameraZ);

    drawHouse();
    drawFloor();

    char cameraInfo[128];
    snprintf(cameraInfo, sizeof(cameraInfo), "Camera Position: (%.2f, %.2f)", cameraX, cameraZ);
    renderText(10, 770, cameraInfo);

    glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y)
{
    keyStates[key] = true;
}

void keyboardUp(unsigned char key, int x, int y)
{
    keyStates[key] = false;
}

void update()
{
    const float step = 0.05f;
    if (keyStates['a'])
        cameraX += step;
    if (keyStates['d'])
        cameraX -= step;
    if (keyStates['w'])
        cameraZ += step;
    if (keyStates['s'])
        cameraZ -= step;
    glutPostRedisplay();
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

    glutInitWindowPosition(100, 100);
    glutInitWindowSize(800, 800);

    glutCreateWindow("3D Scene with House and Floor");

    init();

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutKeyboardUpFunc(keyboardUp);
    glutIdleFunc(update);
    glutMainLoop();

    return 0;
}
