#ifndef ENTRY_H
#define ENTRY_H
#include "film.h"
#include "record.h"
#include <QDate>

/**
 * @brief Klasa Entry - wpis na temat danego filmu
 */
class Entry : public Record
{
    Film* film;

    int star_rating;

    QString text_rating;

    QDate date;
public:
    Entry(int id);

    Entry(int id, Film* &film, int star_rating, const QString &text_rating, const QDate &date);

    QString getLabel();

    QString toText();
};

#endif // ENTRY_H
