//Copyright (c) 2020 Li Yixuan All rights reserved.
//Date : 2020-05-15

#ifndef CHANGEBUTTON_H
#define CHANGEBUTTON_H

#include "../Game/config.h"
#include <QDebug>
#include <QPainter>
#include <QPixmap>
#include <QPropertyAnimation>
#include <QPushButton>
#include <QSize>
#include <QString>

class ChangeButton : public QPushButton
{
	Q_OBJECT
public:
	ChangeButton(QWidget* parent = nullptr,
							 QString	img1_path = PRESS_BUTTON,
							 QString	img2_path = PRESS_BUTTON,
							 int			width	 = 100,
							 int			height = 100);
	~ChangeButton();
	void loadPic1(int iwidth, int iheight);
	void loadPic2(int iwidth, int iheight);
	int getWidth();
	int getHeight();
	void zoomDown();
	void zoomUp();
	int getStatus();

signals:
	void turn1();
	void turn2();

private:
	QString image1_path;
	QString image2_path;
	int widthRatio;
	int heightRatio;
	int widthNumber;
	int heightNumber;
	QPixmap* pic1;
	QPixmap* pic2;
	int loc_y;
	int current_status;
};

#endif // CHANGEBUTTON_H
