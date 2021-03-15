//Copyright (c) 2020 Li Yixuan All rights reserved.
//Date : 2020-05-15

#include "map.h"

Map::Map()
{
	map1 = new QPixmap;
	map2 = new QPixmap;
	map1->load(GAME_BACKGROUND);
	map2->load(GAME_BACKGROUND);

	map1_X = 0;
	map2_X = WINDOW_WIDTH;
}

Map::~Map()
{
	delete map1; map1 = nullptr;
	delete map2; map2 = nullptr;
}

void Map::refresh()
{
	map1_X -= Config::gameSpeed();
	if (map1_X <= -WINDOW_WIDTH)
		map1_X += WINDOW_WIDTH;
	map2_X -= Config::gameSpeed();
	if (map2_X <= 0)
		map2_X += WINDOW_WIDTH;
}

double Map::get1X()
{
	return map1_X;
}

double Map::get2X()
{
	return map2_X;
}

double Map::get1Y()
{
	return map1_Y;
}

double Map::get2Y()
{
	return map2_Y;
}

QPixmap* Map::getMap1()
{
	return map1;
}

QPixmap* Map::getMap2()
{
	return map2;
}
