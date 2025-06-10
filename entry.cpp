#include "entry.h"

Entry::Entry(int id) : Record(id)  {}

Entry::Entry(int id, Film* &film, int stars, const QString &text, const QDate &date) :
    Record(id),
    film(film),
    star_rating(stars),
    text_rating(text),
    date(date)
{}

Entry::~Entry(){

}

QString Entry::getLabel(){
    return film->getLabel();
}

QString Entry::toText(){
    QString output;
    output.append(QString::number(id) +",");
    output.append(QString::number(film->getId()) + ",");
    output.append(QString::number(star_rating) + ",");
    output.append(text_rating + ",");
    output.append(QString::number(date.year()) + "," + QString::number(date.month()) + "," + QString::number(date.month()));
    return output;
}

Film* Entry::getFilm() const{
    return this->film;
}
