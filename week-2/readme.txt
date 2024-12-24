コンパイルコマンド
＝＝＝＝＝＝＝＝＝
以下のコマンドを使用してプログラムをコンパイルし、実行してください。
・Linuxの場合：gcc -o main main.c scene.c -lGL -lGLU -lglut -lm && ./main
・Macの場合：gcc -o main main.c scene.c -framework GLUT -framework OpenGL -lm && ./main

操作ガイド：
・移動方法
    前進：W
    後退：S
    左へ移動：A
    右へ移動：D
・視点操作
    上を向く：I
    下を向く：K
    左を向く：J
    右を向く：L

ワープ機能
＝＝＝＝＝
以下のキーを押すと、指定された部屋に移動できます。
１：廊下
２：応接室
３：居間
４：トイレ
５：洗面
６：浴室
７：ダイニング・キッチン
８：のび太の部屋
９：スポーンポイントに戻る