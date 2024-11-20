/*
 * shapes.c
 *
 * このソースコードは、ドラえもんの描画に使用される様々な形状を定義した関数を書いています。
 * 各関数は、特定の形状（円、楕円、ウィンクなど）を描画するために使用されます。
 *
 * 主な関数：
 * - `drawFlattenedCircle()`: 扁平な円（頭部）
 * - `drawCircle()`: 円
 * - `drawCircleNoOutline()`: 輪郭なしの円（鼻）
 * - `drawPlumpOval()`: 水平楕円
 * - `drawVerticalOval()`: 垂直楕円
 * - `drawEmphasizedHorizontalOval()`: 強調された水平楕円
 * - `drawMagicPocket()`: 四次元ポケット
 *
 */
#include <GL/glut.h>
#include <math.h>
#include "shapes.h"

// Draw Flattened Circle (Head)
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
    glLineWidth(3.0);
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

// Draw Circle
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
    glLineWidth(3.0);
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

// Draw Nose Inner Circle
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

// Draw a plain horizontal oval
void drawPlumpOval(float centerX, float centerY, float radiusX, float radiusY, float plumpFactor, float r, float g, float b)
{
    int numSegments = 100;
    float angle;

    // Fill the oval
    glColor3f(r, g, b);
    glBegin(GL_POLYGON);
    for (int i = 0; i <= numSegments; i++)
    {
        angle = 2.0f * 3.14159f * i / numSegments;
        float x = radiusX * cos(angle);
        float y = radiusY * sin(angle);

        if (y < 0)
        {
            y *= (1.0 + plumpFactor);
        }

        glVertex2f(centerX + x, centerY + y);
    }
    glEnd();

    // Outline the oval
    glColor3f(0.0f, 0.0f, 0.0f);
    glLineWidth(3.0f);
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i <= numSegments; i++)
    {
        angle = 2.0f * 3.14159f * i / numSegments;
        float x = radiusX * cos(angle);
        float y = radiusY * sin(angle);

        if (y < 0)
        {
            y *= (1.0 + plumpFactor);
        }

        glVertex2f(centerX + x, centerY + y);
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
    glLineWidth(3.0);
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

// Draw Emphasized Horizontal Oval
void drawEmphasizedHorizontalOval(float centerX, float centerY, float radiusX, float radiusY, float bulgeFactor, float r, float g, float b)
{
    int numSegments = 100;
    float angle;

    glColor3f(r, g, b);
    glBegin(GL_POLYGON);
    for (int i = 0; i <= numSegments; i++)
    {
        angle = 2.0f * 3.14159f * i / numSegments;
        float x = radiusX * cos(angle);
        float y = radiusY * sin(angle);

        if (y > 0)
        {
            x *= (1.0 + bulgeFactor * (y / radiusY));
        }

        glVertex2f(centerX + x, centerY + y);
    }
    glEnd();

    // Draw the outline
    glColor3f(0.0f, 0.0f, 0.0f);
    glLineWidth(3.0f);
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i <= numSegments; i++)
    {
        angle = 2.0f * 3.14159f * i / numSegments;
        float x = radiusX * cos(angle);
        float y = radiusY * sin(angle);

        if (y > 0)
        {
            x *= (1.0 + bulgeFactor * (y / radiusY));
        }

        glVertex2f(centerX + x, centerY + y);
    }
    glEnd();
}

// Draw Magic Pocket
void drawMagicPocket(float centerX, float centerY, float radiusX, float radiusY, float pocketDepth, float r, float g, float b)
{
    int numSegments = 100;
    float angle;

    // Draw the outline
    glColor3f(0.0f, 0.0f, 0.0f);
    glLineWidth(3.0f);
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i <= numSegments; i++)
    {
        angle = 3.14159f * i / numSegments;
        float x = radiusX * cos(angle);
        float y = radiusY * sin(angle);
        glVertex2f(centerX + x, centerY - y);
    }
    glVertex2f(centerX - radiusX, centerY + pocketDepth);
    glVertex2f(centerX + radiusX, centerY + pocketDepth);
    glEnd();
}

// Draw Right Eye Wink
void drawWink(float x, float y, float radiusX, float radiusY, int topHalf)
{
    int numSegments = 50;
    float angleStart = topHalf ? 0.0 : 3.14159;
    float angleEnd = topHalf ? 3.14159 : 2 * 3.14159;

    glColor3f(0.0, 0.0, 0.0);
    glLineWidth(3.0);
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
