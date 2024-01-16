#include "pch.h"
#include "Point3D.h"

Point3D::Point3D()
{
}

Point3D::Point3D(float inX, float inY, float inZ) : mX(inX), mY(inY), mZ(inZ)
{
}

Point3D::~Point3D()
{
}

float Point3D::x()
{
	return mX;
}

float Point3D::y()
{
	return mY;
}

float Point3D::z()
{
	return mZ;
}

void Point3D::setX(float inX)
{
	mX = inX;
}

void Point3D::setY(float inY)
{
	mY = inY;
}

void Point3D::setZ(float inZ)
{
	mZ = inZ;
}
