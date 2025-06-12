#include "filmdata.h"
#include <QMessagebox>

FilmData::FilmData() {
    readFile(directory.path() + "/films.csv");
}

/**
 * @brief FilmData::FilmData Konstruktor wykorzystywany wyłącznie do tworzenia watchlist
 * @param account Wskaźnik na dane konta do którego należy watchlista
 */
FilmData::FilmData(Database* account){
    this->id = account->getId();
    directory = account->getDir();
    readFile(account->getDir() + "/watchlist.csv");
}

/**
 * @brief FilmData::readFile Metoda odziedziczona z klasy Database. Czyta pliki przygotowane do formatu przechowującego dane o filmach ("films.csv", "watchlist.csv").
 * @param fileName Nazwa pliku
 */
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
    delete filmFile;
}


/**
 * @brief FilmData::getFilms Metoda, która zwraca liste filmóW
 * @return
 */
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
    Record* rec = &film;
    filmList.append(film);
    addRecord(rec);
}

void FilmData::swapFilm(Film &film){
    Record* originalRecord = findRecord(film.getId());
    Film* ptr_originalFilm = static_cast<Film*>(originalRecord);
    Film& originalFilm = *ptr_originalFilm;
    originalFilm = film;
}
