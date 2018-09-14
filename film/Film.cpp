// Sean Moore
// Homework 2 Problem 1
# include "Film.h"
# include <typeinfo>

int FilmList::m_IDCounter = 0;
const QString labelFilmID		= "Film ID:      ";
const QString labelTitle		= "Title:        ";
const QString labelDirector		= "Director:     ";
const QString labelFilmLength	= "Film Length:  ";
const QString labelReleaseDate	= "Release Date: ";
const QString labelFilmTypes	= "Film Type:    ";
const QString labelMPAARatings	= "MPAA Rating:  ";
const QString labelSubject		= "Subject:      ";
const QString labelGradeLevel	= "Grade Level:  ";
const QString labelAuthors      = "Authors:      ";
const QString labelPublisher	= "Publisher:    ";
const QString labelDepartment	= "Department:   ";

QString filmTypeToString(FilmTypes type)
{
    switch (type)
    {
    case Action: return "Action";
    case Comedy: return "Comedy";
    case SciFi: return "SciFi";
    case Thriller: return "Thriller";
    case Horror: return "Horror";
    default: return "";
    }
}

FilmTypes stringToFilmType(QString strType)
{
    if (strType == "Action")
        return Action;
    if (strType == "Comedy")
        return Comedy;
    if (strType == "SciFi")
        return SciFi;
    if (strType == "Thriller")
        return Thriller;
    if (strType == "Horror")
        return Horror;
    return InvalidType;
}

QString ratingToString(MPAARatings rate)
{
    switch (rate)
    {
    case G: return "G";
    case PG: return "PG";
    case PG_13: return "PG-13";
    case R: return "R";
    default: return "";
    }
}

MPAARatings stringToRating(QString strRate)
{
    if (strRate == "G")
        return G;
    if (strRate == "PG")
        return PG;
    if (strRate == "PG-13")
        return PG_13;
    if (strRate == "R")
        return R;
    return InvalidRate;
}

QString gradeToString(GradeLevel grade)
{
    switch (grade)
    {
    case Freshman: return "Freshman";
    case Sophomore: return "Sophomore";
    case Junior: return "Junior";
    case Senior: return "Senior";
    case Graduate: return "Graduate";
    default: return "";
    };
}

GradeLevel stringToGrade(QString strGrade)
{
    if (strGrade == "Freshman")
        return Freshman;
    if (strGrade == "Sophomore")
        return Sophomore;
    if (strGrade == "Junior")
        return Junior;
    if (strGrade == "Senior")
        return Senior;
    if (strGrade == "Graduate")
        return Graduate;
    return InvalidGrade;
}

Film::Film(QStringList& propList)
{
    m_FilmID = propList.takeFirst(); 
    m_Title = propList.takeFirst();
    m_Director = propList.takeFirst();
    
    QString sLength = propList.takeFirst();
    bool ok = false;
    m_FilmLength = sLength.toInt(&ok);
    QString sDate = propList.takeFirst();
    m_ReleaseDate = QDate::fromString(sDate, "yyyy-MM-dd");
}

Film::Film(QString id, QString title, QString dir, quint32 length, QDate relDate) : m_FilmID(id),
    m_Title(title), m_Director(dir), m_FilmLength(length), m_ReleaseDate(relDate)
{}

QString Film::getTitle()
{
    return m_Title;
}

QString Film::getDirector()
{
	return m_Director;
}

QString Film::getFilmID()
{
    return m_FilmID;
}

void Film::setFilmID(QString id)
{
	m_FilmID = id;
}

quint32 Film::getFilmLength()
{
    return m_FilmLength;
}

QDate Film::getReleaseDate()
{
    return m_ReleaseDate;
}

QString Film::toString(bool labeled, QString sepChar)
{
	QString result;
	if (labeled)
		result += labelFilmID;
	result += (m_FilmID + sepChar);
	if (labeled)
		result += labelTitle;
	result += (m_Title + sepChar);
	if (labeled)
		result += labelDirector;
	result += (m_Director + sepChar);
	if (labeled)
		result += labelFilmLength;
	result += (QString::number(m_FilmLength) + sepChar);
	if (labeled)
		result += labelReleaseDate;
	result += m_ReleaseDate.toString("yyyy-MM-dd");
	return result;
}

Educational::Educational(QStringList& propList) : Film(propList)
{
    m_Subject = propList.takeFirst();
    QString sGrade = propList.takeFirst();
    m_GradeLevel = stringToGrade(sGrade);
    m_Authers = propList.takeFirst();
}

Educational::Educational(QString id, QString title, QString dir, quint32 length, QDate relDate, QString subject, GradeLevel grade, QString authors)
    : Film(id, title, dir, length, relDate), m_Subject(subject), m_GradeLevel(grade), m_Authers(authors)
{}

QString Educational::toString(bool labeled, QString sepchar)
{
	QString result = Film::toString(labeled, sepchar);
	result += sepchar;
	if (labeled)
		result += labelSubject;
	result += (m_Subject + sepchar);
	if (labeled)
		result += labelGradeLevel;
	result += (gradeToString(m_GradeLevel) + sepchar);
	if (labeled)
		result += labelAuthors;
	result += m_Authers;
	return result;
}

ByStudents::ByStudents(QStringList& propList) : Educational(propList), m_Department(propList.takeFirst())
{}

ByStudents::ByStudents(QString id, QString title, QString dir, quint32 length, QDate relDate, QString subject, GradeLevel grade, QString authors, QString department)
    : Educational(id, title, dir, length, relDate, subject, grade, authors), m_Department(department)
{}

QString ByStudents::toString(bool labeled, QString sepchar)
{
	QString result = Educational::toString(labeled, sepchar);
	result += sepchar;
	if (labeled)
		result += labelDepartment;
	result += m_Department;
	return result;
}

ByPublishers::ByPublishers(QStringList& propList) : Educational(propList), m_Publisher(propList.takeFirst())
{}

ByPublishers::ByPublishers(QString id, QString title, QString dir, quint32 length, QDate relDate, QString subject, GradeLevel grade, QString authors, QString publisher)
    : Educational(id, title, dir, length, relDate, subject, grade, authors), m_Publisher(publisher)
{}

QString ByPublishers::toString(bool labeled, QString sepchar)
{
	QString result = Educational::toString(labeled, sepchar);
	result += sepchar;
	if (labeled)
		result += labelPublisher;
	result += m_Publisher;
	return result;
}

Entertainment::Entertainment(QStringList& propList) : Film(propList)
{
    QString sType = propList.takeFirst();
    m_Type = stringToFilmType(sType);
    QString sRate = propList.takeFirst();
    m_Rating = stringToRating(sRate);
}

Entertainment::Entertainment(QString id, QString title, QString dir, quint32 length, QDate relDate, FilmTypes type, MPAARatings rating)
    : Film(id, title, dir, length, relDate), m_Type(type), m_Rating(rating)
{}

QString Entertainment::toString(bool labeled, QString sepchar)
{
	QString result = Film::toString(labeled, sepchar);
	result += sepchar;
	if (labeled)
		result += labelFilmTypes;
	result += (filmTypeToString(m_Type) + sepchar);
	if (labeled)
		result += labelMPAARatings;
	result += ratingToString(m_Rating);
	return result;
}

Film* FilmList::findFilm(QString id)
{
    for (int i = 0; i < length(); ++i)
    {
        Film* pFilm = value(i);
        if (pFilm->getFilmID() == id)
            return pFilm;
    }
    return NULL;
}

QStringList FilmList::getID(QString title)
{
    QStringList list;
    for (int i = 0; i < length(); ++i)
    {
        Film* pFilm = value(i);
        if (pFilm->getTitle() == title)
            list.append(pFilm->getFilmID());
    }
    return list;
}

void FilmList::addFilm(Film* film)
{
    if (! film)
        return;
    for (int i = 0; i < length(); ++i)
    {
        Film* pFilm = value(i);
        if (typeid(*film) != typeid(*pFilm))
            continue;
        if (film->getTitle() == pFilm->getTitle() && film->getDirector() == pFilm->getDirector() &&
            film->getFilmLength() == pFilm->getFilmLength() && film->getReleaseDate() == pFilm->getReleaseDate())
            return;
    }
    ++ m_IDCounter;
    film->setFilmID(QString::number(m_IDCounter));
    append(film);
}

void FilmList::removeFilm(QString filmID)
{
    for (int i = 0; i < length(); ++i)
    {
        Film* pFilm = value(i);
        if (pFilm->getFilmID() == filmID)
        {
            delete pFilm;
            removeAt(i);
            break;
        }
    }
}

