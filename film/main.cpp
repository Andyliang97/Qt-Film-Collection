// Sean Moore
// Test code for Homework 2

# include <QUtfStream.h>
// Include the header containing FilmList here.
# include "Film.h"

# include <QString>
# include <QList>

# define shift(n) {	\
	argc -= n;		\
	argv += n;		\
}

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

// add film functions
typedef QStringList (*AddFunc)(FilmList*, bool);
QStringList funcaddgeneral(FilmList* fl, bool top){
	QStringList sl;
	
	sl.append("");	// leave the id blank
	qout << labelTitle			<< flush;	sl.append(qin.readLine());
	qout << labelDirector		<< flush;	sl.append(qin.readLine());
	qout << labelFilmLength		<< flush;	sl.append(qin.readLine());
	qout << labelReleaseDate	<< flush;	sl.append(qin.readLine());
	
	if(top){
		Film* f = NULL;
		try{
			f = new Film(sl);
			fl->addFilm(f);
		}
		catch(QString e){
			if(f){
				delete f;
			}
			throw e;
		}
	}
	
	return sl;
}
QStringList funcaddeducational(FilmList* fl, bool top){
	QStringList sl;
	
	sl.append(funcaddgeneral(fl, false));
	qout << labelSubject		<< flush;	sl.append(qin.readLine());
    while (true) {
        qout << "Grade Level (Freshman, Sophomore, Junior, Senior, Graduate): " << flush;	
        QString tmpInput = qin.readLine();
        if (stringToGrade(tmpInput) != InvalidGrade) {
            sl.append(tmpInput);
            break;
        }
    }
    qout << labelAuthors		<< flush;	sl.append(qin.readLine());
	
	if(top){
		Educational* f = NULL;
		try{
			f = new Educational(sl);
			fl->addFilm(f);
		}
		catch(QString e){
			if(f){
				delete f;
			}
			throw e;
		}
	}
	
	return sl;
}
QStringList funcaddeducationalbystudents(FilmList* fl, bool top){
    QStringList sl;

    sl.append(funcaddeducational(fl, false));
    qout << labelDepartment		<< flush;	sl.append(qin.readLine());

    if(top){
        ByStudents* f = NULL;
        try{
            f = new ByStudents(sl);
            fl->addFilm(f);
        }
        catch(QString e){
            if(f){
                delete f;
            }
            throw e;
        }
    }

    return sl;
}
QStringList funcaddeducationalbypublishers(FilmList* fl, bool top){
    QStringList sl;

    sl.append(funcaddeducational(fl, false));
    qout << labelPublisher		<< flush;	sl.append(qin.readLine());

    if(top){
        ByPublishers* f = NULL;
        try{
            f = new ByPublishers(sl);
            fl->addFilm(f);
        }
        catch(QString e){
            if(f){
                delete f;
            }
            throw e;
        }
    }

    return sl;
}
QStringList funcaddentertainment(FilmList* fl, bool top){
	QStringList sl;
	
	sl.append(funcaddgeneral(fl, false));
    while (true) {
		qout << "Film Type (Action, Comedy, SciFi, Thriller, Horror): " << flush;
        QString tmpInput = qin.readLine();
        if (stringToFilmType(tmpInput) != InvalidType) {
            sl.append(tmpInput);
            break;
        }
    }
    while (true) {
        qout << "MPAA Rating (G, PG, PG-13, R): " << flush;
        QString tmpInput = qin.readLine();
        if (stringToRating(tmpInput) != InvalidRate) {
            sl.append(tmpInput);
            break;
        }
    }
	
	if(top){
		Entertainment* f = NULL;
		try{
			f = new Entertainment(sl);
			fl->addFilm(f);
		}
		catch(QString e){
			if(f){
				delete f;
			}
			throw e;
		}
	}
	
	return sl;
}
const QList<QString> filmSwitch = QList<QString>()
	<< "Add General Film"
	<< "Add Educational Film"
    << "Add Educational Film By Students"
    << "Add Educational Film By Publishers"
	<< "Add Entertainment Film"
;
const QList<AddFunc> addFunc = QList<AddFunc>()
	<< funcaddgeneral
	<< funcaddeducational
    << funcaddeducationalbystudents
    << funcaddeducationalbypublishers
	<< funcaddentertainment
;

// top-level operations
typedef bool (*FilmFunc)(FilmList*);
bool funcadd(FilmList* fl){
	while(1){
		for(int i=0; i<filmSwitch.length(); ++i){
			qout
				<< QString::number(i) << ": " << filmSwitch[i] << endl;
		}
		
		qout << "Choice: " << flush;
		QString line = qin.readLine();
		qout << endl;
		bool ok=false;
		int choice = line.toInt(&ok);
		if(ok && ((0 > choice) || (choice >= filmSwitch.length()))){
			throw QString()+"Must choose a number ["+QString::number(0)+","+QString::number(filmSwitch.length())+")";
		}
		
		addFunc[choice](fl, true);
		break;
	}
	
	return false;
}
bool funcremove(FilmList* fl){
	qout << "Enter Film ID: " << flush;
	fl->removeFilm(qin.readLine());
	
	return false;
}
bool funcfind(FilmList* fl){
	qout << "Enter Film ID: " << flush;
	const QString in = qin.readLine();
	Film* f = fl->findFilm(in);
	
	if(f){
		qout << f->toString(true, "\n") << endl;
	}
	else{
		throw QString()+"No film with ID \""+in+"\".";
	}
	
	return false;
}
bool funcgetid(FilmList* fl){
	qout << "Enter Film Title: " << flush;
	const QString in = qin.readLine();
	
	const QStringList id = fl->getID(in);
	
	if(id.length() == 0){
		throw QString()+"No film with \""+in+"\" as a title.";
	}
	
	for(int i=0; i<id.length(); ++i){
		qout << "Film ID: " << id[i] << endl;
	}
	
	return false;
}
bool funcexit(FilmList* fl){
	(void)fl;
	return true;
}
const QList<QString> taskSwitch = QList<QString>()
	<< "Add film"
	<< "Remove film"
	<< "Find film"
	<< "Get film ID"
	<< "Exit"
;
const QList<FilmFunc> taskFunc = QList<FilmFunc>()
	<< funcadd
	<< funcremove
	<< funcfind
	<< funcgetid
	<< funcexit
;

int main(int argc, char** argv){
	shift(1);
	
	FilmList fl;
	
	while(1){
		try{
			for(int i=0; i<taskSwitch.length(); ++i){
				qout
					<< QString::number(i) << ": " << taskSwitch[i] << endl;
			}
			
			qout << "Choice: " << flush;
			QString line = qin.readLine();
			qout << endl;
			
			bool ok=false;
			int choice = line.toInt(&ok);
			if(ok && ((0 > choice) || (choice >= taskSwitch.length()))){
				throw QString()+"Must choose a number ["+QString::number(0)+","+QString::number(taskSwitch.length())+")";
			}
			
			if(taskFunc[choice](&fl)){
				qDeleteAll(fl);
				break;
			}
			qout << endl;
		}
		catch(QString e){
			qerr << e << endl << endl;
		}
	}
	
	return 0;
}
