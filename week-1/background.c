#include <GL/glut.h>
#include "background.h"
#include "shapes.h"

// 背景を描画する関数
void drawBackground()
{
    // 1. 空の描画（上部2/3）
    glBegin(GL_QUADS);
    // 上の色（空の色）
    glColor3f(135.0f / 255.0f, 206.0f / 255.0f, 235.0f / 255.0f);
    glVertex2f(-1.0f, 1.0f);
    glVertex2f(1.0f, 1.0f);
    // 下の色（地平線近くの色）
    glColor3f(200.0f / 255.0f, 220.0f / 255.0f, 230.0f / 255.0f);
    glVertex2f(1.0f, 0.35f);
    glVertex2f(-1.0f, 0.35f);
    glEnd();

    // 2. 道路の描画（下部1/3）
    glBegin(GL_QUADS);
    // 上の色（薄いグレー）
    glColor3f(190.0f / 255.0f, 190.0f / 255.0f, 190.0f / 255.0f);
    glVertex2f(-1.0f, -0.3f);
    glVertex2f(1.0f, -0.3f);
    // 下の色（濃いグレー）
    glColor3f(105.0f / 255.0f, 105.0f / 255.0f, 105.0f / 255.0f);
    glVertex2f(1.0f, -1.0f);
    glVertex2f(-1.0f, -1.0f);
    glEnd();

    // 3. のび太の家の壁を描画
    glColor3f(253.0f / 255.0f, 253.0f / 255.0f, 150.0f / 255.0f);
    glBegin(GL_QUADS);
    glVertex2f(-1.0f, 0.7f);
    glVertex2f(0.4f, 0.7f);
    glColor3f(193.0f / 255.0f, 193.0f / 255.0f, 90.0f / 255.0f);
    glVertex2f(0.4f, -0.3f);
    glVertex2f(-1.0f, -0.3f);
    glEnd();

    // 3. のび太の家の壁の三角形部分を描画
    glColor3f(253.0f / 255.0f, 253.0f / 255.0f, 150.0f / 255.0f);
    glBegin(GL_TRIANGLES);
    glVertex2f(0.4f, 0.7f);
    glVertex2f(-1.0f, 0.7f);
    glVertex2f(-1.0f, 1.0f);
    glEnd();

    glColor3f(151.0f / 255.0f, 151.0f / 255.0f, 151.0f / 255.0f);
    glBegin(GL_QUADS);
    glVertex2f(-1.0f, 0.75f);
    glVertex2f(-0.9f, 0.75f);
    glVertex2f(-0.9f, 0.85f);
    glVertex2f(-1.0f, 0.85f);
    glEnd();

    glColor3f(0.0f, 0.0f, 0.0f);
    glLineWidth(3.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(-1.0f, 0.75f);
    glVertex2f(-0.9f, 0.75f);
    glVertex2f(-0.9f, 0.85f);
    glVertex2f(-1.0f, 0.85f);
    glEnd();
    glBegin(GL_LINES);
    glVertex2f(-1.0f, 0.783f);
    glVertex2f(-0.9f, 0.783f);
    glEnd();
    glBegin(GL_LINES);
    glVertex2f(-1.0f, 0.817f);
    glVertex2f(-0.9f, 0.817f);
    glEnd();

    // 壁の枠を追加
    glColor3f(0.0f, 0.0f, 0.0f);
    glLineWidth(3.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(-1.0f, 1.0f);
    glVertex2f(0.4f, 0.7f);
    glVertex2f(0.4f, -0.3f);
    glVertex2f(-1.0f, -0.3f);
    glEnd();

    // 屋根をグラデーションで描画
    glBegin(GL_QUADS);
    // 上部の色（明るめ）
    glColor3f(173.0f / 255.0f, 35.0f / 255.0f, 54.0f / 255.0f);
    glVertex2f(-1.0f, 1.075f);
    glVertex2f(0.625f, 0.725f);
    // 下部の色（暗め）
    glColor3f(123.0f / 255.0f, 15.0f / 255.0f, 34.0f / 255.0f);
    glVertex2f(0.4f, 0.7f);
    glVertex2f(-1.0f, 1.0f);
    glEnd();

    // 屋根の枠
    glColor3f(0.0f, 0.0f, 0.0f);
    glLineWidth(3.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(-1.0f, 1.0f);
    glVertex2f(0.4f, 0.7f);
    glVertex2f(0.625f, 0.725f);
    glVertex2f(-1.0f, 1.075f);
    glEnd();

    // 4. のび太の家の玄関を描画
    // ドア
    glBegin(GL_POLYGON);
    // 上部の色（明るめ）
    glColor3f(185.0f / 255.0f, 113.0f / 255.0f, 43.0f / 255.0f);
    glVertex2f(-0.25f, 0.45f);
    glVertex2f(0.25f, 0.45f);
    // 下部の色（暗め）
    glColor3f(145.0f / 255.0f, 73.0f / 255.0f, 23.0f / 255.0f);
    glVertex2f(0.25f, -0.3f);
    glVertex2f(-0.25f, -0.3f);
    glEnd();

    // ドアの枠
    glColor3f(0.0f, 0.0f, 0.0f);
    glLineWidth(3.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.25f, -0.3f);
    glVertex2f(0.25f, -0.3f);
    glVertex2f(0.25f, 0.45f);
    glVertex2f(-0.25f, 0.45f);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.22f, -0.3f);
    glVertex2f(0.13f, -0.3f);
    glVertex2f(0.13f, 0.42f);
    glVertex2f(-0.22f, 0.42f);
    glEnd();

    // ドアの窓
    glBegin(GL_QUADS);
    // 上部の色（明るめ）
    glColor3f(100.0f / 255.0f, 176.0f / 255.0f, 205.0f / 255.0f);
    glVertex2f(-0.13f, 0.325f);
    glVertex2f(0.03f, 0.325f);
    // 下部の色（暗め）
    glColor3f(50.0f / 255.0f, 100.0f / 255.0f, 130.0f / 255.0f);
    glVertex2f(0.03f, 0.15f);
    glVertex2f(-0.13f, 0.15f);
    glEnd();

    // ドアの窓の枠
    glColor3f(0.0f, 0.0f, 0.0f);
    glLineWidth(3.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.13f, 0.15f);
    glVertex2f(0.03f, 0.15f);
    glVertex2f(0.03f, 0.325f);
    glVertex2f(-0.13f, 0.325f);
    glEnd();

    // ドアのノブ
    glColor3f(0.0f, 0.0f, 0.0f);
    drawCircle(0.1f, 0.1f, 0.02f, 1.0f, 1.0f, 0.0f);

    // ドアの右側の窓
    glColor3f(100.0f / 255.0f, 176.0f / 255.0f, 205.0f / 255.0f);
    glBegin(GL_QUADS);
    glVertex2f(0.22f, 0.42f);
    glVertex2f(0.15f, 0.42f);
    glColor3f(50.0f / 255.0f, 100.0f / 255.0f, 130.0f / 255.0f);
    glVertex2f(0.15f, -0.3f);
    glVertex2f(0.22f, -0.3f);

    glEnd();

    // ドアの右側の窓の枠
    glColor3f(0.0f, 0.0f, 0.0f);
    glLineWidth(3.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(0.15f, -0.3f);
    glVertex2f(0.22f, -0.3f);
    glVertex2f(0.22f, 0.42f);
    glVertex2f(0.15f, 0.42f);
    glEnd();
    glBegin(GL_LINES);
    glVertex2f(0.15f, 0.3f);
    glVertex2f(0.22f, 0.3f);
    glEnd();
    glBegin(GL_LINES);
    glVertex2f(0.15f, 0.18f);
    glVertex2f(0.22f, 0.18f);
    glEnd();
    glBegin(GL_LINES);
    glVertex2f(0.15f, 0.06f);
    glVertex2f(0.22f, 0.06f);
    glEnd();
    glBegin(GL_LINES);
    glVertex2f(0.15f, -0.06f);
    glVertex2f(0.22f, -0.06f);
    glEnd();
    glBegin(GL_LINES);
    glVertex2f(0.15f, -0.18f);
    glVertex2f(0.22f, -0.18f);
    glEnd();

    // ドアの屋根
    glBegin(GL_QUADS);
    // 上部の色（明るめ）
    glColor3f(173.0f / 255.0f, 35.0f / 255.0f, 54.0f / 255.0f);
    glVertex2f(-0.25f, 0.55f);
    glVertex2f(0.25f, 0.55f);
    // 下部の色（暗め）
    glColor3f(123.0f / 255.0f, 15.0f / 255.0f, 34.0f / 255.0f);
    glVertex2f(0.45f, 0.45f);
    glVertex2f(-0.45f, 0.45f);
    glEnd();

    // ドアの屋根の枠
    glColor3f(0.0f, 0.0f, 0.0f);
    glLineWidth(3.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.45f, 0.45f);
    glVertex2f(0.45f, 0.45f);
    glVertex2f(0.25f, 0.55f);
    glVertex2f(-0.25f, 0.55f);
    glEnd();

    // 5. フェンスの描画（左右）
    float fenceLeft = -1.1f;
    float fenceRight = -0.4f;
    float fenceBottom = -0.32f;
    float fenceTop = 0.3f;
    float blockWidth = 0.2f;
    float blockHeight = 0.1f;

    for (float y = fenceBottom; y < fenceTop; y += blockHeight)
    {
        for (float x = fenceLeft; x < fenceRight; x += blockWidth)
        {
            // 長方形を描画
            glColor3f(211.0f / 255.0f, 211.0f / 255.0f, 211.0f / 255.0f); // ライトグレー
            glBegin(GL_QUADS);
            glVertex2f(x, y);
            glVertex2f(x + blockWidth, y);
            glVertex2f(x + blockWidth, y + blockHeight);
            glVertex2f(x, y + blockHeight);
            glEnd();

            // 長方形の枠を描画
            glColor3f(0.0f, 0.0f, 0.0f);
            glBegin(GL_LINE_LOOP);
            glVertex2f(x, y);
            glVertex2f(x + blockWidth, y);
            glVertex2f(x + blockWidth, y + blockHeight);
            glVertex2f(x, y + blockHeight);
            glEnd();
        }
    }

    fenceLeft = 0.3f;
    fenceRight = 1.0f;

    for (float y = fenceBottom; y < fenceTop; y += blockHeight)
    {
        for (float x = fenceLeft; x < fenceRight; x += blockWidth)
        {
            // 長方形を描画
            glColor3f(211.0f / 255.0f, 211.0f / 255.0f, 211.0f / 255.0f); // ライトグレー
            glBegin(GL_QUADS);
            glVertex2f(x, y);
            glVertex2f(x + blockWidth, y);
            glVertex2f(x + blockWidth, y + blockHeight);
            glVertex2f(x, y + blockHeight);
            glEnd();

            // 長方形の枠を描画
            glColor3f(0.0f, 0.0f, 0.0f);
            glBegin(GL_LINE_LOOP);
            glVertex2f(x, y);
            glVertex2f(x + blockWidth, y);
            glVertex2f(x + blockWidth, y + blockHeight);
            glVertex2f(x, y + blockHeight);
            glEnd();
        }
    }
}