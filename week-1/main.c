#include <GL/glut.h>
#include "doraemon.h"
#include "background.h"

// コンパイルコマンド：
// gcc -o doraemon main.c doraemon.c shapes.c background.c -lglut -lGL -lm && ./doraemon

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    drawBackground();
    glPushMatrix();
    glTranslatef(-0.3, 0.0, 0.0);
    glScalef(0.5, 0.5, 0.5);
    drawShadow();
    drawHand();
    drawHead();
    drawLegs();
    drawBody();
    drawEyes();
    drawNose();
    drawMouth();
    drawMoustache();
    drawCollar();
    drawBell();
    glPopMatrix();
    glFlush();
}

void init()
{
    glClearColor(173.0 / 255.0, 203.0 / 255.0, 241.0 / 255.0, 1.0);
}

int main(int argc, char *argv[])
{
    // 初期化
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA);

    // ウィンドウの位置とサイズ
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(800, 800);

    // ウィンドウの作成
    glutCreateWindow(argv[0]);

    // 描画関数の設定
    glutDisplayFunc(display);
    init();

    // 無限ループ
    glutMainLoop();
    return 0;
}