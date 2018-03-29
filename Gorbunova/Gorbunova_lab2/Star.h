#pragma once
#include "Shape.h"

class Star : public Shape
{
	Point Vertices[2];

public:
	Star(Point center, Point vertex1, Point vertex2, RGB color);
	void Move(Point point);
	void RotateAroundPoint(Point point, double angle);
	void Scale(double k);
	void SetColor(RGB NColor);
	RGB GetColor();
	void Print(ostream& outstream);
	friend ostream& operator<<(std::ostream& out, Shape& in);
};