//Copyright (c) 2020 Li Yixuan All rights reserved.
//Date : 2020-05-15

#ifndef ATTACK1_H
#define ATTACK1_H

#include "../Game/config.h"
#include "obstacle.h"
#include <QPixmap>
#include <QSound>
#include <QObject>

extern unsigned rander;

class Attack1 : public Obstacle
{
	Q_OBJECT;
public:
	Attack1();
	virtual ~Attack1();
	virtual void useIt() override;
	virtual void updateLoc() override;
	virtual void reLoc() override;
	virtual void setEachPoint() override;
	virtual std::vector <Point> getEachPoint() override;
	virtual QPixmap* getPicRotated() override {return nullptr;}
	double getHeightMid();

signals:
	void playShootMusic();

private:
	std::vector <Point> each_point;
	int is_in_screen;
};

#endif // ATTACK1_H
