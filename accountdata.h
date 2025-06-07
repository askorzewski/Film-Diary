#ifndef ACCOUNTDATA_H
#define ACCOUNTDATA_H
#include "filmdata.h"
#include "film.h"
/**
 * @brief Klasa AccountData dziediczy z Database, służy do obsługi danych dla poszczególnego konta
 */
class AccountData : public Database
{
    QList<Record*> entries;

public:
    FilmData watchlist = FilmData(this);

    AccountData(int id);

    QString getName() const;

    void addToWatchlist(Film* &film);

    QList<Record*> getRecords(int recordType = 0) const;

    void saveToFiles();
};

#endif // ACCOUNTDATA_H
