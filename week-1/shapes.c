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

// Draw Rounded Rectangle
void drawRoundedRect(float x, float y, float width, float height, float borderRadius, float r, float g, float b)
{
    int numSegments = 50; // 円の滑らかさを調整
    float angle;

    // 長方形部分を描画
    glColor3f(r, g, b);
    glBegin(GL_POLYGON);

    // 上辺（左から右）
    glVertex2f(x - width / 2 + borderRadius, y + height / 2);
    glVertex2f(x + width / 2 - borderRadius, y + height / 2);

    // 右辺（上から下）
    glVertex2f(x + width / 2, y + height / 2 - borderRadius);
    glVertex2f(x + width / 2, y - height / 2 + borderRadius);

    // 下辺（右から左）
    glVertex2f(x + width / 2 - borderRadius, y - height / 2);
    glVertex2f(x - width / 2 + borderRadius, y - height / 2);

    // 左辺（下から上）
    glVertex2f(x - width / 2, y - height / 2 + borderRadius);
    glVertex2f(x - width / 2, y + height / 2 - borderRadius);

    glEnd();

    // 四隅の円を描画
    glBegin(GL_POLYGON);

    // 左上
    for (int i = 0; i <= numSegments; i++)
    {
        angle = 3.14159f * i / (2 * numSegments); // 0° to 90°
        glVertex2f(x - width / 2 + borderRadius + borderRadius * cos(angle),
                   y + height / 2 - borderRadius + borderRadius * sin(angle));
    }

    // 右上
    for (int i = 0; i <= numSegments; i++)
    {
        angle = 3.14159f * (1 + i / (2.0 * numSegments)); // 90° to 180°
        glVertex2f(x + width / 2 - borderRadius + borderRadius * cos(angle),
                   y + height / 2 - borderRadius + borderRadius * sin(angle));
    }

    // 右下
    for (int i = 0; i <= numSegments; i++)
    {
        angle = 3.14159f * (2 + i / (2.0 * numSegments)); // 180° to 270°
        glVertex2f(x + width / 2 - borderRadius + borderRadius * cos(angle),
                   y - height / 2 + borderRadius + borderRadius * sin(angle));
    }

    // 左下
    for (int i = 0; i <= numSegments; i++)
    {
        angle = 3.14159f * (3 + i / (2.0 * numSegments)); // 270° to 360°
        glVertex2f(x - width / 2 + borderRadius + borderRadius * cos(angle),
                   y - height / 2 + borderRadius + borderRadius * sin(angle));
    }

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
