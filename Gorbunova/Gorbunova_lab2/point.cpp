#include "stdafx.h"
#include "point.h"
#include <iostream>


Point::Point()
	: X(0), Y(0)
{}

Point::Point(double x = 0, double y = 0)
	: X(x), Y(y)
{}

Point::Point(const Point & p)
{
	X = p.X;
	Y = p.Y;
}

void Point::RotatePoint(Point around, double degAngle)
{
	Point rotpoint(0, 0);
	rotpoint.X = (around.X + (this->X - around.X) * cos(degAngle ) - (this->Y - around.Y) * sin(degAngle ));
	rotpoint.Y = (around.Y + (this->Y - around.Y) * cos(degAngle ) + (this->X - around.X) * sin(degAngle ));
	this->X = rotpoint.X;
	this->Y = rotpoint.Y;
}

Point Point::operator -(const Point& p)
{
	Point tmp(this->X - p.X, this->Y - p.Y);
	return tmp;
}

Point Point::operator+(const Point & p)
{
	return Point(X + p.X, Y + p.Y);
}

Point& Point::operator=(const Point& p)
{
	if (this != &p)
	{
		this->X = p.X;
		this->Y = p.Y;
	}
	return *this;
}

bool Point::operator==(const Point & p)
{
	return (X == p.X) && (Y == p.Y);
}

Point Point::operator*(double a)
{
	this->X = this->X * a;
	this->Y = this->Y * a;
	return *this;
}