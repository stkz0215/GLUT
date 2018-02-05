/*
	gameMain.hpp
	ゲーム時の処理をしている
*/

#pragma once

#include <GL/glut.h>
#include "gameObject.hpp"
#include "main.hpp"

#include <cstdio>

void gameDisplay(myGameScene);
void gameMouse(myGameScene, int, int, int, int);
void gameMouse_motion(myGameScene*, int, int);
void gameKeyboard(unsigned char, int, int);

/*-----------------------------------------------------------------------------------*
画面描き換え
*-----------------------------------------------------------------------------------*/

/* 描画処理本体 */
void gameDisplay(myGameScene scene)
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


	/* 図形の色 (赤)  */
	GLfloat red[] = { 0.8, 0.2, 0.2, 1.0 };
	GLfloat black[] = { 0.0, 0.0, 0.0, 1.0 };
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
	int edge[][2] = {
		{ 0, 1 },
		{ 1, 2 },
		{ 2, 3 },
		{ 3, 0 },
		{ 4, 5 },
		{ 5, 6 },
		{ 6, 7 },
		{ 7, 4 },
		{ 0, 4 },
		{ 1, 5 },
		{ 2, 6 },
		{ 3, 7 }
	};
	int face[][4] = {
		{ 0, 1, 2, 3 },
		{ 1, 5, 6, 2 },
		{ 5, 4, 7, 6 },
		{ 4, 0, 3, 7 },
		{ 4, 5, 1, 0 },
		{ 3, 2, 6, 7 }
	};

	// 背景（景色）の描画
	for (int i = 0; i < 4; i++) {
		glPushMatrix();
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, black);
		glRotated(22.5*i, 0, 1.0, 0);
		glBegin(GL_LINES);
		for (int i = 0; i < 12; ++i) {
			GLdouble tmp = 30,
				tmp1[] = { tmp*vertex[edge[i][0]][0], tmp*vertex[edge[i][0]][1], tmp*vertex[edge[i][0]][2] },
				tmp2[] = { tmp*vertex[edge[i][1]][0], tmp*vertex[edge[i][1]][1], tmp*vertex[edge[i][1]][2] };
			glVertex3dv(tmp1);
			glVertex3dv(tmp2);
		}
		glEnd();
		glPopMatrix();
	}

	// Enemyの描画
	auto itr = scene.enemy.begin();
	while (itr != scene.enemy.end()) {
		glPushMatrix();
		glTranslated(itr->pos_x(), itr->pos_y(), itr->pos_z());
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, red);
		glBegin(GL_QUADS);
		for (int j = 0; j < 6; j++) {
			glNormal3dv(normal[j]);
			for (int i = 0; i < 4; i++) {
				glVertex3dv(vertex[face[j][i]]);
			}
		}
		glEnd();
		glPopMatrix();
		itr++;
	}

	glutSwapBuffers();
}



/*-----------------------------------------------------------------------------------*
入力関係
*-----------------------------------------------------------------------------------*/


void gameMouse(myGameScene *scene, int button, int state, int x, int y) {
	static bool isClicked = false;

	switch (button) {
	case GLUT_LEFT_BUTTON:
		if (state == GLUT_DOWN && scene->ray.dist == 0 && !isClicked) {
			isClicked = true;
			scene->ray.theta_xy = scene->camera.theta_xy;
			scene->ray.theta_xz = scene->camera.theta_xz;
			scene->ray.dist = 50;
		}
		else {
			isClicked = false;
		}
		break;
	}
}

/* マウスを移動した */
void gameMouse_motion(myGameScene *scene, int x, int y) {
	static bool wrap = false;

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
	}
}

/* キーボードが押された */
void gameKeyboard(unsigned char key, int x, int y) {
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
