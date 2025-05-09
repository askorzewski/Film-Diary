#ifndef FILM_H
#define FILM_H
#include <QString>

class Film
{
    int id;
    QString name;
    QString director;
    QString year;
    QString* tags;

public:
    Film(int id, QString name, QString director, QString year);

    //get methods
    int getId() const;
    QString getName() const;
    QString getDirector() const;
    QString getYear() const;

private:

};
#endif // FILM_H
