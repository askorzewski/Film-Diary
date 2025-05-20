#include "film.h"

Film::Film(int id, QString name, QString director, QString year) {
    this->id = id;
    this->name = name;
    this->director = director;
    this->year = year;
}

QString Film::getName() const{
    return this->name;
}

int Film::getId() const{
    return this->id;
}

QString Film::getDirector() const{
    return this->director;
}

QString Film::getYear() const{
    return this->year;
}

void Film::addTag(const QString& tag){
    this->tags<<tag;
}
