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

    Entry(int id, Film* &film, int star_rating, QString &text_rating, const QDate &date);

    ~Entry();

    QString getLabel() const;

    Film* getFilm() const;

    QString toText();

    QString getStars() const;

    QString getReview() const;

    QString getDateText() const;

    QDate getDate() const;

    QStringList getKeywords() const;
};

#endif // ENTRY_H
