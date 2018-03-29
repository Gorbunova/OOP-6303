#pragma once

#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include <string>

class Point
{
public:
	double X;
	double Y;

	Point();
	Point(const Point& p);
	Point(double x, double y);
	void RotatePoint(Point around, double degAngle);
	Point operator-(const Point& p);
	Point operator+(const Point& p);
	Point& operator=(const Point& p);
	bool operator==(const Point& p);
	Point operator*(double a);
};