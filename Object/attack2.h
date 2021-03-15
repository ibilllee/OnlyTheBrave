//Copyright (c) 2020 Li Yixuan All rights reserved.
//Date : 2020-05-15

#ifndef ATTACK2_H
#define ATTACK2_H

#include "../Game/config.h"
#include "obstacle.h"
#include <QPixmap>
#include <QSound>
#include <QObject>
#include <QtMath>

extern unsigned rander;

class Attack2 : public Obstacle
{
	Q_OBJECT;
public:
	Attack2();
	virtual ~Attack2();
	virtual void useIt() override;
	virtual void updateLoc() override {};
	void updateLoc(double);
	virtual void reLoc() override;
	virtual void setEachPoint() override;
	virtual std::vector <Point> getEachPoint() override;
	virtual QPixmap* getPicRotated() override;
	double getHeightMid();

signals:
	void playShootMusic();

protected:
	Point getXYtoMainPoint(Point);

private:
	std::vector <Point> each_point;
	int is_in_screen;
};

#endif // ATTACK2_H
