#include "filmdata.h"
#include <QMessagebox>

FilmData::FilmData() {
    readFile(directory.path() + "/films.csv");
}

//POTEM: Ten konstruktor może byc bardziej ogolny
FilmData::FilmData(Database* account){
    this->id = account->getId();
    directory = account->getDir();
    readFile(account->getDir() + "/watchlist.csv");
}

void FilmData::readFile(const QString &fileName){
    QFile* filmFile = new QFile(fileName);
    if(!filmFile->exists()){
        filmFile->open(QIODevice::NewOnly);
    }

    if(!filmFile->open(QIODevice::ReadOnly)) {
        QMessageBox::information(0, "error", filmFile->errorString());
    }

    QTextStream filmData(filmFile);

    Film* newFilm;
    bool sameId = 0;
    while(!filmData.atEnd()){
        QString line = filmData.readLine();

        QStringList fields = line.split(",");
        int filmId = fields.at(0).toInt();
        sameId = usedId.contains(filmId);
        if(!sameId){
            newFilm = new Film(filmId, fields.at(1), fields.at(2), fields.at(3));
        }
        if(fields.at(4)!="NULL"){
            newFilm->addTag(fields.at(4));
        }
        if(!sameId){
            usedId.append(filmId);
            addFilm(*newFilm);
        }
    }
    //QTextStream(stdout) << fileName << " loaded." << Qt::endl;
    delete filmFile;
}

QList<Film> FilmData::getFilms() const{
    return this->filmList;
}

void FilmData::saveToFiles(){
    if(id == 0){
        writeToFile("films.csv");
    }
    else{
        writeToFile("watchlist.csv");
    }
}

void FilmData::addFilm(Film &film){
    Film* f = new Film(0);
    Record* rec = &film;
    rec = f;
    addRecord(rec);
    filmList.append(film);
}

void FilmData::swapFilm(Film &film){
    Record* originalRecord = findRecord(film.getId());
    Film* ptr_originalFilm = static_cast<Film*>(originalRecord);
    Film& originalFilm = *ptr_originalFilm;
    originalFilm = film;
}
