//Copyright (c) 2020 Li Yixuan All rights reserved.
//Date : 2020-05-15

#include "config.h"
#include "../Scene/mainwindow.h"
#include <iostream>
#include <QApplication>

int main(int argc, char* argv[])
{
	QApplication a(argc, argv);
	MainWindow w;
	w.show();
	w.checkFirstRun();
	return a.exec();
}
