//Copyright (c) 2020 Li Yixuan All rights reserved.
//Date : 2020-05-15

#ifndef GAMEACHIEVE_H
#define GAMEACHIEVE_H

#include "../Game/config.h"
#include "../Game/fileio.h"
#include "../Component/pushbutton.h"

#include <QWidget>
#include <QCloseEvent>
#include <QPainter>
#include <QTimer>
#include <QMessageBox>

namespace Ui
{
	class GameAchieve;
}

class GameAchieve : public QWidget
{
	Q_OBJECT

public:
	explicit GameAchieve(QWidget* parent = nullptr);
	~GameAchieve();
	void initPushButton();
	void setTextColor();
	void updateNameList();

protected:
	virtual void closeEvent(QCloseEvent* event) override;
	virtual void paintEvent(QPaintEvent*) override;

signals:
	void backToMainWindow();
private:
	Ui::GameAchieve* ui;
	PushButton* back;
	PushButton* clear;
};

#endif // GAMEACHIEVE_H
