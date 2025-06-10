#include "accountdata.h"
#include <QMessageBox>

AccountData::AccountData(FilmData* global, int id) : Database(id), globalFilmData(global) {
    QFile file1 = QFile(directory.path() + "/watchlist.csv");
    QFile file2 = QFile(directory.path() + "/entries.csv");
    file1.open(QIODevice::NewOnly);
    file1.close();
    file2.open(QIODevice::NewOnly);
    file2.close();
    readFile("entries.csv");
}

QString AccountData::getName() const{
    return name;
}

QList<Record*> AccountData::getRecords() const{
    return this->records;
}

void AccountData::saveToFiles(){
    writeToFile("entries.csv");
    watchlist.saveToFiles();
}

void AccountData::readFile(const QString &fileName){
    QFile* entryFile = new QFile(directory.path() + "/" + fileName);

    if(!entryFile->open(QIODevice::ReadOnly)) {
        QMessageBox::information(0, "error", entryFile->errorString());
    }
    QTextStream data(entryFile);

    while(!data.atEnd()){
        QString line = data.readLine();
        Entry* newEntry;
        QStringList fields = line.split(",");
        int entryId = fields.at(0).toInt();
        Film* film = static_cast<Film*>(globalFilmData->findRecord(fields.at(1).toInt()));
        int stars = fields.at(2).toInt();
        QString review = fields.at(3);
        QDate date = QDate(fields.at(4).toInt(), fields.at(5).toInt(), fields.at(6).toInt());
        if(!usedId.contains(entryId)){
            newEntry = new Entry(entryId, film, stars, review, date);
            usedId.append(entryId);
        }
        entryList.append(*newEntry);
        records.append(newEntry);
    }
    entryFile->close();
}

void AccountData::addEntry(Entry &entry){
    entryList.append(entry);
    records.append(&entry);
    usedId.append(entry.getId());
}
