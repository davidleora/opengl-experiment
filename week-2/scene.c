#include <GL/glut.h>
#include <math.h>
#include <stdbool.h>
#include "scene.h"

GLuint floorTextureID;

void drawFloorWithGrid(float length, float width, float tileSize)
{
    glColor3f(0.2f, 0.8f, 0.2f);
    glBegin(GL_QUADS);
    glVertex3f(-3, -0.002f, -3);
    glVertex3f(length, -0.002f, -3);
    glVertex3f(length, -0.002f, width + 3);
    glVertex3f(-3, -0.002f, width + 3);
    glEnd();

    glColor3f(0.0f, 0.0f, 0.0f);
    glLineWidth(1.0f);

    glBegin(GL_LINES);

    for (float x = -3; x <= length; x += tileSize)
    {
        glVertex3f(x, -0.001f, -3);
        glVertex3f(x, -0.001f, width + 3);
    }

    for (float z = -3; z <= width + 3; z += tileSize)
    {
        glVertex3f(-3, -0.001f, z);
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

    // Bottom vertices
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

void drawCustomFloor(float startX, float startZ, float endX, float endZ, float startHeight, float endHeight)
{
    glColor3f(0.5f, 0.5f, 0.5f);
    glBegin(GL_QUADS);

    // Bottom face
    glVertex3f(startX, startHeight, startZ); // Bottom-left
    glVertex3f(endX, startHeight, startZ);   // Bottom-right
    glVertex3f(endX, startHeight, endZ);     // Top-right
    glVertex3f(startX, startHeight, endZ);   // Top-left

    // Top face
    glVertex3f(startX, endHeight, startZ); // Bottom-left
    glVertex3f(endX, endHeight, startZ);   // Bottom-right
    glVertex3f(endX, endHeight, endZ);     // Top-right
    glVertex3f(startX, endHeight, endZ);   // Top-left

    // Front face
    glVertex3f(startX, startHeight, startZ); // Bottom-left
    glVertex3f(endX, startHeight, startZ);   // Bottom-right
    glVertex3f(endX, endHeight, startZ);     // Top-right
    glVertex3f(startX, endHeight, startZ);   // Top-left

    // Back face
    glVertex3f(startX, startHeight, endZ); // Bottom-left
    glVertex3f(endX, startHeight, endZ);   // Bottom-right
    glVertex3f(endX, endHeight, endZ);     // Top-right
    glVertex3f(startX, endHeight, endZ);   // Top-left

    // Left face
    glVertex3f(startX, startHeight, startZ); // Bottom-left
    glVertex3f(startX, startHeight, endZ);   // Bottom-right
    glVertex3f(startX, endHeight, endZ);     // Top-right
    glVertex3f(startX, endHeight, startZ);   // Top-left

    // Right face
    glVertex3f(endX, startHeight, startZ); // Bottom-left
    glVertex3f(endX, startHeight, endZ);   // Bottom-right
    glVertex3f(endX, endHeight, endZ);     // Top-right
    glVertex3f(endX, endHeight, startZ);   // Top-left

    glEnd();
}

void drawCustomTriangleFloor(float x1, float z1, float x2, float z2, float x3, float z3, float startHeight, float endHeight)
{
    glColor3f(0.5f, 0.5f, 0.5f);
    glBegin(GL_TRIANGLES);

    // Bottom face (flat at start height)
    glVertex3f(x1, startHeight, z1); // First point
    glVertex3f(x2, startHeight, z2); // Second point
    glVertex3f(x3, startHeight, z3); // Third point

    // Top face (flat at end height)
    glVertex3f(x1, endHeight, z1); // First point
    glVertex3f(x2, endHeight, z2); // Second point
    glVertex3f(x3, endHeight, z3); // Third point

    glEnd();

    glBegin(GL_QUADS);

    // Side faces
    glVertex3f(x1, startHeight, z1);
    glVertex3f(x1, endHeight, z1);
    glVertex3f(x2, endHeight, z2);
    glVertex3f(x2, startHeight, z2);

    glVertex3f(x2, startHeight, z2);
    glVertex3f(x2, endHeight, z2);
    glVertex3f(x3, endHeight, z3);
    glVertex3f(x3, startHeight, z3);

    glVertex3f(x3, startHeight, z3);
    glVertex3f(x3, endHeight, z3);
    glVertex3f(x1, endHeight, z1);
    glVertex3f(x1, startHeight, z1);

    glEnd();

    glColor3f(0.0f, 0.0f, 0.0f); // Black outline
    glLineWidth(2.0f);
    glBegin(GL_LINES);

    // Outline of the base
    glVertex3f(x1, startHeight, z1);
    glVertex3f(x2, startHeight, z2);

    glVertex3f(x2, startHeight, z2);
    glVertex3f(x3, startHeight, z3);

    glVertex3f(x3, startHeight, z3);
    glVertex3f(x1, startHeight, z1);

    // Outline of the top
    glVertex3f(x1, endHeight, z1);
    glVertex3f(x2, endHeight, z2);

    glVertex3f(x2, endHeight, z2);
    glVertex3f(x3, endHeight, z3);

    glVertex3f(x3, endHeight, z3);
    glVertex3f(x1, endHeight, z1);

    // Vertical edges
    glVertex3f(x1, startHeight, z1);
    glVertex3f(x1, endHeight, z1);

    glVertex3f(x2, startHeight, z2);
    glVertex3f(x2, endHeight, z2);

    glVertex3f(x3, startHeight, z3);
    glVertex3f(x3, endHeight, z3);

    glEnd();
}

void drawCustomBlock(float startX, float startZ, float endX, float endZ, float thickness, float startHeight, float height)
{
    float dx = endX - startX;
    float dz = endZ - startZ;
    float length = sqrt(dx * dx + dz * dz);

    dx /= length;
    dz /= length;

    float perpX = -dz * thickness / 2.0f;
    float perpZ = dx * thickness / 2.0f;

    float topHeight = startHeight + height;

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
}

void drawTexturedFloor(float startX, float startZ, float endX, float endZ, float height)
{
    float tileWidth = 2.0f;
    float tileLength = 5.0f;

    float width = endX - startX;  // size in X direction
    float length = endZ - startZ; // size in Z direction
    float uRepeat = length / tileWidth;
    float vRepeat = width / tileLength;

    // Set color to white so we see the texture unmodified
    glColor3f(1.0f, 1.0f, 1.0f);

    // Enable texturing
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, floorTextureID);

    // Draw the floor with the correct texture coordinates
    glBegin(GL_QUADS);
    // Bottom-left corner
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(startX, height, endZ);

    // Bottom-right corner
    glTexCoord2f(uRepeat, 0.0f);
    glVertex3f(startX, height, startZ);

    // Top-right corner
    glTexCoord2f(uRepeat, vRepeat);
    glVertex3f(endX, height, startZ);

    // Top-left corner
    glTexCoord2f(0.0f, vRepeat);
    glVertex3f(endX, height, endZ);
    glEnd();

    // Disable texturing (so subsequent objects won’t be textured)
    glDisable(GL_TEXTURE_2D);
}

void drawGlassPanel(float startX, float startZ, float endX, float endZ, float bottomHeight, float topHeight)
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    // glDepthMask(GL_FALSE);
    glColor4f(0.7f, 0.85f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
    glVertex3f(startX, bottomHeight, startZ);
    glVertex3f(startX, topHeight, startZ);
    glVertex3f(endX, topHeight, endZ);
    glVertex3f(endX, bottomHeight, endZ);
    glEnd();
    // glDepthMask(GL_TRUE);
    glDisable(GL_BLEND);
}

void drawOpaquePanel(float startX, float startZ, float endX, float endZ, float bottomHeight, float topHeight)
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    // glDepthMask(GL_FALSE);
    glColor4f(0.9f, 0.9f, 0.9f, 1.0f);
    glBegin(GL_QUADS);
    glVertex3f(startX, bottomHeight, startZ);
    glVertex3f(startX, topHeight, startZ);
    glVertex3f(endX, topHeight, endZ);
    glVertex3f(endX, bottomHeight, endZ);
    glEnd();
    // glDepthMask(GL_TRUE);
    glDisable(GL_BLEND);
}

void drawCustomCeiling(float startX, float startZ, float endX, float endZ, float height, float thickness)
{
    glColor3f(0.8f, 0.8f, 0.8f);
    glBegin(GL_QUADS);

    // Bottom face (visible from below)
    glVertex3f(startX, height, startZ); // Bottom-left
    glVertex3f(endX, height, startZ);   // Bottom-right
    glVertex3f(endX, height, endZ);     // Top-right
    glVertex3f(startX, height, endZ);   // Top-left

    // Top face (thickness makes this visible from above)
    glVertex3f(startX, height + thickness, startZ); // Bottom-left
    glVertex3f(endX, height + thickness, startZ);   // Bottom-right
    glVertex3f(endX, height + thickness, endZ);     // Top-right
    glVertex3f(startX, height + thickness, endZ);   // Top-left

    // Front face
    glVertex3f(startX, height, startZ);             // Bottom-left
    glVertex3f(endX, height, startZ);               // Bottom-right
    glVertex3f(endX, height + thickness, startZ);   // Top-right
    glVertex3f(startX, height + thickness, startZ); // Top-left

    // Back face
    glVertex3f(startX, height, endZ);             // Bottom-left
    glVertex3f(endX, height, endZ);               // Bottom-right
    glVertex3f(endX, height + thickness, endZ);   // Top-right
    glVertex3f(startX, height + thickness, endZ); // Top-left

    // Left face
    glVertex3f(startX, height, startZ);             // Bottom-left
    glVertex3f(startX, height, endZ);               // Bottom-right
    glVertex3f(startX, height + thickness, endZ);   // Top-right
    glVertex3f(startX, height + thickness, startZ); // Top-left

    // Right face
    glVertex3f(endX, height, startZ);             // Bottom-left
    glVertex3f(endX, height, endZ);               // Bottom-right
    glVertex3f(endX, height + thickness, endZ);   // Top-right
    glVertex3f(endX, height + thickness, startZ); // Top-left

    glEnd();

    glColor3f(0.0f, 0.0f, 0.0f); // Black outline
    glLineWidth(2.0f);
    glBegin(GL_LINES);

    // Bottom edges
    glVertex3f(startX, height, startZ);
    glVertex3f(endX, height, startZ);

    glVertex3f(endX, height, startZ);
    glVertex3f(endX, height, endZ);

    glVertex3f(endX, height, endZ);
    glVertex3f(startX, height, endZ);

    glVertex3f(startX, height, endZ);
    glVertex3f(startX, height, startZ);

    // Top edges
    glVertex3f(startX, height + thickness, startZ);
    glVertex3f(endX, height + thickness, startZ);

    glVertex3f(endX, height + thickness, startZ);
    glVertex3f(endX, height + thickness, endZ);

    glVertex3f(endX, height + thickness, endZ);
    glVertex3f(startX, height + thickness, endZ);

    glVertex3f(startX, height + thickness, endZ);
    glVertex3f(startX, height + thickness, startZ);

    // Vertical edges
    glVertex3f(startX, height, startZ);
    glVertex3f(startX, height + thickness, startZ);

    glVertex3f(endX, height, startZ);
    glVertex3f(endX, height + thickness, startZ);

    glVertex3f(endX, height, endZ);
    glVertex3f(endX, height + thickness, endZ);

    glVertex3f(startX, height, endZ);
    glVertex3f(startX, height + thickness, endZ);

    glEnd();
}

void drawCustomTriangleWallWithStartHeight(float startX, float startZ, float endX, float endZ, float thickness, float startHeight, float height)
{
    // Calculate the direction vector of the wall
    float dx = endX - startX;
    float dz = endZ - startZ;
    float length = sqrt(dx * dx + dz * dz);

    // Normalize the direction vector
    dx /= length;
    dz /= length;

    // Perpendicular vector for base thickness
    float perpX = -dz * thickness / 2.0f;
    float perpZ = dx * thickness / 2.0f;

    float topHeight = startHeight + height;

    // Adjust the apex position to maintain thickness
    float apexX = (startX + endX) / 2.0f;
    float apexZ = (startZ + endZ) / 2.0f;
    float apexOffsetX = -dz * thickness / 2.0f;
    float apexOffsetZ = dx * thickness / 2.0f;

    glColor3f(1.0f, 1.0f, 1.0f);

    // Draw the two side faces (triangles)
    glBegin(GL_TRIANGLES);

    // Left side face
    glVertex3f(startX + perpX, startHeight, startZ + perpZ);         // Bottom-left at start
    glVertex3f(endX + perpX, startHeight, endZ + perpZ);             // Bottom-left at end
    glVertex3f(apexX + apexOffsetX, topHeight, apexZ + apexOffsetZ); // Apex

    // Right side face
    glVertex3f(endX - perpX, startHeight, endZ - perpZ);             // Bottom-right at end
    glVertex3f(startX - perpX, startHeight, startZ - perpZ);         // Bottom-right at start
    glVertex3f(apexX - apexOffsetX, topHeight, apexZ - apexOffsetZ); // Apex

    glEnd();

    // Draw the base face (optional)
    glBegin(GL_QUADS);

    glVertex3f(startX + perpX, startHeight, startZ + perpZ); // Bottom-left at start
    glVertex3f(startX - perpX, startHeight, startZ - perpZ); // Bottom-right at start
    glVertex3f(endX - perpX, startHeight, endZ - perpZ);     // Bottom-right at end
    glVertex3f(endX + perpX, startHeight, endZ + perpZ);     // Bottom-left at end

    glEnd();

    // Draw the outline (edges)
    glColor3f(0.0f, 0.0f, 0.0f); // Black outline
    glLineWidth(2.0f);
    glBegin(GL_LINES);

    // Base edges
    glVertex3f(startX + perpX, startHeight, startZ + perpZ);
    glVertex3f(startX - perpX, startHeight, startZ - perpZ);

    glVertex3f(startX - perpX, startHeight, startZ - perpZ);
    glVertex3f(endX - perpX, startHeight, endZ - perpZ);

    glVertex3f(endX - perpX, startHeight, endZ - perpZ);
    glVertex3f(endX + perpX, startHeight, endZ + perpZ);

    glVertex3f(endX + perpX, startHeight, endZ + perpZ);
    glVertex3f(startX + perpX, startHeight, startZ + perpZ);

    // Left edge to apex
    glVertex3f(startX + perpX, startHeight, startZ + perpZ);
    glVertex3f(apexX + apexOffsetX, topHeight, apexZ + apexOffsetZ);

    glVertex3f(endX + perpX, startHeight, endZ + perpZ);
    glVertex3f(apexX + apexOffsetX, topHeight, apexZ + apexOffsetZ);

    // Right edge to apex
    glVertex3f(startX - perpX, startHeight, startZ - perpZ);
    glVertex3f(apexX - apexOffsetX, topHeight, apexZ - apexOffsetZ);

    glVertex3f(endX - perpX, startHeight, endZ - perpZ);
    glVertex3f(apexX - apexOffsetX, topHeight, apexZ - apexOffsetZ);

    glEnd();
}

void drawQuadRoofSegment(float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3, float x4, float y4, float z4, float roofThickness, float colorRed, float colorGreen, float colorBlue)
{
    float x1t = x1, y1t = y1 + roofThickness, z1t = z1;
    float x2t = x2, y2t = y2 + roofThickness, z2t = z2;
    float x3t = x3, y3t = y3 + roofThickness, z3t = z3;
    float x4t = x4, y4t = y4 + roofThickness, z4t = z4;

    glColor3f(colorRed, colorGreen, colorBlue);

    // Top face
    glBegin(GL_QUADS);
    glVertex3f(x1t, y1t, z1t);
    glVertex3f(x2t, y2t, z2t);
    glVertex3f(x3t, y3t, z3t);
    glVertex3f(x4t, y4t, z4t);
    glEnd();

    // Bottom face
    glBegin(GL_QUADS);
    glVertex3f(x1, y1, z1);
    glVertex3f(x4, y4, z4);
    glVertex3f(x3, y3, z3);
    glVertex3f(x2, y2, z2);
    glEnd();

    // Side #1 (corners 1-2)
    glBegin(GL_QUADS);
    glVertex3f(x1, y1, z1);
    glVertex3f(x2, y2, z2);
    glVertex3f(x2t, y2t, z2t);
    glVertex3f(x1t, y1t, z1t);
    glEnd();

    // Side #2 (corners 2-3)
    glBegin(GL_QUADS);
    glVertex3f(x2, y2, z2);
    glVertex3f(x3, y3, z3);
    glVertex3f(x3t, y3t, z3t);
    glVertex3f(x2t, y2t, z2t);
    glEnd();

    // Side #3 (corners 3-4)
    glBegin(GL_QUADS);
    glVertex3f(x3, y3, z3);
    glVertex3f(x4, y4, z4);
    glVertex3f(x4t, y4t, z4t);
    glVertex3f(x3t, y3t, z3t);
    glEnd();

    // Side #4 (corners 4-1)
    glBegin(GL_QUADS);
    glVertex3f(x4, y4, z4);
    glVertex3f(x1, y1, z1);
    glVertex3f(x1t, y1t, z1t);
    glVertex3f(x4t, y4t, z4t);
    glEnd();

    glColor3f(0.0f, 0.0f, 0.0f);
    glLineWidth(2.0f);
    glBegin(GL_LINES);
    // Top edges
    glVertex3f(x1t, y1t, z1t);
    glVertex3f(x2t, y2t, z2t);
    glVertex3f(x2t, y2t, z2t);
    glVertex3f(x3t, y3t, z3t);
    glVertex3f(x3t, y3t, z3t);
    glVertex3f(x4t, y4t, z4t);
    glVertex3f(x4t, y4t, z4t);
    glVertex3f(x1t, y1t, z1t);

    // Bottom edges
    glVertex3f(x1, y1, z1);
    glVertex3f(x2, y2, z2);
    glVertex3f(x2, y2, z2);
    glVertex3f(x3, y3, z3);
    glVertex3f(x3, y3, z3);
    glVertex3f(x4, y4, z4);
    glVertex3f(x4, y4, z4);
    glVertex3f(x1, y1, z1);

    // Verticals
    glVertex3f(x1, y1, z1);
    glVertex3f(x1t, y1t, z1t);
    glVertex3f(x2, y2, z2);
    glVertex3f(x2t, y2t, z2t);
    glVertex3f(x3, y3, z3);
    glVertex3f(x3t, y3t, z3t);
    glVertex3f(x4, y4, z4);
    glVertex3f(x4t, y4t, z4t);
    glEnd();
}

void drawOuterWindowFrame(float startX, float startZ, float endX, float endZ, float startY, float endY, float thickness)
{
    glColor3f(112.0f / 255.0f, 123.0f / 255.0f, 124.0f / 255.0f);

    if (startX == endX)
    {
        drawCustomBlock(startX, startZ, endX, endZ, thickness, endY - 0.1f, 0.1f);
        drawCustomBlock(startX, startZ, endX, endZ, thickness, startY, 0.1f);
        drawCustomBlock(startX, startZ, endX, startZ + 0.1f, thickness, startY, endY - startY);
        drawCustomBlock(startX, endZ - 0.1f, endX, endZ, thickness, startY, endY - startY);
    }
    else if (startZ == endZ)
    {
        drawCustomBlock(startX, startZ, endX, endZ, thickness, endY - 0.1f, 0.1f);
        drawCustomBlock(startX, startZ, endX, endZ, thickness, startY, 0.1f);
        drawCustomBlock(startX, startZ, startX + 0.1f, endZ, thickness, startY, endY - startY);
        drawCustomBlock(endX - 0.1f, startZ, endX, endZ, thickness, startY, endY - startY);
    }
}

void drawOuterDoorFrame(float startX, float startZ, float endX, float endZ, float startY, float endY, float thickness)
{
    glColor3f(135.0f / 255.0f, 54.0f / 255.0f, 0.0f);

    if (startX == endX)
    {
        drawCustomBlock(startX, startZ, endX, endZ, thickness, endY - 0.1f, 0.1f);
        drawCustomBlock(startX, startZ, endX, endZ, thickness, startY, 0.1f);
        drawCustomBlock(startX, startZ, endX, startZ + 0.1f, thickness, startY, endY - startY);
        drawCustomBlock(startX, endZ - 0.1f, endX, endZ, thickness, startY, endY - startY);
    }
    else if (startZ == endZ)
    {
        drawCustomBlock(startX, startZ, endX, endZ, thickness, endY - 0.1f, 0.1f);
        drawCustomBlock(startX, startZ, endX, endZ, thickness, startY, 0.1f);
        drawCustomBlock(startX, startZ, startX + 0.1f, endZ, thickness, startY, endY - startY);
        drawCustomBlock(endX - 0.1f, startZ, endX, endZ, thickness, startY, endY - startY);
    }
}

void drawInnerWindowFrame(float startX, float startZ, float endX, float endZ, float startY, float endY, float thickness, char windowType)
{
    glColor3f(153.0f / 255.0f, 163.0f / 255.0f, 164.0f / 255.0f);

    if (startX == endX)
    {
        float midZ = (startZ + endZ) / 2.0f;
        drawCustomBlock(startX, startZ + 0.1f, endX, midZ, thickness / 8.0f, startY + 0.1f, thickness / 8.0f);
        drawCustomBlock(startX, startZ + 0.1f, endX, midZ, thickness / 8.0f, endY - 0.1f - thickness / 8.0f, thickness / 8.0f);
        if (windowType == 'A' || windowType == 'B')
        {
            drawCustomBlock(startX, startZ + 0.1f, endX, startZ + 0.2f, thickness / 8.0f, startY + 0.1f, endY - startY - 0.2f);
            drawCustomBlock(startX, midZ, endX, midZ - 0.1f, thickness / 8.0f, startY + 0.1f, endY - startY - 0.2f);
        }
        if (windowType == 'A' || windowType == 'C')
        {
            drawCustomBlock(startX, startZ + 0.1f, endX, midZ, thickness / 8.0f, (endY + startY) / 2 - thickness / 8.0f, thickness / 4.0f);
        }

        drawCustomBlock(startX, midZ, endX, endZ - 0.1f, thickness / 8.0f, startY + 0.1f, thickness / 8.0f);
        drawCustomBlock(startX, midZ, endX, endZ - 0.1f, thickness / 8.0f, endY - 0.1f - thickness / 8.0f, thickness / 8.0f);
        if (windowType == 'A' || windowType == 'B')
        {
            drawCustomBlock(startX, midZ, endX, midZ + 0.1f, thickness / 8.0f, startY + 0.1f, endY - startY - 0.2f);
            drawCustomBlock(startX, endZ - 0.2f, endX, endZ - 0.1f, thickness / 8.0f, startY + 0.1f, endY - startY - 0.2f);
        }
        if (windowType == 'A' || windowType == 'C')
        {
            drawCustomBlock(startX, midZ, endX, endZ - 0.1f, thickness / 8.0f, (endY + startY) / 2 - thickness / 8.0f, thickness / 4.0f);
        }

        drawGlassPanel(startX, startZ, endX, midZ, startY, endY);
        drawGlassPanel(startX, midZ, endX, endZ, startY, endY);
    }
    else if (startZ == endZ)
    {
        float midX = (startX + endX) / 2.0f;
        drawCustomBlock(startX + 0.1f, startZ, midX, endZ, thickness / 8.0f, startY + 0.1f, thickness / 8.0f);
        drawCustomBlock(startX + 0.1f, startZ, midX, endZ, thickness / 8.0f, endY - 0.1f - thickness / 8.0f, thickness / 8.0f);
        if (windowType == 'A' || windowType == 'B')
        {
            drawCustomBlock(startX + 0.1f, startZ, startX + 0.2f, endZ, thickness / 8.0f, startY + 0.1f, endY - startY - 0.2f);
            drawCustomBlock(midX, startZ, midX - 0.1f, endZ, thickness / 8.0f, startY + 0.1f, endY - startY - 0.2f);
        }
        if (windowType == 'A' || windowType == 'C')
        {
            drawCustomBlock(startX + 0.1f, startZ, midX, endZ, thickness / 8.0f, (endY + startY) / 2 - thickness / 8.0f, thickness / 4.0f);
        }

        drawCustomBlock(midX, startZ, endX - 0.1f, endZ, thickness / 8.0f, startY + 0.1f, thickness / 8.0f);
        drawCustomBlock(midX, startZ, endX - 0.1f, endZ, thickness / 8.0f, endY - 0.1f - thickness / 8.0f, thickness / 8.0f);
        if (windowType == 'A' || windowType == 'B')
        {
            drawCustomBlock(midX, startZ, midX + 0.1f, endZ, thickness / 8.0f, startY + 0.1f, endY - startY - 0.2f);
            drawCustomBlock(endX - 0.2f, startZ, endX - 0.1f, endZ, thickness / 8.0f, startY + 0.1f, endY - startY - 0.2f);
        }
        if (windowType == 'A' || windowType == 'C')
        {
            drawCustomBlock(midX, startZ, endX - 0.1f, endZ, thickness / 4.0f, (endY + startY) / 2 - thickness / 8.0f, thickness / 4.0f);
        }

        drawGlassPanel(startX, startZ, midX, endZ, startY, endY);
        drawGlassPanel(midX, startZ, endX, endZ, startY, endY);
    }
}

void drawInnerWindowFrame2(float startX, float startZ, float endX, float endZ, float startY, float endY, float thickness)
{
    glColor3f(153.0f / 255.0f, 163.0f / 255.0f, 164.0f / 255.0f);

    float midX = (startX + endX) / 2.0f;
    drawCustomBlock(startX + 0.1f, startZ, midX, endZ, thickness / 2.0f, startY + 0.1f, thickness / 2.0f);
    drawCustomBlock(startX + 0.1f, startZ, midX, endZ, thickness / 2.0f, endY - 0.1f - thickness / 2.0f, thickness / 2.0f);
    drawCustomBlock(startX + 0.1f, startZ, startX + 0.1f + thickness / 2.0f, endZ, thickness / 2.0f, startY + 0.1f, endY - startY - 0.2f);
    drawCustomBlock(midX, startZ, midX - thickness / 2.0f, endZ, thickness / 2.0f, startY + 0.1f, endY - startY - 0.2f);
    drawCustomBlock(startX + 0.1f, startZ, midX, endZ, thickness / 2.0f, (endY + startY) / 2 - thickness / 4.0f, thickness / 2.0f);

    drawCustomBlock(midX, startZ, endX - 0.1f, endZ, thickness / 2.0f, startY + 0.1f, thickness / 2.0f);
    drawCustomBlock(midX, startZ, endX - 0.1f, endZ, thickness / 2.0f, endY - 0.1f - thickness / 2.0f, thickness / 2.0f);
    drawCustomBlock(midX, startZ, midX + thickness / 2.0f, endZ, thickness / 2.0f, startY + 0.1f, endY - startY - 0.2f);
    drawCustomBlock(endX - 0.1f - thickness / 2.0f, startZ, endX - 0.1f, endZ, thickness / 2.0f, startY + 0.1f, endY - startY - 0.2f);
    drawCustomBlock(midX, startZ, endX - 0.1f, endZ, thickness / 2.0f, (endY + startY) / 2 - thickness / 4.0f, thickness / 2.0f);

    drawGlassPanel(startX, startZ, midX, endZ, startY, endY);
    drawGlassPanel(midX, startZ, endX, endZ, startY, endY);
}

void drawCustomWindowA(float startX, float startZ, float endX, float endZ, float startY, float endY, float thickness)
{
    drawOuterWindowFrame(startX, startZ, endX, endZ, startY, endY, thickness);
    drawInnerWindowFrame(startX, startZ, endX, endZ, startY, endY, thickness, 'A');
}

void drawCustomWindowB(float startX, float startZ, float endX, float endZ, float startY, float endY, float thickness)
{
    drawOuterWindowFrame(startX, startZ, endX, endZ, startY, endY, thickness);
    drawInnerWindowFrame(startX, startZ, endX, endZ, startY, endY, thickness, 'B');
}

void drawCustomWindowC(float startX, float startZ, float endX, float endZ, float startY, float endY, float thickness)
{
    drawOuterWindowFrame(startX, startZ, endX, endZ, startY, endY, thickness);
    drawInnerWindowFrame(startX, startZ, endX, endZ, startY, endY, thickness, 'C');
}

void drawGlassSlidingDoor(float startX, float startZ, float endX, float endZ, float startY, float endY, float thickness)
{
    drawOuterWindowFrame(startX, startZ, endX, endZ, startY, endY, thickness);
    drawInnerWindowFrame2(startX, startZ, endX, endZ, startY, endY, thickness);
}

void drawMainDoorFrame(float startX, float startZ, float endX, float endZ, float startY, float endY, float thickness)
{

    float midZ = (startZ + endZ) / 2.0f;
    glColor3f(123.0f / 255.0f, 36.0f / 255.0f, 28.0f / 255.0f);
    if (startX == endX)
    {
        drawCustomBlock(startX, startZ, endX, endZ, thickness, endY - 0.1f, 0.1f);
        drawCustomBlock(startX, startZ, endX, endZ, thickness, startY, 0.1f);
        drawCustomBlock(startX, startZ, endX, startZ + 0.1f, thickness, startY, endY - startY);
        drawCustomBlock(startX, endZ - 0.1f, endX, endZ, thickness, startY, endY - startY);
    }
    else if (startZ == endZ)
    {
        drawCustomBlock(startX, startZ, endX, endZ, thickness, endY - 0.1f, 0.1f);
        drawCustomBlock(startX, startZ, endX, endZ, thickness, startY, 0.1f);
        drawCustomBlock(startX, startZ, startX + 0.1f, endZ, thickness, startY, endY - startY);
        drawCustomBlock(endX - 0.1f, startZ, endX, endZ, thickness, startY, endY - startY);
    }

    glColor3f(169.0f / 255.0f, 50.0f / 255.0f, 38.0f / 255.0f);
    drawCustomBlock(startX, startZ + 0.1f, endX, endZ - 0.1f, thickness / 2, 1.8f, 0.1f);
    drawCustomBlock(startX, midZ - 0.05f, endX, midZ + 0.05f, thickness / 2, 1.9f, 0.3f);
    drawCustomBlock(startX, startZ + 0.66f, endX, startZ + 0.76f, thickness / 2, 0.0f, 1.8f);
    drawCustomBlock(startX, startZ + 0.1f, endX, startZ + 0.66f, thickness / 2, 1.6f, 0.05f);
    drawCustomBlock(startX, startZ + 0.1f, endX, startZ + 0.66f, thickness / 2, 1.4f, 0.05);
    drawCustomBlock(startX, startZ + 0.1f, endX, startZ + 0.66f, thickness / 2, 1.2f, 0.05);
    drawCustomBlock(startX, startZ + 0.1f, endX, startZ + 0.66f, thickness / 2, 1.0f, 0.05);
    drawCustomBlock(startX, startZ + 0.1f, endX, startZ + 0.66f, thickness / 2, 0.8f, 0.05);
    drawCustomBlock(startX, startZ + 0.1f, endX, startZ + 0.66f, thickness / 2, 0.6f, 0.05);
    drawCustomBlock(startX, startZ + 0.1f, endX, startZ + 0.66f, thickness / 2, 0.4f, 0.05);
    drawCustomBlock(startX, startZ + 0.1f, endX, startZ + 0.66f, thickness / 2, 0.0f, 0.25);

    drawGlassPanel(startX, startZ + 0.1f, endX, startZ + 0.66f, 0.0f, 1.8f);
    drawGlassPanel(startX, startZ, endX, endZ, 1.9f, 2.2f);
}

void drawDoorTypeA(float startX, float startZ, float endX, float endZ, float startY, float endY, float thickness)
{
    if (startZ == endZ)
    {
        drawCustomBlock(startX, startZ, endX, endZ, thickness, startY, thickness);
        drawCustomBlock(startX, startZ, endX, endZ, thickness, endY - thickness, thickness);
        drawCustomBlock(startX, startZ, startX + thickness, endZ, thickness, startY, endY - startY);
        drawCustomBlock(endX - thickness, startZ, endX, endZ, thickness, startY, endY - startY);

        drawCustomBlock(startX + thickness, startZ, endX - thickness, startZ, thickness, startY + (endY - startY) / 3.0f, thickness / 2.0f);
        drawCustomBlock(startX + thickness, startZ, endX - thickness, startZ, thickness, startY + 2.0f * (endY - startY) / 3.0f, thickness / 2.0f);
        drawOpaquePanel(startX + thickness, startZ, endX - thickness, endZ, startY, endY);
    }
    else if (startX == endX)
    {
        drawCustomBlock(startX, startZ, endX, endZ, thickness, startY, thickness);
        drawCustomBlock(startX, startZ, endX, endZ, thickness, endY - thickness, thickness);
        drawCustomBlock(startX, startZ, startX, startZ + thickness, thickness, startY, endY - startY);
        drawCustomBlock(startX, endZ - thickness, endX, endZ, thickness, startY, endY - startY);

        drawCustomBlock(startX, startZ + thickness, startX, endZ - thickness, thickness, startY + (endY - startY) / 3.0f, thickness / 2.0f);
        drawCustomBlock(startX, startZ + thickness, startX, endZ - thickness, thickness, startY + 2.0f * (endY - startY) / 3.0f, thickness / 2.0f);
        drawOpaquePanel(startX, startZ + thickness, endX, endZ - thickness, startY, endY);
    }
}

void drawDoorTypeB(float startX, float startZ, float endX, float endZ, float startY, float endY, float thickness)
{
    glColor3f(205.0f / 255.0f, 97.0f / 255.0f, 85.0f / 255.0f);
    bool vertical = (startX == endX);
    float doorWidth = vertical ? fabsf(endZ - startZ) : fabsf(endX - startX);
    float doorHeight = endY - startY;
    float cutOutStartY = startY + doorHeight * 0.55f;
    float cutOutTopY = endY - 0.3f;
    float cutOutWidth = doorWidth * 0.375f;
    if (!vertical)
    {
        float doorZ = startZ;
        drawCustomBlock(startX, doorZ, endX, doorZ, thickness, cutOutTopY, endY - cutOutTopY);
        drawCustomBlock(startX, doorZ, endX, doorZ, thickness, startY, cutOutStartY - startY);
        drawCustomBlock(startX, doorZ, startX + cutOutWidth, doorZ, thickness, cutOutStartY, (cutOutTopY - cutOutStartY));
        drawCustomBlock(endX - cutOutWidth, doorZ, endX, doorZ, thickness, cutOutStartY, (cutOutTopY - cutOutStartY));
        drawGlassPanel(startX, doorZ, endX, doorZ, cutOutStartY, cutOutTopY);
    }
    else
    {
        float doorX = startX;
        drawCustomBlock(doorX, endZ, doorX, startZ, thickness, cutOutTopY, endY - cutOutTopY);
        drawCustomBlock(doorX, endZ, doorX, startZ, thickness, startY, cutOutStartY - startY);
        drawCustomBlock(doorX, startZ, doorX, startZ + cutOutWidth, thickness, cutOutStartY, (cutOutTopY - cutOutStartY));
        drawCustomBlock(doorX, endZ - cutOutWidth, doorX, endZ, thickness, cutOutStartY, (cutOutTopY - cutOutStartY));
        drawGlassPanel(doorX, endZ, doorX, startZ, cutOutStartY, cutOutTopY);
    }
}

void drawDoorTypeC(float startX, float startZ, float endX, float endZ, float startY, float endY, float thickness)
{
    glColor3f(211.0 / 255.0f, 84.0 / 255.0f, 0.0f);
    drawCustomBlock(startX, startZ, endX, endZ, thickness, startY, endY - startY);
}

void drawSlidingDoor(float startX, float startZ, float endX, float endZ, float startY, float endY, float thickness)
{
    thickness = thickness / 2.0f;
    if (startZ == endZ)
    {
        float mid = (startX + endX) / 2.0f;
        glColor3f(0.0f, 0.0f, 0.0f);
        drawCustomBlock(startX, startZ + 0.03f, mid, endZ + 0.03f, thickness + 0.1f, startY, thickness);
        drawCustomBlock(startX, startZ + 0.03f, mid, endZ + 0.03f, thickness + 0.1f, endY - thickness, thickness);
        drawCustomBlock(startX, startZ + 0.03f, startX + thickness, endZ + 0.03f, thickness + 0.1f, startY, endY - startY);
        drawCustomBlock(mid - thickness, startZ + 0.03f, mid, endZ + 0.03f, thickness + 0.1f, startY, endY - startY);

        glColor3f(1.0f, 1.0f, 1.0f);
        drawCustomBlock(startX + thickness - 0.01f, startZ + 0.03f, mid - thickness + 0.01f, endZ + 0.03f, thickness, startY + thickness, (endY - startY) / 3.0f);
        drawCustomBlock(startX + thickness - 0.01f, startZ + 0.03f, mid - thickness + 0.01f, endZ + 0.03f, thickness, startY + thickness + 2.0f * (endY - startY) / 3.0f, (endY - startY) / 3.0f);

        glColor3f(236.0f / 255.0f, 112.0f / 255.0f, 99.0f / 255.0f);
        drawCustomBlock(startX + thickness - 0.01f, startZ + 0.03f, mid - thickness + 0.01f, endZ + 0.03f, thickness, startY + thickness + (endY - startY) / 3.0f, (endY - startY) / 3.0f);

        glColor3f(0.0f, 0.0f, 0.0f);
        drawCustomBlock(mid, startZ - 0.03f, endX, endZ - 0.03f, thickness + 0.1f, startY, thickness);
        drawCustomBlock(mid, startZ - 0.03f, endX, endZ - 0.03f, thickness + 0.1f, endY - thickness, thickness);
        drawCustomBlock(mid, startZ - 0.03f, mid + thickness, endZ - 0.03f, thickness + 0.1f, startY, endY - startY);
        drawCustomBlock(endX - thickness, startZ - 0.03f, endX, endZ - 0.03f, thickness + 0.1f, startY, endY - startY);

        glColor3f(1.0f, 1.0f, 1.0f);
        drawCustomBlock(mid + thickness - 0.01f, startZ - 0.03f, endX - thickness + 0.01f, endZ - 0.03f, thickness, startY + thickness, (endY - startY) / 3.0f);
        drawCustomBlock(mid + thickness - 0.01f, startZ - 0.03f, endX - thickness + 0.01f, endZ - 0.03f, thickness, startY + thickness + 2.0f * (endY - startY) / 3.0f, (endY - startY) / 3.0f);

        glColor3f(236.0f / 255.0f, 112.0f / 255.0f, 99.0f / 255.0f);
        drawCustomBlock(mid + thickness - 0.01f, startZ - 0.03f, endX - thickness + 0.01f, endZ - 0.03f, thickness, startY + thickness + (endY - startY) / 3.0f, (endY - startY) / 3.0f);
    }
}