#include <GL/glut.h>
#include <math.h>

#include "scene.h"

void drawFloorWithGrid(float length, float width, float tileSize)
{
    glColor3f(0.2f, 0.8f, 0.2f);
    glBegin(GL_QUADS);
    glVertex3f(0, -0.002f, 0);
    glVertex3f(length, -0.002f, 0);
    glVertex3f(length, -0.002f, width);
    glVertex3f(0, -0.002f, width);
    glEnd();

    glColor3f(0.0f, 0.0f, 0.0f);
    glLineWidth(1.0f);

    glBegin(GL_LINES);

    for (float x = 0; x <= length; x += tileSize)
    {
        glVertex3f(x, -0.001f, 0);
        glVertex3f(x, -0.001f, width);
    }

    for (float z = 0; z <= width; z += tileSize)
    {
        glVertex3f(0, -0.001f, z);
        glVertex3f(length, -0.001f, z);
    }

    glEnd();
}

void drawCustomWall(float startX, float startZ, float endX, float endZ, float thickness, float height)
{
    float dx = endX - startX;
    float dz = endZ - startZ;
    float length = sqrt(dx * dx + dz * dz);

    dx /= length;
    dz /= length;

    float perpX = -dz * thickness / 2.0f;
    float perpZ = dx * thickness / 2.0f;

    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);

    glVertex3f(startX + perpX, 0.0f, startZ + perpZ); // Bottom-left
    glVertex3f(startX - perpX, 0.0f, startZ - perpZ); // Bottom-right
    glVertex3f(endX - perpX, 0.0f, endZ - perpZ);     // Top-right
    glVertex3f(endX + perpX, 0.0f, endZ + perpZ);     // Top-left

    // Top vertices (for height)
    glVertex3f(startX + perpX, height, startZ + perpZ); // Top-left
    glVertex3f(startX - perpX, height, startZ - perpZ); // Top-right
    glVertex3f(endX - perpX, height, endZ - perpZ);     // Bottom-right
    glVertex3f(endX + perpX, height, endZ + perpZ);     // Bottom-left

    // Front face
    glVertex3f(startX + perpX, 0.0f, startZ + perpZ);   // Bottom-left
    glVertex3f(startX - perpX, 0.0f, startZ - perpZ);   // Bottom-right
    glVertex3f(startX - perpX, height, startZ - perpZ); // Top-right
    glVertex3f(startX + perpX, height, startZ + perpZ); // Top-left

    // Back face
    glVertex3f(endX + perpX, 0.0f, endZ + perpZ);   // Bottom-left
    glVertex3f(endX - perpX, 0.0f, endZ - perpZ);   // Bottom-right
    glVertex3f(endX - perpX, height, endZ - perpZ); // Top-right
    glVertex3f(endX + perpX, height, endZ + perpZ); // Top-left

    // Left face
    glVertex3f(startX + perpX, 0.0f, startZ + perpZ);   // Bottom-left
    glVertex3f(endX + perpX, 0.0f, endZ + perpZ);       // Bottom-right
    glVertex3f(endX + perpX, height, endZ + perpZ);     // Top-right
    glVertex3f(startX + perpX, height, startZ + perpZ); // Top-left

    // Right face
    glVertex3f(startX - perpX, 0.0f, startZ - perpZ);   // Bottom-left
    glVertex3f(endX - perpX, 0.0f, endZ - perpZ);       // Bottom-right
    glVertex3f(endX - perpX, height, endZ - perpZ);     // Top-right
    glVertex3f(startX - perpX, height, startZ - perpZ); // Top-left

    glEnd();

    glColor3f(0.0f, 0.0f, 0.0f);
    glLineWidth(2.0f);
    glBegin(GL_LINES);

    // Bottom edges
    glVertex3f(startX + perpX, 0.0f, startZ + perpZ);
    glVertex3f(startX - perpX, 0.0f, startZ - perpZ);

    glVertex3f(startX - perpX, 0.0f, startZ - perpZ);
    glVertex3f(endX - perpX, 0.0f, endZ - perpZ);

    glVertex3f(endX - perpX, 0.0f, endZ - perpZ);
    glVertex3f(endX + perpX, 0.0f, endZ + perpZ);

    glVertex3f(endX + perpX, 0.0f, endZ + perpZ);
    glVertex3f(startX + perpX, 0.0f, startZ + perpZ);

    // Top edges
    glVertex3f(startX + perpX, height, startZ + perpZ);
    glVertex3f(startX - perpX, height, startZ - perpZ);

    glVertex3f(startX - perpX, height, startZ - perpZ);
    glVertex3f(endX - perpX, height, endZ - perpZ);

    glVertex3f(endX - perpX, height, endZ - perpZ);
    glVertex3f(endX + perpX, height, endZ + perpZ);

    glVertex3f(endX + perpX, height, endZ + perpZ);
    glVertex3f(startX + perpX, height, startZ + perpZ);

    // Vertical edges
    glVertex3f(startX + perpX, 0.0f, startZ + perpZ);
    glVertex3f(startX + perpX, height, startZ + perpZ);

    glVertex3f(startX - perpX, 0.0f, startZ - perpZ);
    glVertex3f(startX - perpX, height, startZ - perpZ);

    glVertex3f(endX + perpX, 0.0f, endZ + perpZ);
    glVertex3f(endX + perpX, height, endZ + perpZ);

    glVertex3f(endX - perpX, 0.0f, endZ - perpZ);
    glVertex3f(endX - perpX, height, endZ - perpZ);

    glEnd();
}

void drawCustomWallWithStartHeight(float startX, float startZ, float endX, float endZ, float thickness, float startHeight, float height)
{
    float dx = endX - startX;
    float dz = endZ - startZ;
    float length = sqrt(dx * dx + dz * dz);

    dx /= length;
    dz /= length;

    float perpX = -dz * thickness / 2.0f;
    float perpZ = dx * thickness / 2.0f;

    float topHeight = startHeight + height;

    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);

    // Bottom face
    glVertex3f(startX + perpX, startHeight, startZ + perpZ); // Bottom-left
    glVertex3f(startX - perpX, startHeight, startZ - perpZ); // Bottom-right
    glVertex3f(endX - perpX, startHeight, endZ - perpZ);     // Top-right
    glVertex3f(endX + perpX, startHeight, endZ + perpZ);     // Top-left

    // Top face
    glVertex3f(startX + perpX, topHeight, startZ + perpZ); // Top-left
    glVertex3f(startX - perpX, topHeight, startZ - perpZ); // Top-right
    glVertex3f(endX - perpX, topHeight, endZ - perpZ);     // Bottom-right
    glVertex3f(endX + perpX, topHeight, endZ + perpZ);     // Bottom-left

    // Front face
    glVertex3f(startX + perpX, startHeight, startZ + perpZ); // Bottom-left
    glVertex3f(startX - perpX, startHeight, startZ - perpZ); // Bottom-right
    glVertex3f(startX - perpX, topHeight, startZ - perpZ);   // Top-right
    glVertex3f(startX + perpX, topHeight, startZ + perpZ);   // Top-left

    // Back face
    glVertex3f(endX + perpX, startHeight, endZ + perpZ); // Bottom-left
    glVertex3f(endX - perpX, startHeight, endZ - perpZ); // Bottom-right
    glVertex3f(endX - perpX, topHeight, endZ - perpZ);   // Top-right
    glVertex3f(endX + perpX, topHeight, endZ + perpZ);   // Top-left

    // Left face
    glVertex3f(startX + perpX, startHeight, startZ + perpZ); // Bottom-left
    glVertex3f(endX + perpX, startHeight, endZ + perpZ);     // Bottom-right
    glVertex3f(endX + perpX, topHeight, endZ + perpZ);       // Top-right
    glVertex3f(startX + perpX, topHeight, startZ + perpZ);   // Top-left

    // Right face
    glVertex3f(startX - perpX, startHeight, startZ - perpZ); // Bottom-left
    glVertex3f(endX - perpX, startHeight, endZ - perpZ);     // Bottom-right
    glVertex3f(endX - perpX, topHeight, endZ - perpZ);       // Top-right
    glVertex3f(startX - perpX, topHeight, startZ - perpZ);   // Top-left

    glEnd();

    glColor3f(0.0f, 0.0f, 0.0f);
    glLineWidth(2.0f);
    glBegin(GL_LINES);

    // Bottom edges
    glVertex3f(startX + perpX, startHeight, startZ + perpZ);
    glVertex3f(startX - perpX, startHeight, startZ - perpZ);

    glVertex3f(startX - perpX, startHeight, startZ - perpZ);
    glVertex3f(endX - perpX, startHeight, endZ - perpZ);

    glVertex3f(endX - perpX, startHeight, endZ - perpZ);
    glVertex3f(endX + perpX, startHeight, endZ + perpZ);

    glVertex3f(endX + perpX, startHeight, endZ + perpZ);
    glVertex3f(startX + perpX, startHeight, startZ + perpZ);

    // Top edges
    glVertex3f(startX + perpX, topHeight, startZ + perpZ);
    glVertex3f(startX - perpX, topHeight, startZ - perpZ);

    glVertex3f(startX - perpX, topHeight, startZ - perpZ);
    glVertex3f(endX - perpX, topHeight, endZ - perpZ);

    glVertex3f(endX - perpX, topHeight, endZ - perpZ);
    glVertex3f(endX + perpX, topHeight, endZ + perpZ);

    glVertex3f(endX + perpX, topHeight, endZ + perpZ);
    glVertex3f(startX + perpX, topHeight, startZ + perpZ);

    // Vertical edges
    glVertex3f(startX + perpX, startHeight, startZ + perpZ);
    glVertex3f(startX + perpX, topHeight, startZ + perpZ);

    glVertex3f(startX - perpX, startHeight, startZ - perpZ);
    glVertex3f(startX - perpX, topHeight, startZ - perpZ);

    glVertex3f(endX + perpX, startHeight, endZ + perpZ);
    glVertex3f(endX + perpX, topHeight, endZ + perpZ);

    glVertex3f(endX - perpX, startHeight, endZ - perpZ);
    glVertex3f(endX - perpX, topHeight, endZ - perpZ);

    glEnd();
}

void drawCustomFloor(float startX, float startZ, float length, float width, float height)
{
    glColor3f(0.5f, 0.5f, 0.5f);
    glBegin(GL_QUADS);

    // Bottom face
    glVertex3f(startX, 0.0f, startZ);                  // Bottom-left
    glVertex3f(startX + length, 0.0f, startZ);         // Bottom-right
    glVertex3f(startX + length, 0.0f, startZ + width); // Top-right
    glVertex3f(startX, 0.0f, startZ + width);          // Top-left

    // Top face
    glVertex3f(startX, height, startZ);                  // Bottom-left
    glVertex3f(startX + length, height, startZ);         // Bottom-right
    glVertex3f(startX + length, height, startZ + width); // Top-right
    glVertex3f(startX, height, startZ + width);          // Top-left

    // Front face
    glVertex3f(startX, 0.0f, startZ);            // Bottom-left
    glVertex3f(startX + length, 0.0f, startZ);   // Bottom-right
    glVertex3f(startX + length, height, startZ); // Top-right
    glVertex3f(startX, height, startZ);          // Top-left

    // Back face
    glVertex3f(startX, 0.0f, startZ + width);            // Bottom-left
    glVertex3f(startX + length, 0.0f, startZ + width);   // Bottom-right
    glVertex3f(startX + length, height, startZ + width); // Top-right
    glVertex3f(startX, height, startZ + width);          // Top-left

    // Left face
    glVertex3f(startX, 0.0f, startZ);           // Bottom-left
    glVertex3f(startX, 0.0f, startZ + width);   // Bottom-right
    glVertex3f(startX, height, startZ + width); // Top-right
    glVertex3f(startX, height, startZ);         // Top-left

    // Right face
    glVertex3f(startX + length, 0.0f, startZ);           // Bottom-left
    glVertex3f(startX + length, 0.0f, startZ + width);   // Bottom-right
    glVertex3f(startX + length, height, startZ + width); // Top-right
    glVertex3f(startX + length, height, startZ);         // Top-left

    glEnd();

    glColor3f(0.0f, 0.0f, 0.0f); // Black outline
    glLineWidth(2.0f);
    glBegin(GL_LINES);

    // Bottom edges
    glVertex3f(startX, 0.0f, startZ);
    glVertex3f(startX + length, 0.0f, startZ);

    glVertex3f(startX + length, 0.0f, startZ);
    glVertex3f(startX + length, 0.0f, startZ + width);

    glVertex3f(startX + length, 0.0f, startZ + width);
    glVertex3f(startX, 0.0f, startZ + width);

    glVertex3f(startX, 0.0f, startZ + width);
    glVertex3f(startX, 0.0f, startZ);

    // Top edges
    glVertex3f(startX, height, startZ);
    glVertex3f(startX + length, height, startZ);

    glVertex3f(startX + length, height, startZ);
    glVertex3f(startX + length, height, startZ + width);

    glVertex3f(startX + length, height, startZ + width);
    glVertex3f(startX, height, startZ + width);

    glVertex3f(startX, height, startZ + width);
    glVertex3f(startX, height, startZ);

    // Vertical edges
    glVertex3f(startX, 0.0f, startZ);
    glVertex3f(startX, height, startZ);

    glVertex3f(startX + length, 0.0f, startZ);
    glVertex3f(startX + length, height, startZ);

    glVertex3f(startX + length, 0.0f, startZ + width);
    glVertex3f(startX + length, height, startZ + width);

    glVertex3f(startX, 0.0f, startZ + width);
    glVertex3f(startX, height, startZ + width);

    glEnd();
}

void drawCustomCeiling(float startX, float startZ, float length, float width, float heightPosition, float thickness)
{
    glColor3f(0.8f, 0.8f, 0.8f);
    glBegin(GL_QUADS);

    // Bottom face (visible from below)
    glVertex3f(startX, heightPosition, startZ);                  // Bottom-left
    glVertex3f(startX + length, heightPosition, startZ);         // Bottom-right
    glVertex3f(startX + length, heightPosition, startZ + width); // Top-right
    glVertex3f(startX, heightPosition, startZ + width);          // Top-left

    // Top face (thickness makes this visible from above)
    glVertex3f(startX, heightPosition + thickness, startZ);                  // Bottom-left
    glVertex3f(startX + length, heightPosition + thickness, startZ);         // Bottom-right
    glVertex3f(startX + length, heightPosition + thickness, startZ + width); // Top-right
    glVertex3f(startX, heightPosition + thickness, startZ + width);          // Top-left

    // Front face
    glVertex3f(startX, heightPosition, startZ);                      // Bottom-left
    glVertex3f(startX + length, heightPosition, startZ);             // Bottom-right
    glVertex3f(startX + length, heightPosition + thickness, startZ); // Top-right
    glVertex3f(startX, heightPosition + thickness, startZ);          // Top-left

    // Back face
    glVertex3f(startX, heightPosition, startZ + width);                      // Bottom-left
    glVertex3f(startX + length, heightPosition, startZ + width);             // Bottom-right
    glVertex3f(startX + length, heightPosition + thickness, startZ + width); // Top-right
    glVertex3f(startX, heightPosition + thickness, startZ + width);          // Top-left

    // Left face
    glVertex3f(startX, heightPosition, startZ);                     // Bottom-left
    glVertex3f(startX, heightPosition, startZ + width);             // Bottom-right
    glVertex3f(startX, heightPosition + thickness, startZ + width); // Top-right
    glVertex3f(startX, heightPosition + thickness, startZ);         // Top-left

    // Right face
    glVertex3f(startX + length, heightPosition, startZ);                     // Bottom-left
    glVertex3f(startX + length, heightPosition, startZ + width);             // Bottom-right
    glVertex3f(startX + length, heightPosition + thickness, startZ + width); // Top-right
    glVertex3f(startX + length, heightPosition + thickness, startZ);         // Top-left

    glEnd();

    glColor3f(0.0f, 0.0f, 0.0f); // Black outline
    glLineWidth(2.0f);
    glBegin(GL_LINES);

    // Bottom edges
    glVertex3f(startX, heightPosition, startZ);
    glVertex3f(startX + length, heightPosition, startZ);

    glVertex3f(startX + length, heightPosition, startZ);
    glVertex3f(startX + length, heightPosition, startZ + width);

    glVertex3f(startX + length, heightPosition, startZ + width);
    glVertex3f(startX, heightPosition, startZ + width);

    glVertex3f(startX, heightPosition, startZ + width);
    glVertex3f(startX, heightPosition, startZ);

    // Top edges
    glVertex3f(startX, heightPosition + thickness, startZ);
    glVertex3f(startX + length, heightPosition + thickness, startZ);

    glVertex3f(startX + length, heightPosition + thickness, startZ);
    glVertex3f(startX + length, heightPosition + thickness, startZ + width);

    glVertex3f(startX + length, heightPosition + thickness, startZ + width);
    glVertex3f(startX, heightPosition + thickness, startZ + width);

    glVertex3f(startX, heightPosition + thickness, startZ + width);
    glVertex3f(startX, heightPosition + thickness, startZ);

    // Vertical edges
    glVertex3f(startX, heightPosition, startZ);
    glVertex3f(startX, heightPosition + thickness, startZ);

    glVertex3f(startX + length, heightPosition, startZ);
    glVertex3f(startX + length, heightPosition + thickness, startZ);

    glVertex3f(startX + length, heightPosition, startZ + width);
    glVertex3f(startX + length, heightPosition + thickness, startZ + width);

    glVertex3f(startX, heightPosition, startZ + width);
    glVertex3f(startX, heightPosition + thickness, startZ + width);

    glEnd();
}
