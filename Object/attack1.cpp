//Copyright (c) 2020 Li Yixuan All rights reserved.
//Date : 2020-05-15

#include "attack1.h"

Attack1::Attack1()
{
	this->releaseIt();

	QString pic_path = QString(ATTACK_1_PIC);
	pic = new QPixmap;
	pic->load(pic_path);

	setEachPoint();
}

Attack1::~Attack1()
{}

void Attack1::useIt()
{
	is_free = 0;
	is_in_screen = 0;
	reLoc();
}

void Attack1::updateLoc()
{
	if (isFree())
		return;
	loc.first -= Config::rocketSpeed();
	if (!is_in_screen && (loc.first <= WINDOW_WIDTH))
	{
		is_in_screen = 1;
		emit this->playShootMusic();
	}
	if (loc.first <= -pic->width())
	{
		is_in_screen = 0;
		releaseIt();
	}
}

void Attack1:: reLoc()
{
	srand(rander);
	double height = rander = (rand() % ((int)(FLOOR_Y - pic->height())));
	loc = std::make_pair(
		WINDOW_WIDTH + Config::rocketSpeed() * SIGN_DELAY_TIME / REFRESH_RATE, height);
}

void Attack1::setEachPoint()
{
	each_point.push_back(std::make_pair(17, 11));
	each_point.push_back(std::make_pair(4, 19));
	each_point.push_back(std::make_pair(17, 28));
	each_point.push_back(std::make_pair(33, 28));
	each_point.push_back(std::make_pair(40, 38));
	each_point.push_back(std::make_pair(64, 35));
	each_point.push_back(std::make_pair(47, 28));
	each_point.push_back(std::make_pair(86, 28));
	each_point.push_back(std::make_pair(93, 38));
	each_point.push_back(std::make_pair(105, 38));
	each_point.push_back(std::make_pair(99, 26));
	each_point.push_back(std::make_pair(107, 20));
	each_point.push_back(std::make_pair(100, 12));
	each_point.push_back(std::make_pair(105, 3));
	each_point.push_back(std::make_pair(94, 1));
	each_point.push_back(std::make_pair(85, 11));
	each_point.push_back(std::make_pair(46, 11));
	each_point.push_back(std::make_pair(51, 2));
}

std::vector <Point> Attack1::getEachPoint()
{
	std::vector <Point> tmpVec;
	for (int i = 0, lim = each_point.size(); i < lim; i++)
		tmpVec.push_back(std::make_pair(each_point[i].first + loc.first,
																		each_point[i].second + loc.second));
	return tmpVec;
}

double Attack1::getHeightMid()
{
	return loc.second + pic->height() / 2;
}
