#pragma once

#define _USE_MATH_DEFINES
#include <cmath>

class gameObject {
public:
	// ç¿ïW
	double x;
	double y;
	double z;
	// âÒì]é≤[rad]
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
	const double movespeed = 0.001;
	double theta_xy;
	double theta_xz;

	myCamera() :
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