#include <GL/glut.h>
#include <math.h>
#include "doraemon.h"

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

// 5. Moustache
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

// 9. Body
void drawBody()
{

    int numSegments = 50;    // Number of segments for the curve
    float a = -0.28571f;     // Parabola curvature factor
    float h = 0.52f;         // X-coordinate of the vertex (right side)
    float h2 = -0.52f;       // X-coordinate of the vertex (left side)
    float k = -0.75f;        // Y-coordinate of the vertex
    float gapWidth = 0.1f;   // Width of the gap between the legs
    float gapHeight = -1.0f; // Height of the gap (higher than -1.1)
    float h3 = gapWidth / 2 - 0.035f;
    float h4 = -gapWidth / 2 + 0.035f;

    glColor3f(41.0f / 255.0f, 134.0f / 255.0f, 204.0f / 255.0f); // Blue color for the body

    // **Right Side of the Body**
    glBegin(GL_POLYGON);

    // **Step 2:** Move up along the gap to the top edge
    glVertex2f(gapWidth / 2, -0.4f);

    // **Step 3:** Top horizontal line (from gap to right edge)
    for (float x = gapWidth / 2; x <= 0.485f; x += 0.01f)
    {
        glVertex2f(x, -0.4f);
    }

    // **Step 4:** Right side curve (from top to bottom)
    for (float y = -0.4f; y >= -1.1f; y -= (1.1f - 0.4f) / numSegments)
    {
        float x = a * (y - k) * (y - k) + h;
        glVertex2f(x, y);
    }

    // **Step 5:** Bottom horizontal line (from curve back to gap)
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

    // **Left Side of the Body**
    glBegin(GL_POLYGON);

    // **Step 2:** Move up along the gap to the top edge
    glVertex2f(-gapWidth / 2, -0.4f);

    // **Step 3:** Top horizontal line (from gap to left edge)
    for (float x = -gapWidth / 2; x >= -0.485f; x -= 0.01f)
    {
        glVertex2f(x, -0.4f);
    }

    // **Step 4:** Left side curve (from top to bottom)
    for (float y = -0.4f; y >= -1.1f; y -= (1.1f - 0.4f) / numSegments)
    {
        float x = -a * (y - k) * (y - k) + h2;
        glVertex2f(x, y);
    }

    // **Step 5:** Bottom horizontal line (from curve back to gap)
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
}
