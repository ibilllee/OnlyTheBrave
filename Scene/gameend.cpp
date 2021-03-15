//Copyright (c) 2020 Li Yixuan All rights reserved.
//Date : 2020-05-15

#include "gameend.h"
#include "ui_gameend.h"

GameEnd::GameEnd(QWidget* parent) :
	QWidget(parent),
	ui(new Ui::GameEnd)
{
	ui->setupUi(this);
	setWindowFlag(Qt::FramelessWindowHint);
	setTransparency();
	setWindowModality(Qt::ApplicationModal);
	connect(ui->lineEdit, &QLineEdit::returnPressed, ui->back_button, &QPushButton::released);
	connect(ui->back_button, &QPushButton::released, this, &QWidget::hide);
}

GameEnd::~GameEnd()
{
	delete ui; ui = nullptr;
}

void GameEnd::setTransparency()
{
	this->setWindowOpacity(GAME_END_WINDOW_TRANSPARENCY);
	this->setStyleSheet("background-color:rgb(176,216,232)");

	this->setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);
	QPainterPath path;
	QRectF rect = QRectF(0, 0, this->width(), this->height());
	path.addRoundRect(rect, 15, 15);
	QPolygon polygon = path.toFillPolygon().toPolygon();
	QRegion region(polygon);
	setMask(region);
}

void GameEnd::setScore(double x)
{
	ui->score_label->setText(QString("您的分数是:%1米").arg(QString::number(x, 'f', 1)));
}

QPushButton* GameEnd::getBackButton()
{
	return ui->back_button;
}

QLineEdit* GameEnd::getLineEdit()
{
	return ui->lineEdit;
}
