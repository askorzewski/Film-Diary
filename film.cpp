#include "film.h"

Film::Film(int id) : Record(id){

}

Film::Film(int id, QString name, QString director, QString year) :
    Record(id),
    name(name),
    director(director),
    year(year)
{}

QString Film::getName() const{
    return this->name;
}


QString Film::getDirector() const{
    return this->director;
}

QString Film::getYear() const{
    return this->year;
}

void Film::addTag(const QString& tag){
    if(tags.empty()){
        tags = {tag};
    }
    else{
        tags<<tag;
    }
}

QString Film::toText(){
    if(tags.empty()) {
        return QString(QString::number(id) + "," + name + "," + director + ",NULL");
    }
    QString output;
    for(QString tag : tags){
        output = QString(QString::number(id) + "," + name + "," + director + ",");
        output.append(tag);
    }
    return output;
}

QString Film::getLabel(){
    return QString(name + " (" + year + ")");
}


