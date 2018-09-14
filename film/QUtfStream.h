// Sean Moore
// 905418396
// sean8051@vt.edu
// ECE 3574
// Homework 2

# pragma once

# include <QTextStream>
# include <QTextCodec>
# include <QIODevice>
# include <QString>
# include <stdio.h>

class QUtfStream : public QTextStream {
public:
	QUtfStream();
	QUtfStream ( QIODevice * device );
	QUtfStream ( FILE * fileHandle, QIODevice::OpenMode openMode = QIODevice::ReadWrite );
	QUtfStream ( QString * string, QIODevice::OpenMode openMode = QIODevice::ReadWrite );
	QUtfStream ( QByteArray * array, QIODevice::OpenMode openMode = QIODevice::ReadWrite );
	QUtfStream ( const QByteArray & array, QIODevice::OpenMode openMode = QIODevice::ReadOnly );
	virtual ~QUtfStream();
};

extern QUtfStream qout;
extern QUtfStream qerr;
extern QUtfStream qin;
