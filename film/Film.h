// Sean Moore
// Homework 2 Problem 1
// Student Name:Junjie Liang
// Student ID:905965464
// Email address: junjl97@vt.edu
// Class: ECE3574


# pragma once

# include <QString>
# include <QStringList>
# include <QList>
# include <QDate>

enum FilmTypes
{
    InvalidType,
    Action,
    Comedy,
    SciFi,
    Thriller,
    Horror,
};

enum MPAARatings
{
    InvalidRate,
    G,
    PG,
    PG_13,
    R,
};

enum GradeLevel
{
    InvalidGrade,
    Freshman,
    Sophomore,
    Junior,
    Senior,
    Graduate,
};

class Film
{
public:
    Film(QStringList& propList);
    Film(QString id, QString title, QString dir, quint32 length, QDate relDate);
	virtual ~Film() {}

    virtual QString toString(bool labeled, QString sepChar);

    QString getTitle();
    QString getDirector();
    quint32 getFilmLength();
    QDate   getReleaseDate();

    QString getFilmID();
    void    setFilmID(QString id);

private:
    QString m_FilmID;
    QString m_Title;
    QString m_Director;
    quint32 m_FilmLength;
    QDate m_ReleaseDate;
};

class Educational : public Film
{
public:
    Educational(QStringList& propList);
    Educational(QString id, QString title, QString dir, quint32 length, QDate relDate, QString subject, GradeLevel grade, QString authors);
    
    virtual QString toString(bool labeled, QString sepchar);

private:
    QString m_Subject;
    GradeLevel m_GradeLevel;
    QString m_Authers;
};

class ByStudents : public Educational
{
public:
    ByStudents(QStringList& propList);
    ByStudents(QString id, QString title, QString dir, quint32 length, QDate relDate, QString subject, GradeLevel grade, QString authors, QString department);

    virtual QString toString(bool labeled, QString sepchar);

private:
    QString m_Department;
};

class ByPublishers : public Educational
{
public:
    ByPublishers(QStringList& propList);
    ByPublishers(QString id, QString title, QString dir, quint32 length, QDate relDate, QString subject, GradeLevel grade, QString authors, QString publisher);

    virtual QString toString(bool labeled, QString sepchar);

private:
    QString m_Publisher;
};

class Entertainment : public Film
{
public:
    Entertainment(QStringList& propList);
    Entertainment(QString id, QString title, QString dir, quint32 length, QDate relDate, FilmTypes type, MPAARatings rating);
    
    virtual QString toString(bool labeled, QString sepchar);

private:
    FilmTypes m_Type;
    MPAARatings m_Rating;
};

// The filelist structure 
class FilmList : public QList<Film*>
{
public:
    QString toString();

    Film* findFilm(QString id);

    QStringList getID(QString title);

    void addFilm(Film* film);

    void removeFilm(QString filmID);

    static  int m_IDCounter;
};

QString filmTypeToString(FilmTypes type);
FilmTypes stringToFilmType(QString strType);
QString ratingToString(MPAARatings rate);
MPAARatings stringToRating(QString strRate);
QString gradeToString(GradeLevel grade);
GradeLevel stringToGrade(QString strGrade);

