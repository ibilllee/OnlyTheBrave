//Copyright (c) 2020 Li Yixuan All rights reserved.
//Date : 2020-05-15

#ifndef OVERLAPDETECTION_H
#define OVERLAPDETECTION_H

#include "config.h"
#include <iostream>
#include <vector>

#define eps 1e-1

typedef std::pair <double, double> Point;

class OverlapDetection
{
public:
	static bool check(std::vector <Point>, std::vector <Point> );
	static bool check1(Point, std::vector <Point> );
	static bool check2(Point, Point, Point, Point);
	static double mult(Point, Point, Point);
};

#endif // OVERLAPDETECTION_H
