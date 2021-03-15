//Copyright (c) 2020 Li Yixuan All rights reserved.
//Date : 2020-05-15

#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "../Game/config.h"
#include <QDebug>
#include <QPixmap>
#include <QObject>
#include <QtMath>
#include <vector>

typedef std::pair <double, double> Point;

class Obstacle : public QObject
{
	Q_OBJECT;
public:
	Obstacle(QObject* parent = nullptr);
	virtual ~Obstacle();
	void loadLengthXY();
	virtual void updateLoc() = 0;
	virtual void reLoc() = 0;
	virtual void setEachPoint() = 0;
	virtual std::vector <Point> getEachPoint() = 0;
	void setSINCOS();
	virtual bool isFree();
	virtual void useIt();
	virtual void releaseIt();
	void setLocX(double = 0);
	void setLocY(double = 0);
	double getLocX();
	double getLocY();
	virtual QPixmap* getPic();
	virtual QPixmap* getPicRotated() = 0;

protected:
	QPixmap* pic;
	QPixmap pic_tmp;
	Point loc;
	bool is_free;
	double length_X;
	double length_Y;
	double angle;
	double angle_ABS;
	double angle_SIN;
	double angle_COS;
};

#endif // OBSTACLE_H
