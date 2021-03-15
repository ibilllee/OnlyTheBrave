//Copyright (c) 2020 Li Yixuan All rights reserved.
//Date : 2020-05-15

#ifndef GAMEEND_H
#define GAMEEND_H

#include "../Game/config.h"
#include "../Game/fileio.h"

#include <QWidget>
#include <QPalette>
#include <QtWin>
#include <windows.h>
#include <QPainter>
#include <QPushButton>
#include <QLineEdit>
#include <QPainterPath>

namespace Ui
{
	class GameEnd;
}

class GameEnd : public QWidget
{
	Q_OBJECT

public:
	explicit GameEnd(QWidget* parent = nullptr);
	~GameEnd();
	void setTransparency();
	void setScore(double);
	QPushButton* getBackButton();
	QLineEdit* getLineEdit();
private:
	Ui::GameEnd* ui;
};

#endif // GAMEEND_H
