#include "accountdata.h"

AccountData::AccountData(int id) : Database(id) {
    QFile(directory.path() + "/watchlist.csv").open(QIODevice::NewOnly);
    QFile(directory.path() + "/entries.csv").open(QIODevice::NewOnly);
}

QString AccountData::getName() const{
    return name;
}

void AccountData::addToWatchlist(Film* &film){
    Record* record = film;
    watchlist.addFilm(*film);
    watchlist.addRecord(record);

}

QList<Record*> AccountData::getRecords(int recordType) const{
    if(recordType == 1){
        return watchlist.getRecords();
    }
    return records;
}

void AccountData::saveToFiles(){
    writeToFile("entries.csv");
    watchlist.saveToFiles();
}
