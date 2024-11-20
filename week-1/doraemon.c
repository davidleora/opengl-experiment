/*
 * doraemon.c
 *
 * このソースコードは、ドラえもんの各パーツを描画するための関数を書いています。
 * その描画要素ごとに関数を分けています。
 * `shapes.h`の図形描画ヘルパー関数を活用して具体的な形を作成しています。
 *
 * 主な関数：
 * - `drawHead()`: 頭部を描画（青い部分と白い部分）
 * - `drawEyes()`: 目を描画（左目、右目、左瞳、右ウインク）
 * - `drawNose()`: 鼻を描画（赤い部分と白い部分）
 * - `drawMouth()`: 口を描画（縦線と笑顔）
 * - `drawMoustache()`: ヒゲを左右それぞれ３本ずつ描画
 * - `drawCollar()`: 赤い首輪を描画
 * - `drawBell()`: 鈴を描画（外側と内側）
 * - `drawBody()`: 体を描画（青い部分と白い部分、四次元ポケットも含む）
 * - `drawHand()`: 手を描画（右手と左手）
 * - `drawLegs()`: 脚を描画（右足と左足）
 * - `drawShadow()`: 影を描画
 *
 */
#include <GL/glut.h>
#include "doraemon.h"
#include "shapes.h"
#include <math.h>

// 1. Head
void drawHead()
{
    // TODO: Implement drawing of the main blue head and inner white head
    drawFlattenedCircle(0.0, 0.0, 0.6, 41.0 / 255.0, 134.0 / 255.0, 204.0 / 255.0, 0.05);
    drawFlattenedCircle(0.0, -0.033, 0.56, 1.0, 1.0, 1.0, 0.21);
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

    glColor3f(0.0, 0.0, 0.0);
    glLineWidth(3.0);
    glBegin(GL_LINES);
    glVertex2f(0.0, 0.22);
    glVertex2f(0.0, -0.23);
    glEnd();
}

// 4. Mouth
void drawMouth()
{
    // TODO: Implement drawing of the vertical line and the smile
    glColor3f(0.0, 0.0, 0.0);
    glLineWidth(3.0);
    glBegin(GL_LINE_STRIP);

    int numSegments = 100;
    float centerX = 0.0;
    float centerY = 0.37;
    float radius = 0.52;
    float startAngle = 3.14159 * 2 / 11;
    float endAngle = 3.14159 * 9 / 11;
    float deepnessFactor = 1.15;

    for (int i = 0; i <= numSegments; i++)
    {
        float angle = startAngle + (endAngle - startAngle) * i / numSegments;
        float x = radius * cos(angle);
        float y = radius * sin(angle);

        if (y > 0)
        {
            y *= deepnessFactor;
        }

        glVertex2f(centerX + x, centerY - y);
    }
    glEnd();
}

// 5. Whiskers
void drawMoustache()
{
    // TODO: Implement drawing of the moustache
    glColor3f(0.0, 0.0, 0.0);
    glLineWidth(3.0);

    glBegin(GL_LINES);

    // Top left whisker
    glVertex2f(-0.1, 0.2);
    glVertex2f(-0.42, 0.28);

    // Middle left whisker
    glVertex2f(-0.1, 0.1);
    glVertex2f(-0.5, 0.11);

    // Bottom left whisker
    glVertex2f(-0.1, 0.0);
    glVertex2f(-0.47, -0.07);

    // Top right whisker
    glVertex2f(0.1, 0.2);
    glVertex2f(0.42, 0.28);

    // Middle right whisker
    glVertex2f(0.1, 0.1);
    glVertex2f(0.5, 0.11);

    // Bottom right whisker
    glVertex2f(0.1, 0.0);
    glVertex2f(0.47, -0.07);

    glEnd();
}

// 6. Collar
void drawCollar()
{
    // TODO: Implement drawing of the collar
    float centerX = 0.0;
    float centerY = -0.35;
    float width = 0.97;
    float height = 0.06;

    float halfWidth = width / 2.0;
    float halfHeight = height / 2.0;
    float radiusX = halfWidth;
    float radiusY = halfHeight;

    float dyStep = 0.001;

    for (float j = 0; j <= height; j += dyStep)
    {
        glColor3f(1.0, 0.0, 0.0); // Red color

        glBegin(GL_LINE_STRIP);
        for (int i = 0; i <= 100; i++)
        {
            float angle = 3.14159 + (3.14159 * i / 100); // From 180° to 360°
            float dx = radiusX * cos(angle);
            float dy = radiusY * sin(angle);
            glVertex2f(centerX + dx, centerY + dy - j);
        }
        glEnd();
    }

    // Draw black outline
    glColor3f(0.0, 0.0, 0.0);
    glLineWidth(3.0);

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

    // Outer bell (yellow)
    drawCircle(0.0, -0.48, 0.09, 1.0, 215.0 / 255.0, 0.0);

    // Inner black circle
    drawCircle(0.0, -0.50, 0.023, 0.0, 0.0, 0.0);

    // Small black line
    glColor3f(0.0, 0.0, 0.0);
    glLineWidth(3.0);
    glBegin(GL_LINES);
    glVertex2f(0.0, -0.485);
    glVertex2f(0.0, -0.57);
    glEnd();

    // Inner bell design (yellow, upside-down arc)
    float centerX = 0.0;
    float centerY = -0.47;
    float width = 0.19;
    float height = 0.03;
    float dyStep = 0.001;
    int numSegments = 100;

    float halfWidth = width / 2.0;
    float radiusX = halfWidth;
    float radiusY = height / 2.0;

    // Loop to draw stacked yellow lines (upside-down)
    for (float j = 0; j <= height; j += dyStep)
    {
        glColor3f(1.0, 215.0 / 255.0, 0.0);

        glBegin(GL_LINE_STRIP);
        for (int i = 0; i <= numSegments; i++)
        {
            float angle = (3.14159 * i / numSegments); // From 0° to 180°
            float dx = radiusX * cos(angle) * 0.92;
            float dy = radiusY * sin(angle);
            glVertex2f(centerX + dx, centerY + dy + j);
        }
        glEnd();
    }

    // Black outline for the inner bell design
    glColor3f(0.0, 0.0, 0.0);
    glLineWidth(3.0);

    glBegin(GL_LINE_LOOP);
    for (int i = 0; i <= numSegments; i++)
    {
        float angle = (3.14159 * i / numSegments); // From 0° to 180°
        float dx = radiusX * cos(angle) * 0.92;
        float dy = radiusY * sin(angle);
        glVertex2f(centerX + dx, centerY + dy + height);
    }
    for (int i = 0; i <= numSegments; i++)
    {
        float angle = 3.14159 + (3.14159 * i / numSegments); // From 180° to 360°
        float dx = radiusX * cos(angle);
        float dy = radiusY * sin(angle);
        glVertex2f(centerX + dx, centerY - dy);
    }
    glEnd();
}

// 8. Body
void drawBody()
{
    // TODO: Implement drawing of the body
    int numSegments = 50;
    float a = -0.12245f;
    float h = 0.50f;
    float h2 = -0.50f;
    float k = -0.75f;
    float gapWidth = 0.1f;
    float gapHeight = -1.0f;
    float h3 = gapWidth / 2 - 0.035f;
    float h4 = -gapWidth / 2 + 0.035f;

    glColor3f(41.0f / 255.0f, 134.0f / 255.0f, 204.0f / 255.0f);
    float rotationAngle = -5.0f;
    // Right Side of the Body
    glBegin(GL_POLYGON);
    float rotatedX, rotatedY;

    glVertex2f(gapWidth / 2, -0.4f);

    for (float y = -0.4f; y >= -1.1f; y -= (1.1f - 0.4f) / numSegments)
    {
        float x = a * (y - k) * (y - k) + h;
        glVertex2f(x, y);
    }

    for (float x = a * (-1.1f - k) * (-1.1f - k) + h; x >= gapWidth / 2; x -= 0.01f)
    {
        glVertex2f(x, -1.1f);
    }

    for (float y = -1.1f; y <= -0.4f; y += (1.1f - 0.4f) / numSegments)
    {
        float x = -a * (y - k) * (y - k) + h3;
        glVertex2f(x, y);
    }
    glEnd();

    // Left Side of the Body
    glBegin(GL_POLYGON);

    glVertex2f(-gapWidth / 2, -0.4f);

    for (float y = -0.4f; y >= -1.1f; y -= (1.1f - 0.4f) / numSegments)
    {
        float x = -a * (y - k) * (y - k) + h2;
        glVertex2f(x, y);
    }

    for (float x = -a * (-1.1f - k) * (-1.1f - k) + h2; x <= -gapWidth / 2; x += 0.01f)
    {
        glVertex2f(x, -1.1f);
    }

    for (float y = -1.1f; y <= -0.4f; y += (1.1f - 0.4f) / numSegments)
    {
        float x = a * (y - k) * (y - k) + h4;
        glVertex2f(x, y);
    }
    glEnd();

    drawCircleNoOutline(0.0, -0.73, 0.32, 41.0 / 255.0, 134.0 / 255.0, 204.0 / 255.0);
    drawEmphasizedHorizontalOval(0.0, -0.71, 0.36, 0.3, 0.11, 1.0, 1.0, 1.0);
    drawMagicPocket(0.0, -0.73, 0.28, 0.2, 0.05, 1.0, 1.0, 1.0);

    glColor3f(0.0f, 0.0f, 0.0f); // Black color for the outline
    glLineWidth(3.0f);

    glBegin(GL_LINE_STRIP);
    for (float y = -0.4f; y >= -1.11f; y -= (1.1f - 0.4f) / numSegments)
    {
        if (y <= -0.5f)
        {
            float x = a * (y - k) * (y - k) + h;
            glVertex2f(x, y);
        }
    }
    glEnd();

    glBegin(GL_LINE_STRIP);
    for (float x = a * (-1.1f - k) * (-1.1f - k) + h; x >= -a * (-1.1f - k) * (-1.1f - k) + h3 - 0.01; x -= 0.01f)
    {
        glVertex2f(x, -1.1f);
    }
    glEnd();

    glBegin(GL_LINE_STRIP);
    for (float y = -1.1f; y <= -0.4f; y += (1.1f - 0.4f) / numSegments)
    {
        if (y <= -1.04f)
        {
            float x = -a * (y - k) * (y - k) + h3;
            glVertex2f(x, y);
        }
    }
    glEnd();

    glBegin(GL_LINE_STRIP);
    for (float y = -0.4f; y >= -1.11f; y -= (1.1f - 0.4f) / numSegments)
    {
        if (y <= -0.5f)
        {
            float x = -a * (y - k) * (y - k) + h2;
            glVertex2f(x, y);
        }
    }
    glEnd();

    glBegin(GL_LINE_STRIP);
    for (float x = -a * (-1.1f - k) * (-1.1f - k) + h2; x <= -gapWidth / 2 + 0.03; x += 0.01f)
    {
        glVertex2f(x, -1.1f);
    }
    glEnd();

    glBegin(GL_LINE_STRIP);
    for (float x = -gapWidth / 2 + 0.02; x <= gapWidth / 2 - 0.02; x += 0.01f)
    {
        float y = -1.05f;
        glVertex2f(x, y);
    }
    glEnd();

    glBegin(GL_LINE_STRIP);
    for (float y = -1.1f; y <= -0.4f; y += (1.1f - 0.4f) / numSegments)
    {
        if (y <= -1.04f)
        {
            float x = a * (y - k) * (y - k) + h4;
            glVertex2f(x, y);
        }
    }
    glEnd();
}

// 9. Hand
void drawHand()
{
    // TODO: Implement drawing of the hand
    glColor3f(41.0f / 255.0f, 134.0f / 255.0f, 204.0f / 255.0f);
    glBegin(GL_QUADS);
    glVertex2f(0.7, -0.59);
    glVertex2f(0.7, -0.72);
    glVertex2f(0.49, -0.62);
    glVertex2f(0.487, -0.418);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2f(-0.64, -0.18);
    glVertex2f(-0.72, -0.3);
    glVertex2f(-0.49, -0.62);
    glVertex2f(-0.487, -0.3);
    glEnd();

    glColor3f(0.0, 0.0, 0.0);
    glLineWidth(3.0);
    glBegin(GL_LINE_STRIP);
    glVertex2f(0.68, -0.718);
    glVertex2f(0.49, -0.62);
    glEnd();

    glBegin(GL_LINE_STRIP);
    glVertex2f(0.69, -0.58);
    glVertex2f(0.48, -0.41);
    glEnd();

    glBegin(GL_LINE_STRIP);
    glVertex2f(-0.72, -0.3);
    glVertex2f(-0.49, -0.62);
    glEnd();

    glBegin(GL_LINE_STRIP);
    glVertex2f(-0.64, -0.18);
    glVertex2f(-0.487, -0.3);
    glEnd();

    drawCircle(0.7, -0.65, 0.1, 255 / 255.0, 255.0 / 255.0, 255.0 / 255.0);
    drawCircle(-0.7, -0.2, 0.1, 255 / 255.0, 255.0 / 255.0, 255.0 / 255.0);
}

// 10. Legs
void drawLegs()
{
    // TODO: Implement drawing of the legs
    drawPlumpOval(0.265f, -1.145f, 0.265f, 0.1f, 0.3f, 1.0f, 1.0f, 1.0f);  // Right leg
    drawPlumpOval(-0.265f, -1.145f, 0.265f, 0.1f, 0.3f, 1.0f, 1.0f, 1.0f); // Left leg
}

// 11. Shadow
void drawShadow()
{
    drawEmphasizedHorizontalOval(0.0, -1.15, 0.6, 0.2, 0.1, 100.0 / 255.0, 100.0 / 255.0, 100.0 / 255.0);
}