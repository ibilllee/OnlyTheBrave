//Copyright (c) 2020 Li Yixuan All rights reserved.
//Date : 2020-05-15

#include "obstruct1.h"

Obstruct1::Obstruct1(int type)
{
	this->type = type;
	this->releaseIt();

	srand(rander);
	pic_type	= rander = rand();
	pic_type %= 4;
	if (type == 1)
		pic_type++;
	else
		pic_type += 5;
	QString pic_path = QString(OBSTRUCT_1_PIC).arg(pic_type);
	pic = new QPixmap();
	pic->load(pic_path);
	loadLengthXY();

	setEachPoint();
}

Obstruct1::~Obstruct1()
{}

void Obstruct1::updateLoc()
{
	if (isFree())
		return;
	loc.first -= Config::gameSpeed();
	if (loc.first <= -pic->width())
		releaseIt();
}

void Obstruct1::reLoc()
{
	if (type == 1)
		loc = std::make_pair(WINDOW_WIDTH, FLOOR_Y - pic->height());
	else
		loc = std::make_pair(WINDOW_WIDTH, 0);
}

void Obstruct1::setEachPoint()
{
	each_point[1].push_back(std::make_pair(97, 3));
	each_point[1].push_back(std::make_pair(49, 11));
	each_point[1].push_back(std::make_pair(13, 44));
	each_point[1].push_back(std::make_pair(10, 137));
	each_point[1].push_back(std::make_pair(95, 156));
	each_point[1].push_back(std::make_pair(199, 135));
	each_point[1].push_back(std::make_pair(187, 52));
	each_point[1].push_back(std::make_pair(131, 34));

	each_point[2].push_back(std::make_pair(144, 3));
	each_point[2].push_back(std::make_pair(45, 15));
	each_point[2].push_back(std::make_pair(2, 85));
	each_point[2].push_back(std::make_pair(16, 147));
	each_point[2].push_back(std::make_pair(106, 164));
	each_point[2].push_back(std::make_pair(212, 134));
	each_point[2].push_back(std::make_pair(219, 70));
	each_point[2].push_back(std::make_pair(177, 18));

	each_point[3].push_back(std::make_pair(109, 9));
	each_point[3].push_back(std::make_pair(60, 26));
	each_point[3].push_back(std::make_pair(25, 61));
	each_point[3].push_back(std::make_pair(5, 151));
	each_point[3].push_back(std::make_pair(119, 180));
	each_point[3].push_back(std::make_pair(224, 155));
	each_point[3].push_back(std::make_pair(213, 74));
	each_point[3].push_back(std::make_pair(153, 18));

	each_point[4].push_back(std::make_pair(99, 10));
	each_point[4].push_back(std::make_pair(35, 34));
	each_point[4].push_back(std::make_pair(9, 95));
	each_point[4].push_back(std::make_pair(10, 161));
	each_point[4].push_back(std::make_pair(123, 175));
	each_point[4].push_back(std::make_pair(220, 156));
	each_point[4].push_back(std::make_pair(219, 92));
	each_point[4].push_back(std::make_pair(166, 23));

	each_point[5].push_back(std::make_pair(8, 18));
	each_point[5].push_back(std::make_pair(9, 96));
	each_point[5].push_back(std::make_pair(43, 141));
	each_point[5].push_back(std::make_pair(100, 152));
	each_point[5].push_back(std::make_pair(139, 116));
	each_point[5].push_back(std::make_pair(189, 100));
	each_point[5].push_back(std::make_pair(200, 21));
	each_point[5].push_back(std::make_pair(156, 1));
	each_point[5].push_back(std::make_pair(54, 3));

	each_point[6].push_back(std::make_pair(9, 31));
	each_point[6].push_back(std::make_pair(4, 92));
	each_point[6].push_back(std::make_pair(28, 145));
	each_point[6].push_back(std::make_pair(109, 165));
	each_point[6].push_back(std::make_pair(191, 144));
	each_point[6].push_back(std::make_pair(221, 91));
	each_point[6].push_back(std::make_pair(197, 23));
	each_point[6].push_back(std::make_pair(54, 9));

	each_point[7].push_back(std::make_pair(6, 26));
	each_point[7].push_back(std::make_pair(27, 124));
	each_point[7].push_back(std::make_pair(97, 172));
	each_point[7].push_back(std::make_pair(185, 142));
	each_point[7].push_back(std::make_pair(221, 74));
	each_point[7].push_back(std::make_pair(218, 23));
	each_point[7].push_back(std::make_pair(104, 4));
	each_point[7].push_back(std::make_pair(43, 10));

	each_point[8].push_back(std::make_pair(8, 20));
	each_point[8].push_back(std::make_pair(13, 101));
	each_point[8].push_back(std::make_pair(37, 141));
	each_point[8].push_back(std::make_pair(103, 165));
	each_point[8].push_back(std::make_pair(161, 154));
	each_point[8].push_back(std::make_pair(224, 74));
	each_point[8].push_back(std::make_pair(215, 13));
	each_point[8].push_back(std::make_pair(112, 2));
}

std::vector <Point> Obstruct1::getEachPoint()
{
	std::vector <Point> tmpVec;
	for (int i = 0, lim = each_point[pic_type].size(); i < lim; i++)
		tmpVec.push_back(std::make_pair(each_point[pic_type][i].first + loc.first,
																		each_point[pic_type][i].second + loc.second));
	return tmpVec;
}

int Obstruct1::getType()
{
	return pic_type;
}
