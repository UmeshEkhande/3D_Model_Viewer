#pragma once
#include "pch.h"

class GEOMETRY_API Point2D
{

public:
	Point2D();
	Point2D(float inX, float inY);
	~Point2D();

public:
	float x();
	float y();

	void setX(float inX);
	void setY(float inY);

private:
	float mX;
	float mY;
};

