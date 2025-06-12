#include "entry.h"

Entry::Entry(int id) : Record(id)  {}

Entry::Entry(int id, Film* &film, int stars, QString &text, const QDate &date) :
    Record(id),
    film(film),
    star_rating(stars),
    text_rating(text),
    date(date)
{}

Entry::~Entry(){

}

QString Entry::getLabel() const{
    return film->getLabel();
}

QString Entry::toText() {
    QString output;
    output.append(QString::number(id) +",");
    output.append(QString::number(film->getId()) + ",");
    output.append(QString::number(star_rating) + ",");
    text_rating.replace("\n", "%0A");
    output.append(text_rating + ",");
    output.append(QString::number(date.year()) + "," + QString::number(date.month()) + "," + QString::number(date.month()));
    output.append("\n");
    return output;
}

Film* Entry::getFilm() const{
    return this->film;
}

QString Entry::getStars() const{
    return QString::number(star_rating);
}

QString Entry::getReview() const{
    return this->text_rating;
}

QString Entry::getDateText() const{
    QString output(QString::number(date.day()) + "." + QString::number(date.month()) + "." + QString::number(date.year()));
    return output;
}

QDate Entry::getDate() const{
    return date;
}

QStringList Entry::getKeywords() const{
    return film->getKeywords();
}
