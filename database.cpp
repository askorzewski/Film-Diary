#include "database.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QDir>

/**
 * @brief Database::Database - konstruktor, automatycznie szuka bazowe
 * @param id
 */
Database::Database(int id) {
    QDir directory = this->directory;
    directory.current();
    if(directory.exists("Data"+QString::number(id))){
        directory.cd("Data"+QString::number(id));
        *this = Database(id, directory.path());
        return;
    }
    if(!directory.mkdir("Data"+QString::number(id))){
        QMessageBox::information(0, "error", "Directory could not be created.");
    }
    directory.cd("Data"+QString::number(id));
    QFile filmFile = QFile(directory.path()+"/films.csv");
    QFile entryFile = QFile(directory.path()+"/entries.csv");
    if(!filmFile.open(QIODevice::NewOnly)) {
        QMessageBox::information(0, "error", filmFile.errorString());
    }
    if(!entryFile.open(QIODevice::NewOnly)) {
        QMessageBox::information(0, "error", entryFile.errorString());
    }
}

Database::Database(int id, QString path){
    this->readFilmFile(path+"/films.csv");
    //this->readEntryFile(path+"/entries.csv");
}


void Database::readFilmFile(const QString &fileName){
    QFile* filmFile = new QFile(fileName);
    QList<Film> filmList;

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
            Film newFilm(filmId, fields.at(1), fields.at(2), fields.at(3));
            usedId.append(filmId);
            filmList.append(newFilm);
        }
        if(fields.at(4)!="NULL"){
            filmList[filmId].addTag(fields.at(4));
        }
    }
    QTextStream(stdout) << fileName << " loaded." << Qt::endl;
    delete filmFile;
    this->films=filmList;
}

void Database::addFilm(const Film &film){
    this->films.append(film);
}

int Database::assignId(){
    int newId = *(usedId.end()-1)+1;
    usedId.append(newId);
    return newId;
}

QList<Record> Database::getFilms() const{
    return this->films;
}

void saveToFile(){

}
