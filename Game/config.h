//Copyright (c) 2020 Li Yixuan All rights reserved.
//Date : 2020-05-15

#ifndef CONFIG_H
#define CONFIG_H

/*----------主页配置---------*/
#define WINDOW_WIDTH 1440
#define WINDOW_HEIGHT 826
#define WINDOW_ICON "://Material/Picture/aircraft.png"
#define WINDOW_TITLE "勇往直前"
#define MAIN_BACKGROUND "://Material/Picture/mainpage.png"

/*--------游戏界面配置-------*/
#define GAME_BACKGROUND "://Material/Picture/background.jpg"
#define REFRESH_RATE 5.0
#define CEIL_Y 0
#define FLOOR_Y 773.0
#define EPS 2.0

/*--------记录界面配置-------*/
#define RECORD_BACKGROUND_PIC "://Material/Picture/record_background.png"

/*--------介绍界面配置-------*/
#define BACKGROUND_PIC "://Material/Picture/mainpage_without_txt.png"

/*----------物理配置---------*/
#define G_Force 8.0
#define REFRESH_TIME (REFRESH_RATE * 0.013)
#define REFRESH_PER_SEC (1000 / REFRESH_RATE)
#define FLY_FORCE 225.0
#define FLY_V0 -2.0

/*----------人物配置---------*/
#define MAN_PIC "://Material/Picture/man_%1.png"
#define PLAYER_LOC_X 500.0
#define CHANGE_PIC_TIMES 32

/*----------障碍配置---------*/
#define OBSTRUCT_1_PIC "://Material/Picture/stone_%1.png"
#define OBSTRUCT_1_NUM 7
#define OBSTRUCT_2_PIC "://Material/Picture/obstical_%2.png"
#define OBSTRUCT_2_TYPES_P1 6
#define OBSTRUCT_2_NUM 7
#define ATTACK_1_PIC "://Material/Picture/bullet_1.png"
#define ATTACK_1_NUM 3
#define ATTACK_2_PIC "://Material/Picture/bullet_2.png"
#define ATTACK_2_NUM 3
#define ATTACK_2_PIC_X 87.0
#define ATTACK_2_PIC_Y 71.0
#define ATTACK_2_dANGLE 0.18
#define OBSTACLE_SIGN_PIC "://Material/Picture/warning.png"
#define OBSTACLE_SIGN_ANIMATION_TIME 60
#define OBSTACLE_SIGN_NUM 5
#define SIGN_DELAY_TIME 2000
#define OBSTACLE_COUNT_LIM 260

/*----------音乐配置---------*/
#define BACKGROUND_MUSIC "://Material/Music/background.wav"
#define BOOM_MUSIC "://Material/Music/boom.wav"
#define SHOOT_MUSIC "://Material/Music/shoot.wav"
#define COIN_MUSIC "://Material/Music/coin.wav"
#define GAME_MUSIC "://Material/Music/gameMusic_%1.wav"
#define ROCKET_MUSIC "://Material/Music/rocket.wav"

#define BACKGROUND_MUSIC_VOLUME 70
#define GAME_MUSIC_VOLUME 40
#define ROCKET_MUSIC_VOLUME 40
#define SHOOT_MUSIC_VOLUME 80
#define COIN_MUSIC_VOLUME 60

/*----------按钮配置---------*/
#define ZOOM_DOWN_DURATION 75
#define ZOOM_UP_DURATION 150
#define EASING_CURVE QEasingCurve::OutQuart
#define LOOP_DELAY 10

/*-------按钮图标文字配置------*/
#define PRESS_BUTTON "://Material/Picture/PressButton.png"
#define START_GAME_TEXT "://Material/Picture/start_game.png"
#define VIEW_RECORD_TEXT "://Material/Picture/view-record.png"
#define ABOUT_TEXT "://Material/Picture/about.png"
#define YES_MUSIC "://Material/Picture/yes_music.png"
#define NO_MUSIC "://Material/Picture/no_music.png"
#define PRESS_BUTTON_LITE "://Material/Picture/PressButto_lite.png"
#define BACK_TXT "://Material/Picture/back_txt.png"
#define CLEAR_TXT "://Material/Picture/clear_txt.png"
#define CLEAR_CACHE_TXT "://Material/Picture/clear_cache_txt.png"

/*--------游戏状态配置-------*/
#define STATUS_BAR_PIC "://Material/Picture/status_bar.png"
#define STATUS_BAR_PIC_X 100
#define STATUS_BAR_PIC_Y 20
#define STATUS_BAR_WORD_dX 7
#define STATUS_BAR_WORD_dY 7
#define TEXT_FONT "黑体"
#define TEXT_SIZE 12

/*----------金币配置---------*/
#define COIN_PIC "://Material/Picture/coin.png"
#define COIN_NUM 5
#define EXITING_DURATION 700
#define COIN_COUNT_LIM 550

/*---------防护服配置--------*/
#define PROTECTION_PIC "://Material/Picture/protection.png"
#define PROTECTION_TRANSPARENCY 110
#define PROTECTION_PRICE 3
#define PROTECTION_dX -10
#define PROTECTION_dY -5

/*--------结束界面配置-------*/
#define GAME_END_WINDOW_TRANSPARENCY 0.8

/*----------存档配置---------*/
#define FILE_NAME "OLB_Record.txt"

/*----------其他配置---------*/
#define SEPERATOR "------------------------------------------------------------------------\n"

#include <vector>
#include <QStandardPaths>

class Config
{
public:
	Config();
	static double gameSpeed();
	static double rocketSpeed();
	static double getObstacle2EachPointX(int);
	static double getObstacle2EachPointY(int);
};

#endif // CONFIG_H
