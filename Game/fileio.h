//Copyright (c) 2020 Li Yixuan All rights reserved.
//Date : 2020-05-15

#ifndef FILEIO_H
#define FILEIO_H

#include "config.h"
#include <QString>
#include <QDebug>
#include <QFile>
#include <QStandardPaths>
#include <QFileInfo>
#include <QVector>
#include <QDir>

typedef std::pair <QString, double> Record;

extern QString storage_path;

class FileIO
{
public:
	FileIO();
	static void appendRecord(QVector <Record> record_list_append);
	static void appendRecord(Record record_append);
	static void writeRecord(QVector <Record> record_list);
	static QVector <Record> readRecord();
	static QVector <Record> sortedRecord();
	static void decreaseRecordTo(int res);
	static void sortRecord();
	static bool isFileExist(QString full_file_name);
	static bool deleteFileOrFolder(const QString& strPath);
};

#endif // FILEIO_H
