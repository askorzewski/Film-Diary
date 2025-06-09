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
    this->id = id;
    QDir dir;
    directory.current();
    if(dir.exists("Data/Data"+QString::number(id))){
        dir.cd("Data/Data"+QString::number(id));
        this->directory = dir;
        return;
    }
    if(!dir.mkdir("Data/Data"+QString::number(id))){
        QMessageBox::information(0, "error", "Folder" + dir.absolutePath() + "nie mógł zostać stworzony.");
    }
    dir.cd("Data/Data"+QString::number(id));
    this->directory=dir;

    this->fileList = directory.entryList();
}

/**
 * @brief Database::Database Konstruktor służący do importu istniejącego folderu do folderu wewnętrznego i zrobienie z niego bazy
 * @param id - numer bazy
 * @param path - ścieżka folderu importowanego
 */
Database::Database(int id, QString path){
    this->id = id;
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
        QMessageBox::information(0, "error", "Folder" + target_dir.absolutePath() + "nie mógł zostać stworzony.");
    }
    target_dir.cd("Data"+QString::number(id));
    moveFiles(source_dir, target_dir);
    this->directory=target_dir;

    this->fileList = directory.entryList();
}

Database::~Database(){

}



void Database::addRecord(Record* &record){
    if(!usedId.contains(record->getId())){
        usedId.append(record->getId());
    }
    records.emplaceBack(record);
}

int Database::freeId(){
    int newId = usedId.last()+1;
    usedId.append(newId);
    return newId;
}

//Dla typów listy recordów możesz potem uzyc enuma
QList<Record*> Database::getRecords() const{
    return this->records;
}

void Database::writeToFile(QString filename, const QList<Record*> &recordList){
    QFile file(directory.path() + "/" +filename);
    if(!file.open(QIODevice::WriteOnly)) {
        QMessageBox::information(0, "error", filename + " - zapis" + file.errorString());
    }
    QTextStream stream(&file);

    for(int id : usedId){
        if(id == 0){
            continue;
        }
        Record* record = findRecord(id);
        if(record!=nullptr){
            QString recordText = record->toText();
            stream<<recordText;
        }
    }
    file.close();
}

void Database::writeToFile(const QString &filename){
    writeToFile(filename, records);
}


void Database::moveFiles(const QDir &source, const QDir &target){
    QStringList source_files = source.entryList();
    for(QString filename : source_files){
        QFile file = QFile(source.path() + filename);
        file.copy(target.path() + filename);
    }
}

QString Database::getDir() const{
    return directory.absolutePath();
}

void Database::setName(QString &name){
    this->name = name;
}

int Database::getId() const{
    return this->id;
}

Record* Database::findRecord(int id){
    QListIterator<Record*> it(records);
    while(it.hasNext()){
        Record* rec = it.next();
        if(id == rec->getId())
            return rec;
    }
    return nullptr;
}

void Database::deleteRecord(int id){
    Record* rec = findRecord(id);
    records.removeOne(rec);
}
//void Database::saveToFiles(){}

bool Database::clear(){
    QStringList files = directory.entryList();
    for(QString file : files){
        if(!directory.remove(file)){
            QMessageBox::information(0, "error", "Nie udało się usunąć pliku z folderu.");
            return 1;
        };
    }
    if(!QDir::current().rmdir(directory.path())){
        QMessageBox::information(0, "error", "Nie udało się usunąć folderu.");
        return 1;
    }
    return 0;
}

void Database::swapRecord(Record *record){
    Record *originalRecord = findRecord(record->getId());
    *originalRecord = *record;
}

