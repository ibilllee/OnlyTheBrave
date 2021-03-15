//Copyright (c) 2020 Li Yixuan All rights reserved.
//Date : 2020-05-15

#include "player.h"

Player::Player() :
	is_protected(0)
{
	loadPic();
	loadEachPoint();
	setProperty();
}

Player::~Player()
{
	delete pic1; pic1 = nullptr;
	delete pic2; pic2 = nullptr;
	delete pic3; pic3 = nullptr;
	delete pic4; pic4 = nullptr;
}

void Player::setProperty()
{
	F_N = std::make_pair(0, 0);
	F_T = std::make_pair(0, 0);
	F_All = std::make_pair(0, 0);
	v = std::make_pair(0, 0);
	a = std::make_pair(0, 0);
	loc = std::make_pair(0, 0);
	m = 10.0;
	G = std::make_pair(0, m * G_Force);
	this->updateF_All();
	this->setLoc(PLAYER_LOC_X, 500);
	this->setState(4);
}

void Player::loadPic()
{
	pic1 = new QPixmap;
	pic1->load(QString(MAN_PIC).arg(1));
	pic2 = new QPixmap;
	pic2->load(QString(MAN_PIC).arg(2));
	pic3 = new QPixmap;
	pic3->load(QString(MAN_PIC).arg(3));
	pic4 = new QPixmap;
	pic4->load(QString(MAN_PIC).arg(4));
}

void Player::setState(int id)
{
	int preState = current_state;

	current_state = id;
	if (id == 3)
	{
		F_T = std::make_pair(0, -FLY_FORCE);
		if (preState <= 2)
			v.second = FLY_V0;
		updateAandV();
	}
	else
		F_T = std::make_pair(0, 0);
}

int Player::getState()
{
	return current_state;
}

double Player::getLocX()
{
	return loc.first;
}

double Player::getLocY()
{
	return loc.second;
}

double Player::getLengthX()
{
	return getPicWithoutCount()->width();
}

double Player::getLengthY()
{
	return getPicWithoutCount()->height();
}

QPixmap* Player::getPic()
{
	if (current_state == 1)
	{
		timesCounter++;
		if (timesCounter >= (int)CHANGE_PIC_TIMES)
			timesCounter = 0, setState(2);
		return pic1;
	}
	else if (current_state == 2)
	{
		timesCounter++;
		if (timesCounter >= (int)CHANGE_PIC_TIMES)
			timesCounter = 0, setState(1);
		return pic2;
	}
	else if (current_state == 3)
		return pic3;
	else
		return pic4;
}

QPixmap* Player::getPicWithoutCount()
{
	if (current_state == 1)
		return pic1;
	else if (current_state == 2)
		return pic2;
	else if (current_state == 3)
		return pic3;
	else
		return pic4;
}

void Player::updateF_All()
{
	int pre_state = current_state;
	double preF_N = F_N.second;
	if (loc.second >= FLOOR_Y - getLengthY())
	{
		loc.second = FLOOR_Y - getLengthY();
		F_N = std::make_pair(0, -m * G_Force);
		a = std::make_pair(0, 0);
		v = std::make_pair(0, 0);
	}
	else if (loc.second <= CEIL_Y)
	{
		loc.second = CEIL_Y;
		F_N = std::make_pair(0, FLY_FORCE + m * G_Force);
		a = std::make_pair(0, 0);
		v = std::make_pair(0, 0);
	}
	else
		F_N = std::make_pair(0, 0);
	if ((pre_state != 3) && (preF_N == 0.0) && (F_N.second == -m * G_Force))
		setState(1);
	if ((current_state == 4) && (F_N.second == -m * G_Force))
		setState(1);
	F_All = std::make_pair(F_N.first + F_T.first + G.first,
												 F_N.second + F_T.second + G.second);
}

void Player::updateAandV()
{
	updateF_All();
	a = std::make_pair(F_All.first / m, F_All.second / m);
	v = std::make_pair(v.first + a.first * REFRESH_TIME,
										 v.second + a.second * REFRESH_TIME);
}

void Player::updateLoc()
{
	updateAandV();
	loc = std::make_pair(loc.first + v.first * REFRESH_TIME,
											 loc.second + v.second * REFRESH_TIME);
}

void Player::setLoc(double x, double y)
{
	loc.first	 = x;
	loc.second = y;
}

void Player::loadEachPoint()
{
	each_point[1].push_back(std::make_pair(48, 2));
	each_point[1].push_back(std::make_pair(35, 12));
	each_point[1].push_back(std::make_pair(47, 31));
	each_point[1].push_back(std::make_pair(34, 52));
	each_point[1].push_back(std::make_pair(59, 77));
	each_point[1].push_back(std::make_pair(42, 76));
	each_point[1].push_back(std::make_pair(54, 93));
	each_point[1].push_back(std::make_pair(29, 90));
	each_point[1].push_back(std::make_pair(38, 106));
	each_point[1].push_back(std::make_pair(38, 96));
	each_point[1].push_back(std::make_pair(58, 99));
	each_point[1].push_back(std::make_pair(58, 114));
	each_point[1].push_back(std::make_pair(80, 114));
	each_point[1].push_back(std::make_pair(59, 86));
	each_point[1].push_back(std::make_pair(76, 63));
	each_point[1].push_back(std::make_pair(57, 29));
	each_point[1].push_back(std::make_pair(71, 27));
	each_point[1].push_back(std::make_pair(72, 14));

	each_point[2].push_back(std::make_pair(44, 9));
	each_point[2].push_back(std::make_pair(32, 17));
	each_point[2].push_back(std::make_pair(43, 36));
	each_point[2].push_back(std::make_pair(28, 57));
	each_point[2].push_back(std::make_pair(41, 69));
	each_point[2].push_back(std::make_pair(39, 94));
	each_point[2].push_back(std::make_pair(19, 86));
	each_point[2].push_back(std::make_pair(11, 98));
	each_point[2].push_back(std::make_pair(22, 98));
	each_point[2].push_back(std::make_pair(33, 105));
	each_point[2].push_back(std::make_pair(58, 91));
	each_point[2].push_back(std::make_pair(84, 112));
	each_point[2].push_back(std::make_pair(99, 101));
	each_point[2].push_back(std::make_pair(64, 85));
	each_point[2].push_back(std::make_pair(72, 64));
	each_point[2].push_back(std::make_pair(53, 35));
	each_point[2].push_back(std::make_pair(66, 34));
	each_point[2].push_back(std::make_pair(68, 21));

	each_point[3].push_back(std::make_pair(26, 13));
	each_point[3].push_back(std::make_pair(40, 33));
	each_point[3].push_back(std::make_pair(32, 55));
	each_point[3].push_back(std::make_pair(46, 66));
	each_point[3].push_back(std::make_pair(60, 93));
	each_point[3].push_back(std::make_pair(34, 94));
	each_point[3].push_back(std::make_pair(51, 109));
	each_point[3].push_back(std::make_pair(49, 99));
	each_point[3].push_back(std::make_pair(68, 98));
	each_point[3].push_back(std::make_pair(71, 113));
	each_point[3].push_back(std::make_pair(92, 107));
	each_point[3].push_back(std::make_pair(66, 84));
	each_point[3].push_back(std::make_pair(77, 61));
	each_point[3].push_back(std::make_pair(52, 28));
	each_point[3].push_back(std::make_pair(63, 25));
	each_point[3].push_back(std::make_pair(63, 12));
	each_point[3].push_back(std::make_pair(41, 4));

	each_point[4].push_back(std::make_pair(26, 13));
	each_point[4].push_back(std::make_pair(40, 33));
	each_point[4].push_back(std::make_pair(32, 55));
	each_point[4].push_back(std::make_pair(46, 66));
	each_point[4].push_back(std::make_pair(60, 93));
	each_point[4].push_back(std::make_pair(34, 94));
	each_point[4].push_back(std::make_pair(51, 109));
	each_point[4].push_back(std::make_pair(49, 99));
	each_point[4].push_back(std::make_pair(68, 98));
	each_point[4].push_back(std::make_pair(71, 113));
	each_point[4].push_back(std::make_pair(92, 107));
	each_point[4].push_back(std::make_pair(66, 84));
	each_point[4].push_back(std::make_pair(77, 61));
	each_point[4].push_back(std::make_pair(52, 28));
	each_point[4].push_back(std::make_pair(63, 25));
	each_point[4].push_back(std::make_pair(63, 12));
	each_point[4].push_back(std::make_pair(41, 4));
}

std::vector <Point> Player::getEachPoint()
{
	std::vector <Point> tmpVec;
	for (int i = 0, lim = each_point[current_state].size(); i < lim; i++)
		tmpVec.push_back(std::make_pair(each_point[current_state][i].first + loc.first,
																		each_point[current_state][i].second + loc.second));
	return tmpVec;
}

bool Player::isProtected() const
{
	return is_protected;
}

void Player::setProtected()
{
	is_protected = 1;
}

void Player::setUnprotected()
{
	is_protected = 0;
}
