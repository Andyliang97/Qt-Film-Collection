// Sean Moore
// Homework 2 Problem 1
// Student Name:Junjie Liang
// Student ID:905965464
// Email address: junjl97@vt.edu
// Class: ECE3574

#ifndef LIBRARY_UI_H_                                                                           
#define LIBRARY_UI_H_  

#include <QStringList>
#include <QTextStream>
#include <QFile>
#include <QDate>
#include <QDebug>

class Library;

class LibraryUI
{
public:
	enum Choices { READ = 1, ADD, FIND, REMOVE, SAVE, LIST, QUIT };
	enum Types { BOOK, REFERENCEBOOK, TEXTBOOK, DVD, FILM, DATADVD };

public:
	LibraryUI(Library* lib);

	void add(QStringList objdata);
	void read();
	void enterData();
	QString find();
	void remove();
	void save();
	void list();
	QStringList promptRefItem();
	QStringList promptBook();
	QStringList promptReferenceBook();
	QStringList promptTextBook();
	QStringList promptDVD();
	QStringList promptFilm();
	QStringList promptDataBase();
	Choices nextTask();
	void prepareToQuit(bool saved);

private:
	Library* m_Lib;
};
#endif 

