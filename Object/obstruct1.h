//Copyright (c) 2020 Li Yixuan All rights reserved.
//Date : 2020-05-15

#ifndef OBSTRUCT1_H
#define OBSTRUCT1_H

#include "../Game/config.h"
#include "obstacle.h"
#include "windows.h"
#include <QDebug>
#include <QPixmap>

extern unsigned rander;

class Obstruct1 : public Obstacle
{
public:
	Obstruct1(int type = 1);
	virtual ~Obstruct1();
	virtual void updateLoc() override;
	virtual void reLoc() override;
	virtual void setEachPoint() override;
	virtual std::vector <Point> getEachPoint() override;
	int getType();
	virtual QPixmap* getPicRotated() override { return nullptr; };

private:
	int type;
	int pic_type;
	std::vector <Point> each_point[9];
};

#endif // OBSTRUCT1_H
