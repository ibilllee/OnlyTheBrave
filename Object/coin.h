//Copyright (c) 2020 Li Yixuan All rights reserved.
//Date : 2020-05-15

#ifndef COIN_H
#define COIN_H

#include "../Game/config.h"
#include "obstacle.h"

#include <QPixmap>
#include <QLabel>
#include <QTimer>
#include <QPropertyAnimation>

class Coin : public Obstacle
{
	Q_OBJECT
public:
	Coin();
	~Coin();
	virtual void reLoc() override;
	virtual void updateLoc() override;
	virtual void setEachPoint() override;
	virtual std::vector <Point> getEachPoint() override;
	virtual QPixmap* getPicRotated() override { return nullptr; };

private:
	std::vector <Point> each_point;

signals:
};

#endif // COIN_H
