
#include "stdafx.h"
#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include "Star.h"
#include "Pentagon.h"
#include "Triangle.h"
#include "point.h"
#include "Sircle.h"



using namespace System;

int main()
{
	struct RGB red = { 255,0,0 };
	struct RGB green = { 0,192,0 };
	struct RGB blue = { 0,32,255 };
	double rad = 90 * (M_PI / 180);


//КРУГ
	/*Circle cir({4,4}, 2, green);
	cout << cir << endl;
	cout << "...Scaling..." << endl;
	cir.Scale(2);
	cout << cir << endl;
	cout << "...Rotation..." << endl;
	cout << "...Color setting..." << endl;
	cir.RotateAroundPoint({4,1}, rad);
	cir.SetColor(blue);
	cout << cir << endl;
	cout << "...Moving..."<< endl;
	cir.Move( {2,1});
	cout << cir << endl;*/


	/*
	//ПЯТИУГОЛЬНИК
	Pentagon pent({6,6},{5,3} , blue);
	cout << pent << endl;
	cout << "...Color setting..." << endl;
	pent.SetColor(red);
	cout << "...Moving..." << endl;
	pent.Move({ 4,0 });
	cout << pent << endl;
	cout << "...Scaling..." << endl;
	pent.Scale(1.5);
	cout << pent << endl;
	cout << "...Rotation..." << endl;
	pent.RotateAroundPoint({4,0}, rad );
	cout << pent << endl;*/
	/*
	//ЗВЕЗДА
	Star zvezd({ 5,2.5 }, { 8,6 }, {5.5, 4.5}, green);
	cout << zvezd << endl;
	cout << "...Color setting..." << endl;
	zvezd.SetColor(red);
	cout << "...Moving..." << endl;
	zvezd.Move({ 3,0 });
	cout << zvezd << endl;
	cout << "...Scaling..." << endl;
	zvezd.Scale(2);
	cout << zvezd << endl;
	cout << "...Rotation..." << endl;
	zvezd.RotateAroundPoint({ 3,0 }, rad);
	cout << zvezd << endl; */



    return 0;
}
