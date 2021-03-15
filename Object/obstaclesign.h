//Copyright (c) 2020 Li Yixuan All rights reserved.
//Date : 2020-05-15

#ifndef OBSTACLESIGN_H
#define OBSTACLESIGN_H

#include "../Game/config.h"
#include <QObject>
#include <QPropertyAnimation>
#include <QDebug>
#include <QPixmap>
#include <QLabel>
#include <QTimer>
#include <QThread>

class ObstacleSign : public QLabel
{
	Q_OBJECT
public:
	ObstacleSign(QWidget* parent = nullptr);
	~ObstacleSign();
	void runAnimation();
	void showOnScreen(int height_mid, int time);
	void closeTimer();
	bool isFree();
private:
	QPropertyAnimation* animation;
	QPixmap* pic;
	int width;
	int height;
	int is_show;
	QTimer* timer_act;
};

#endif // OBSTACLESIGN_H
