//Copyright (c) 2020 Li Yixuan All rights reserved.
//Date : 2020-05-15

#ifndef PLAYER_H
#define PLAYER_H

#include "../Game/config.h"
#include <QDebug>
#include <QPixmap>
#include <iostream>
#include <vector>

typedef std::pair <double, double> Point;

class Player
{
public:
	Player();
	~Player();
	void setProperty();
	void setState(int = 1);
	int getState();
	double getLocX();
	double getLocY();
	double getLengthX();
	double getLengthY();

	void loadPic();
	QPixmap* getPic();
	QPixmap* getPicWithoutCount();

	void updateF_All();
	void updateAandV();
	void updateLoc();
	void setLoc(double = 0, double = 0);

	void loadEachPoint();
	std::vector <Point> getEachPoint();

	bool isProtected() const;
	void setProtected();
	void setUnprotected();

private:
	QPixmap* pic1;
	QPixmap* pic2;
	QPixmap* pic3;
	QPixmap* pic4;
	unsigned current_state;
	unsigned timesCounter = 0;

	double width;
	double hidth;
	double m;
	Point G;
	Point F_N;
	Point F_T;
	Point F_All;
	Point v;
	Point a;
	Point loc;
	std::vector <Point> each_point[5];
	bool is_protected;
};

#endif // PLAYER_H
