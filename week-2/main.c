#include <GL/glut.h>
#include <stdbool.h>
#include <stdio.h>
#include <math.h>
#include "scene.h"

#define _USE_MATH_DEFINES
#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 860
#define TEXWIDTH 256
#define TEXHEIGHT 256
// #define M_PI 3.14159265358979323846

float cameraX = 16.0f;
float cameraY = 1.3f;
float cameraZ = 3.5f;
float cameraYaw = 180.0f;
float cameraPitch = 0.0f;

GLuint textureID;
bool keyStates[256] = {false};
float movementSpeed = 0.1f;

void loadFloorTexture(const char *filename)
{
    GLubyte floorTexture[TEXHEIGHT][TEXWIDTH][4];
    FILE *fp = fopen(filename, "rb");
    if (!fp)
    {
        perror(filename);
        return;
    }

    size_t bytesRead = fread(floorTexture, sizeof(floorTexture), 1, fp);
    if (bytesRead != 1)
    {
        fprintf(stderr, "Error reading floor texture data.\n");
    }
    fclose(fp);

    glGenTextures(1, &floorTextureID);
    glBindTexture(GL_TEXTURE_2D, floorTextureID);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, TEXWIDTH, TEXHEIGHT, 0, GL_RGBA, GL_UNSIGNED_BYTE, floorTexture);

    // Set filtering
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    // Set wrap mode to repeat so the texture can tile
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
}

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
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(90.0, (double)WINDOW_WIDTH / (double)WINDOW_HEIGHT, 0.1, 100.0);

    glMatrixMode(GL_MODELVIEW);

    glutSetCursor(GLUT_CURSOR_NONE);
    glutWarpPointer(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
    loadFloorTexture("assets/textures/flooring.raw");
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
    float rotationSpeed = 1.0f;

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
    if (keyStates['[']) // Move up
    {
        cameraY += movementSpeed;
    }
    if (keyStates[']']) // Move down
    {
        cameraY -= movementSpeed;
    }
    if (cameraY < 1.3f)
    {
        cameraY = 1.3f;
    }
    if (cameraY > 6.0f)
    {
        cameraY = 6.0f;
    }
    if (cameraX < -1.0f)
    {
        cameraX = -1.0f;
    }
    if (cameraX > 16.5f)
    {
        cameraX = 16.5f;
    }
    if (cameraZ < -1.0f)
    {
        cameraZ = -1.0f;
    }
    if (cameraZ > 11.5f)
    {
        cameraZ = 11.5f;
    }
    glutPostRedisplay();
}

void drawTexturedCube(float size)
{
    float half = size / 2.0f;
    glBindTexture(GL_TEXTURE_2D, textureID);
    glEnable(GL_TEXTURE_2D);

    glBegin(GL_QUADS);

    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-half, -half, half);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(half, -half, half);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(half, half, half);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-half, half, half);
    glEnd();

    glDisable(GL_TEXTURE_2D);
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

    // Camera Initial Settings
    gluLookAt(cameraX, cameraY, cameraZ, targetX, targetY, targetZ, 0.0f, 1.0f, 0.0f);

    glPushMatrix();
    glScalef(0.75f, 1.0f, 0.75f);

    // Main Grid
    drawFloorWithGrid(22.0f, 13.0f, 1.0f);
    drawCustomFloor(18.5f, 3.0f, 22.0f, 6.0f, 0.0f, 0.01f);

    // First Floor Main Door
    drawMainDoorFrame(18.5f, 3.4f, 18.5f, 5.6f, -0.089f, 2.3f, 0.2f);
    drawDoorTypeB(18.5f, 4.16f, 18.5f, 5.5f, 0.0f, 1.8f, 0.1f);

    // First Floor Walls
    drawCustomWall(0.0f, 3.0f, 0.0f, 7.0f, 0.1f, 2.8f);                         // 1
    drawCustomWallWithStartHeight(0.0f, 7.0f, 0.0f, 9.0f, 0.1f, 0.0f, 0.9f);    // 2
    drawCustomWallWithStartHeight(0.0f, 7.0f, 0.0f, 9.0f, 0.1f, 2.1f, 0.7f);    // 3
    drawCustomWall(0.0f, 9.0f, 0.0f, 11.0f, 0.1f, 2.8f);                        // 4
    drawCustomWall(0.0f, 3.0f, 0.5f, 3.0f, 0.1f, 2.8f);                         // 5
    drawCustomWallWithStartHeight(0.5f, 3.0f, 2.0f, 3.0f, 0.1f, 2.0f, 0.8f);    // 6
    drawCustomWall(0.0f, 11.0f, 1.8f, 11.0f, 0.1f, 2.8f);                       // 7
    drawCustomWallWithStartHeight(1.8f, 11.0f, 4.4f, 11.0f, 0.1f, 2.0f, 0.8f);  // 8
    drawCustomWall(4.4f, 11.0f, 6.0f, 11.0f, 0.1f, 2.8f);                       // 9
    drawCustomWall(2.0f, 3.0f, 3.0f, 3.0f, 0.1f, 2.8f);                         // 10
    drawCustomWallWithStartHeight(3.0f, 3.0f, 5.0f, 3.0f, 0.1f, 0.0f, 0.9f);    // 11
    drawCustomWallWithStartHeight(3.0f, 3.0f, 5.0f, 3.0f, 0.1f, 2.1f, 0.7f);    // 12
    drawCustomWall(5.0f, 3.0f, 9.2f, 3.0f, 0.1f, 2.8f);                         // 13
    drawCustomWall(6.0f, 3.0f, 6.0f, 0.0f, 0.1f, 2.8f);                         // 14
    drawCustomWall(6.0f, 0.0f, 7.0f, 0.0f, 0.1f, 2.8f);                         // 15
    drawCustomWallWithStartHeight(7.0f, 0.0f, 8.3f, 0.0f, 0.1f, 0.0f, 0.9f);    // 16
    drawCustomWallWithStartHeight(7.0f, 0.0f, 8.3f, 0.0f, 0.1f, 2.1f, 0.7f);    // 17
    drawCustomWall(8.3f, 0.0f, 10.4f, 0.0f, 0.1f, 2.8f);                        // 18
    drawCustomWallWithStartHeight(10.4f, 0.0f, 11.7f, 0.0f, 0.1f, 0.0f, 0.9f);  // 19
    drawCustomWallWithStartHeight(10.4f, 0.0f, 11.7f, 0.0f, 0.1f, 2.1f, 0.7f);  // 20
    drawCustomWall(11.7f, 0.0f, 12.4f, 0.0f, 0.1f, 2.8f);                       // 21
    drawCustomWallWithStartHeight(12.4f, 0.0f, 13.7f, 0.0f, 0.1f, 0.0f, 0.9f);  // 22
    drawCustomWallWithStartHeight(12.4f, 0.0f, 13.7f, 0.0f, 0.1f, 2.1f, 0.7f);  // 23
    drawCustomWall(13.7f, 0.0f, 13.8f, 0.0f, 0.1f, 2.8f);                       // 24
    drawCustomWall(9.1f, 0.0f, 9.1f, 1.5f, 0.1f, 2.8f);                         // 25
    drawCustomWallWithStartHeight(9.1f, 1.5f, 9.1f, 3.0f, 0.1f, 2.0f, 0.8f);    // 26
    drawCustomWallWithStartHeight(9.2f, 3.0f, 10.8f, 3.0f, 0.1f, 2.0f, 0.8f);   // 27
    drawCustomWall(10.8f, 3.0f, 12.2f, 3.0f, 0.1f, 2.8f);                       // 28
    drawCustomWall(12.2f, 3.0f, 12.2f, 0.0f, 0.1f, 2.8f);                       // 29
    drawCustomWall(13.8f, 0.0f, 13.8f, 3.0f, 0.1f, 2.8f);                       // 30
    drawCustomWallWithStartHeight(12.2f, 3.0f, 13.8f, 3.0f, 0.1f, 2.0f, 0.8f);  // 31
    drawCustomWall(13.8f, 3.0f, 18.5f, 3.0f, 0.1f, 2.8f);                       // 32
    drawCustomWall(18.5f, 3.0f, 18.5f, 3.4f, 0.1f, 2.8f);                       // 33
    drawCustomWallWithStartHeight(18.5f, 3.4f, 18.5f, 5.6f, 0.1f, 2.3f, 0.5f);  // 34
    drawCustomWall(18.5f, 5.6f, 18.5f, 7.2f, 0.1f, 2.8f);                       // 35
    drawCustomWallWithStartHeight(18.5f, 7.2f, 18.5f, 10.6f, 0.1f, 0.0f, 0.9f); // 36
    drawCustomWallWithStartHeight(18.5f, 7.2f, 18.5f, 10.6f, 0.1f, 2.1f, 0.7f); // 37
    drawCustomWall(18.5f, 10.6f, 18.5f, 12.4f, 0.1f, 2.8f);                     // 38
    drawCustomWall(17.8f, 12.4f, 18.5f, 12.4f, 0.1f, 2.8f);                     // 39
    // drawCustomWallWithStartHeight(14.8f, 12.4f, 16.8f, 12.4f, 0.1f, 0.0f, 0.9f); // 40
    drawCustomWallWithStartHeight(14.8f, 12.4f, 17.8f, 12.4f, 0.1f, 2.0f, 0.8f); // 41
    drawCustomWall(11.0f, 12.4f, 14.8f, 12.4f, 0.1f, 2.8f);                      // 42
    drawCustomWallWithStartHeight(8.0f, 12.4f, 11.0f, 12.4f, 0.1f, 2.0f, 0.8f);  // 43
    drawCustomWall(6.0f, 12.4f, 8.0f, 12.4f, 0.1f, 2.8f);                        // 44
    drawCustomWall(6.0f, 4.6f, 6.0f, 12.4f, 0.1f, 2.8f);                         // 45
    // drawCustomWall(0.0f, 4.5f, 1.5f, 4.5f, 0.1f, 2.8f);                       // 46
    drawCustomWall(6.0f, 4.6f, 10.6f, 4.6f, 0.1f, 2.8f);                       // 47
    drawCustomWall(6.0f, 6.0f, 10.6f, 6.0f, 0.1f, 2.8f);                       // 48
    drawCustomWallWithStartHeight(10.6f, 6.0f, 13.4f, 6.0f, 0.1f, 2.0f, 0.8f); // 49
    drawCustomWall(13.4f, 6.0f, 14.0, 6.0f, 0.1f, 2.8f);                       // 50
    drawCustomWall(13.8, 12.4f, 13.8f, 6.0f, 0.1f, 2.8f);                      // 51
    drawCustomWall(15.2f, 6.0f, 18.5f, 6.0f, 0.1f, 2.8f);                      // 52
    drawCustomWallWithStartHeight(14.0f, 6.0f, 15.2f, 6.0f, 0.1f, 2.0f, 0.8f); // 53
    drawCustomWallWithStartHeight(6.0f, 3.0f, 6.0f, 4.6f, 0.1f, 2.0f, 0.8f);   // 54

    // First Floor Floors & Ceilings
    drawCustomCeiling(0.0f, 3.0f, 6.0f, 11.0f, 2.6f, 0.1f);   // Dining Room CEILING
    drawCustomCeiling(6.0f, 0.0f, 13.8f, 3.0f, 2.6f, 0.1f);   // Shower Room, Powder Room, Toilet CEILING
    drawCustomCeiling(6.0f, 3.0f, 10.4f, 4.6f, 2.6f, 0.1f);   // Hallway CEILING 1
    drawCustomCeiling(10.4f, 3.0f, 18.5f, 6.0f, 2.6f, 0.1f);  // Hallway CEILING 2
    drawCustomCeiling(6.0f, 6.0f, 13.8f, 12.4f, 2.6f, 0.1f);  // Living Room CEILING
    drawCustomCeiling(13.8f, 6.0f, 18.5f, 12.4, 2.6f, 0.1f);  // Meeting Room CEILING
    drawCustomFloor(0.0f, 3.0f, 2.0f, 4.5f, 0.0f, 0.125f);    // Dining Room FLOOR 1
    drawCustomFloor(2.0f, 3.0f, 6.0f, 11.0f, 0.0f, 0.25f);    // Dining Room FLOOR 2
    drawCustomFloor(0.0f, 4.5f, 2.0f, 11.0f, 0.0f, 0.25f);    // Dining Room FLOOR 3
    drawCustomFloor(6.0f, 0.0f, 13.8f, 3.0f, 0.0f, 0.25f);    // Shower Room, Powder Room, Toilet FLOOR
    drawCustomFloor(6.0f, 3.0f, 17.0f, 6.0f, 0.0f, 0.25f);    // Hallway FLOOR
    drawCustomFloor(17.0f, 3.0f, 18.5f, 6.0f, 0.0f, 0.01f);   // Hallway FLOOR 2
    drawCustomFloor(6.0f, 6.0f, 18.5f, 12.4f, 0.0f, 0.25f);   // Living Room & Meeting Room FLOOR
    drawCustomFloor(1.8f, 11.0f, 4.4f, 11.6f, 0.0f, 0.25f);   // Kitchen Backyard FLOOR
    drawCustomFloor(0.5, 2.4f, 2.0f, 3.0f, 0.0f, 0.125f);     // Kitchen Backyard FLOOR 2
    drawCustomFloor(8.0f, 12.4f, 11.0f, 13.0f, 0.0f, 0.25f);  // Living Room Backyard FLOOR
    drawCustomFloor(14.8f, 12.4f, 17.8f, 13.0f, 0.0f, 0.25f); // Meeting Room Backyard FLOOR

    drawTexturedFloor(6.0f, 3.0f, 17.0f, 6.0f, 0.251f);   // Hallway Floor TEXTURE
    drawTexturedFloor(13.8f, 6.0f, 18.5f, 12.4f, 0.251f); // Living Room TEXTURE

    // First Floor Glass Sliding Doors
    drawGlassSlidingDoor(1.8f, 11.0f, 4.4f, 11.0f, 0.15f, 2.0f, 0.1f);   // Kitchen Backyard SLIDING DOOR
    drawGlassSlidingDoor(8.0f, 12.4f, 11.0f, 12.4f, 0.15f, 2.0f, 0.1f);  // Living Room Backyard SLIDING DOOR
    drawGlassSlidingDoor(14.8f, 12.4f, 17.8f, 12.4f, 0.15f, 2.0f, 0.1f); // Meeting Room Backyard SLIDING DOOR

    // First Floor Windows
    drawCustomWindowA(18.5f, 7.2f, 18.5f, 10.6f, 0.9f, 2.1f, 0.2f);
    drawCustomWindowB(12.4f, 0.0f, 13.7f, 0.0f, 0.9f, 2.1f, 0.2f);
    drawCustomWindowB(10.4f, 0.0f, 11.7f, 0.0f, 0.9f, 2.1f, 0.2f);
    drawCustomWindowB(7.0f, 0.0f, 8.3f, 0.0f, 0.9f, 2.1f, 0.2f);
    drawCustomWindowB(3.0f, 3.0f, 5.0f, 3.0f, 0.9f, 2.1f, 0.2f);
    drawCustomWindowB(0.0f, 7.0f, 0.0f, 9.0f, 0.9f, 2.1f, 0.2f);

    // First Floor Door Frames
    drawOuterDoorFrame(14.0f, 6.0f, 15.2f, 6.0f, 0.16f, 2.0f, 0.2f);
    drawOuterDoorFrame(10.6f, 6.0f, 13.4f, 6.0f, 0.16f, 2.0f, 0.2f);
    drawOuterDoorFrame(6.0f, 3.05f, 6.0f, 4.55f, 0.16f, 2.0f, 0.1f);
    drawOuterDoorFrame(5.9f, 3.05f, 5.9f, 5.75f, 0.16f, 2.0f, 0.1f);
    drawOuterDoorFrame(12.2f, 3.0f, 13.8f, 3.0f, 0.16f, 2.0f, 0.2f);
    drawOuterDoorFrame(9.2f, 2.95f, 10.8f, 2.95f, 0.16f, 2.0f, 0.1f);
    drawOuterDoorFrame(7.8f, 3.05f, 10.8f, 3.05f, 0.16f, 2.0f, 0.1f);
    drawOuterDoorFrame(9.1f, 1.5f, 9.1f, 3.0f, 0.16f, 2.0f, 0.2f);
    drawOuterDoorFrame(0.5f, 3.0f, 2.0f, 3.0f, 0.025f, 2.0f, 0.1f);

    // First Floor Doors
    drawDoorTypeA(9.2f, 3.05f, 10.7f, 3.05f, 0.25f, 1.9f, 0.1f);  // Powder Room DOOR
    drawDoorTypeA(5.9f, 3.15f, 5.9f, 4.45f, 0.25f, 1.9f, 0.1f);   // Kitchen DOOR
    drawDoorTypeB(12.2f, 3.0f, 13.8f, 3.0f, 0.25f, 1.9f, 0.1f);   // Toilet DOOR
    drawDoorTypeC(14.0f, 6.0f, 15.2f, 6.0f, 0.25f, 1.9f, 0.1f);   // Meeting Room DOOR
    drawDoorTypeB(0.6f, 3.0f, 1.9f, 3.0f, 0.125f, 1.9f, 0.1f);    // Dining Room Backyard DOOR
    drawSlidingDoor(10.7f, 6.0f, 13.3f, 6.0f, 0.25f, 1.9f, 0.1f); // Living Room DOOR

    // Stair
    drawCustomFloor(10.2f, 4.6f, 10.599f, 6.0f, 0.0f, 0.5375f);
    drawCustomFloor(9.8f, 4.6f, 10.2f, 6.0f, 0.0f, 0.825f);
    drawCustomFloor(9.4f, 4.6f, 9.8f, 6.0f, 0.0f, 1.1125f);
    drawCustomFloor(9.0f, 4.6f, 9.4f, 6.0f, 0.0f, 1.4f);
    drawCustomFloor(8.6f, 4.6f, 9.0f, 6.0f, 0.0f, 1.6875f);
    drawCustomFloor(8.2f, 4.6f, 8.6f, 6.0f, 0.0f, 1.975f);
    drawCustomFloor(7.8f, 4.6f, 8.2f, 6.0f, 0.0f, 2.2625f);
    drawCustomFloor(7.4f, 4.6f, 7.8f, 6.0f, 0.0f, 2.55f);
    drawCustomTriangleFloor(6.7f, 4.6f, 7.4f, 4.6f, 7.4f, 6.0f, 0.0f, 2.8375f);
    drawCustomTriangleFloor(6.0f, 4.6f, 6.7f, 4.6f, 7.4f, 6.0f, 0.0f, 3.125f);
    drawCustomTriangleFloor(6.0f, 4.6f, 6.0f, 5.1f, 7.4f, 6.0f, 0.0f, 3.125f);
    drawCustomTriangleFloor(6.0f, 5.1f, 6.0f, 6.0f, 7.4f, 6.0f, 0.0f, 3.4125f);

    // Second Floor Walls
    drawCustomWallWithStartHeight(6.0f, 4.6f, 6.0f, 7.2f, 0.1f, 2.8f, 3.2f);     // 55
    drawCustomWallWithStartHeight(6.0f, 7.2f, 6.0f, 9.4f, 0.1f, 2.8f, 1.8f);     // 56
    drawCustomWallWithStartHeight(6.0f, 7.2f, 6.0f, 9.4f, 0.1f, 5.5f, 0.5f);     // 57
    drawCustomWallWithStartHeight(6.0f, 9.4f, 6.0f, 12.4f, 0.1f, 2.8f, 3.2f);    // 58
    drawCustomWallWithStartHeight(6.0f, 12.4f, 6.2f, 12.4f, 0.1f, 2.8f, 3.2f);   // 59
    drawCustomWallWithStartHeight(6.2f, 12.4f, 7.3f, 12.4f, 0.1f, 2.8f, 1.8f);   // 60
    drawCustomWallWithStartHeight(6.2f, 12.4f, 7.3f, 12.4f, 0.1f, 5.5f, 0.5f);   // 61
    drawCustomWallWithStartHeight(7.3f, 12.4f, 13.8f, 12.4f, 0.1f, 2.8f, 3.2f);  // 62
    drawCustomWallWithStartHeight(13.8f, 6.0f, 13.8f, 7.45f, 0.1f, 2.8f, 3.2f);  // 63
    drawCustomWallWithStartHeight(13.8f, 7.45f, 13.8f, 9.75f, 0.1f, 2.8f, 1.8f); // 64
    drawCustomWallWithStartHeight(13.8f, 7.45f, 13.8f, 9.75f, 0.1f, 5.5f, 0.5f); // 65
    drawCustomWallWithStartHeight(13.8f, 9.75f, 13.8f, 12.4f, 0.1f, 2.8f, 3.2f); // 66
    drawCustomWallWithStartHeight(13.8f, 6.0f, 12.45f, 6.0f, 0.1f, 2.8f, 3.2f);  // 67
    drawCustomWallWithStartHeight(12.45f, 6.0f, 11.25f, 6.0f, 0.1f, 2.8f, 1.8f); // 68
    drawCustomWallWithStartHeight(12.45f, 6.0f, 11.25f, 6.0f, 0.1f, 5.5f, 0.5f); // 69
    drawCustomWallWithStartHeight(11.25f, 6.0f, 7.4f, 6.0f, 0.1f, 2.8f, 3.2f);   // 70
    drawCustomWallWithStartHeight(7.4f, 6.0f, 7.4f, 7.8f, 0.1f, 2.8f, 3.2f);     // 71
    drawCustomWallWithStartHeight(7.4f, 7.8f, 7.4f, 9.4f, 0.1f, 5.5f, 0.5f);     // 72
    drawCustomWallWithStartHeight(7.4f, 9.4f, 7.4f, 11.2f, 0.1f, 2.8f, 3.2f);    // 73
    drawCustomWallWithStartHeight(7.4f, 11.2f, 7.4f, 12.4f, 0.1f, 5.0f, 1.0f);   // 74
    drawCustomWallWithStartHeight(7.4f, 11.2f, 9.0f, 11.2f, 0.1f, 2.8f, 3.2f);   // 75
    drawCustomWallWithStartHeight(9.0f, 11.2f, 12.0f, 11.2f, 0.1f, 5.5f, 0.5f);  // 76
    drawCustomWallWithStartHeight(9.0f, 11.2f, 9.0f, 12.4f, 0.1f, 2.8f, 3.2f);   // 77
    drawCustomWallWithStartHeight(12.0f, 11.2f, 13.8f, 11.2f, 0.1f, 2.8f, 3.2f); // 78
    drawCustomWallWithStartHeight(8.0f, 4.6f, 6.0f, 4.6f, 0.1f, 2.8f, 3.2f);     // 79
    drawCustomWallWithStartHeight(9.0f, 4.6f, 8.0f, 4.6f, 0.1f, 2.8f, 1.8f);     // 80
    drawCustomWallWithStartHeight(9.0f, 4.6f, 8.0f, 4.6f, 0.1f, 5.5f, 0.5f);     // 81
    drawCustomWallWithStartHeight(9.9f, 4.6f, 9.0f, 4.6f, 0.1f, 2.8f, 3.2f);     // 82
    drawCustomWallWithStartHeight(9.9f, 6.0f, 9.9f, 4.6f, 0.1f, 2.8f, 3.2f);     // 83

    // Second Floor Floors & Ceilings
    drawCustomFloor(6.0f, 6.0f, 13.8f, 12.4f, 2.8f, 3.7f);
    drawCustomCeiling(6.0f, 6.0f, 13.8f, 12.4f, 5.95f, 0.1f);
    drawCustomCeiling(6.0f, 4.6f, 9.9f, 6.0f, 5.95f, 0.1f);

    // Second Floor Windows
    drawCustomWindowA(13.8f, 7.45f, 13.8f, 9.75f, 4.6f, 5.5f, 0.2f);
    drawCustomWindowB(11.25f, 6.0f, 12.45f, 6.0f, 4.6f, 5.5f, 0.2f);
    drawCustomWindowA(6.0f, 7.2f, 6.0f, 9.4f, 4.6f, 5.5f, 0.2f);
    drawCustomWindowB(6.2f, 12.4f, 7.3f, 12.4f, 4.6f, 5.5f, 0.2f);
    drawCustomWindowC(8.0f, 4.6f, 9.0f, 4.6f, 4.6f, 5.5f, 0.2f);

    // Second Floor Door Frames
    drawOuterDoorFrame(7.4f, 7.8f, 7.4f, 9.4f, 3.61f, 5.5f, 0.2f);
    drawOuterDoorFrame(9.0f, 11.2f, 12.0f, 11.2f, 3.61f, 5.5f, 0.2f);
    drawOuterDoorFrame(7.4f, 11.2f, 7.4f, 12.4f, 3.61f, 5.0f, 0.2f);

    // Second Floor Doors
    drawDoorTypeC(7.4f, 7.9f, 7.4f, 9.3f, 3.7f, 5.4f, 0.f);       // Bedroom 1 DOOR
    drawDoorTypeC(7.4f, 11.3f, 7.4f, 12.3f, 3.7f, 4.9f, 0.1f);    // Storage Room DOOR
    drawSlidingDoor(12.0f, 11.2f, 9.0f, 11.2f, 3.7f, 5.4f, 0.1f); // Bedroom 2 DOOR

    // Triangle Walls
    drawCustomTriangleWallWithStartHeight(0.0f, 3.0f, 0.0f, 11.0f, 0.1f, 2.8f, 1.2f);
    drawCustomTriangleWallWithStartHeight(18.5f, 3.0f, 18.5f, 12.4f, 0.1f, 2.8f, 1.2f);
    drawCustomTriangleWallWithStartHeight(6.0f, 6.0f, 6.0f, 12.4f, 0.1f, 6.0f, 1.2f);
    drawCustomTriangleWallWithStartHeight(6.0f, 0.0f, 13.8f, 0.0f, 0.1f, 2.8f, 0.766f);
    drawCustomTriangleWallWithStartHeight(6.0f, 4.6f, 9.9f, 4.6f, 0.1f, 6.0f, 1.0f);
    drawCustomTriangleWallWithStartHeight(13.8f, 6.0f, 13.8f, 12.4f, 0.1f, 6.0f, 1.2f);

    // Roofs
    // drawThickRoofSegment(16.55f, 2.0f, 16.55f, 7.7f, 5.5f, 2.545f, 4.0f, 0.1f);
    // drawThickRoofSegment(12.1f, 2.0f, 12.1f, 6.0f, 3.4f, 2.545f, 3.566f, 0.1f);
    // drawThickRoofSegment(16.55f, 7.7f, 16.55f, 13.4f, 5.5f, 4.0f, 2.545f, 0.1f);
    // drawThickRoofSegment(9.9f, 12.4f, 9.9f, 13.4f, 7.8f, 2.8f, 2.545f, 0.1f);
    // drawThickRoofSegment(5.0f, 1.8f, 9.9f, 1.8f, 5.6f, 2.492f, 4.0f, 0.1f);
    // drawThickRoofSegment(9.9f, 2.5f, 14.8f, 2.5f, 7.0f, 4.0f, 2.492f, 0.1f);
    // drawThickRoofSegment(2.5f, 2.0f, 2.5f, 7.0f, 7.0f, 2.5f, 4.0f, 0.1f);
    // drawThickRoofSegment(2.5f, 7.0f, 2.5f, 12.0f, 7.0f, 4.0f, 2.5f, 0.1f);
    // drawThickRoofSegment(9.9f, 5.0f, 9.9f, 9.2f, 9.8f, 5.625f, 7.2f, 0.1f);
    // drawThickRoofSegment(9.9f, 13.4f, 9.9f, 9.2f, 9.8f, 5.625f, 7.2f, 0.1f);
    // drawThickRoofSegment(10.631f, 6.4f, 7.95f, 6.4f, 5.6f, 5.625f, 7.0f, 0.1f);
    // drawThickRoofSegment(5.269f, 6.4f, 7.95f, 6.4f, 5.6f, 5.625f, 7.0f, 0.1f);
    drawQuadRoofSegment(9.9f, 7.2f, 9.2f, 14.3f, 7.2f, 9.2f, 14.3f, 5.825f, 5.5f, 9.9f, 5.825f, 5.5f, 0.1f, 255.0f / 255.0f, 253.0f / 255.0f, 208.0f / 255.0f);
    drawQuadRoofSegment(5.5f, 7.2f, 9.2f, 6.0f, 7.2f, 9.2f, 6.0f, 5.825f, 5.5f, 5.5f, 5.825f, 5.5f, 0.1f, 255.0f / 255.0f, 253.0f / 255.0f, 208.0f / 255.0f);
    drawQuadRoofSegment(6.0f, 7.2f, 9.2f, 9.9f, 7.2f, 9.2f, 9.9f, 6.0f, 5.971f, 6.0f, 6.0f, 5.971f, 0.1f, 255.0f / 255.0f, 253.0f / 255.0f, 208.0f / 255.0f);
    drawQuadRoofSegment(5.5f, 7.2f, 9.2f, 14.3f, 7.2f, 9.2f, 14.3f, 5.825f, 12.9f, 5.5f, 5.825f, 12.9f, 0.1f, 255.0f / 255.0f, 253.0f / 255.0f, 208.0f / 255.0f);
    drawQuadRoofSegment(7.95f, 7.0f, 4.1f, 10.241f, 5.825f, 4.1f, 10.241f, 5.825f, 5.5f, 7.95f, 7.0f, 8.661f, 0.1f, 255.0f / 255.0f, 253.0f / 255.0f, 208.0f / 255.0f);
    drawQuadRoofSegment(5.659f, 5.825f, 4.1f, 7.95f, 7.0f, 4.1f, 7.95f, 7.0f, 8.661f, 5.659f, 5.825f, 5.5f, 0.1f, 255.0f / 255.0f, 253.0f / 255.0f, 208.0f / 255.0f);

    drawQuadRoofSegment(5.5f, 2.647f, -0.5f, 9.9f, 3.566f, -0.5f, 9.9f, 3.566f, 4.6f, 5.5f, 2.647f, 4.6f, 0.1f, 255.0f / 255.0f, 253.0f / 255.0f, 208.0f / 255.0f);
    drawQuadRoofSegment(9.9f, 3.566f, -0.5f, 9.9f, 3.566f, 6.0f, 14.3f, 2.647f, 2.5f, 14.3f, 2.647f, -0.5f, 0.1f, 255.0f / 255.0f, 253.0f / 255.0f, 208.0f / 255.0f);
    drawQuadRoofSegment(9.9f, 3.566f, 6.0f, 14.3f, 2.647f, 2.5f, 19.0f, 2.647f, 2.5f, 19.0f, 3.566f, 6.0f, 0.1f, 255.0f / 255.0f, 253.0f / 255.0f, 208.0f / 255.0f);
    drawQuadRoofSegment(13.8f, 3.566f, 6.0f, 19.0f, 3.566f, 6.0f, 19.0f, 4.0f, 7.7f, 13.8f, 4.0f, 7.7f, 0.1f, 255.0f / 255.0f, 253.0f / 255.0f, 208.0f / 255.0f);
    drawQuadRoofSegment(13.8f, 2.647f, 12.9f, 19.0f, 2.647f, 12.9f, 19.0f, 4.0f, 7.7f, 13.9f, 4.0f, 7.7f, 0.1f, 255.0f / 255.0f, 253.0f / 255.0f, 208.0f / 255.0f);
    drawQuadRoofSegment(6.0f, 2.77f, 12.4f, 13.8f, 2.77f, 12.4f, 13.8f, 2.647f, 12.9f, 6.0f, 2.647f, 12.9f, 0.1f, 255.0f / 255.0f, 253.0f / 255.0f, 208.0f / 255.0f);
    drawQuadRoofSegment(6.0f, 4.0f, 7.0f, 6.0f, 2.647f, 11.5f, -0.5f, 2.647f, 11.5f, -0.5f, 4.0f, 7.0f, 0.1f, 255.0f / 255.0f, 253.0f / 255.0f, 208.0f / 255.0f);
    drawQuadRoofSegment(6.0f, 2.647f, 2.5f, -0.5f, 2.647f, 2.5f, -0.5f, 4.0f, 7.0f, 6.0f, 4.0f, 7.0f, 0.1f, 255.0f / 255.0f, 253.0f / 255.0f, 208.0f / 255.0f);
    drawQuadRoofSegment(-0.5f, 2.647f, 2.5f, 6.0f, 2.647f, 2.5f, 9.9f, 3.28f, 4.6f, -0.5f, 3.28f, 4.6f, 0.1f, 255.0f / 255.0f, 253.0f / 255.0f, 208.0f / 255.0f);

    drawQuadRoofSegment(9.9f, 7.31f, 9.2f, 14.3f, 7.31f, 9.2f, 14.3f, 5.935f, 5.5f, 9.9f, 5.935f, 5.5f, 0.03f, 133.0f / 255.0f, 41.0f / 255.0f, 40.0f / 255.0f);
    drawQuadRoofSegment(5.5f, 7.31f, 9.2f, 6.0f, 7.31f, 9.2f, 6.0f, 5.935f, 5.5f, 5.5f, 5.935f, 5.5f, 0.03f, 133.0f / 255.0f, 41.0f / 255.0f, 40.0f / 255.0f);
    drawQuadRoofSegment(6.0f, 7.31f, 9.2f, 9.9f, 7.31f, 9.2f, 9.9f, 6.11f, 5.971f, 6.0f, 6.11f, 5.971f, 0.03f, 133.0f / 255.0f, 41.0f / 255.0f, 40.0f / 255.0f);
    drawQuadRoofSegment(5.5f, 7.31f, 9.2f, 14.3f, 7.31f, 9.2f, 14.3f, 5.935f, 12.9f, 5.5f, 5.935f, 12.9f, 0.03f, 133.0f / 255.0f, 41.0f / 255.0f, 40.0f / 255.0f);
    drawQuadRoofSegment(7.95f, 7.11f, 4.1f, 10.241f, 5.935f, 4.1f, 10.241f, 5.935f, 5.5f, 7.95f, 7.11f, 8.661f, 0.03f, 133.0f / 255.0f, 41.0f / 255.0f, 40.0f / 255.0f);
    drawQuadRoofSegment(5.659f, 5.935f, 4.1f, 7.95f, 7.11f, 4.1f, 7.95f, 7.11f, 8.661f, 5.659f, 5.935f, 5.5f, 0.03f, 133.0f / 255.0f, 41.0f / 255.0f, 40.0f / 255.0f);
    drawQuadRoofSegment(5.5f, 2.757f, -0.5f, 9.9f, 3.676f, -0.5f, 9.9f, 3.676f, 4.6f, 5.5f, 2.757f, 4.6f, 0.03f, 133.0f / 255.0f, 41.0f / 255.0f, 40.0f / 255.0f);
    drawQuadRoofSegment(9.9f, 3.676f, -0.5f, 9.9f, 3.676f, 6.0f, 14.3f, 2.757f, 2.5f, 14.3f, 2.757f, -0.5f, 0.03f, 133.0f / 255.0f, 41.0f / 255.0f, 40.0f / 255.0f);
    drawQuadRoofSegment(9.9f, 3.676f, 6.0f, 14.3f, 2.757f, 2.5f, 19.0f, 2.757f, 2.5f, 19.0f, 3.676f, 6.0f, 0.03f, 133.0f / 255.0f, 41.0f / 255.0f, 40.0f / 255.0f);
    drawQuadRoofSegment(13.8f, 3.676f, 6.0f, 19.0f, 3.676f, 6.0f, 19.0f, 4.11f, 7.7f, 13.8f, 4.11f, 7.7f, 0.03f, 133.0f / 255.0f, 41.0f / 255.0f, 40.0f / 255.0f);
    drawQuadRoofSegment(13.8f, 2.757f, 12.9f, 19.0f, 2.757f, 12.9f, 19.0f, 4.11f, 7.7f, 13.9f, 4.11f, 7.7f, 0.03f, 133.0f / 255.0f, 41.0f / 255.0f, 40.0f / 255.0f);
    drawQuadRoofSegment(6.0f, 2.88f, 12.4f, 13.8f, 2.88f, 12.4f, 13.8f, 2.757f, 12.9f, 6.0f, 2.757f, 12.9f, 0.03f, 133.0f / 255.0f, 41.0f / 255.0f, 40.0f / 255.0f);
    drawQuadRoofSegment(6.0f, 4.11f, 7.0f, 6.0f, 2.757f, 11.5f, -0.5f, 2.757f, 11.5f, -0.5f, 4.11f, 7.0f, 0.03f, 133.0f / 255.0f, 41.0f / 255.0f, 40.0f / 255.0f);
    drawQuadRoofSegment(6.0f, 2.757f, 2.5f, -0.5f, 2.757f, 2.5f, -0.5f, 4.11f, 7.0f, 6.0f, 4.11f, 7.0f, 0.03f, 133.0f / 255.0f, 41.0f / 255.0f, 40.0f / 255.0f);
    drawQuadRoofSegment(-0.5f, 2.757f, 2.5f, 6.0f, 2.757f, 2.5f, 9.9f, 3.39f, 4.6f, -0.5f, 3.39f, 4.6f, 0.03f, 133.0f / 255.0f, 41.0f / 255.0f, 40.0f / 255.0f);

    glPopMatrix();

    // Coordinates UI
    // Reset transformations for UI rendering
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, WINDOW_WIDTH, 0, WINDOW_HEIGHT);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    // Render UI text without scaling issues
    char cameraInfo[128];
    snprintf(cameraInfo, sizeof(cameraInfo), "Position: (%.2f, %.2f, %.2f)", cameraX * 4.0f / 3.0f, cameraY, cameraZ * 4.0f / 3.0f);
    renderText(10, WINDOW_HEIGHT - 20, cameraInfo);

    // Restore the original projection matrix
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);

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
