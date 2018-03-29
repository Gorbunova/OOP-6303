#pragma once
#include "Shape.h"

class Circle : public Shape
{
public:
	Circle(Point center, double radius, RGB color);
	void Move(Point point);
	void RotateAroundPoint(Point point, double angle);
	void Scale(double k);
	void SetColor(RGB NewColor);
	RGB GetColor();
	double get_radius();
	void Print(ostream& outstream);
	friend ostream& operator<<(std::ostream& out, Shape& in);

private:
	Point center;
	double Radius;
};