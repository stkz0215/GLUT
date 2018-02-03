/*
	main.cpp
*/

#include <GL/glut.h>
#include "main.hpp"
#include "gameObject.hpp"


/* グローバル変数 */
myWindow window = myWindow();
myCamera camera = myCamera();
myLight light0 = myLight(0, 0, 0);

/* 関数プロトタイプ */
void init();
void display();
void timer(int);
void resize(int, int);
//void mouse(int, int, int, int);
void mouse_motion(int, int);
void keyboard(unsigned char, int, int);



/*-----------------------------------------------------------------------------------*
	メイン関数、初期化
 *-----------------------------------------------------------------------------------*/

 /* メイン関数 */
int main(int argc, char *argv[]) {
	// GLUT初期化
	glutInit(&argc, argv);

	// ウィンドウ作成
	window;
	window.createWindow();

	// コールバック関数の登録
	glutDisplayFunc(display);
	glutReshapeFunc(resize);
	glutTimerFunc(100, timer, 0);
	glutMotionFunc(mouse_motion);
	glutPassiveMotionFunc(mouse_motion);
	glutKeyboardFunc(keyboard);
	//glutMouseFunc(mouse);
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
	glClearColor(0.0, 0.0, 1.0, 1.0);

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
	//glLightfv(GL_LIGHT1, GL_DIFFUSE, green);

	// マウスカーソル非表示
	glutSetCursor(GLUT_CURSOR_NONE);
}



/*-----------------------------------------------------------------------------------*
	画面描き換え
*-----------------------------------------------------------------------------------*/

/* 描画処理本体 */
void display(void)
{
	// バックバッファクリア
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// 変換行列初期化
	glLoadIdentity();

	// 視点位置と視線方向
	gluLookAt(camera.x, camera.y, camera.z, camera.lookat_x(), camera.lookat_y(), camera.lookat_z(), 0.0, 1.0, 0.0);

	// 光源の位置設定
	glLightfv(GL_LIGHT0, GL_POSITION, light0.pos());
	//glLightfv(GL_LIGHT1, GL_POSITION, light1pos);

	/* ---------- 中央の立方体 ---------- */
	glPushMatrix();
	static int a = 5;
	glTranslated(++a, 0, 0);
	/* 図形の回転 */
	glRotated(25, 0.0, 1.0, 0.0);

	/* 図形の色 (赤)  */
	GLfloat red[] = { 0.8, 0.2, 0.2, 1.0 };
	GLdouble normal[][3] = {
		{ 0.0, 0.0,-1.0 },
		{ 1.0, 0.0, 0.0 },
		{ 0.0, 0.0, 1.0 },
		{ -1.0, 0.0, 0.0 },
		{ 0.0,-1.0, 0.0 },
		{ 0.0, 1.0, 0.0 }
	};
	GLdouble vertex[][3] = {
		{ -1, -1, -1 },
		{ 1, -1, -1 },
		{ 1.0, 1.0, -1 },
		{ -1, 1.0, -1 },
		{ -1, -1, 1.0 },
		{ 1.0, -1, 1.0 },
		{ 1.0, 1.0, 1.0 },
		{ -1, 1.0, 1.0 }
	};
	int face[][4] = {
		{ 0, 1, 2, 3 },
		{ 1, 5, 6, 2 },
		{ 5, 4, 7, 6 },
		{ 4, 0, 3, 7 },
		{ 4, 5, 1, 0 },
		{ 3, 2, 6, 7 }
	};

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, red);

	/* 図形の描画 */
	//glColor3d(0.0, 0.0, 0.0);
	glBegin(GL_QUADS);
	for (int j = 0; j < 6; j++) {
		glNormal3dv(normal[j]);
		for (int i = 0; i < 4; i++) {
			glVertex3dv(vertex[face[j][i]]);
		}
	}
	glEnd();
	glPopMatrix();

	///* ---------- 世界の壁 ---------- */
	//glPushMatrix();

	//glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, white);

	///* 図形の描画 */
	////glColor3d(0.0, 0.0, 0.0);
	//glBegin(GL_LINES);
	//for (j = 0; j < 6; ++j) {
	//	glNormal3dv(normal[j]);
	//	for (i = 0; i < 4; ++i) {
	//		GLdouble a = 300;
	//		GLdouble vertex_tmp[] = { vertex[my_floor[j][i]][0] * a, vertex[my_floor[j][i]][1] * a, vertex[my_floor[j][i]][2] * a };
	//		glVertex3dv(vertex_tmp);
	//	}
	//}
	//glEnd();
	//glPopMatrix();


	glutSwapBuffers();

	
	///* 一周回ったら回転角を 0 に戻す */
	//if (isAPushed) if (++r >= 360) r = 0;
}

/* タイマー */
void timer(int) {
	glutPostRedisplay();
	glutTimerFunc(16, timer, 0);
}

/* ウィンドウサイズ変更 */
void resize(int w, int h) {
	glViewport(0, 0, w, h);

	/* 透視変換行列の設定 */
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90.0, (double)w / (double)h, 1.0, 50.0);

	/* モデルビュー変換行列の設定 */
	glMatrixMode(GL_MODELVIEW);
}



/*-----------------------------------------------------------------------------------*
	入力関係
 *-----------------------------------------------------------------------------------*/

/* マウスを移動した */
void mouse_motion(int x, int y) {
	static bool wrap = false;

	if (!wrap) {
		int dx = x - window.width / 2;
		int dy = y - window.height / 2;

		camera.theta_xz += camera.movespeed * dx;
		camera.theta_xy -= camera.movespeed * dy;

		if (camera.theta_xz >= 2*M_PI) camera.theta_xz = 0;
		if (camera.theta_xy >= M_PI_2) camera.theta_xy = M_PI_2;
		if (camera.theta_xy <= -M_PI_2) camera.theta_xy = -M_PI_2;

		wrap = true;
		glutWarpPointer(window.width / 2, window.height / 2);
	}
	else {
		wrap = false;
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