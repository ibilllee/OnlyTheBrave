//Copyright (c) 2020 Li Yixuan All rights reserved.
//Date : 2020-05-15

#ifndef PLAYSCENE_H
#define PLAYSCENE_H

#include "../Object/allobstacle.h"
#include "../Object/coin.h"
#include "../Game/config.h"
#include "../Component/map.h"
#include "../Component/musicplayer.h"
#include "../Object/obstaclesign.h"
#include "../Game/overlapdetection.h"
#include "../Object/player.h"
#include "windows.h"
#include "gameachieve.h"
#include "../Component/scoredisplay.h"
#include "gameend.h"
#include "../Game/fileio.h"

#include <QCloseEvent>
#include <QDebug>
#include <QMainWindow>
#include <QMessageBox>
#include <QPaintEvent>
#include <QPainter>
#include <QTimer>
#include <QUrl>
#include <QProcess>

extern clock_t startTime;
extern clock_t nowTime;
extern clock_t tmpTime;
extern bool is_playing_music;
extern unsigned rander;

class PlayScene : public QWidget
{
	Q_OBJECT
public:
	explicit PlayScene(QWidget* parent = nullptr);
	~PlayScene();
	void initialization();
	void setTimer();
	void createObj();
	void createMusic();
	void initProtection();

	void play();
	void endPlay();
	void pause();
	void resume();
	void initVar();

	void addObstacle();
	void addObstruct1();
	void addObstrcut2();
	void addAttack1();
	void addAttack2();
	void addCoin();
	void coinExit(Coin*);
	void addObstacleSign(double, double = 1000);
	void randObstruct1(int times);
	void setProtected();
	void setUnProtected();
	void shutDownAllMusic();

	bool collision();
	void updateDistance();
	void refreshObject();
	void collisionDetection();
	bool scenceChoose();

protected:
	virtual void paintEvent(QPaintEvent*) override;
	virtual void keyPressEvent(QKeyEvent* event) override;
	virtual void keyReleaseEvent(QKeyEvent* event) override;
	virtual void closeEvent(QCloseEvent* event) override;

private:
	QTimer* timer;
	Map* background;
	MusicPlayer* background_player;
	MusicPlayer* rocket_player;
	MusicPlayer* shoot_player;
	MusicPlayer* coin_player;
	Player* player;

	Obstruct1* obstruct1_down[OBSTRUCT_1_NUM];
	Obstruct1* obstruct1_up[OBSTRUCT_1_NUM];
	Obstruct2* obstruct2[OBSTRUCT_2_TYPES_P1][OBSTRUCT_2_NUM];
	Attack1* attack1[ATTACK_1_NUM];
	Attack2* attack2[ATTACK_2_NUM];
	ObstacleSign* obstacle_sign[OBSTACLE_SIGN_NUM];
	Coin* coin[COIN_NUM];
	QLabel* coin_label;
	ScoreDisplay* score_display;
	QLabel* protection;
	GameEnd* game_end;

	unsigned obstacle_counter;
	unsigned coin_counter;
	unsigned emergency_stop;
	int status;
	bool protection_status;
	bool is_collision;
	bool emit_by_back_button;
signals:
	void backToMainWindow();
};

#endif // PLAYSCENE_H
