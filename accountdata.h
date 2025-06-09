#ifndef ACCOUNTDATA_H
#define ACCOUNTDATA_H
#include "filmdata.h"
#include "entry.h"

/**
 * @brief Klasa AccountData dziediczy z Database, służy do obsługi danych dla poszczególnego konta
 */
class AccountData : public Database
{
    QList<Record*> entries;

    FilmData* globalFilmData;

    QList<Entry> entryList;

public:
    FilmData watchlist = FilmData(this);

    AccountData(FilmData* global, int id);

    QString getName() const;

    void addToWatchlist(Film* &film);

    void readFile(const QString &fileName);

    QList<Record*> getRecords(int recordType = 0) const;

    void saveToFiles();
};

#endif // ACCOUNTDATA_H
