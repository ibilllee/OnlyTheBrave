//Copyright (c) 2020 Li Yixuan All rights reserved.
//Date : 2020-05-15

#include "obstacle.h"

Obstacle::Obstacle(QObject* parent) : QObject(parent)
{}

Obstacle::~Obstacle()
{
	delete pic; pic = nullptr;
}

void Obstacle::loadLengthXY()
{
	length_X = pic->width();
	length_Y = pic->height();
}

void Obstacle::setSINCOS()
{
	angle_SIN = qFastSin(angle_ABS * M_PI / 180.0);
	angle_COS = qFastCos(angle_ABS * M_PI / 180.0);
}

bool Obstacle::isFree()
{
	return is_free;
}

void Obstacle::useIt()
{
	is_free = 0;
	reLoc();
}

void Obstacle::releaseIt()
{
	is_free = 1;
}

double Obstacle::getLocX()
{
	return loc.first;
}

double Obstacle::getLocY()
{
	return loc.second;
}

QPixmap* Obstacle::getPic()
{
	return pic;
}
