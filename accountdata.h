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
    /**
     * @brief globalFilmData - wskaźnik na globalną baze filmów (pole klasy MainWindow), używana przez wpisy do znaleźienia filmów po ID.
     */
    FilmData* globalFilmData;

    /**
     * @brief entryList Lista w której przechowywane są obiekty klasy Entry dla danego konta
     */
    QList<Entry> entryList;

    /**
     * @brief watchlist Baza klasy FilmData przechowująca filmy do listy "Do obejrzenia" dla danego konta
     */
    FilmData watchlist = FilmData(this);

    /**
     * @brief readFile Czyta plik w formacie do przechowywania wpisów
     * @param filename Nazwa pliku
     */
    void readFile(const QString &filename);
public:
    /**
     * @brief AccountData Konstruktor automatycznie czyta lub tworzy pliki w których przechowywane są dane
     * @param global Wskaźnik do globalnej bazy filmów
     * @param id Id bazy danych
     */
    AccountData(FilmData* global, int id);

    /**
     * @brief getName
     * @return Nazwa bazy danych (konta)
     */
    QString getName() const;

    /**
     * @brief addEntry Dodaje do wpis do entryList i wskaźnik do Database::records.
     * @param entry
     */
    void addEntry(Entry &entry);

    /**
     * @brief saveToFiles Zapisuje wpisy do "entries.csv" watchlist do "watchlist.csv"
     */
    void saveToFiles();
};

#endif // ACCOUNTDATA_H
