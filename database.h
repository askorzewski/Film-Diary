#ifndef DATABASE_H
#define DATABASE_H
#include "record.h"
#include <QStringList>
#include <QDir>
#include <QFile>

/**
 * @brief Klasa Database służy do przechowywania i obsługi wskaźników obiekty klasy Record.
 */
class Database
{

protected:
    /**
     * @brief id Służy do rozróżniania baz danych w folderach. Folder globalnej bazy danych ma id = 0.
     */
    int id;

    /**
     * @brief name
     */
    QString name;

    /**
     * @brief usedId - lista użytych już numerów dla danych rekordów w bazie
     */
    QVector<int> usedId = {0};

    /**
     * @brief records - rekordy danej bazy
     */
    QList<Record*> records;


    /**
     * @brief directory - folder w którym przechowywane są pliki danej bazy
     */
    QDir directory;

    /**
     * @brief fileList - lista plików wewnątrz folderu bazy danych
     */
    QStringList fileList;

public:
    /**
     * @brief Database Konstruktor tworzy folder Data/Data*id* w plikach programu i zapisuje swoją ścieżke
     */
    Database(int id = 0);
    /**
     * @brief Database - konstruktor który importuje bazę z zewnątrz programu (ostatecznie niewykorzystany)
     * @param id - id bazy danych
     * @param path - ścieżka do zawnętrznej bazy
     */
    Database(int id, const QString path);
    virtual ~Database();
    /**
     * @brief readFile Wczytuje z pliku dane i przechowuje w odpowiednich listach.
     * @param fileName
     */
    virtual void readFile(const QString &fileName) = 0;

    /**
     * @brief getRecords
     * @return Lista wskaźników na rekordy bazqy
     */
    QList<Record*> getRecords() const;

    /**
     * @brief getDir
     * @return Ścieżka folderu bazy danych
     */
    QString getDir() const;


    /**
     * @brief addRecord - dodaje nowy record do bazy
     * @param record - dodawany rekord
     */
    void addRecord(Record* &record);

    /**
     * @brief freeId zwraca następny wolny numer id dla rekordu w bazie
     * @return wolny numer wewnątrz bazy
     */
    int freeId();

    /**
     * @brief setName Zmienia imię na podane
     * @param name Nowe imię
     */
    void setName(QString &name);

    /**
     * @brief getId
     * @return id bazy danych
     */
    int getId() const;

    /**
     * @brief findRecord Znajduje odpowiedni record po id. Jeśli takowego nie znajdzie zwraca nullptr.
     * @param id Id rekordu
     * @return Wskaźnik znaleźionego rekordu
     */
    Record* findRecord(int id);

    /**
     * @brief deleteRecord Usuwanie rekordu z bazy po id.
     * @param id Id usuwanego rekordu
     */
    void deleteRecord(int id);

    /**
     * @brief deleteRecord Znajduje rekord przekazany jako argument metody i go usuwa z bazy
     * @param record Wskaźnik na usuwany rekord
     */
    void deleteRecord(Record *record);

    virtual void saveToFiles() = 0;

    /**
     * @brief clear Usuwa wszystkie pliki z wewnątz folderu bazy.
     * @return 1 - wystąpił błąd, 0 - usuwanie powiodło się
     */
    bool clear();

    /**
     * @brief swapRecord Zamiana rekordu o danym numerze id na nowy z tym samym numerem.
     * @param record Nowy rekord
     */
    void swapRecord(Record* record);
protected:
    /**
     * @brief writeToFile - zapisuje do pliku rekordy danej bazy
     * @param filename nazwa pliku wewnątrz floderu bazy
     */
    void writeToFile(const QString &filename);

    /**
     * @brief writeToFile
     * @param filename
     * @param recordList
     */
    void writeToFile(QString filename, const QList<Record*> &recordList);
private:
    static void moveFiles(const QDir &source, const QDir &target);
};

#endif // DATABASE_H
