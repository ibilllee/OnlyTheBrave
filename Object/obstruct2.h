//Copyright (c) 2020 Li Yixuan All rights reserved.
//Date : 2020-05-15

#ifndef OBSTRUCT2_H
#define OBSTRUCT2_H

#include "obstacle.h"
#include <QMatrix>
#include <QtMath>

extern unsigned rander;

class Obstruct2 : public Obstacle
{
public:
	Obstruct2(int type = 1);
	virtual ~Obstruct2();
	virtual void updateLoc() override;
	virtual void reLoc() override;
	virtual void setEachPoint() override;
	virtual std::vector <Point> getEachPoint() override;
	virtual void useIt() override;
	virtual void releaseIt() override;
	int getType();
	virtual QPixmap* getPicRotated() override;

private:
	int type;
	double XX;
	double YY;
};

#endif // OBSTRUCT2_H
