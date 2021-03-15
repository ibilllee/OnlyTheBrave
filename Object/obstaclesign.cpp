//Copyright (c) 2020 Li Yixuan All rights reserved.
//Date : 2020-05-15

#include "obstaclesign.h"

ObstacleSign::ObstacleSign(QWidget* parent)
{
	this->setParent(parent);

	pic = new QPixmap(OBSTACLE_SIGN_PIC);
	width	 = pic->width();
	height = pic->height();

	this->setFixedSize(width, height);
	this->setPixmap(*pic);
	animation = new QPropertyAnimation(this, "geometry");
	is_show = 0;
}

ObstacleSign::~ObstacleSign()
{
	delete animation; animation = nullptr;
	delete pic; pic = nullptr;
}

void ObstacleSign::showOnScreen(int height_mid, int time)
{
	this->show();
	is_show = 1;
	this->move(WINDOW_WIDTH - width, height_mid - height / 2.0);

	timer_act = new QTimer(this);
	timer_act->start(OBSTACLE_SIGN_ANIMATION_TIME * 1.5);

	connect(timer_act, &QTimer::timeout, [ = ](){
		runAnimation();
	});

	QTimer::singleShot(time, this, [ = ](){
		is_show = 0;
		if (timer_act->isActive())
			timer_act->stop();
		this->hide();
	});
}

void ObstacleSign::closeTimer()
{
	timer_act->stop();
	delete timer_act; timer_act = nullptr;
}

bool ObstacleSign::isFree()
{
	if (!is_show)
		return 1;
	return 0;
}

void ObstacleSign::runAnimation()
{
	animation->setDuration(OBSTACLE_SIGN_ANIMATION_TIME);
	animation->setStartValue(QRect(this->x(), this->y(), pic->width(), pic->height()));
	if (is_show == 1)
	{
		animation->setEndValue(QRect(this->x() - 10, this->y(), pic->width(), pic->height()));
		is_show = 2;
	}
	else
	{
		animation->setEndValue(QRect(this->x() + 10, this->y(), pic->width(), pic->height()));
		is_show = 1;
	}
	animation->setEasingCurve(QEasingCurve::Linear);
	animation->start();
}
