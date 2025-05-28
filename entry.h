#ifndef ENTRY_H
#define ENTRY_H
#include "film.h"

/**
 * @brief Klasa Entry - wpis na temat danego filmu
 */
class Entry : public Record
{
    Film* film;

    int star_rating;

    QString text_rating;

public:
    Entry();
};

#endif // ENTRY_H
