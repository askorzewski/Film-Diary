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
    QList<int> usedId;

    /**
     * @brief records - rekordy danej bazy
     */
    QList<Record*> records;
    //Potencjalnie zmień na std::vector - poczytaj czego lepiej korzystać

    /**
     * @brief directory - folder w którym przechowywane są pliki danej bazy
     */
    QDir directory;

    QStringList fileList;

public:
    Database(int id = 0);
    Database(int id, QString path);
    ~Database();


    QList<Record*> getRecords() const;

    QString getDir() const;

    void writeToFile(QString filename);

    /**
     * @brief addRecord - dodaje nowy record do bazy
     * @param record - dodawany rekord
     */
    void addRecord(Record *record);

    /**
     * @brief freeId zwraca następny wolny numer id w bazie
     * @return wolny numer wewnątrz bazy
     */
    int freeId();

    void setName(QString &name);

    int getId() const;

private:
    void moveFiles(const QDir &source, const QDir &target);
};

#endif // DATABASE_H
