#ifndef FILM_H
#define FILM_H
#include <QString>
#include <QStringList>
#include "record.h"
/**
 * @brief Klasa Film opisuje dany film
 */
class Film : public Record
{
    QString name;
    QString director;
    QString year;


public:
    QStringList tags;
    Film();
    Film(int id, QString name, QString director, QString year);

    //get methods
    int getId() const;
    QString getName() const;
    QString getDirector() const;
    QString getYear() const;

    void addTag(const QString& tag);

    /**
     * @brief toText
     * @return Dane obiektu w formie tekstowej do zapisu w pliku
     */
    QString toText();
private:

};
#endif // FILM_H
