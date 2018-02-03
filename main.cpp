/*
	main.cpp
*/

#include <GL/glut.h>
#include "main.hpp"
#include "gameObject.hpp"


/* �O���[�o���ϐ� */
myWindow window = myWindow();
myCamera camera = myCamera();
myLight light0 = myLight(0, 0, 0);

/* �֐��v���g�^�C�v */
void init();
void display();
void timer(int);
void resize(int, int);
//void mouse(int, int, int, int);
void mouse_motion(int, int);
void keyboard(unsigned char, int, int);



/*-----------------------------------------------------------------------------------*
	���C���֐��A������
 *-----------------------------------------------------------------------------------*/

 /* ���C���֐� */
int main(int argc, char *argv[]) {
	// GLUT������
	glutInit(&argc, argv);

	// �E�B���h�E�쐬
	window;
	window.createWindow();

	// �R�[���o�b�N�֐��̓o�^
	glutDisplayFunc(display);
	glutReshapeFunc(resize);
	glutTimerFunc(100, timer, 0);
	glutMotionFunc(mouse_motion);
	glutPassiveMotionFunc(mouse_motion);
	glutKeyboardFunc(keyboard);
	//glutMouseFunc(mouse);
	//glutKeyboardUpFunc(keyboard_up);

	// ������
	init();

	// ���C�����[�v
	glutMainLoop();

	return 0;
}


/* ���������� */
void init() {
	// �w�i�F
	glClearColor(0.0, 0.0, 1.0, 1.0);

	// �[�x�e�X�g�L����
	glEnable(GL_DEPTH_TEST);

	// �J�����O�L����
	// -�w�������Ă���ʂ��폜
	// -�}�`�̒��_�������v����̏ꍇ�w�������Ă���Ɣ��f����
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CW);
	glFrontFace(GL_BACK);

	// ���C�g
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	//glLightfv(GL_LIGHT1, GL_DIFFUSE, green);

	// �}�E�X�J�[�\����\��
	glutSetCursor(GLUT_CURSOR_NONE);
}



/*-----------------------------------------------------------------------------------*
	��ʕ`������
*-----------------------------------------------------------------------------------*/

/* �`�揈���{�� */
void display(void)
{
	// �o�b�N�o�b�t�@�N���A
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// �ϊ��s�񏉊���
	glLoadIdentity();

	// ���_�ʒu�Ǝ�������
	gluLookAt(camera.x, camera.y, camera.z, camera.lookat_x(), camera.lookat_y(), camera.lookat_z(), 0.0, 1.0, 0.0);

	// �����̈ʒu�ݒ�
	glLightfv(GL_LIGHT0, GL_POSITION, light0.pos());
	//glLightfv(GL_LIGHT1, GL_POSITION, light1pos);

	/* ---------- �����̗����� ---------- */
	glPushMatrix();
	static int a = 5;
	glTranslated(++a, 0, 0);
	/* �}�`�̉�] */
	glRotated(25, 0.0, 1.0, 0.0);

	/* �}�`�̐F (��)  */
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

	/* �}�`�̕`�� */
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

	///* ---------- ���E�̕� ---------- */
	//glPushMatrix();

	//glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, white);

	///* �}�`�̕`�� */
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

	
	///* �����������]�p�� 0 �ɖ߂� */
	//if (isAPushed) if (++r >= 360) r = 0;
}

/* �^�C�}�[ */
void timer(int) {
	glutPostRedisplay();
	glutTimerFunc(16, timer, 0);
}

/* �E�B���h�E�T�C�Y�ύX */
void resize(int w, int h) {
	glViewport(0, 0, w, h);

	/* �����ϊ��s��̐ݒ� */
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90.0, (double)w / (double)h, 1.0, 50.0);

	/* ���f���r���[�ϊ��s��̐ݒ� */
	glMatrixMode(GL_MODELVIEW);
}



/*-----------------------------------------------------------------------------------*
	���͊֌W
 *-----------------------------------------------------------------------------------*/

/* �}�E�X���ړ����� */
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

/* �L�[�{�[�h�������ꂽ */
void keyboard(unsigned char key, int x, int y) {
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