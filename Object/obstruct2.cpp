//Copyright (c) 2020 Li Yixuan All rights reserved.
//Date : 2020-05-15

#include "obstruct2.h"

Obstruct2::Obstruct2(int type)
{
	this->type = type;
	this->releaseIt();

	QString pic_path = QString(OBSTRUCT_2_PIC).arg(type);
	pic = new QPixmap();
	pic->load(pic_path);
	loadLengthXY();

	setEachPoint();
}

Obstruct2::~Obstruct2()
{}

void Obstruct2::updateLoc()
{
	if (isFree())
		return;
	loc.first -= Config::gameSpeed();
	if (loc.first <= -pic->height())
		releaseIt();
}

void Obstruct2::reLoc()
{
	srand(time(NULL));
	double height = (rand() % ((int)(FLOOR_Y - pic->height())));
	loc = std::make_pair(WINDOW_WIDTH, height);
}

void Obstruct2::setEachPoint()
{
	XX = Config::getObstacle2EachPointX(type);
	YY = Config::getObstacle2EachPointY(type);
}

std::vector <Point> Obstruct2::getEachPoint()
{
	std::vector <Point> tmp;
	if (angle >= 0)
	{
		tmp.push_back(std::make_pair(YY * angle_SIN, 0));
		tmp.push_back(std::make_pair(0, YY * angle_COS));
		tmp.push_back(std::make_pair(XX * angle_COS, XX * angle_SIN + YY * angle_COS));
		tmp.push_back(std::make_pair(XX * angle_COS + YY * angle_SIN, XX * angle_SIN));
	}
	else
	{
		tmp.push_back(std::make_pair(0, XX * angle_SIN));
		tmp.push_back(std::make_pair(YY * angle_SIN, YY * angle_COS + XX * angle_SIN));
		tmp.push_back(std::make_pair(YY * angle_SIN + XX * angle_COS, YY * angle_COS));
		tmp.push_back(std::make_pair(XX * angle_COS, 0));
	}
	for (int i = 0, lim = tmp.size(); i < lim; i++)
	{
		tmp[i].first	+= loc.first;
		tmp[i].second += loc.second;
	}
	return tmp;
}

void Obstruct2::useIt()
{
	is_free = 0;
	this->reLoc();
	srand(time(NULL));
	angle = rand() % 181 - 90;
	angle_ABS = (angle >= 0 ? angle : -angle);
	setSINCOS();

	QMatrix mat;
	mat.rotate(angle);
	pic_tmp = pic->transformed(mat, Qt::SmoothTransformation);
	mat.rotate(-angle);
}

void Obstruct2::releaseIt()
{
	is_free = 1;
}

int Obstruct2::getType()
{
	return type;
}

QPixmap* Obstruct2::getPicRotated()
{
	return &pic_tmp;
}
