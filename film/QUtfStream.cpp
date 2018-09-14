// Sean Moore
// 905418396
// sean8051@vt.edu
// ECE 3574
// Homework 2

# include "QUtfStream.h"

QUtfStream::QUtfStream() :
QTextStream(){
	setCodec(QTextCodec::codecForName("UTF-8"));
};
QUtfStream::QUtfStream ( QIODevice* device ) :
QTextStream ( device ){
	setCodec(QTextCodec::codecForName("UTF-8"));
};
QUtfStream::QUtfStream ( FILE * fileHandle, QIODevice::OpenMode openMode ) :
QTextStream ( fileHandle, openMode  ){
	setCodec(QTextCodec::codecForName("UTF-8"));
};
QUtfStream::QUtfStream ( QString * string, QIODevice::OpenMode openMode ) :
QTextStream ( string, openMode ){
	setCodec(QTextCodec::codecForName("UTF-8"));
};
QUtfStream::QUtfStream ( QByteArray * array, QIODevice::OpenMode openMode ) :
QTextStream ( array, openMode ){
	setCodec(QTextCodec::codecForName("UTF-8"));
};
QUtfStream::QUtfStream ( const QByteArray & array, QIODevice::OpenMode openMode ) :
QTextStream ( array, openMode ){
	setCodec(QTextCodec::codecForName("UTF-8"));
}
QUtfStream::~QUtfStream() {
}

QUtfStream qout(stdout, QIODevice::WriteOnly);
QUtfStream qerr(stderr, QIODevice::WriteOnly);
QUtfStream qin(stdin, QIODevice::ReadOnly);
