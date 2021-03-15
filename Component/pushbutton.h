//Copyright (c) 2020 Li Yixuan All rights reserved.
//Date : 2020-05-15

#ifndef PUSHBUTTON_H
#define PUSHBUTTON_H

#include "../Game/config.h"

#include <QDebug>
#include <QPainter>
#include <QPixmap>
#include <QPropertyAnimation>
#include <QPushButton>
#include <QSize>
#include <QString>
#include <QEvent>

class PushButton : public QPushButton
{
	Q_OBJECT
public:
	PushButton(QWidget* parent	 = nullptr,
						 QString	img_path = PRESS_BUTTON,
						 QString	txt_path = PRESS_BUTTON,
						 int			width	 = 100,
						 int			height = 100);
	~PushButton();
	void loadPic1(int iwidth, int iheight);
	void addText(QString txt_path);
	int getWidth();
	int getHeight();
	void zoomDown();
	void zoomUp();
	virtual void leaveEvent(QEvent*) override;
private:
	QString image_path;
	int widthRatio;
	int heightRatio;
	int widthNumber;
	int heightNumber;
	int loc_y = 0;
	bool is_zooming_up = 0;
	QPixmap* pic1;
	QPropertyAnimation* animation1;
};

#endif // PUSHBUTTON_H
