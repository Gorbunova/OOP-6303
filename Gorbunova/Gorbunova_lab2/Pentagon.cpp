#include "stdafx.h"
#include "Pentagon.h"
#include "point.h"



Pentagon::Pentagon(Point vert, Point cent, RGB color)
{
	if (!(vert == cent))
	{
		vertex = vert;
		Color = color;
		ID = Number;
		Number++;
		Center = cent;
		Name = "Pentagon";
	}
	else
	{
		ID = -1;
		for (int i = 0; i < 2; i++)
		{
			Point Nullp(0, 0);
			vertex = Nullp;
			Center = Nullp;
		}
		Name = "Error";
	}
}
void Pentagon::Move(Point point)
{
	Point difference = point - Center;
	vertex = vertex + difference;
	Center = Center + difference;
}

void Pentagon::RotateAroundPoint(Point point, double angle)
{
	vertex.RotatePoint(point, angle);
	Center.RotatePoint(point, angle);
}

void Pentagon::Scale(double k)
{
	vertex = vertex*k;
}

void Pentagon::SetColor(RGB NewColor)
{
	Color = NewColor;
}

RGB Pentagon::GetColor()
{
	return Color;
}



void Pentagon::Print(ostream & outstream)
{
	outstream << "Name:\t" << Name << endl;
	outstream << "ID:\t" << ID << endl;
	outstream << "Center:\t(" << Center.X << "; " << Center.Y << ")" << endl;
	outstream << "Vertex:\t(" << vertex.X << ";"<< vertex.Y << ")" << endl;
	outstream << "Color:\t(" << Color.Red << "; " << Color.Green << "; " << Color.Blue << ")" << endl;
}