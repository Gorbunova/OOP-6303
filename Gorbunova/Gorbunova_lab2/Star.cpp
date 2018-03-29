#include "stdafx.h"
#include "Star.h"
#include <iostream>


Star::Star(Point center, Point vertex1, Point vertex2, RGB color)
{
	if ((!(center == vertex1)) && (!(center == vertex2)) && (!(vertex1 == vertex2)))
	{
		Vertices[0] = vertex1;
		Vertices[1] = vertex2;
		Color = color;
		ID = Number;
		Number++;
		Center = center;
		Name = "Star";
	}
	else
	{
		ID = -1;
		Point Nullp(0, 0);
		Vertices[0] = Nullp;
		Vertices[1] = Nullp;
		Name = "Error";
	}
}

void Star::Move(Point point)
{
	Point difference = point - Center;
	Vertices[0] = Vertices[0] + difference;
	Vertices[1] = Vertices[1] + difference;
	Center = Center + difference;
}

void Star::RotateAroundPoint(Point point, double angle)
{
	Vertices[0].RotatePoint(point, angle);
	Vertices[1].RotatePoint(point, angle);
	Center.RotatePoint(point, angle);
}

void Star::Scale(double k)
{
	Vertices[0] = Vertices[0] * k;
	Vertices[1] = Vertices[1] * k;
}

void Star::SetColor(RGB NewColor)
{
	Color = NewColor;
}

RGB Star::GetColor()
{
	return Color;
}



void Star::Print(ostream & outstream)
{
	outstream << "Name:\t" << Name << endl;
	outstream << "ID:\t" << ID << endl;
	outstream << "Center:\t(" << Center.X << "; " << Center.Y << ")" << endl;
	outstream << "Vertices:\t";
	for (int i = 0; i < 2; i++)
		cout << "(" << Vertices[i].X << "; " << Vertices[i].Y << ") ";
	outstream << endl;
	outstream << "Color:\t(" << Color.Red << "; " << Color.Green << "; " << Color.Blue << ")" << endl;
}