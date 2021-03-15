//Copyright (c) 2020 Li Yixuan All rights reserved.
//Date : 2020-05-15

#include "musicplayer.h"

MusicPlayer::MusicPlayer(QWidget* parent, QString msc_path, int vlm, int is_loop)
	: music_path(msc_path)
	, volume(vlm)
{
	is_playing = 0;
	this->QSoundEffect::setParent(parent);
	this->setSource(QUrl::fromLocalFile(music_path));
	this->setVolume(0);
	if (is_loop == 1)
	{
		this->setLoopCount(QSoundEffect::Infinite);
		loop = 1;
	}
	else
		loop = 0;
	is_lock = 0;
	this->start();
}

void MusicPlayer::run()
{
	while (!isInterruptionRequested())
	{
		QMutexLocker lock(&m_lock);
		if (go_restart)
		{
			this->play();
			go_restart = 0;
		}
		msleep(LOOP_DELAY);
	}
	return;
}

void MusicPlayer::resume()
{
	this->setVolume(volume * 0.01);
	if (!this->isPlaying())
		go_restart = 1;
}

void MusicPlayer::restart()
{
	this->setVolume(volume * 0.01);
	go_restart = 1;
}

void MusicPlayer::pause()
{
	this->setVolume(0);
}

void MusicPlayer::deleteMe()
{
	if (isRunning())
	{
		this->requestInterruption();
		this->wait();
	}
}
