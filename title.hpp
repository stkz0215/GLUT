#pragma once

#pragma once

#include <GL/glut.h>
#include "gameObject.hpp"
#include "main.hpp"

void titleDisplay(myGameScene scene);
void titleMouse(myGameScene *, int, int, int, int);
void titleMouse_motion(myGameScene*, int, int);
void titleKeyboard(unsigned char, int, int);

/*-----------------------------------------------------------------------------------*
画面描き換え
*-----------------------------------------------------------------------------------*/

/* 描画処理本体 */
void titleDisplay(myGameScene scene)
{
	// バックバッファクリア
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// 変換行列初期化
	glLoadIdentity();

	// 視点位置と視線方向
	gluLookAt(scene.camera.x, scene.camera.y, scene.camera.z, scene.camera.lookat_x(), scene.camera.lookat_y(), scene.camera.lookat_z(), 0.0, 1.0, 0.0);

	// 光源の位置設定
	glLightfv(GL_LIGHT0, GL_POSITION, scene.light0.pos());
	//glLightfv(GL_LIGHT1, GL_POSITION, light1pos);

	glutSwapBuffers();
}

/*-----------------------------------------------------------------------------------*
入力関係
*-----------------------------------------------------------------------------------*/

void titleMouse(myGameScene* scene, int button, int state, int x, int y) {
	switch (state) {
	case GLUT_UP:
		scene->state = MYSTATE_GAME;
		glutWarpPointer(scene->window->width / 2, scene->window->height / 2);
		// マウスカーソル非表示
		glutSetCursor(GLUT_CURSOR_NONE);
		break;
	}
}

/* マウスを移動した */
void titleMouse_motion(myGameScene *scene, int x, int y) {
	/*static bool wrap = false;

	if (!wrap) {
		int dx = x - scene->window->width / 2;
		int dy = y - scene->window->height / 2;

		scene->camera.theta_xz += scene->camera.movespeed * dx;
		scene->camera.theta_xy -= scene->camera.movespeed * dy;

		if (scene->camera.theta_xz >= 2 * M_PI)  scene->camera.theta_xz = 0;
		if (scene->camera.theta_xy >= M_PI_2)  scene->camera.theta_xy = M_PI_2;
		if (scene->camera.theta_xy <= -M_PI_2) scene->camera.theta_xy = -M_PI_2;

		wrap = true;
		glutWarpPointer(scene->window->width / 2, scene->window->height / 2);
	}
	else {
		wrap = false;
	}*/
}

/* キーボードが押された */
void titleKeyboard(unsigned char key, int x, int y) {
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
