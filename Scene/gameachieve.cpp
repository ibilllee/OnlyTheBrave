//Copyright (c) 2020 Li Yixuan All rights reserved.
//Date : 2020-05-15

#include "gameachieve.h"
#include "ui_gameachieve.h"

GameAchieve::GameAchieve(QWidget* parent) :
	QWidget(parent),
	ui(new Ui::GameAchieve)
{
	ui->setupUi(this);
	setTextColor();
	initPushButton();
}

GameAchieve::~GameAchieve()
{
	delete ui; ui = nullptr;
	delete back; back = nullptr;
	delete clear; clear = nullptr;
}

void GameAchieve::initPushButton()
{
	clear = new PushButton(this, PRESS_BUTTON_LITE, CLEAR_TXT, 100, 100);
	clear->move( WINDOW_WIDTH * 0.5 - clear->width() * 2.5, WINDOW_HEIGHT * 0.91);
	back = new PushButton(this, PRESS_BUTTON_LITE, BACK_TXT, 100, 100);
	back->move( WINDOW_WIDTH * 0.5 + back->width() * 1.5, WINDOW_HEIGHT * 0.91);

	connect(back, &QPushButton::clicked, [ = ](){
		QTimer::singleShot(200, this, [ = ]()
		{
			emit close();
		});
	});
	connect(clear, &QPushButton::clicked, [ = ](){
		QMessageBox::StandardButton button;
		button = QMessageBox::question(this, tr("提示"), QString(tr("确认清空数据？")),
																	 QMessageBox::Yes | QMessageBox::No);
		if (button == QMessageBox::Yes)
		{
			FileIO::decreaseRecordTo(0);
			updateNameList();
		}
	});
}

void GameAchieve::setTextColor()
{
	ui->name_label_1->setStyleSheet("color:white");
	ui->name_label_2->setStyleSheet("color:white");
	ui->name_label_3->setStyleSheet("color:white");
	ui->name_label_4->setStyleSheet("color:white");
	ui->name_label_5->setStyleSheet("color:white");
	ui->score_label_1->setStyleSheet("color:white");
	ui->score_label_2->setStyleSheet("color:white");
	ui->score_label_3->setStyleSheet("color:white");
	ui->score_label_4->setStyleSheet("color:white");
	ui->score_label_5->setStyleSheet("color:white");
}

void GameAchieve::updateNameList()
{
	QVector <Record> name_list = FileIO::sortedRecord();
	int size = name_list.size();
	if (FileIO::isFileExist(storage_path) == false)
		size = 0;
	if (size >= 1)
	{
		ui->name_label_1->setText(name_list[0].first);
		ui->score_label_1->setText(QString("%1").arg(name_list[0].second));
	}
	else
	{
		ui->name_label_1->setText("暂缺");
		ui->score_label_1->setText("0.0");
	}
	if (size >= 2)
	{
		ui->name_label_2->setText(name_list[1].first);
		ui->score_label_2->setText(QString("%1").arg(name_list[1].second));
	}
	else
	{
		ui->name_label_2->setText("暂缺");
		ui->score_label_2->setText("0.0");
	}
	if (size >= 3)
	{
		ui->name_label_3->setText(name_list[2].first);
		ui->score_label_3->setText(QString("%1").arg(name_list[2].second));
	}
	else
	{
		ui->name_label_3->setText("暂缺");
		ui->score_label_3->setText("0.0");
	}
	if (size >= 4)
	{
		ui->name_label_4->setText(name_list[3].first);
		ui->score_label_4->setText(QString("%1").arg(name_list[3].second));
	}
	else
	{
		ui->name_label_4->setText("暂缺");
		ui->score_label_4->setText("0.0");
	}
	if (size >= 5)
	{
		ui->name_label_5->setText(name_list[4].first);
		ui->score_label_5->setText(QString("%1").arg(name_list[4].second));
	}
	else
	{
		ui->name_label_5->setText("暂缺");
		ui->score_label_5->setText("0.0");
	}
}

void GameAchieve::closeEvent(QCloseEvent* event)
{
	emit backToMainWindow();
	event->accept();
}

void GameAchieve::paintEvent(QPaintEvent*)
{
	QPainter painter(this);

	QPixmap* back_ground = new QPixmap;
	back_ground->load(RECORD_BACKGROUND_PIC);
	painter.drawPixmap(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, *back_ground);
}
