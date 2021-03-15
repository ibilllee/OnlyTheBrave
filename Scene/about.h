//Copyright (c) 2020 Li Yixuan All rights reserved.
//Date : 2020-05-15

#ifndef ABOUT_H
#define ABOUT_H

#include "../Game/config.h"
#include "../Component/pushbutton.h"
#include "../Game/fileio.h"

#include <QWidget>
#include <QCloseEvent>
#include <QPainter>
#include <QTimer>
#include <QMessageBox>

extern QString storage_path;

namespace Ui
{
	class About;
}

class About : public QWidget
{
	Q_OBJECT
public:
	explicit About(QWidget* parent = nullptr);
	~About();
	void setWindowTransparency();
	void setButton();

protected:
	virtual void closeEvent(QCloseEvent* event) override;
	virtual void paintEvent(QPaintEvent*) override;

private:
	Ui::About* ui;
	PushButton* back;
	PushButton* clear;

signals:
	void backToMainWindow();
};

#endif // ABOUT_H
