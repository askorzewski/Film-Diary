#include "filmdata.h"
#include <QMessagebox>

FilmData::FilmData() {
    readFilmFile(directory.path() + "/films.csv");

}

//POTEM: Ten konstruktor może byc bardziej ogolny
FilmData::FilmData(Database* account){
    this->id = account->getId();
    directory = account->getDir();
    readFilmFile(account->getDir() + "/watchlist.csv");
}

void FilmData::readFilmFile(const QString &fileName){
    QFile* filmFile = new QFile(fileName);

    if(!filmFile->open(QIODevice::ReadOnly)) {
        QMessageBox::information(0, "error", filmFile->errorString());
    }

    QTextStream filmData(filmFile);
    //bool firstLine = 1;
    while(!filmData.atEnd()){
        QString line = filmData.readLine();
        // if(firstLine){
        //     firstLine = 0;
        //     continue;
        // }
        Film* newFilm;
        QStringList fields = line.split(",");
        int filmId = fields.at(0).toInt();
        if(!usedId.contains(filmId)){
            newFilm = new Film(filmId, fields.at(1), fields.at(2), fields.at(3));
            usedId.append(filmId);
        }
        else{
            continue;
        }
        if(fields.at(4)!="NULL"){
            newFilm->addTag(fields.at(4));
        }
        filmList.append(*newFilm);
        records.append(newFilm);
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
    filmList.append(film);
}
