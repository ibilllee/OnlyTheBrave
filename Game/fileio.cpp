//Copyright (c) 2020 Li Yixuan All rights reserved.
//Date : 2020-05-15

#include "fileio.h"

FileIO::FileIO()
{}

void FileIO::appendRecord(QVector <Record> record_list_append)
{
	QFile* file_write = new QFile(storage_path);
	file_write->open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text);
	if (record_list_append[0].second == -1) return;
	QTextStream write(file_write);
	for (int i = 0, lim = record_list_append.size(); i < lim; i++)
		write << record_list_append[i].first << "," << record_list_append[i].second << "\n";
	file_write->close();
}

void FileIO::appendRecord(Record record_append)
{
	QFile* file_write = new QFile(storage_path);
	file_write->open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text);
	if (record_append.second == -1.0) return;
	QTextStream write(file_write);
	write << record_append.first << "," << record_append.second << "\n";
	file_write->close();
}

void FileIO::writeRecord(QVector <Record> record_list)
{
	QFile* file_write = new QFile(storage_path);
	file_write->open(QIODevice::WriteOnly | QIODevice::Text);
	if (record_list.size() == 0)
	{
		QTextStream write(file_write);
		write << "";
		file_write->close();
		return;
	}
	if (record_list[0].second == -1) return;
	QTextStream write(file_write);
	for (int i = 0, lim = record_list.size(); i < lim; i++)
		write << record_list[i].first << "," << record_list[i].second << "\n";
	file_write->close();
}

QVector <Record> FileIO::readRecord()
{
	QVector <Record> record_list;
	if (isFileExist(storage_path) == false)
	{
		record_list.push_back(std::make_pair("", -1));
		return record_list;
	}
	QString file_path = storage_path;
	QFile* file_read	= new QFile(file_path);
	file_read->open(QIODevice::ReadOnly | QIODevice::Text);

	QString temp_string;
	QStringList temp_string_list;
	int i = 0;
	while (!file_read->atEnd())
	{
		temp_string = QString::fromLocal8Bit(file_read->readLine());
		temp_string_list = temp_string.split(",");
		++i;
		if (temp_string_list.size() == 2)
			record_list.push_back(std::make_pair(temp_string_list[0], temp_string_list[1].toDouble()));
	}
	file_read->close();
	return record_list;
}

QVector <Record> FileIO::sortedRecord()
{
	QVector <Record> record_list;
	record_list = readRecord();
	if (record_list.empty() == false)
		sort(record_list.begin(), record_list.end(), [ = ](const Record& a, const Record& b){
			return a.second > b.second;
		});
	return record_list;
}

void FileIO::decreaseRecordTo(int res)
{
	QVector <Record> record_list;
	record_list = sortedRecord();
	if (record_list.size() > res)
		for (int i = 1, lim = record_list.size() - res; i <= lim; i++)
			record_list.pop_back();
	writeRecord(record_list);
}

void FileIO::sortRecord()
{
	writeRecord(sortedRecord());
}

bool FileIO::isFileExist(QString full_file_name)
{
	QFileInfo fileInfo(full_file_name);
	if (fileInfo.isFile())
		return true;
	return false;
}

bool FileIO::deleteFileOrFolder(const QString& strPath)
{
	if (strPath.isEmpty() || !QDir().exists(strPath))
		return false;
	QFileInfo fileInfo(strPath);

	if (fileInfo.isFile())
		QFile::remove(strPath);
	else if (fileInfo.isDir())
	{
		QDir qDir(strPath);
		qDir.setFilter(QDir::AllEntries | QDir::NoDotAndDotDot);
		QFileInfoList fileInfoLst = qDir.entryInfoList();
		foreach (QFileInfo qFileInfo, fileInfoLst)
		{
			if (qFileInfo.isFile())
				qDir.remove(qFileInfo.absoluteFilePath());
			else
			{
				deleteFileOrFolder(qFileInfo.absoluteFilePath());
				qDir.rmdir(qFileInfo.absoluteFilePath());
			}
		}
		qDir.rmdir(fileInfo.absoluteFilePath());
	}
	return true;
}
