#ifndef ACCOUNTDATA_H
#define ACCOUNTDATA_H
#include "filmdata.h"
#include "entry.h"

/**
 * @brief Klasa AccountData dziediczy z Database, służy do obsługi danych dla poszczególnego konta
 */
class AccountData : public Database
{
    friend class MainWindow;

    FilmData* globalFilmData;

    QList<Entry> entryList;
	
    FilmData watchlist = FilmData(this);

    void readFile(const QString &filename);
public:
    AccountData(FilmData* global, int id);

    QString getName() const;

    void addToWatchlist(Film &film);

    void addEntry(Entry &entry);

    QList<Record*> getRecords() const;

    void saveToFiles();
};

#endif // ACCOUNTDATA_H
