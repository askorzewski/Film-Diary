#ifndef DATABASE_H
#define DATABASE_H
#include "film.h"
#include "entry.h"
#include <QStringList>
#include <QDir>
/**
 * @brief Klasa Database służy do obsługi różnego rodzaju danych
 */
class Database
{
    QList<Record> films;
    QDir directory;

public:
    Database(int id = 0);
    Database(int id, QString path);

    QList<Film> getFilms() const;

    void readFilmFile(const QString &fileName);
    void readEntryFile(const QString &fileName);

    void WritetoFile();
    void addFilm(const Film &film);
    int assignId();
protected:
    QString name;
    QList<int> usedId;
};

#endif // DATABASE_H
