#include "stdafx.h"
#include "Sircle.h"
#include "point.h"

Circle::Circle(Point center, double radius, RGB color)
{
	Radius = radius;
	if (radius != 0)
	{
		Color = color;
		Center = center;
		ID = Number;
		Number++;
		Name = "Circle";
	}
	else
	{
		Point NullP(0, 0);
		for (int i = 0; i < 3; i++)
			center = NullP;
		ID = -1;
		Name = "Error";
	}
}

void Circle::Move(Point newcenter)
{
	Center = newcenter;
}

void Circle::RotateAroundPoint(Point point, double angle)
{
	Center.RotatePoint(point, angle);
}

void Circle::Scale(double k)
{
	Radius *= k;
}

void Circle::SetColor(RGB NewColor)
{
	Color = NewColor;
}

RGB Circle::GetColor()
{
	return Color;
}


double Circle::get_radius()
{
	return Radius;
}

void Circle::Print(ostream & outstream)
{
	outstream << "Name:\t" << Name << endl;
	outstream << "ID:\t" << ID << endl;
	outstream << "Center:\t(" << Center.X << "; " << Center.Y << ")" << endl;
	outstream << "Radius:\t" << Radius << endl;
	outstream << "Color:\t(" << Color.Red << "; " << Color.Green << "; " << Color.Blue << ")" << endl;
}
