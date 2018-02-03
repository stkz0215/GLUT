#pragma once
#include <GL/glut.h>
#include <cstdio>

#define WINDOW_NAME "Test"
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

class myWindow {
public:
	int width;
	int height;
	int center_x;
	int center_y;

	myWindow() :
		width(WINDOW_WIDTH),
		height(WINDOW_HEIGHT),
		center_x(100),//glutGet(GLUT_SCREEN_WIDTH)/2 - width/2),
		center_y(100)//glutGet(GLUT_SCREEN_HEIGHT)/2 - height/2)

	{
		
	}

	void createWindow() {
		glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
		glutInitWindowPosition(center_x, center_y);
		glutInitWindowSize(width, height);
		glutCreateWindow(WINDOW_NAME);
	}

};