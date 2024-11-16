#include <GL/glut.h>
#include <math.h>
#include "doraemon.h"

// Draw Circle
void drawFlattenedCircle(float x, float y, float radius, float r, float g, float b, float flattenFactor)
{
    int numSegments = 100;
    float angle;

    // Draw the filled circle
    glColor3f(r, g, b);
    glBegin(GL_POLYGON);
    for (int i = 0; i < numSegments; i++)
    {
        angle = 2.0f * 3.14159f * i / numSegments;

        float dx = radius * cos(angle);
        float dy = radius * sin(angle);

        if (dy > 0)
        {
            dy *= (1.0 - flattenFactor);
        }

        glVertex2f(x + dx, y + dy);
    }
    glEnd();

    // Draw the black outline
    glColor3f(0.0, 0.0, 0.0);
    glLineWidth(2.0);
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < numSegments; i++)
    {
        angle = 2.0f * 3.14159f * i / numSegments;

        float dx = radius * cos(angle);
        float dy = radius * sin(angle);

        if (dy > 0)
        {
            dy *= (1.0 - flattenFactor);
        }

        glVertex2f(x + dx, y + dy);
    }
    glEnd();
}

void drawCircle(float x, float y, float radius, float r, float g, float b)
{
    int numSegments = 100;
    float angle;

    // Draw the filled circle
    glColor3f(r, g, b);
    glBegin(GL_POLYGON);
    for (int i = 0; i < numSegments; i++)
    {
        angle = 2.0f * 3.14159f * i / numSegments;

        float dx = radius * cos(angle);
        float dy = radius * sin(angle);

        glVertex2f(x + dx, y + dy);
    }
    glEnd();

    // Draw the black outline
    glColor3f(0.0, 0.0, 0.0);
    glLineWidth(2.0);
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < numSegments; i++)
    {
        angle = 2.0f * 3.14159f * i / numSegments;

        float dx = radius * cos(angle);
        float dy = radius * sin(angle);

        glVertex2f(x + dx, y + dy);
    }
    glEnd();
}

void drawCircleNoOutline(float x, float y, float radius, float r, float g, float b)
{
    int numSegments = 100;
    float angle;

    // Draw the filled circle
    glColor3f(r, g, b);
    glBegin(GL_POLYGON);
    for (int i = 0; i < numSegments; i++)
    {
        angle = 2.0f * 3.14159f * i / numSegments;

        float dx = radius * cos(angle);
        float dy = radius * sin(angle);

        glVertex2f(x + dx, y + dy);
    }
    glEnd();
}

// Draw Vertical Oval
void drawVerticalOval(float x, float y, float radiusX, float radiusY, float r, float g, float b)
{
    int numSegments = 100;
    float angle;

    glColor3f(r, g, b);
    glBegin(GL_POLYGON);
    for (int i = 0; i < numSegments; i++)
    {
        angle = 2.0f * 3.14159f * i / numSegments;

        float dx = radiusX * cos(angle);
        float dy = radiusY * sin(angle);

        glVertex2f(x + dx, y + dy);
    }
    glEnd();

    // Draw black outline
    glColor3f(0.0, 0.0, 0.0);
    glLineWidth(2.0);
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < numSegments; i++)
    {
        angle = 2.0f * 3.14159f * i / numSegments;
        float dx = radiusX * cos(angle);
        float dy = radiusY * sin(angle);
        glVertex2f(x + dx, y + dy);
    }
    glEnd();
}

void drawWink(float x, float y, float radiusX, float radiusY, int topHalf)
{
    int numSegments = 50;
    float angleStart = topHalf ? 0.0 : 3.14159;
    float angleEnd = topHalf ? 3.14159 : 2 * 3.14159;

    glColor3f(0.0, 0.0, 0.0);
    glLineWidth(2.5);
    glBegin(GL_LINE_STRIP);
    for (int i = 0; i <= numSegments; i++)
    {
        float angle = angleStart + (angleEnd - angleStart) * i / numSegments;
        float dx = radiusX * cos(angle);
        float dy = radiusY * sin(angle);
        glVertex2f(x + dx, y + dy);
    }
    glEnd();
}

// 1. Head
void drawHead()
{
    // TODO: Implement drawing of the main blue head and inner white head
    drawFlattenedCircle(0.0, 0.0, 0.6, 41.0 / 255.0, 134.0 / 255.0, 204.0 / 255.0, 0.05);
    drawFlattenedCircle(0.0, -0.035, 0.555, 1.0, 1.0, 1.0, 0.21);
}

// 2. Eyes
void drawEyes()
{
    // TODO: Implement drawing of the left eye, right eye, left pupil, right wink
    drawVerticalOval(-0.105, 0.43, 0.105, 0.12, 1.0, 1.0, 1.0);
    drawVerticalOval(0.105, 0.43, 0.105, 0.12, 1.0, 1.0, 1.0);
    drawVerticalOval(-0.05, 0.42, 0.03, 0.045, 0.0, 0.0, 0.0);
    drawVerticalOval(-0.04, 0.42, 0.01, 0.02, 1.0, 1.0, 1.0);
    drawWink(0.065, 0.40, 0.035, 0.04, 1);
}

// 3. Nose
void drawNose()
{
    // TODO: Implement drawing of the red nose and white inner nose
    drawCircle(0.0, 0.29, 0.067, 1.0, 0.0, 0.0);
    drawCircleNoOutline(-0.02, 0.31, 0.024, 1.0, 1.0, 1.0);
}

// 4. Mouth
void drawMouth()
{
    // TODO: Implement drawing of the vertical line and the smile
}

// 5. Moustache
void drawMoustache()
{
    // TODO: Implement drawing of the moustache
}

// 6. Collar
void drawCollar()
{
    float centerX = 0.0;
    float centerY = -0.35;
    float width = 0.97;
    float height = 0.05;

    float halfWidth = width / 2.0;
    float halfHeight = height / 2.0;
    float radiusX = halfWidth;
    float radiusY = halfHeight;

    float dyStep = 0.001; // Small step for smooth lines

    // Loop to draw stacked lines
    for (float j = 0; j <= height; j += dyStep)
    {
        glColor3f(1.0, 0.0, 0.0); // Red color

        // Draw a single horizontal strip
        glBegin(GL_LINE_STRIP);
        for (int i = 0; i <= 100; i++)
        {
            float angle = 3.14159 + (3.14159 * i / 100); // From 180° to 360°
            float dx = radiusX * cos(angle);
            float dy = radiusY * sin(angle);
            glVertex2f(centerX + dx, centerY + dy - j); // Stack vertically by subtracting j
        }
        glEnd();
    }

    // Draw black outline
    glColor3f(0.0, 0.0, 0.0);
    glLineWidth(2.0);

    glBegin(GL_LINE_LOOP);
    for (int i = 0; i <= 100; i++)
    {
        float angle = 3.14159 + (3.14159 * i / 100); // From 180° to 360°
        float dx = radiusX * cos(angle);
        float dy = radiusY * sin(angle);
        glVertex2f(centerX + dx, centerY + dy);
    }
    glVertex2f(centerX + halfWidth, centerY - halfHeight);
    for (int i = 0; i <= 100; i++)
    {
        float angle = (3.14159 * i / 100); // From 0° to 180°
        float dx = radiusX * cos(angle);
        float dy = radiusY * sin(angle);
        glVertex2f(centerX + dx, centerY - dy - height);
    }
    glVertex2f(centerX - halfWidth, centerY - halfHeight);
    glEnd();
}

// 7. Bell
void drawBell()
{
    // TODO: Implement drawing of the outer bell and inner bell
}

// 8. Cover the bottom part of the head
void coverBottomPart()
{
    glColor3f(173.0 / 255.0, 203.0 / 255.0, 241.0 / 255.0);

    glBegin(GL_QUADS);
    glVertex2f(-0.7, -0.61);
    glVertex2f(0.7, -0.61);
    glVertex2f(0.7, -0.4);
    glVertex2f(-0.7, -0.4);
    glEnd();
}