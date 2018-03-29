#pragma once
#include "point.h"

using namespace std;

struct RGB
{
	int Red;
	int Green;
	int Blue;
};

class Shape
{
public:
	Point Center;
	RGB Color;
	int Number;
	int ID;
	string Name;

	virtual void Move(Point point) = 0;
	virtual void RotateAroundPoint(Point point, double degAngle) = 0;
	virtual void Scale(double k) = 0;
	virtual void SetColor(RGB NColor) = 0;
	virtual RGB GetColor() = 0;
	virtual void Print(ostream& outstream) = 0;
	friend ostream& operator<<(std::ostream& outstream, Shape& object);
};