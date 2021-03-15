//Copyright (c) 2020 Li Yixuan All rights reserved.
//Date : 2020-05-15

#ifndef SCOREDISPLAY_H
#define SCOREDISPLAY_H

#include "../Game/config.h"
#include <QLabel>
#include <QPainter>
#include <QDebug>

class ScoreDisplay : public QLabel
{
	Q_OBJECT
public:
	ScoreDisplay(QWidget* parent = nullptr);
	~ScoreDisplay();
	void setBackPic();
	void setInitialText();
	void modifyDistance(double add_dis);
	void modifyCoin(int add_num);
	void update();
	int getCoinNum() const;
	double getScore() const;

private:
	QLabel* back_pic_label;
	QPixmap* back_pic;
	double distance;
	int coin_num;
};

#endif // SCOREDISPLAY_H
