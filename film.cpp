#include "film.h"

Film::Film(int id) : Record(id){
}

Film::Film(int id, QString name, QString director, QString year) :
    Record(id),
    name(name),
    director(director),
    year(year){
}



Film::~Film(){

}

QString Film::getName() const{
    return this->name;
}


QString Film::getDirector() const{
    return this->director;
}

QString Film::getYear() const{
    return this->year;
}

void Film::addTag(QString tag){
    tag = tag.trimmed();
    if(tags.empty()){
        tags = {tag};
    }
    else{
        tags<<tag;
    }
}

QString Film::toText(){
    if(tags.empty()|| tags[0]== " "||tags[0]=="") {
        return QString(QString::number(id) + "," + name + "," + director + "," + year + ",NULL" + "\n");
    }
    QString output;
    for(QString tag : tags){
        output.append(QString(QString::number(id) + "," + name + "," + director + "," + year + ", " + tag + "\n" ));
    }
    return output;
}

QString Film::getLabel() const{
    return QString(name + " (" + year + ")");
}

QStringList Film::getKeywords() const {
    QStringList output = QStringList(name.split(" "));
    output.append(QStringList(director.split(" ")));
    output.append(tags);
    return output;
}

