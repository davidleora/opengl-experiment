#ifndef SHAPES_H
#define SHAPES_H

// Draw Flattened Circle (Head)
void drawFlattenedCircle(float x, float y, float radius, float r, float g, float b, float flattenFactor);

// Draw Circle
void drawCircle(float x, float y, float radius, float r, float g, float b);

// Draw Nose Inner Circle
void drawCircleNoOutline(float x, float y, float radius, float r, float g, float b);

// Draw a plain horizontal oval
void drawPlumpOval(float centerX, float centerY, float radiusX, float radiusY, float plumpFactor, float r, float g, float b);

// Draw Vertical Oval
void drawVerticalOval(float x, float y, float radiusX, float radiusY, float r, float g, float b);

// Draw Emphasized Horizontal Oval
void drawEmphasizedHorizontalOval(float centerX, float centerY, float radiusX, float radiusY, float bulgeFactor, float r, float g, float b);

// Draw Magic Pocket
void drawMagicPocket(float centerX, float centerY, float radiusX, float radiusY, float pocketDepth, float r, float g, float b);

// Draw Rounded Rectangle
void drawRoundedRect(float x, float y, float width, float height, float borderRadius, float r, float g, float b);

// Draw Right Eye Wink
void drawWink(float x, float y, float radiusX, float radiusY, int topHalf);

#endif // SHAPES_H