#ifndef FILMDATA_H
#define FILMDATA_H
#include "database.h"
#include "film.h"

/**
 * @brief Klasa FilmData zawiera wszystkie filmy
 */
class FilmData : public Database
{
    QList<Film> filmList;


public:
    FilmData(); //Global filmdata
    FilmData(Database* account); //Account-specific filmdata

    QList<Film> getFilms() const;

    void readFilmFile(const QString &fileName);

    void saveToFiles();

    void addFilm(Film &film);
};
#endif // FILMDATA_H
