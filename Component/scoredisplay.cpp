//Copyright (c) 2020 Li Yixuan All rights reserved.
//Date : 2020-05-15

#include "scoredisplay.h"

ScoreDisplay::ScoreDisplay(QWidget* parent) :
	distance(0), coin_num(0)
{
	this->setParent(parent);
	back_pic_label = new QLabel(parent);

	setBackPic();
	setInitialText();
}

ScoreDisplay::~ScoreDisplay()
{
	delete back_pic; back_pic = nullptr;
	delete back_pic_label; back_pic_label = nullptr;
}

void ScoreDisplay::setBackPic()
{
	back_pic = new QPixmap;
	back_pic->load(STATUS_BAR_PIC);
	QPixmap temp(back_pic->size());
	temp.fill(Qt::transparent);
	QPainter p1(&temp);
	p1.setCompositionMode(QPainter::CompositionMode_Source);
	p1.drawPixmap(0, 0, *back_pic);
	p1.setCompositionMode(QPainter::CompositionMode_DestinationIn);
	p1.fillRect(temp.rect(), QColor(0, 0, 0, 180));
	p1.end();
	*back_pic = temp;
	back_pic_label->setPixmap(*back_pic);
	back_pic_label->setFixedSize(back_pic->width(), back_pic->height());
	back_pic_label->move(STATUS_BAR_PIC_X, STATUS_BAR_PIC_Y);
	back_pic_label->show();
}

void ScoreDisplay::setInitialText()
{
	QFont tmp;

	tmp.setFamily(TEXT_FONT);
	tmp.setPointSize(TEXT_SIZE);
	this->setFont(tmp);
	this->move(STATUS_BAR_PIC_X + STATUS_BAR_WORD_dX, STATUS_BAR_PIC_Y + STATUS_BAR_WORD_dY);
	this->setFixedSize(500, 40);
	this->setStyleSheet("color:white;");
	this->raise();
	this->show();
}

void ScoreDisplay::modifyDistance(double add_dis)
{
	distance += add_dis;
	update();
}

void ScoreDisplay::modifyCoin(int add_num)
{
	coin_num += add_num;
	update();
}

void ScoreDisplay::update()
{
	this->setText(QString("前进距离:%1  已获金币:%2").arg(QString::number(distance, 'f',
																																1)).arg(coin_num));
}

int ScoreDisplay::getCoinNum() const
{
	return coin_num;
}

double ScoreDisplay::getScore() const
{
	return distance;
}
