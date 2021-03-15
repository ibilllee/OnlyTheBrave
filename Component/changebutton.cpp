//Copyright (c) 2020 Li Yixuan All rights reserved.
//Date : 2020-05-15

#include "changebutton.h"

ChangeButton::ChangeButton(QWidget* parent,
													 QString	img1_path,
													 QString	img2_path,
													 int			iwidth,
													 int			iheight)
{
	current_status = 1;
	loc_y = 0;
	this->setParent(parent);
	image1_path = img1_path;
	image2_path = img2_path;
	widthRatio	= iwidth;
	heightRatio = iheight;

	loadPic1(iwidth, iheight);
	loadPic2(iwidth, iheight);

	this->setFixedSize(widthNumber, heightNumber);
	this->setStyleSheet("QPushButton{border:0px;}");
	this->setIcon(*pic1);
	this->setIconSize(QSize(pic1->width(), pic1->height()));

	connect(this, &ChangeButton::pressed, this, &ChangeButton::zoomDown);
	connect(this, &ChangeButton::released, [ = ]()
	{
		zoomUp();
		if (current_status == 1)
		{
			current_status = 2;
			this->setIcon(*pic2);
			emit this->turn2();
		}
		else
		{
			current_status = 1;
			this->setIcon(*pic1);
			emit this->turn1();
		}
	});
}

ChangeButton::~ChangeButton()
{
	delete pic1; pic1 = nullptr;
	delete pic2; pic2 = nullptr;
}

void ChangeButton::loadPic1(int iwidth, int iheight)
{
	pic1 = new QPixmap;
	bool check = pic1->load(image1_path);
	if (check == false)
		qDebug() << image1_path << "图片加载失败";
	widthNumber	 = pic1->width() * iwidth / 100;
	heightNumber = pic1->height() * iheight / 100;
	*pic1 = pic1->scaled(widthNumber, heightNumber, Qt::KeepAspectRatio);
}

void ChangeButton::loadPic2(int iwidth, int iheight)
{
	pic2 = new QPixmap;
	bool check = pic2->load(image2_path);
	if (check == false)
		qDebug() << image2_path << "图片加载失败";
	widthNumber	 = pic1->width() * iwidth / 100;
	heightNumber = pic1->height() * iheight / 100;
	*pic1 = pic1->scaled(widthNumber, heightNumber, Qt::KeepAspectRatio);
}

int ChangeButton::getWidth()
{
	return widthNumber;
}

int ChangeButton::getHeight()
{
	return heightNumber;
}

void ChangeButton::zoomDown()
{
	if (!loc_y)
		loc_y = this->y();
	QPropertyAnimation* animation1 = new QPropertyAnimation(this, "geometry");
	animation1->setDuration(ZOOM_DOWN_DURATION);         // Set the interval

	animation1->setStartValue(QRect(this->x(), this->y(), this->width(),
																	this->height()));
	animation1->setEndValue(QRect(this->x(), loc_y + 10, this->width(),
																this->height()));
	animation1->setEasingCurve(EASING_CURVE);         // Set the transition curve
	animation1->start();
}

void ChangeButton::zoomUp()
{
	QPropertyAnimation* animation1 = new QPropertyAnimation(this, "geometry");

	animation1->setDuration(ZOOM_UP_DURATION);         // Set the interval

	animation1->setStartValue(QRect(this->x(), this->y(), this->width(),
																	this->height()));
	animation1->setEndValue(QRect(this->x(), loc_y, this->width(), this->height()));
	animation1->setEasingCurve(EASING_CURVE);         // Set the transition curve
	animation1->start();
}

int ChangeButton::getStatus()
{
	return current_status;
}
