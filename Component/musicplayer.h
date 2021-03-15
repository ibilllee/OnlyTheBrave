//Copyright (c) 2020 Li Yixuan All rights reserved.
//Date : 2020-05-15

#ifndef MUSICPLAYER_H
#define MUSICPLAYER_H

#include "../Game/config.h"

#include <QDebug>
#include <QMutex>
#include <QSoundEffect>
#include <QThread>
#include <QWidget>

class MusicPlayer : public QSoundEffect, public QThread
{
public:
	MusicPlayer(QWidget* parent		= nullptr,
							QString	 msc_path = BACKGROUND_MUSIC,
							int			 vlm = 100,
							int			 is_loop = 0);
	void check();
	void resume();
	void restart();
	void pause();
	void deleteMe();

protected:
	virtual void run() override;

private:
	QString music_path;
	QMutex m_lock;
	int volume;
	bool go_restart;
	bool is_playing;
	bool loop;
	bool is_lock;
};

#endif // MUSICPLAYER_H
