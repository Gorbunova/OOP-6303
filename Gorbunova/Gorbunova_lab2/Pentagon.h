
#pragma once
#include "Shape.h"
class Pentagon :
	public Shape
{
	Point vertex;

public:
	class Pentagon(Point vert, Point cent, RGB color);
	void Move(Point point);
	void RotateAroundPoint(Point point, double angle);
	void Scale(double k);
	void SetColor(RGB NewColor);
	RGB GetColor();
	void Print(ostream& outstream);
	friend ostream& operator<<(std::ostream& out, Shape& in);
};