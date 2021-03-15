//Copyright (c) 2020 Li Yixuan All rights reserved.
//Date : 2020-05-15

#include "pushbutton.h"

PushButton::PushButton(QWidget* parent, QString img_path, QString txt_path, int iwidth, int iheight)
	: loc_y(0)
{
	this->setParent(parent);
	image_path	= img_path;
	widthRatio	= iwidth;
	heightRatio = iheight;

	loadPic1(iwidth, iheight);
	addText(txt_path);

	this->setFixedSize(widthNumber, heightNumber);
	this->setStyleSheet("QPushButton{border:0px;}");
	this->setIcon(*pic1);
	this->setIconSize(QSize(pic1->width(), pic1->height()));
	animation1 = new QPropertyAnimation(this, "geometry");

	connect(this, &PushButton::pressed, this, &PushButton::zoomDown);
	connect(this, &PushButton::released, this, &PushButton::zoomUp);
}

PushButton::~PushButton()
{
	delete pic1; pic1 = nullptr;
	delete animation1; animation1 = nullptr;
}

void PushButton::loadPic1(int iwidth, int iheight)
{
	pic1 = new QPixmap;
	bool check = pic1->load(image_path);
	if (check == false)
		qDebug() << image_path << "图片加载失败";
	widthNumber	 = pic1->width() * iwidth / 100;
	heightNumber = pic1->height() * iheight / 100;
	*pic1 = pic1->scaled(widthNumber, heightNumber, Qt::KeepAspectRatio);
}

void PushButton::addText(QString txt_path)
{
	QPainter painter(pic1);
	QPixmap pic2;

	pic2.load(txt_path);
	painter.drawPixmap((pic1->width() - pic2.width()) / 2,
										 (pic1->height() - pic2.height()) / 2, pic2.width(), pic2.height(), pic2);
}

int PushButton::getWidth()
{
	return widthNumber;
}

int PushButton::getHeight()
{
	return heightNumber;
}

void PushButton::zoomDown()
{
	if (!loc_y)
		loc_y = this->y();
	animation1->setDuration(ZOOM_DOWN_DURATION);   //Set the interval

	animation1->setStartValue(QRect(this->x(), this->y(), this->width(), this->height()));
	animation1->setEndValue(QRect(this->x(), loc_y + 10, this->width(), this->height()));
	animation1->setEasingCurve(EASING_CURVE);   //Set the transition curve
	animation1->start();
}

void PushButton::zoomUp()
{
	is_zooming_up = 1;
	animation1->setDuration(ZOOM_UP_DURATION);   //Set the interval

	animation1->setStartValue(QRect(this->x(), this->y(), this->width(), this->height()));
	animation1->setEndValue(QRect(this->x(), loc_y, this->width(), this->height()));

	animation1->setEasingCurve(EASING_CURVE);   //Set the transition curve
	animation1->start();
	is_zooming_up = 0;
}

void PushButton::leaveEvent(QEvent*)
{
	if (loc_y && (this->y() != loc_y) && (is_zooming_up == 0))
		zoomUp();
}
