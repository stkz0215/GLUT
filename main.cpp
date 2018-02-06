/*
	main.cpp
	大外の処理をしている
*/

#include <GL/glut.h>
#include "gameObject.hpp"
#include "main.hpp"
#include "title.hpp"
#include "gameMain.hpp"

/* グローバル変数 */
/*
myWindow window = myWindow();
myCamera camera = myCamera();
myLight light0 = myLight(0, 0, 0);
*/
myGameScene scene;

/* 関数プロトタイプ */
void init();
void display();
void timer(int);
void resize(int, int);
void mouse(int, int, int, int);
void mouse_motion(int, int);
void keyboard(unsigned char, int, int);


/*-----------------------------------------------------------------------------------*
	メイン関数、初期化
 *-----------------------------------------------------------------------------------*/

 /* メイン関数 */
int main(int argc, char *argv[]) {
	// GLUT初期化
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_RGBA);


	// ウィンドウ作成
	myWindow* window = new myWindow();
	window->createWindow();

	// シーン作成
	scene = myGameScene(window);

	// コールバック関数の登録
	glutDisplayFunc(display);
	glutReshapeFunc(resize);
	glutTimerFunc(100, timer, 0);
	glutMouseFunc(mouse);
	glutMotionFunc(mouse_motion);
	glutPassiveMotionFunc(mouse_motion);
	glutKeyboardFunc(keyboard);
	//glutKeyboardUpFunc(keyboard_up);

	// 初期化
	init();
	
	// メインループ
	glutMainLoop();

	return 0;
}


/* 初期化処理 */
void init() {
	// 背景色
	glClearColor(0.8, 0.8, 0.8, 1.0);

	// 深度テスト有効化
	glEnable(GL_DEPTH_TEST);

	// カリング有効化
	// -背を向けている面を削除
	// -図形の頂点が反時計周りの場合背を向けていると判断する
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CW);
	glFrontFace(GL_BACK);

	// ライト
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	//glLightfv(GL_	1, GL_DIFFUSE, green);
}



/*-----------------------------------------------------------------------------------*
	画面描き換え
*-----------------------------------------------------------------------------------*/

/* 描画処理本体 */
void display(void)
{
	switch (scene.state) {
	case MYSTATE_TITLE:
		titleDisplay(scene);
		break;
	case MYSTATE_GAME:
		gameDisplay(scene);
		break;
	}

	return;
}

/* タイマー */
void timer(int) {
	glutTimerFunc(16, timer, 0);
	glutPostRedisplay();
	scene.update();
}

/* ウィンドウサイズ変更 */
void resize(int w, int h) {
	glViewport(0, 0, w, h);

	/* 透視変換行列の設定 */
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (double)w / (double)h, 0.1, 100.0);

	/* モデルビュー変換行列の設定 */
	glMatrixMode(GL_MODELVIEW);
}



/*-----------------------------------------------------------------------------------*
	入力関係
 *-----------------------------------------------------------------------------------*/

/* マウスのボタンが押された */
void mouse(int button, int state, int x, int y) {
	switch (scene.state) {
	case MYSTATE_TITLE:
		titleMouse(&scene, button, state, x, y);
		break;
	case MYSTATE_GAME:
		gameMouse(&scene, button, state, x, y);
		break;
	}
}

/* マウスを移動した */
void mouse_motion(int x, int y) {
	switch (scene.state) {
	case MYSTATE_TITLE:
		break;
	case MYSTATE_GAME:
		gameMouse_motion(&scene, x, y);
		break;
	}
}

/* キーボードが押された */
void keyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 'q':
	case 'Q':
	case '\033':  // '\033' は ESC の ASCII コード
		exit(0);
		break;
	default:
		break;
	}
}