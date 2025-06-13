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
    /**
     * @brief film Wskaźnik do filmu o który opisuje wpis. (Sam obiekt znajduje się w globalnej bazie filmów).
     */
    Film* film;

    /**
     * @brief star_rating Ocena filmu w skali 1-10
     */
    int star_rating;

    /**
     * @brief text_rating Recenzja zapisana jako text.
     */
    QString text_rating;

    /**
     * @brief date Data w której obejrzano film
     */
    QDate date;
public:

    Entry(int id);

    Entry(int id, Film* &film, int star_rating, QString &text_rating, const QDate &date);

    ~Entry();
    /**
     * @brief getLabel
     * @return Label pola film tego obiektu
     */
    QString getLabel() const;

    Film* getFilm() const;
    /**
     * @brief toText Odziedziczona z klasy Record. Uwaga: Przy zamianie text_rating do wersji pliku zmieniono symbol nowej linii (\ n) na (%0A)
     * @return
     */
    QString toText();

    QString getStars() const;

    QString getReview() const;

    QString getDateText() const;

    QDate getDate() const;

    QStringList getKeywords() const;
};

#endif // ENTRY_H
