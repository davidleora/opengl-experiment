#include <GL/glut.h>

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);

    // 軸
    glBegin(GL_TRIANGLE_STRIP);
    glColor3d(0.4, 1.0, 0.3);
    glVertex2d(-0.05, -0.8);
    glVertex2d(0.05, -0.8);
    glVertex2d(-0.05, -1.2);
    glVertex2d(0.05, -1.3);
    glVertex2d(-0.08, -1.4);
    glVertex2d(-0.03, -1.5);
    glEnd();

    // 右葉っぱ
    glBegin(GL_TRIANGLES);
    glColor3d(0.2, 0.5, 0.3);
    glVertex2d(-0.03, -1.5);
    glVertex2d(0.38, -1.0);
    glVertex2d(1.0, -1.1);
    glColor3d(0.2, 0.6, 0.3);
    glVertex2d(-0.03, -1.5);
    glVertex2d(0.65, -1.4);
    glVertex2d(1.0, -1.1);
    glEnd();

    // 左葉っぱ
    glBegin(GL_TRIANGLES);
    glColor3d(0.2, 0.6, 0.3);
    glVertex2d(-0.03, -1.5);
    glVertex2d(-0.40, -1.0);
    glVertex2d(-1.0, -1.1);
    glColor3d(0.2, 0.5, 0.3);
    glVertex2d(-0.03, -1.5);
    glVertex2d(-0.80, -1.4);
    glVertex2d(-1.0, -1.1);
    glEnd();

    // 花びら
    glColor3d(1.0, 0.0, 0.0);
    glBegin(GL_TRIANGLE_FAN);
    glColor3d(1.0, 1.0, 1.0); // 白
    glVertex2d(0.0, 0.0);
    glColor3d(1.0, 0.0, 0.0); // 赤
    glVertex2d(0.0, 1.0);
    glColor3d(0.8, 0.0, 0.0); // 赤
    glVertex2d(0.6, 0.6);
    glColor3d(1.0, 0.0, 0.0); // 赤
    glVertex2d(1.0, 0.0);
    glColor3d(0.8, 0.0, 0.0); // 赤
    glVertex2d(0.6, -0.6);
    glColor3d(1.0, 0.0, 0.0); // 赤
    glVertex2d(0.0, -1.0);
    glColor3d(0.8, 0.0, 0.0); // 赤
    glVertex2d(-0.6, -0.6);
    glColor3d(1.0, 0.0, 0.0); // 赤
    glVertex2d(-1.0, 0.0);
    glColor3d(0.8, 0.0, 0.0); // 赤
    glVertex2d(-0.6, 0.6);
    glColor3d(1.0, 0.0, 0.0); // 赤
    glVertex2d(0.0, 1.0);
    glEnd();

    glFlush();
}

void resize(int w, int h)
{
    /* ウィンドウ全体をビューポートにする */
    glViewport(0, 0, w, h);

    /* 変換行列の初期化 */
    glLoadIdentity();

    /* スクリーン上の表示領域をビューポートの大きさに比例させる */
    glOrtho(-w / 200.0, w / 200.0, -h / 200.0, h / 200.0, -1.0, 1.0);
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'q':
    case 'Q':
    case '\033': /* '\033' は ESC の ASCII コード */
        exit(0);
    default:
        break;
    }
}

void init(void)
{
    glClearColor(1.0, 1.0, 1.0, 1.0);
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA);
    glutCreateWindow(argv[0]);
    glutDisplayFunc(display);
    glutReshapeFunc(resize);
    glutKeyboardFunc(keyboard);
    init();
    glutMainLoop();
    return 0;
}