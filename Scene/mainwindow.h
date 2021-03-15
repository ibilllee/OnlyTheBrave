//Copyright (c) 2020 Li Yixuan All rights reserved.
//Date : 2020-05-15

#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "../Component/changebutton.h"
#include "../Game/config.h"
#include "../Component/musicplayer.h"
#include "playscene.h"
#include "../Component/pushbutton.h"
#include "windows.h"
#include "gameachieve.h"
#include "about.h"

#include <QDebug>
#include <QMainWindow>
#include <QMessageBox>
#include <QPaintEvent>
#include <QPainter>
#include <QCloseEvent>

extern bool is_playing_music;
extern QString storage_path;

QT_BEGIN_NAMESPACE
namespace Ui
{
	class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget* parent = nullptr);
	~MainWindow();
	void initialization();
	void createButton();
	void startBackgoundMusic();
	void createSubWindow();
	void changeWindow();
	void checkFirstRun();

	void resumeMusic(MusicPlayer**);
	void restartMusic(MusicPlayer**);
	void pauseMusic(MusicPlayer**);

public slots:
	void changeNoMusic();
	void changeYesMusic();

protected:
	void paintEvent(QPaintEvent*);
	void closeEvent(QCloseEvent*);

private:
	Ui::MainWindow* ui;
	QPixmap* back_ground;
	MusicPlayer* background_player;

	PushButton* start_button;
	PushButton* view_record_button;
	PushButton* about_button;
	ChangeButton* music_button;
	GameAchieve* game_achieve;
	About* about_scene;

	PlayScene* play_scene;
};
#endif // MAINWINDOW_H
