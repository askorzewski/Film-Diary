#ifndef FILMDATA_H
#define FILMDATA_H
#include "database.h"
#include "film.h"

/**
 * @brief Klasa FilmData zawiera wszystkie filmy
 */
class FilmData : public Database
{
private:

    QList<Film> filmList;

    friend class film;

    void readFilmFile(const QString &fileName);
public:
    FilmData(); //Global filmdata
    FilmData(Database* account); //Account-specific filmdata

    QList<Film> getFilms() const;

    void saveToFiles();

    void addFilm(Film &film);
};

#endif // FILMDATA_H
