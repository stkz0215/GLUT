#pragma once
#include <list>
#include <random>
#include <cmath>
#include <GL/glut.h>
#include "gameObject.hpp"

#define WINDOW_NAME "Test"
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

enum myState {MYSTATE_TITLE, MYSTATE_GAME};

using namespace std;

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

class myGameScene {
public:
	myState state;
	unsigned long long int frames;
	myWindow *window;
	myCamera camera;
	myLight light0;
	list<myObject> enemy;
	myObject ray;

	myGameScene(){}

	myGameScene(myWindow* _w) :
		state(MYSTATE_TITLE),
		window(_w),
		frames(0),
		camera(myCamera()),
		light0(myLight())
	{

	}

	void update() {
		switch (state) {
		case MYSTATE_TITLE:
			
			break;
		case MYSTATE_GAME:
			/* ---------------
				衝突判定
			   --------------- */
			if (ray.dist > 0) {
				printf("\n\n\n\n\nray\n");
				double ln = 10000000;
				double norm[] = { ray.pos_x() / ray.dist, ray.pos_y()/ray.dist , ray.pos_z()/ray.dist };
				auto itr = enemy.begin();
				while (itr != enemy.end()) {
					double t = (norm[0]*itr->pos_x() + norm[1]*itr->pos_y() + norm[2]*itr->pos_z()) / ray.dist;
					double vt[] = {ray.pos_x()*t, ray.pos_y()*t, ray.pos_z()*t };
					double h[] = {vt[0]-itr->pos_x(), vt[1]-itr->pos_y(), vt[2]-itr->pos_z()};
					double len = sqrt(h[0]*h[0] + h[1]*h[1] + h[2]*h[2]);

					ln = (ln < len) ? ln : len;
					if (len < 1) itr = enemy.erase(itr);
					else itr++;
				}
				printf("len:%f, enemy:%d\n", ln, enemy.size());
				ray = myObject();
			}
			/* ---------------
				オブジェクト移動
			   --------------- */
			random_device rnd;     // 非決定的な乱数生成器を生成
			mt19937 mt(rnd());     //  メルセンヌ・ツイスタの32ビット版、引数は初期シード値
			uniform_real_distribution<> rand_rad(0, M_PI);
			if (frames%300 == 0) {
				for (int i = 0; i < 5; i++) {
					enemy.push_back(myObject(50, 0.05, rand_rad(mt)/2-M_PI_4, 2*rand_rad(mt), 0, 0));
				}
			}

			auto itr = enemy.begin();
			while (itr != enemy.end()) {
				itr->dist -= itr->v_dist;
				itr->theta_xy += itr->v_theta_xy;
				//itr->theta_xz += itr->v_theta_xz;
				if (itr->theta_xy <= -M_PI || M_PI <= itr->theta_xy) itr->theta_xy = 0;
				//if (itr->theta_xz <= -M_PI || M_PI <= itr->theta_xz) itr->theta_xz = 0;
				
				if (itr->dist <= 1) itr = enemy.erase(itr);
				else itr++;
			}
			frames++;
			break;
		}
	}
};
