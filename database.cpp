#include "database.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QDir>

/**
 * @brief Database::Database - konstruktor, automatycznie szuka lub tworzy folder o nazwie "Data*id*".
 * @param id
 */
Database::Database(int id) {
    QDir dir;
    directory.current();
    if(dir.exists("Data"+QString::number(id))){
        dir.cd("Data"+QString::number(id));
        this->directory = dir;
        return;
    }
    if(!dir.mkdir("Data"+QString::number(id))){
        QMessageBox::information(0, "error", "Directory could not be created.");
    }
    dir.cd("Data"+QString::number(id));
    this->directory=dir;
}

/**
 * @brief Database::Database Konstruktor służący do importu istniejącego folderu do folderu wewnętrznego i zrobienie z niego bazy
 * @param id - numer bazy
 * @param path - ścieżka folderu importowanego
 */
Database::Database(int id, QString path){
    QDir target_dir;
    QDir source_dir(path);

    target_dir.current();
    if(target_dir.exists("Data"+QString::number(id))){
        target_dir.cd("Data"+QString::number(id));
        moveFiles(source_dir, target_dir);
        this->directory = target_dir;
        return;
    }
    if(!target_dir.mkdir("Data"+QString::number(id))){
        QMessageBox::information(0, "error", "Directory could not be created.");
    }
    target_dir.cd("Data"+QString::number(id));
    moveFiles(source_dir, target_dir);
    this->directory=target_dir;
}


void Database::addRecord(Record* record){
    this->records.append(record);
}

int Database::assignId(){
    int newId = *(usedId.end()-1)+1;
    usedId.append(newId);
    return newId;
}

QList<Record*> Database::getRecords() const{
    return this->records;
}

void Database::writeToFile(QString filename){
    QFile file(directory.path() + filename);
    if(!file.open(QIODevice::WriteOnly)) {
        QMessageBox::information(0, "error", file.errorString());
    }
    QTextStream stream(&file);

    for(Record* record : records){
        stream<<record->toText();
    }
    file.close();
}

void Database::moveFiles(const QDir &source, const QDir &target){
    QStringList source_files = source.entryList();
    for(QString filename : source_files){
        QFile file = QFile(source.path() + filename);
        file.copy(target.path() + filename);
    }
}
