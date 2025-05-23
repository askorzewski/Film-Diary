#ifndef FILMDATA_H
#define FILMDATA_H
#include "database.h"
#include "film.h"
/**
 * @brief Klasa FilmData zawiera wszystkie filmy
 */
class FilmData : public Database
{
    QList<Film*> filmList;
public:
    FilmData();

    QList<Film*> getFilms() const;

    void readFilmFile(const QString &fileName);    
};

#endif // FILMDATA_H
