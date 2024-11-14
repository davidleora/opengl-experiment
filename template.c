#include <GL/glut.h>

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glFlush();
}

void init()
{
    glClearColor(0.0, 0.0, 1.0, 1.0);
}

int main(int argc, char *argv[])
{
    // 初期化
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA);

    // ウィンドウの作成
    glutCreateWindow(argv[0]);

    // 描画関数の設定
    glutDisplayFunc(display);
    init();

    // 無限ループ
    glutMainLoop();
    return 0;
}