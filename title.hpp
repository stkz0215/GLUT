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
��ʕ`������
*-----------------------------------------------------------------------------------*/

/* �`�揈���{�� */
void titleDisplay(myGameScene scene)
{
	// �o�b�N�o�b�t�@�N���A
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// �ϊ��s�񏉊���
	glLoadIdentity();

	// ���_�ʒu�Ǝ�������
	gluLookAt(scene.camera.x, scene.camera.y, scene.camera.z, scene.camera.lookat_x(), scene.camera.lookat_y(), scene.camera.lookat_z(), 0.0, 1.0, 0.0);

	// �����̈ʒu�ݒ�
	glLightfv(GL_LIGHT0, GL_POSITION, scene.light0.pos());
	//glLightfv(GL_LIGHT1, GL_POSITION, light1pos);

	glutSwapBuffers();
}

/*-----------------------------------------------------------------------------------*
���͊֌W
*-----------------------------------------------------------------------------------*/

void titleMouse(myGameScene* scene, int button, int state, int x, int y) {
	switch (state) {
	case GLUT_UP:
		scene->state = MYSTATE_GAME;
		glutWarpPointer(scene->window->width / 2, scene->window->height / 2);
		// �}�E�X�J�[�\����\��
		glutSetCursor(GLUT_CURSOR_NONE);
		break;
	}
}

/* �}�E�X���ړ����� */
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

/* �L�[�{�[�h�������ꂽ */
void titleKeyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 'q':
	case 'Q':
	case '\033':  // '\033' �� ESC �� ASCII �R�[�h
		exit(0);
		break;
	default:
		break;
	}
}
