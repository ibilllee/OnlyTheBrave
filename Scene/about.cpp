//Copyright (c) 2020 Li Yixuan All rights reserved.
//Date : 2020-05-15

#include "about.h"
#include "ui_about.h"
#include <QDebug>

About::About(QWidget* parent) :
	QWidget(parent),
	ui(new Ui::About)
{
	ui->setupUi(this);
	setWindowTransparency();
	setButton();
}

About::~About()
{
	delete ui; ui = nullptr;
}

void About::setWindowTransparency()
{
	ui->textBrowser->setStyleSheet(
		"QTextEdit{background-color:rgb(176,216,232,100);border-radius:3px;}");
	QFont tmp;
	tmp.setFamily("黑体");
	ui->textBrowser->setFont(tmp);
}

void About::setButton()
{
	clear = new PushButton(this, PRESS_BUTTON_LITE, CLEAR_CACHE_TXT, 100, 100);
	clear->move( WINDOW_WIDTH * 0.5 - clear->width() * 2.5, WINDOW_HEIGHT * 0.90);

	back = new PushButton(this, PRESS_BUTTON_LITE, BACK_TXT, 100, 150);
	back->move( WINDOW_WIDTH * 0.5 + back->width() * 1.5, WINDOW_HEIGHT * 0.90);

	connect(back, &QPushButton::clicked, [ = ]()
	{
		QTimer::singleShot(200, this, [ = ]()
		{
			emit close();
		});
	});
	connect(clear, &QPushButton::clicked, [ = ]()
	{
		QTimer::singleShot(200, this, [ = ]()
		{
			if (FileIO::isFileExist(storage_path) == true)
				FileIO::deleteFileOrFolder(storage_path);
			QMessageBox::information(this, "提示", "操作已完成");
		});
	});
}

void About::closeEvent(QCloseEvent* event)
{
	emit backToMainWindow();
	event->accept();
}

void About::paintEvent(QPaintEvent*)
{
	QPainter painter(this);

	QPixmap* back_ground = new QPixmap;
	back_ground->load(BACKGROUND_PIC);
	painter.drawPixmap(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, *back_ground);
}
