//Copyright (c) 2020 Li Yixuan All rights reserved.
//Date : 2020-05-15

#include "attack2.h"

Attack2::Attack2()
{
	this->releaseIt();

	QString pic_path = QString (ATTACK_2_PIC);
	pic = new QPixmap;
	pic->load(pic_path);

	setEachPoint();
}

Attack2::~Attack2()
{}

void Attack2::useIt()
{
	is_free = 0;
	is_in_screen = 0;
	angle = 0;
	reLoc();
}

void Attack2::updateLoc(double player_y)
{
	if (isFree())
		return;
	double angle_RAD = angle / 180.0 * M_PI;
	if (is_in_screen)
	{
		loc.first	 -= Config::rocketSpeed() * cos(angle_RAD);
		loc.second -= Config::rocketSpeed() * sin(angle_RAD);
	}
	else
		loc.first -= Config::rocketSpeed();
	if ((loc.first >= PLAYER_LOC_X) && is_in_screen)
	{
		double tmp_X, tmp_Y;
		if (angle >= 0)
		{
			tmp_X = loc.first + 0.5 * ATTACK_2_PIC_Y * sin(angle_RAD);
			tmp_Y = loc.second + 0.5 * ATTACK_2_PIC_Y * cos(angle_RAD);
		}
		else
		{
			tmp_X = loc.first - 0.5 * ATTACK_2_PIC_Y * sin(angle_RAD);
			tmp_Y = loc.second + 0.5 * ATTACK_2_PIC_Y * cos(angle_RAD) - ATTACK_2_PIC_X * sin(
				angle_RAD);
		}
		double angle_CON;
		angle_CON = atan2(tmp_Y - player_y, tmp_X - PLAYER_LOC_X);
		angle += (angle_CON - angle_RAD) * ATTACK_2_dANGLE;
		if (angle > 45)
			angle = 45;
		else if (angle < -45)
			angle = -45;
	}
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

void Attack2::reLoc()
{
	srand(rander);
	double height = rander = (rand() % ((int)(FLOOR_Y - pic->height())));
	loc = std::make_pair(
		WINDOW_WIDTH + Config::rocketSpeed() * SIGN_DELAY_TIME / REFRESH_RATE, height);
}

void Attack2::setEachPoint()
{
	each_point.push_back(std::make_pair(11, 6));
	each_point.push_back(std::make_pair(28, 26));
	each_point.push_back(std::make_pair(17, 37));
	each_point.push_back(std::make_pair(0, 43));
	each_point.push_back(std::make_pair(17, 50));
	each_point.push_back(std::make_pair(28, 59));
	each_point.push_back(std::make_pair(12, 80));
	each_point.push_back(std::make_pair(25, 86));
	each_point.push_back(std::make_pair(38, 80));
	each_point.push_back(std::make_pair(26, 79));
	each_point.push_back(std::make_pair(42, 54));
	each_point.push_back(std::make_pair(53, 59));
	each_point.push_back(std::make_pair(53, 27));
	each_point.push_back(std::make_pair(42, 31));
	each_point.push_back(std::make_pair(27, 7));
	each_point.push_back(std::make_pair(38, 5));
	each_point.push_back(std::make_pair(24, 0));
}

std::vector <Point> Attack2::getEachPoint()
{
	std::vector <Point> tmpVec;
	Point tmpPoint;
	for (int i = 0, lim = each_point.size(); i < lim; i++)
	{
		tmpPoint = getXYtoMainPoint(each_point[i]);
		if (angle >= 0)
			tmpVec.push_back(std::make_pair(each_point[i].first + loc.first + ATTACK_2_PIC_Y *
																			sin(angle / 180.0 * M_PI),
																			each_point[i].second + loc.second));
		else
			tmpVec.push_back(std::make_pair(each_point[i].first + loc.first,
																			each_point[i].second + loc.second + ATTACK_2_PIC_X *
																			sin(-angle / 180.0 * M_PI)));
	}
	return tmpVec;
}

QPixmap* Attack2::getPicRotated()
{
	QMatrix mat;

	mat.rotate(angle);
	pic_tmp = pic->transformed(mat, Qt::SmoothTransformation);
	mat.rotate(-angle);
	return &pic_tmp;
}

double Attack2::getHeightMid()
{
	return loc.second + pic->height() / 2;
}

Point Attack2::getXYtoMainPoint(Point a)
{
	double tmp_angle, lenght;

	lenght = a.first * a.first + a.second * a.second;
	tmp_angle = atan2(a.second, a.first) + angle / 180.0 * M_PI;
	return std::make_pair(lenght * cos(tmp_angle), lenght * sin(tmp_angle));
}
