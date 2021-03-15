//Copyright (c) 2020 Li Yixuan All rights reserved.
//Date : 2020-05-15

#include "playscene.h"

PlayScene::PlayScene(QWidget* parent)
	: QWidget(parent)
{
	srand(time(NULL));
	rander = rand();
	initialization();
}

PlayScene::~PlayScene()
{}

void PlayScene::initialization()
{
	this->setFixedSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	this->setWindowIcon(QIcon(WINDOW_ICON));
	this->setWindowTitle(WINDOW_TITLE);
}

void PlayScene::setTimer()
{
	timer = new QTimer(this);
	timer->setInterval(REFRESH_RATE);
}

void PlayScene::createObj()
{
	background = new Map;
	player = new Player;
	score_display = new ScoreDisplay(this);
	coin_label = new QLabel(this);
	coin_label->setPixmap(QPixmap(COIN_PIC));
	game_end = new GameEnd;
	connect(game_end->getBackButton(), &QPushButton::released, [&](){
		QString temp_name = game_end->getLineEdit()->text();
		if (temp_name == "") temp_name = "Player";
		FileIO::appendRecord(std::make_pair(temp_name, QString::number(score_display->getScore(), 'f',
																																	 1).toDouble()));
		FileIO::decreaseRecordTo(50);
		emit backToMainWindow();
		emit_by_back_button = 1;
		emit close();
	});
	for (int i = 0; i < OBSTRUCT_1_NUM; i++)
		obstruct1_down[i] = new Obstruct1(1);
	for (int i = 0; i < OBSTRUCT_1_NUM; i++)
		obstruct1_up[i] = new Obstruct1(2);
	for (int i = 1; i < OBSTRUCT_2_TYPES_P1; i++)
		for (int j = 0; j < OBSTRUCT_2_NUM; j++)
			obstruct2[i][j] = new Obstruct2(i);
	for (int i = 0; i < ATTACK_1_NUM; i++)
	{
		attack1[i] = new Attack1;
		connect(attack1[i], &Attack1::playShootMusic, [ = ](){
			if (is_playing_music)
				this->shoot_player->resume();
		});
	}
	for (int i = 0; i < ATTACK_2_NUM; i++)
	{
		attack2[i] = new Attack2;
		connect(attack2[i], &Attack2::playShootMusic, [ = ](){
			if (is_playing_music)
				shoot_player->resume();
		});
	}
	for (int i = 0; i < OBSTACLE_SIGN_NUM; i++)
		obstacle_sign[i] = new ObstacleSign(this);
	for (int i = 0; i < COIN_NUM; i++)
		coin[i] = new Coin;
	initProtection();
}

void PlayScene::createMusic()
{
	srand(time(NULL));
	QString game_music_path = QString(GAME_MUSIC).arg(rand() % 4 + 1);

	background_player = new MusicPlayer(this, game_music_path, GAME_MUSIC_VOLUME, 1);
	rocket_player = new MusicPlayer(this, ROCKET_MUSIC, ROCKET_MUSIC_VOLUME, 1);
	shoot_player	= new MusicPlayer(this, SHOOT_MUSIC, SHOOT_MUSIC_VOLUME, 0);
	coin_player = new MusicPlayer(this, COIN_MUSIC, COIN_MUSIC_VOLUME, 0);
}

void PlayScene::initProtection()
{
	protection = new QLabel(this);

	QPixmap protection_pic;
	protection_pic.load(PROTECTION_PIC);
	QPixmap temp(protection_pic.size());
	temp.fill(Qt::transparent);
	QPainter p1(&temp);
	p1.setCompositionMode(QPainter::CompositionMode_Source);
	p1.drawPixmap(0, 0, protection_pic);
	p1.setCompositionMode(QPainter::CompositionMode_DestinationIn);
	p1.fillRect(temp.rect(), QColor(0, 0, 0, PROTECTION_TRANSPARENCY));
	p1.end();

	protection->setPixmap(temp);
	protection->setFixedSize(temp.width(), temp.height());
	protection->hide();
}

void PlayScene::play()
{
	createObj();
	setTimer();
	createMusic();
	initVar();

	timer->start();
	startTime = clock();
	if (is_playing_music)
		background_player->restart();
	connect(timer, &QTimer::timeout, [ = ]()
	{
		addObstacle();
		addCoin();
		refreshObject();
		updateDistance();
		collisionDetection();
		update();
	});
}

void PlayScene::endPlay()
{
	timer->stop();
	emergency_stop = 0;

	background_player->deleteMe();
	rocket_player->deleteMe();
	shoot_player->deleteMe();
	coin_player->deleteMe();
	delete timer; timer = nullptr;
	delete background;       background = nullptr;
	delete rocket_player;    rocket_player = nullptr;
	delete shoot_player;     shoot_player	 = nullptr;
	delete background_player; background_player = nullptr;
	delete player;           player = nullptr;
	delete score_display;    score_display = nullptr;
	delete coin_label;       coin_label = nullptr;
	disconnect(game_end, 0, 0, 0);
	delete game_end;
	for (int i = 0; i < OBSTRUCT_1_NUM; i++)
		delete obstruct1_down[i], obstruct1_down[i] = nullptr;
	for (int i = 0; i < OBSTRUCT_1_NUM; i++)
		delete obstruct1_up[i], obstruct1_up[i] = nullptr;
	for (int i = 1; i < OBSTRUCT_2_TYPES_P1; i++)
		for (int j = 0; j < OBSTRUCT_2_NUM; j++)
			delete obstruct2[i][j], obstruct2[i][j] = nullptr;
	for (int i = 0; i < ATTACK_1_NUM; i++)
		delete attack1[i], attack1[i] = nullptr;
	for (int i = 0; i < ATTACK_2_NUM; i++)
		delete attack2[i], attack2[i] = nullptr;
	for (int i = 0; i < OBSTACLE_SIGN_NUM; i++)
		delete obstacle_sign[i], obstacle_sign[i] = nullptr;
	for (int i = 0; i < COIN_NUM; i++)
		delete coin[i], coin[i] = nullptr;
}

void PlayScene::pause()
{
	tmpTime = clock();
	timer->stop();
	background_player->pause();
}

void PlayScene::resume()
{
	timer->start();
	if (is_playing_music)
		background_player->resume();
	startTime += clock() - tmpTime;
}

void PlayScene::initVar()
{
	obstacle_counter = 0;
	coin_counter = 0;
	status = 0;
	protection_status = 0;
	is_collision = 0;
	emit_by_back_button = 0;
}

void PlayScene::addObstacle()
{
	if (++obstacle_counter <= OBSTACLE_COUNT_LIM)
		return;
	obstacle_counter = 0;
	int type = rand() % 24 + 1;
	if (type <= 10)
		addObstruct1();
	else if (type <= 20)
		addObstrcut2();
	else if (type <= 22)
		addAttack1();
	else
		addAttack2();
}

void PlayScene::addObstruct1()
{
	randObstruct1(3);
	int type = rand() % 2;
	if (type)
	{
		for (int i = 0; i < OBSTRUCT_1_NUM; i++)
			if (obstruct1_down[i]->isFree())
			{
				obstruct1_down[i]->useIt();
				break;
			}
	}
	else
		for (int i = 0; i < OBSTRUCT_1_NUM; i++)
			if (obstruct1_up[i]->isFree())
			{
				obstruct1_up[i]->useIt();
				break;
			}
}

void PlayScene::addObstrcut2()
{
	int type = rand() % 5 + 1;
	for (int i = 0; i < OBSTRUCT_2_NUM; i++)
		if (obstruct2[type][i]->isFree())
		{
			obstruct2[type][i]->useIt();
			break;
		}
}

void PlayScene::addAttack1()
{
	for (int i = 0; i < ATTACK_1_NUM; i++)
		if (attack1[i]->isFree())
		{
			attack1[i]->useIt();
			addObstacleSign(attack1[i]->getHeightMid(), SIGN_DELAY_TIME);
			break;
		}
}

void PlayScene::addAttack2()
{
	for (int i = 0; i < ATTACK_2_NUM; i++)
		if (attack2[i]->isFree())
		{
			attack2[i]->useIt();
			addObstacleSign(attack2[i]->getHeightMid(), SIGN_DELAY_TIME);
			break;
		}
}

void PlayScene::addCoin()
{
	if (++coin_counter <= COIN_COUNT_LIM)
		return;
	coin_counter = 0;
	for (int i = 0; i < COIN_NUM; i++)
		if (coin[i]->isFree())
		{
			coin[i]->useIt();
			break;
		}
}

void PlayScene::coinExit(Coin* my_coin)
{
	if (is_playing_music)
		coin_player->resume();
	coin_label->show();

	QPropertyAnimation* animation = new QPropertyAnimation(coin_label, "geometry", this);
	animation->setDuration(EXITING_DURATION);
	animation->setStartValue(QRect(my_coin->getLocX(), my_coin->getLocY(), 100, 100));
	animation->setEndValue(QRect(my_coin->getLocX(), -100, 100, 100));
	animation->setEasingCurve(QEasingCurve::InBack);
	animation->start();

	QTimer::singleShot(EXITING_DURATION, [&](){
		score_display->modifyCoin(1);
		coin_label->hide();
	});
}

void PlayScene::addObstacleSign(double height, double msec)
{
	for (int i = 0; i < OBSTACLE_SIGN_NUM; i++)
		if (obstacle_sign[i]->isFree())
		{
			obstacle_sign[i]->showOnScreen(height, msec);
			break;
		}
}

void PlayScene::randObstruct1(int times)
{
	Obstruct1* tmp;
	for (int i = 0; i < times; i++)
	{
		int a = rand() % OBSTRUCT_1_NUM;
		int b = rand() % OBSTRUCT_1_NUM;
		tmp = obstruct1_up[a];
		obstruct1_up[a] = obstruct1_up[b];
		obstruct1_up[b] = tmp;

		tmp = obstruct1_down[a];
		obstruct1_down[a] = obstruct1_down[b];
		obstruct1_down[b] = tmp;
	}
}

void PlayScene::setProtected()
{
	player->setProtected();
	protection_status = 1;
	protection->move(PROTECTION_dX + player->getLocX(),
									 PROTECTION_dY + player->getLocY());
	protection->show();
}

void PlayScene::setUnProtected()
{
	player->setUnprotected();
	protection_status = 0;
	protection->hide();
}

void PlayScene::shutDownAllMusic()
{
	background_player->pause();
	rocket_player->pause();
	shoot_player->pause();
	coin_player->pause();
}

bool PlayScene::collision()
{
	if (protection_status == 1)
	{
		setUnProtected();
		return 0;
	}
	else
	{
		is_collision = 1;
		shutDownAllMusic();
		emit close();
		return 1;
	}
}

void PlayScene::updateDistance()
{
	score_display->modifyDistance(Config::gameSpeed() * REFRESH_TIME * 0.1);
}

void PlayScene::refreshObject()
{
	background->refresh();
	player->updateLoc();
	for (int i = 0; i < OBSTRUCT_1_NUM; i++)
	{
		if (!obstruct1_down[i]->isFree())
			obstruct1_down[i]->updateLoc();
		if (!obstruct1_up[i]->isFree())
			obstruct1_up[i]->updateLoc();
	}
	for (int i = 1; i < OBSTRUCT_2_TYPES_P1; i++)
		for (int j = 0; j < OBSTRUCT_2_NUM; j++)
			if (!obstruct2[i][j]->isFree())
				obstruct2[i][j]->updateLoc();
	for (int i = 0; i < ATTACK_1_NUM; i++)
		if (!attack1[i]->isFree())
			attack1[i]->updateLoc();
	for (int i = 0; i < ATTACK_2_NUM; i++)
		if (!attack2[i]->isFree())
			attack2[i]->updateLoc(player->getLocY());
	for (int i = 0; i < COIN_NUM; i++)
		if (!coin[i]->isFree())
			coin[i]->updateLoc();
	if (protection_status == 1)
		protection->move(PROTECTION_dX + player->getLocX(),
										 PROTECTION_dY + player->getLocY());
}

void PlayScene::collisionDetection()
{
	std::vector <Point> player_point;
	player_point = player->getEachPoint();
	for (int i = 0; i < OBSTRUCT_1_NUM; i++)
	{
		if (obstruct1_up[i]->isFree())
			continue;
		if (OverlapDetection::check(obstruct1_up[i]->getEachPoint(), player_point))
		{
			if (collision() == 1)
				return;
			else
				obstruct1_up[i]->releaseIt();
		}
	}
	for (int i = 0; i < OBSTRUCT_1_NUM; i++)
	{
		if (obstruct1_down[i]->isFree())
			continue;
		if (OverlapDetection::check(obstruct1_down[i]->getEachPoint(), player_point))
		{
			if (collision() == 1)
				return;
			else
				obstruct1_down[i]->releaseIt();
		}
	}
	for (int i = 1; i < OBSTRUCT_2_TYPES_P1; i++)
		for (int j = 0; j < OBSTRUCT_2_NUM; j++)
		{
			if (obstruct2[i][j]->isFree())
				continue;
			if (OverlapDetection::check(obstruct2[i][j]->getEachPoint(), player_point))
			{
				if (collision() == 1)
					return;
				else
					obstruct2[i][j]->releaseIt();
			}
		}
	for (int i = 0; i < ATTACK_1_NUM; i++)
	{
		if (attack1[i]->isFree())
			continue;
		if (OverlapDetection::check(attack1[i]->getEachPoint(), player_point))
		{
			if (collision() == 1)
				return;
			else
				attack1[i]->releaseIt();
		}
	}
	for (int i = 0; i < ATTACK_2_NUM; i++)
	{
		if (attack2[i]->isFree())
			continue;
		if (OverlapDetection::check(attack2[i]->getEachPoint(), player_point))
		{
			if (collision() == 1)
				return;
			else
				attack2[i]->releaseIt();
		}
	}
	for (int i = 0; i < COIN_NUM; i++)
	{
		if (coin[i]->isFree())
			continue;
		if (OverlapDetection::check(coin[i]->getEachPoint(), player_point))
		{
			coinExit(coin[i]);
			coin[i]->releaseIt();
		}
	}
}

bool PlayScene::scenceChoose()
{
	this->pause();
	QMessageBox::StandardButton button;
	button = QMessageBox::question(this, tr("暂停"), QString(tr("是否返回主界面")),
																 QMessageBox::Yes | QMessageBox::No);
	if (button == QMessageBox::No)
	{
		this->resume();
		return 0;
	}
	else
	{
		if (protection_status == true)
			setUnProtected();
		emit this->backToMainWindow();
		return 1;
	}
}

void PlayScene::paintEvent(QPaintEvent*)
{
	QPainter painter(this);

	//Draw map
	painter.drawPixmap(background->get1X(), background->get1Y(), *background->getMap1());
	painter.drawPixmap(background->get2X(), background->get2Y(), *background->getMap2());

	//Draw Coin
	for (int i = 0; i < COIN_NUM; i++)
		if (!coin[i]->isFree())
			painter.drawPixmap(coin[i]->getLocX(), coin[i]->getLocY(), *coin[i]->getPic());
	//Draw Obstrcut2
	for (int i = 1; i < OBSTRUCT_2_TYPES_P1; i++)
		for (int j = 0; j < OBSTRUCT_2_NUM; j++)
			if (!obstruct2[i][j]->isFree())
				painter.drawPixmap(obstruct2[i][j]->getLocX(),
													 obstruct2[i][j]->getLocY(), *obstruct2[i][j]->getPicRotated());
	//Draw Obstruct1
	for (int i = 0; i < OBSTRUCT_1_NUM; i++)
	{
		if (!obstruct1_down[i]->isFree())
			painter.drawPixmap(obstruct1_down[i]->getLocX(),
												 obstruct1_down[i]->getLocY(), *obstruct1_down[i]->getPic());
		if (!obstruct1_up[i]->isFree())
			painter.drawPixmap(obstruct1_up[i]->getLocX(),
												 obstruct1_up[i]->getLocY(), *obstruct1_up[i]->getPic());
	}
	//Draw Attack1
	for (int i = 0; i < ATTACK_1_NUM; i++)
		if (!attack1[i]->isFree())
			painter.drawPixmap(attack1[i]->getLocX(), attack1[i]->getLocY(), *attack1[i]->getPic());
	//Draw Attack2
	for (int i = 0; i < ATTACK_2_NUM; i++)
		if (!attack2[i]->isFree())
			painter.drawPixmap(attack2[i]->getLocX(),
												 attack2[i]->getLocY(), *attack2[i]->getPicRotated());
	//Draw player
	painter.drawPixmap(player->getLocX(), player->getLocY(), *player->getPic());
}

void PlayScene::keyPressEvent(QKeyEvent* event)
{
	if (event->key() == Qt::Key_Space)
	{
		if (is_playing_music && (status == 0))
		{
			rocket_player->resume();
			status = 1;
		}
		player->setState(3);
		refreshObject();
		update();
	}
	else if (event->key() == Qt::Key_Escape)
		emit close();
	else if (event->key() == Qt::Key_Control)
		if ((protection_status == 0) && (score_display->getCoinNum() >= PROTECTION_PRICE))
		{
			score_display->modifyCoin(-PROTECTION_PRICE);
			setProtected();
		}
}

void PlayScene::keyReleaseEvent(QKeyEvent* event)
{
	if (event->key() == Qt::Key_Space)
	{
		player->setState(4);
		if (is_playing_music && (status == 1))
		{
			rocket_player->pause();
			status = 0;
		}
	}
}

void PlayScene::closeEvent(QCloseEvent* event)
{
	if (emit_by_back_button == true)
		event->accept();
	else if (is_collision == 1)
	{
		game_end->setScore(score_display->getScore());
		game_end->show();
		double ax = this->x() + this->width() / 2.0 - game_end->width() / 2.0;
		double ay = this->y() + this->height() / 2.0 - game_end->height() / 2.0;
		if (ax < 0) ax = 0;
		if (ax > GetSystemMetrics(SM_CXSCREEN) - game_end->width())
			ax = GetSystemMetrics(SM_CXSCREEN) - game_end->width();
		if (ay < 0) ay = 0;
		if (ay > GetSystemMetrics(SM_CYSCREEN) - game_end->height() - 100)
			ay = GetSystemMetrics(SM_CYSCREEN) - game_end->height() - 100;
		game_end->setGeometry(ax, ay, game_end->width(), game_end->height());
		this->pause();
		event->ignore();
	}
	else
	{
		if (scenceChoose() == 1)
			event->accept();
		else
			event->ignore();
	}
}
