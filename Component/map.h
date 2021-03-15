//Copyright (c) 2020 Li Yixuan All rights reserved.
//Date : 2020-05-15

#ifndef MAP_H
#define MAP_H

#include "../Game/config.h"
#include <QPixmap>

class Map
{
public:
	Map();
	~Map();
	void refresh();
	double get1X();
	double get2X();
	double get1Y();
	double get2Y();
	QPixmap* getMap1();
	QPixmap* getMap2();

private:
	QPixmap* map1;
	QPixmap* map2;

	double map1_X;
	double map2_X;
	const double map1_Y = 0;
	const double map2_Y = 0;
};

#endif // MAP_H
