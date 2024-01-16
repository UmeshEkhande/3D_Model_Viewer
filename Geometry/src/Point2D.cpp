#include "pch.h"
#include "Point2D.h"

Point2D::Point2D()
{
	mX = 0.0f;
	mY = 0.0f;
}

Point2D::Point2D(float inX, float inY) : mX(inX), mY(inY)
{
}

Point2D::~Point2D()
{
}

float Point2D::x()
{
	return mX;
}

float Point2D::y()
{
	return mY;
}

void Point2D::setX(float inX)
{
	mX = inX;
}

void Point2D::setY(float inY)
{
	mY = inY;
}
