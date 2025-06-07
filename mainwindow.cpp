//#include <iostream>
#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QTextBrowser>
#include <QRegularExpression>
#include "filmdata.h"
#include "addfilm.h"


//1366x718

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    loadAccountData();
    reloadStartUi();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loadAccountData(){
    QFile* accountFile = new QFile(dir.path() + "/Data/accounts.csv");

    if(!accountFile->open(QIODevice::ReadOnly)) { //Sprawdź czy plik był wczytany
        QMessageBox::information(0, "error", accountFile->fileName() + ": " + accountFile->errorString());
    }

    QTextStream data(accountFile); //Wczytaj z pliku do wektora obiektów
    while(!data.atEnd()){
        QString line = data.readLine();
        QStringList fields = line.split(",");
        AccountData newAccount = AccountData(fields[0].toInt());
        newAccount.setName(fields[1]);
        accounts.append(newAccount);
    }
    delete accountFile;
}


void MainWindow::deleteAccount(QString &name){
    QList<AccountData>::Iterator account = accounts.begin();
    while(account != accounts.end()){
        if(name == account->getName()){
            account->clear();
            accounts.erase(account);
            break;
        }
        account++;
    }

    QString strId = QString::number(account->getId());
    QFile accountFile = QFile(dir.path() + "/Data/accounts.csv");
    QFile temp_file = QFile(dir.path() + "/Data/temp_accounts.csv");

    if(!accountFile.open(QIODevice::ReadOnly)) {
        QMessageBox::information(0, "error", accountFile.fileName() + ": " + accountFile.errorString());
    }
    if(!temp_file.open(QIODevice::WriteOnly)) {
        QMessageBox::information(0, "error", temp_file.fileName() + ": " + temp_file.errorString());
    }

    QTextStream data(&accountFile);
    QTextStream out(&temp_file);
    while(!data.atEnd()){
        QString line = data.readLine();
        QStringList fields = line.split(",");
        if(fields[0]==strId){
        }
        else{
            out<<line;
            out<<Qt::endl;
        }
    }
    if(!accountFile.remove()){
       QMessageBox::information(0, "error", accountFile.fileName() + ": " + accountFile.errorString());
    }
    if(!temp_file.rename("Data/accounts.csv")){
        QMessageBox::information(0, "error", temp_file.fileName() + ": " + temp_file.errorString());
    }

}




/*
 * Start Screen
*/

void MainWindow::reloadStartUi(){
    QList<QPushButton*> existingButtons = ui->verticalLayoutWidget->findChildren<QPushButton*>(NULL);
    for(QPushButton* button : existingButtons){
        button->disconnect();
        button->setVisible(false);
        button->deleteLater();
        button->close();
    }
    for(AccountData account : accounts){
        QPushButton* button = new QPushButton(account.getName());
        ui->verticalLayout->addWidget(button, 40);
        button->setObjectName(account.getName());
        button->setCheckable(true);
        button->setFixedSize(QSize(500, 65));
        button->setFont(QFont("Bahnschrift", 30, QFont::Bold));
        button->show();
        QObject::connect (button,SIGNAL(clicked(bool)),this,SLOT(chooseAccount()));
    }
}


void MainWindow::chooseAccount(){
    if(accountSelected!=" "){
        QPushButton* toggledbutton = findChild<QPushButton*>(accountSelected);
        toggledbutton->toggle();
    }
    QObject* sender = QObject::sender();
    accountSelected = sender->objectName();
    //std::cout<<accountSelected.toStdString()<<std::endl;
}



void MainWindow::on_buttonDelete_clicked()
{
    if(accountSelected == " "){
        return;
    }
    deleteAccount(accountSelected);
    accountSelected = " ";
    reloadStartUi();
}



void MainWindow::on_buttonNew_clicked()
{
    ui->addNazwa->setFixedSize(300,100);
}



void MainWindow::on_buttonBox_accepted()
{
    int freeId;
    if(accounts.empty()){
        freeId = 1;
    }
    else {
        freeId = accounts.last().getId()+1;
    }
    QLineEdit* name_container = ui->addNazwa->findChild<QLineEdit*>(NULL);
    QString name = name_container->text();

    AccountData newAccount(freeId);
    newAccount.setName(name);
    accounts.append(newAccount);
    ui->addNazwa->setFixedSize(0,0);

    QFile accountFile = QFile("Data/accounts.csv");
    if(!accountFile.open(QIODevice::Append)){
        QMessageBox::information(0, "error", accountFile.fileName() + ": " + accountFile.errorString());
    }
    QTextStream accountStream(&accountFile);

    accountStream<<QString::number(freeId)<<","<<name<<Qt::endl;
    accountFile.close();
    reloadStartUi();
}


void MainWindow::on_buttonBox_rejected()
{
    ui->addNazwa->setFixedSize(0,0);
}


void MainWindow::on_buttonLoad_clicked()
{
    if(accountSelected == " "){
        return;
    }
    for(AccountData &account : accounts){
        if(accountSelected == account.getName()){
            data = &account;
        }
    }
    ui->startScreen->setFixedSize(0,0);
    ui->mainScreen->setFixedSize(1366,718);
    this->loadToTable(data->getRecords(1));
}


void MainWindow::on_actionWyloguj_triggered()
{
    ui->startScreen->setFixedSize(1366,718);
    ui->mainScreen->setFixedSize(0,0);
}



/*
 * Main Screen
*/

void MainWindow::loadToTable(QList<Record*> records){
    QList<QPushButton*> existingButtons = ui->mainScreen->currentWidget()->findChildren<QPushButton*>(QRegularExpression("^[0-9]+$"));
    for(QPushButton* button : existingButtons){
        button->disconnect();
        button->setVisible(false);
        button->deleteLater();
        button->close();
    }
    //Switch/case for tab later
    int row = 0;
    QString tabName = "WatchRow";
    for(Record* recordData : records){
        row = row % 3;
        QString tableName = QString(tabName + QString::number(row));
        row++;
        QVBoxLayout* table = ui->mainScreen->currentWidget()->findChild<QVBoxLayout*>(tableName);
        if(recordData == nullptr){
            continue;
        }
        QPushButton* recordInTable = new QPushButton();
        table->insertWidget(0, recordInTable);
        recordInTable->setObjectName(QString::number(recordData->getId()));
        recordInTable->setCheckable(true);
        recordInTable->setFlat(true);
        recordInTable->setText(recordData->getLabel());
        recordInTable->resize(recordInTable->sizeHint().width(), (recordInTable->sizeHint().height())+100);
        QObject::connect (recordInTable,SIGNAL(clicked(bool)),this,SLOT(selectRecord()));
    }
}

void MainWindow::selectRecord(){
    if(recordSelected != nullptr){
        QPushButton* toggledbutton = findChild<QPushButton*>(QString::number(recordSelected->getId()));
        toggledbutton->toggle();
    }
    QObject* sender = QObject::sender();
    recordSelected = data->watchlist.findRecord(sender->objectName().toInt());
}


void MainWindow::on_main_edit_clicked(){
    if(recordSelected==nullptr){
        return;
    }
    int tabIndex = this->ui->mainScreen->currentIndex();
    switch(tabIndex){
    case 1:
        int recordId = this->recordSelected->getId();

        filmData.deleteRecord(recordId);
        data->watchlist.deleteRecord(recordId);
        AddFilm form(this, static_cast<Film*>(recordSelected));
        form.exec();

        Film newFilm = form.getData(recordId);
        filmData.swapRecord(&newFilm);
    }
}

void MainWindow::on_actionZapisz_triggered()
{
    data->saveToFiles();
    filmData.saveToFiles();
}


void MainWindow::on_main_new_clicked()
{
    int tabIndex = this->ui->mainScreen->currentIndex();
    switch(tabIndex){
    case 0:
        break;
    case 1:
        AddFilm form(this);
        form.exec();
        Film* newFilm = new Film(form.getData(filmData.freeId()));
        for(QString tag : form.getTags()){
            newFilm->addTag(tag);
        }
        Record* filmRecord = newFilm;
        filmData.addRecord(filmRecord);
        filmData.addFilm(*newFilm);
        data->addToWatchlist(newFilm);
        this->loadToTable(data->watchlist.getRecords());
        break;
    }


}

