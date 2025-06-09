#ifndef DATABASE_H
#define DATABASE_H
#include "record.h"
#include <QStringList>
#include <QDir>
#include <QFile>

/**
 * @brief Klasa Database służy do obsługi różnego rodzaju danych
 */
class Database
{

protected:
    int id;

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
    Database(int id = 0);
    /**
     * @brief Database - konstruktor który importuje bazę z zewnątrz programu
     * @param id - id bazy danych
     * @param path - ścieżka do zawnętrznej bazy
     */
    Database(int id, const QString path);
    ~Database();

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
     * @brief freeId zwraca następny wolny numer id w bazie
     * @return wolny numer wewnątrz bazy
     */
    int freeId();

    void setName(QString &name);

    int getId() const;

    Record* findRecord(int id);

    void deleteRecord(int id);

    void deleteRecord(Record *record);

    virtual void saveToFiles() = 0;

    bool clear();

    void swapRecord(Record* record);
protected:
    /**
     * @brief writeToFile - zapisuje do pliku rekordy
     * @param filename nazwa pliku wewnątrz floderu bazy
     */
    void writeToFile(const QString &filename);

    void writeToFile(QString filename, const QList<Record*> &recordList);
private:
    static void moveFiles(const QDir &source, const QDir &target);
};

#endif // DATABASE_H
