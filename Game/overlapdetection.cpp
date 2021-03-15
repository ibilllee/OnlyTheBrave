//Copyright (c) 2020 Li Yixuan All rights reserved.
//Date : 2020-05-15

#include "overlapdetection.h"

using std::max;
using std::min;
#include <QThread>
#include <QDebug>

bool OverlapDetection::check(std::vector <Point> a, std::vector <Point> b)
{
	int aSize = a.size();
	int bSize = b.size();
	for (int i = 0; i < aSize; i++)
		if (check1(a[i], b) == 1)
			return 1;
	for (int i = 0; i < aSize; i++)
		for (int j = 0; j < bSize; j++)
			if (check2(a[i], a[(i + 1) % aSize], b[j], b[(j + 1) % bSize]) == 1)
				return 1;
	return 0;
}

bool OverlapDetection::check1(Point p, std::vector <Point> b)
{
	int nCross = 0;
	int bSize	 = b.size();
	for (int i = 0; i < bSize; i++)
	{
		Point p1 = b[i];
		Point p2 = b[(i + 1) % bSize];
		if (p1.second == p2.second)
			continue;
		if (p.second < std::min(p1.second, p2.second))
			continue;
		if (p.second >= std::max(p1.second, p2.second))
			continue;
		double x = (double)(p.second - p1.second) * (double)(p2.first - p1.first) /
							 (double)(p2.second - p1.second) + p1.first;
		if (x > p.first)
			nCross++;
	}
	return (nCross & 1);
}

double OverlapDetection::mult(Point p0, Point p1, Point p2)
{
	return (p0.first - p1.first) * (p0.second - p2.second) - (p0.second - p1.second) *
				 (p0.first - p2.first);
}

bool OverlapDetection::check2(Point a, Point b, Point c, Point d)
{
	if (max(a.first, b.first) < min(c.first, d.first))
		return false;
	if (max(a.second, b.second) < min(c.second, d.second))
		return false;
	if (max(c.first, d.first) < min(a.first, b.first))
		return false;
	if (max(c.second, d.second) < min(a.second, b.second))
		return false;
	if (mult(a, c, b) * mult(a, b, d) < 0)
		return false;
	if (mult(c, a, d) * mult(c, d, b) < 0)
		return false;
	return true;
}
