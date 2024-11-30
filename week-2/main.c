#include <GL/glut.h>
#include <stdbool.h>
#include <stdio.h>
#include <math.h>

#include "scene.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 800

float cameraX = 20.5f;
float cameraY = 1.3f;
float cameraZ = 4.5f;
float cameraYaw = 180.0f;
float cameraPitch = 0.0f;

bool keyStates[256] = {false};
float movementSpeed = 0.1f;

void renderText(float x, float y, const char *text)
{
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0.0, WINDOW_WIDTH, 0.0, WINDOW_HEIGHT);

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

    gluPerspective(90.0, (double)WINDOW_WIDTH / (double)WINDOW_HEIGHT, 0.1, 100.0);

    glMatrixMode(GL_MODELVIEW);

    glutSetCursor(GLUT_CURSOR_NONE);
    glutWarpPointer(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
}

void keyboard(unsigned char key, int x, int y)
{
    if (key == 27)
        exit(0);
    keyStates[key] = true;
}

void keyboardUp(unsigned char key, int x, int y)
{
    keyStates[key] = false;
}

void update()
{
    float radYaw = cameraYaw * M_PI / 180.0f;
    float rotationSpeed = 1.3f;

    float dirX = cos(radYaw);
    float dirZ = sin(radYaw);

    float rightX = -sin(radYaw);
    float rightZ = cos(radYaw);

    if (keyStates['w'])
    {
        cameraX += dirX * movementSpeed;
        cameraZ += dirZ * movementSpeed;
    }
    if (keyStates['s'])
    {
        cameraX -= dirX * movementSpeed;
        cameraZ -= dirZ * movementSpeed;
    }
    if (keyStates['a'])
    {
        cameraX -= rightX * movementSpeed;
        cameraZ -= rightZ * movementSpeed;
    }
    if (keyStates['d'])
    {
        cameraX += rightX * movementSpeed;
        cameraZ += rightZ * movementSpeed;
    }
    if (keyStates['j']) // Rotate left
    {
        cameraYaw -= rotationSpeed;
    }
    if (keyStates['l']) // Rotate right
    {
        cameraYaw += rotationSpeed;
    }
    if (keyStates['i']) // Look up
    {
        cameraPitch += rotationSpeed;
        if (cameraPitch > 89.0f)
            cameraPitch = 89.0f;
    }
    if (keyStates['k']) // Look down
    {
        cameraPitch -= rotationSpeed;
        if (cameraPitch < -89.0f)
            cameraPitch = -89.0f;
    }

    glutPostRedisplay();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();

    float radYaw = cameraYaw * M_PI / 180.0f;
    float radPitch = cameraPitch * M_PI / 180.0f;
    float dirX = cos(radYaw) * cos(radPitch);
    float dirY = sin(radPitch);
    float dirZ = sin(radYaw) * cos(radPitch);

    float targetX = cameraX + dirX;
    float targetY = cameraY + dirY;
    float targetZ = cameraZ + dirZ;

    gluLookAt(cameraX, cameraY, cameraZ, targetX, targetY, targetZ, 0.0f, 1.0f, 0.0f);

    drawFloorWithGrid(22.0f, 13.0f, 1.0f);
    drawCustomWall(0.0f, 3.0f, 0.0f, 11.0f, 0.05f, 2.5f);
    drawCustomWall(0.0f, 11.0f, 6.0f, 11.0f, 0.05f, 2.5f);
    drawCustomWall(1.5f, 3.0f, 9.2f, 3.0f, 0.05f, 2.5f);
    drawCustomWall(6.0f, 3.0f, 6.0f, 0.0f, 0.05f, 2.5f);
    drawCustomWall(6.0f, 0.0f, 13.8f, 0.0f, 0.05f, 2.5f);
    drawCustomWall(9.1f, 0.0f, 9.1f, 1.5f, 0.05f, 2.5f);
    drawCustomWall(10.8f, 3.0f, 12.2f, 3.0f, 0.05f, 2.5f);
    drawCustomWall(12.2f, 3.0f, 12.2f, 0.0f, 0.05f, 2.5f);
    drawCustomWall(13.8f, 0.0f, 13.8f, 3.0f, 0.05f, 2.5f);
    drawCustomWall(13.8f, 3.0f, 18.5f, 3.0f, 0.05f, 2.5f);
    drawCustomWall(18.5f, 3.0f, 18.5f, 3.4f, 0.05f, 2.5f);
    drawCustomWall(18.5f, 5.6f, 18.5f, 12.4f, 0.05f, 2.5f);
    drawCustomWall(6.0f, 12.4f, 18.5f, 12.4f, 0.05f, 2.5f);
    drawCustomWall(6.0f, 4.6f, 6.0f, 12.4f, 0.05f, 2.5f);
    drawCustomWall(0.0f, 4.5f, 1.5f, 4.5f, 0.05f, 2.5f);
    drawCustomWall(6.0f, 4.6f, 10.4f, 4.6f, 0.05f, 2.5f);
    drawCustomWall(6.0f, 6.0f, 10.6f, 6.0f, 0.05f, 2.5f);
    drawCustomWall(13.4f, 6.0f, 14.0, 6.0f, 0.05f, 2.5f);
    drawCustomWall(13.8, 12.4f, 13.8f, 6.0f, 0.0f, 2.5f);
    drawCustomWall(15.2f, 6.0f, 18.5f, 6.0f, 0.05f, 2.5f);

    drawCustomWallWithStartHeight(0.0f, 3.0f, 1.5f, 3.0f, 0.05f, 2.0f, 0.5f);
    drawCustomWallWithStartHeight(14.0f, 6.0f, 15.2f, 6.0f, 0.05f, 2.0f, 0.5f);
    drawCustomWallWithStartHeight(10.6f, 6.0f, 13.4f, 6.0f, 0.05f, 2.0f, 0.5f);
    drawCustomWallWithStartHeight(6.0f, 3.0f, 6.0f, 4.6f, 0.05f, 2.0f, 0.5f);
    drawCustomWallWithStartHeight(9.2f, 3.0f, 10.8f, 3.0f, 0.05f, 2.0f, 0.5f);
    drawCustomWallWithStartHeight(9.1f, 1.5f, 9.1f, 3.0f, 0.05f, 2.0f, 0.5f);
    drawCustomWallWithStartHeight(12.2f, 3.0f, 13.8f, 3.0f, 0.05f, 2.0f, 0.5f);
    drawCustomWallWithStartHeight(18.5f, 3.4f, 18.5f, 5.6f, 0.05f, 2.3f, 0.2f);

    drawCustomFloor(6.0f, 6.0f, 12.5f, 6.4f, 0.25f);
    drawCustomFloor(6.0f, 3.0f, 11.0f, 3.0f, 0.25f);
    drawCustomFloor(0.0f, 3.0f, 6.0f, 8.0f, 0.25f);
    drawCustomFloor(6.0f, 0.0f, 7.8f, 3.0f, 0.25f);

    drawCustomCeiling(0.0f, 3.0f, 6.0f, 8.0f, 2.5f, 0.05f);
    drawCustomCeiling(6.0f, 0.0f, 7.8f, 4.6f, 2.5f, 0.05f);
    drawCustomCeiling(6.0f, 6.0f, 12.5f, 6.4f, 2.5f, 0.05f);
    drawCustomCeiling(10.4f, 4.6f, 3.4f, 1.4f, 2.5f, 0.05f);
    drawCustomCeiling(13.8f, 3.0f, 4.7f, 9.4f, 2.5f, 0.05f);

    char cameraInfo[128];
    snprintf(cameraInfo, sizeof(cameraInfo), "Position: (%.2f, %.2f, %.2f)", cameraX, cameraY, cameraZ);
    renderText(10, WINDOW_HEIGHT - 20, cameraInfo);

    glutSwapBuffers();
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

    glutInitWindowPosition(100, 100);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);

    glutCreateWindow("3D Scene with House and Floor");

    init();

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutKeyboardUpFunc(keyboardUp);
    glutIdleFunc(update);

    glutMainLoop();

    return 0;
}
