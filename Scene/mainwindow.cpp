//Copyright (c) 2020 Li Yixuan All rights reserved.
//Date : 2020-05-15

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
	: QMainWindow(parent)
	, ui(new Ui::MainWindow)
{
	play_scene = nullptr;
	ui->setupUi(this);
	initialization();
	createButton();
	startBackgoundMusic();
	createSubWindow();
	changeWindow();
}

MainWindow::~MainWindow()
{
	background_player->deleteMe();
	delete background_player; background_player = nullptr;
	delete play_scene;        play_scene = nullptr;
	delete game_achieve;      game_achieve = nullptr;
	delete ui;                ui = nullptr;
	delete back_ground;       back_ground	 = nullptr;
	delete start_button;      start_button = nullptr;
	delete view_record_button; view_record_button = nullptr;
	delete about_button;      about_button = nullptr;
	delete about_scene;       about_scene	 = nullptr;
}

void MainWindow::initialization()
{
	this->setFixedSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	is_playing_music = 1;
}

void MainWindow::createButton()
{
	start_button = new PushButton(this, PRESS_BUTTON, START_GAME_TEXT, 100, 100);
	view_record_button = new PushButton(this, PRESS_BUTTON, VIEW_RECORD_TEXT, 100, 100);
	about_button = new PushButton(this, PRESS_BUTTON, ABOUT_TEXT, 100, 100);
	music_button = new ChangeButton(this, YES_MUSIC, NO_MUSIC, 100, 100);

	connect(music_button, &ChangeButton::turn1, this, &MainWindow::changeYesMusic);
	connect(music_button, &ChangeButton::turn2, this, &MainWindow::changeNoMusic);

	start_button->move((this->width() - start_button->getWidth()) / 2, this->height() * 0.4);
	view_record_button->move((this->width() - view_record_button->getWidth()) / 2,
													 this->height() * 0.6);
	about_button->move((this->width() - about_button->getWidth()) / 2, this->height() * 0.8);
	music_button->move(80, this->height() * 0.8);
}

void MainWindow::startBackgoundMusic()
{
	background_player = new MusicPlayer(this, BACKGROUND_MUSIC, BACKGROUND_MUSIC_VOLUME, 1);
	restartMusic(&background_player);
}

void MainWindow::createSubWindow()
{
	play_scene = new PlayScene;
	game_achieve = new GameAchieve;
	about_scene	 = new About;
}

void MainWindow::changeWindow()
{
	connect(start_button, &QPushButton::released, [ = ]()  //create PlayScene
	{
		QTimer::singleShot(200, this, [ = ]()
		{
			this->hide();
			pauseMusic(&background_player);
			play_scene->setGeometry(this->geometry());
			play_scene->show();
			play_scene->play();
		});
	});
	connect(play_scene, &PlayScene::backToMainWindow, [ = ]()  //back to home page
	{
		this->setGeometry(play_scene->geometry());
		this->show();
		if (is_playing_music)
			background_player->restart();
		play_scene->endPlay();
	});
	connect(view_record_button, &QPushButton::released, [ = ]() //create GameAchieve
	{
		QTimer::singleShot(200, this, [ = ]()
		{
			this->hide();
			game_achieve->updateNameList();
			game_achieve->setGeometry(this->geometry());
			game_achieve->show();
		});
	});
	connect(game_achieve, &GameAchieve::backToMainWindow, [ = ](){
		this->setGeometry(game_achieve->geometry());
		this->show();
	});
	connect(about_button, &QPushButton::released, [ = ]() //create AboutScene
	{
		QTimer::singleShot(200, this, [ = ]()
		{
			this->hide();
			about_scene->setGeometry(this->geometry());
			about_scene->show();
		});
	});
	connect(about_scene, &About::backToMainWindow, [ = ](){
		this->setGeometry(about_scene->geometry());
		this->show();
	});
}

void MainWindow::checkFirstRun()
{
	if (FileIO::isFileExist(storage_path) == false)
	{
		QMessageBox::StandardButton button;
		button = QMessageBox::question(this, tr("提示"), QString(tr("第一次运行，是否打开游戏规则？")),
																	 QMessageBox::Yes | QMessageBox::No);
		if (button == QMessageBox::Yes)
		{
			this->hide();
			about_scene->setGeometry(this->geometry());
			about_scene->show();
		}
	}
}

void MainWindow::paintEvent(QPaintEvent*)
{
	QPainter painter(this);

	back_ground = new QPixmap;
	back_ground->load(MAIN_BACKGROUND);
	painter.drawPixmap(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, *back_ground);
}

void MainWindow::closeEvent(QCloseEvent*)
{}

void MainWindow::resumeMusic(MusicPlayer** player)
{
	(*player)->resume();
}

void MainWindow::restartMusic(MusicPlayer** player)
{
	(*player)->restart();
}

void MainWindow::pauseMusic(MusicPlayer** player)
{
	(*player)->pause();
}

void MainWindow::changeNoMusic()
{
	pauseMusic(&background_player);
	is_playing_music = false;
}

void MainWindow::changeYesMusic()
{
	resumeMusic(&background_player);
	is_playing_music = true;
}
