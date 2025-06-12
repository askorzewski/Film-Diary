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
    Film(int id);
    Film(int id, QString name, QString director, QString year);
    ~Film();

    //get methods
    QString getName() const;
    QString getDirector() const;
    QString getYear() const;

    void addTag(const QString &tag);

    QStringList tags;
    /**
     * @brief toText
     * @return Dane obiektu w formie tekstowej do zapisu w pliku
     */
    QString toText() const;

    QString getLabel() const;

private:

};
#endif // FILM_H
