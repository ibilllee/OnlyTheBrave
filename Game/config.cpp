//Copyright (c) 2020 Li Yixuan All rights reserved.
//Date : 2020-05-15

#include "config.h"
#include <QDebug>
#include <QtMath>

bool is_playing_music;
clock_t startTime;
clock_t nowTime;
clock_t tmpTime;
QString storage_path = QStandardPaths::writableLocation(QStandardPaths::HomeLocation) +
											 "/AppData/Local/OLB_Record.txt";
unsigned rander;

Config::Config()
{}

double Config::gameSpeed()
{
	double tmp = pow((0.0001 * (clock() - startTime) + 5.0), 0.4) - 1.4;
	return tmp * REFRESH_RATE / 2.0;
}

double Config::rocketSpeed()
{
	return gameSpeed() * 3.0;
}

double Config::getObstacle2EachPointY(int type)
{
	double height;
	if (type == 1)
		height = 217;
	else if (type == 2)
		height = 174;
	else if (type == 3)
		height = 128;
	else if (type == 4)
		height = 108;
	else
		height = 76;
	return height;
}

double Config::getObstacle2EachPointX(int type)
{
	if (type)
		return 36;
	return 36;
}
