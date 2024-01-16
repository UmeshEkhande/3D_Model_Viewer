#pragma once
#include "pch.h"

class GEOMETRY_API Point3D
{

public:
	Point3D();
	Point3D(float inX, float inY , float inZ);
	~Point3D();

public:
	float x();
	float y();
	float z();

	void setX(float inX);
	void setY(float inY);
	void setZ(float inZ);

private:
	float mX;
	float mY;
	float mZ;
};
