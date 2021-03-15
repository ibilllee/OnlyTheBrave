//Copyright (c) 2020 Li Yixuan All rights reserved.
//Date : 2020-05-15

#include "coin.h"

Coin::Coin()
{
	this->releaseIt();

	pic = new QPixmap;
	pic->load(COIN_PIC);

	setEachPoint();
}

Coin::~Coin()
{}

void Coin::reLoc()
{
	int tmp = rand() % (int)(FLOOR_Y - pic->height());

	loc = std::make_pair(WINDOW_WIDTH, tmp);
}

unsigned test = 0;

void Coin::updateLoc()
{
	if (is_free)
		return;
	loc.first -= Config::gameSpeed();
	if (loc.first <= -pic->width())
		releaseIt();
}

void Coin::setEachPoint()
{
	each_point.push_back(std::make_pair(50, 0));
	each_point.push_back(std::make_pair(25, 6));
	each_point.push_back(std::make_pair(7, 22));
	each_point.push_back(std::make_pair(0, 50));
	each_point.push_back(std::make_pair(7, 94));
	each_point.push_back(std::make_pair(25, 78));
	each_point.push_back(std::make_pair(50, 100));
	each_point.push_back(std::make_pair(75, 78));
	each_point.push_back(std::make_pair(93, 94));
	each_point.push_back(std::make_pair(100, 50));
	each_point.push_back(std::make_pair(93, 22));
	each_point.push_back(std::make_pair(75, 6));
}

std::vector <Point> Coin::getEachPoint()
{
	std::vector <Point> tmpVec;
	for (int i = 0, lim = each_point.size(); i < lim; i++)
		tmpVec.push_back(std::make_pair(each_point[i].first + loc.first,
																		each_point[i].second + loc.second));
	return tmpVec;
}
