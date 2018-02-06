/*
	main.cpp
	��O�̏��������Ă���
*/

#include <GL/glut.h>
#include "gameObject.hpp"
#include "main.hpp"
#include "title.hpp"
#include "gameMain.hpp"

/* �O���[�o���ϐ� */
/*
myWindow window = myWindow();
myCamera camera = myCamera();
myLight light0 = myLight(0, 0, 0);
*/
myGameScene scene;

/* �֐��v���g�^�C�v */
void init();
void display();
void timer(int);
void resize(int, int);
void mouse(int, int, int, int);
void mouse_motion(int, int);
void keyboard(unsigned char, int, int);


/*-----------------------------------------------------------------------------------*
	���C���֐��A������
 *-----------------------------------------------------------------------------------*/

 /* ���C���֐� */
int main(int argc, char *argv[]) {
	// GLUT������
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_RGBA);


	// �E�B���h�E�쐬
	myWindow* window = new myWindow();
	window->createWindow();

	// �V�[���쐬
	scene = myGameScene(window);

	// �R�[���o�b�N�֐��̓o�^
	glutDisplayFunc(display);
	glutReshapeFunc(resize);
	glutTimerFunc(100, timer, 0);
	glutMouseFunc(mouse);
	glutMotionFunc(mouse_motion);
	glutPassiveMotionFunc(mouse_motion);
	glutKeyboardFunc(keyboard);
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
	glClearColor(0.8, 0.8, 0.8, 1.0);

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
	//glLightfv(GL_	1, GL_DIFFUSE, green);
}



/*-----------------------------------------------------------------------------------*
	��ʕ`������
*-----------------------------------------------------------------------------------*/

/* �`�揈���{�� */
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

/* �^�C�}�[ */
void timer(int) {
	glutTimerFunc(16, timer, 0);
	glutPostRedisplay();
	scene.update();
}

/* �E�B���h�E�T�C�Y�ύX */
void resize(int w, int h) {
	glViewport(0, 0, w, h);

	/* �����ϊ��s��̐ݒ� */
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (double)w / (double)h, 0.1, 100.0);

	/* ���f���r���[�ϊ��s��̐ݒ� */
	glMatrixMode(GL_MODELVIEW);
}



/*-----------------------------------------------------------------------------------*
	���͊֌W
 *-----------------------------------------------------------------------------------*/

/* �}�E�X�̃{�^���������ꂽ */
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

/* �}�E�X���ړ����� */
void mouse_motion(int x, int y) {
	switch (scene.state) {
	case MYSTATE_TITLE:
		break;
	case MYSTATE_GAME:
		gameMouse_motion(&scene, x, y);
		break;
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