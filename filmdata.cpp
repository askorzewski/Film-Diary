#include "filmdata.h"
#include <QMessagebox>

FilmData::FilmData() {
    readFilmFile(directory.path() + "/films.csv");
}

void FilmData::readFilmFile(const QString &fileName){
    QFile* filmFile = new QFile(fileName);

    if(!filmFile->open(QIODevice::ReadOnly)) { //Sprawdź czy plik był wczytany
        QMessageBox::information(0, "error", filmFile->errorString());
    }

    QTextStream filmData(filmFile); //Wczytaj z pliku do wektora obiektów
    bool firstLine = 1;
    while(!filmData.atEnd()){
        QString line = filmData.readLine();
        if(firstLine){
            firstLine = 0;
            continue;
        }
        QStringList fields = line.split(",");
        int filmId = fields.at(0).toInt();
        if(!usedId.contains(filmId)){
            Film* newFilm = new Film(filmId, fields.at(1), fields.at(2), fields.at(3));
            usedId.append(filmId);
            filmList.append(newFilm);
            records.append(newFilm);
        }
        if(fields.at(4)!="NULL"){
            filmList[filmId]->addTag(fields.at(4));
        }
    }
    QTextStream(stdout) << fileName << " loaded." << Qt::endl;
    delete filmFile;
}

QList<Film*> FilmData::getFilms() const{
    return this->filmList;
}
