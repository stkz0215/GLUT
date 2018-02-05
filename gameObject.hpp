/*
	gameObject.hpp
	ゲームオブジェクトに関するクラス群
 */

#pragma once

#define _USE_MATH_DEFINES
#include <cmath>

class gameObject {
public:
	// 座標
	double x;
	double y;
	double z;
	// 回転軸[rad]
	double axis_x;
	double axis_y;
	double axis_z;

	gameObject() :
		x(0),
		y(0),
		z(0),
		axis_x(0),
		axis_y(0),
		axis_z(0)
	{
	
	};

	gameObject(double _x, double _y, double _z) :
		x(_x),
		y(_y),
		z(_z),
		axis_x(0),
		axis_y(0),
		axis_z(0)
	{
	
	};
};

class myCamera : public gameObject  {
public:
	double movespeed;
	double theta_xy;
	double theta_xz;

	myCamera() :
		movespeed(0.001),
		theta_xy(0),
		theta_xz(0)
	{

	};

	double lookat_x() {
		return cos(theta_xy) * cos(theta_xz);
	}
	double lookat_y() {
		return sin(theta_xy);
	}
	double lookat_z() {
		return sin(theta_xz)*cos(theta_xy);
	}

};

class myLight : public gameObject {
public:
	double w;

	myLight() :
		w(1)
	{

	}

	myLight(double _x, double _y, double _z) :
		gameObject(_x, _y, _z),
		w(1)
	{

	}

	GLfloat *pos() {
		GLfloat ret[] = { x, y, z, w };
		return ret;
	}
};

class myObject : public gameObject {
public:
	double dist; // 原点からの距離
	double v_dist; // 速度
	double theta_xy;
	double theta_xz;
	double v_theta_xy; // 速度
	double v_theta_xz;

	myObject() :
		dist(0),
		v_dist(0),
		theta_xy(0),
		theta_xz(0),
		v_theta_xy(0),
		v_theta_xz(0)
	{

	}

	myObject(double _d, double _vd, double _txy, double _txz, double _vtxy, double _vtxz) :
		dist(_d),
		v_dist(_vd),
		theta_xy(_txy),
		theta_xz(_txz),
		v_theta_xy(_vtxy),
		v_theta_xz(_vtxz)
	{

	}

	double pos_x() {
		return dist * cos(theta_xy) * cos(theta_xz);
	}
	double pos_y() {
		return dist * sin(theta_xy);
	}
	double pos_z() {
		return dist * sin(theta_xz) * cos(theta_xy);
	}
};

class myBullet : public gameObject {

};