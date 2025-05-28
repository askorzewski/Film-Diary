//#include <iostream>
#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include "FilmData.h"
#include "addfilm.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    loadAccountData();
    reloadUi();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loadAccountData(){
    QFile* accountFile = new QFile(dir.path() + "/Data/accounts.csv");

    if(!accountFile->open(QIODevice::ReadWrite)) { //Sprawdź czy plik był wczytany
        QMessageBox::information(0, "error", accountFile->errorString());
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

\
void MainWindow::deleteAccount(QString &name){
    QList<AccountData>::Iterator account = accounts.begin();
    while(account != accounts.end()){
        if(name == account->getName()){
            accounts.erase(account);
        }
    }

    QString strId = QString::number(account->getId());
    QFile accountFile = QFile(dir.path() + "/Data/accounts.csv");
    QFile temp_file = QFile(QDir::tempPath() + "accounts.csv");

    if(!accountFile.open(QIODevice::ReadOnly)) {
        QMessageBox::information(0, "error", accountFile.errorString());
    }
    if(!temp_file.open(QIODevice::WriteOnly)) {
        QMessageBox::information(0, "error", accountFile.errorString());
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
        }
    }
    if(!accountFile.remove()){
    }
    if(!temp_file.rename(dir.path() + accountFile.fileName())){
    }

    delete account;
}

void MainWindow::reloadUi(){
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



// void MainWindow::on_przyciskWczytaj_clicked()
// {
//     //Wybieranie folderu z plikami - później automatycznie przy wyborze konta
//     QFileDialog dialog(this);
//     QStringList* selectedDirList = new QStringList;
//     dialog.setFileMode(QFileDialog::Directory);
//     if (dialog.exec())
//             *selectedDirList = dialog.selectedFiles();
//     QString selectedDir = selectedDirList->constFirst();
//     delete selectedDirList;

//     //Tworzenie listy plików na podstawie wybranego folderu
//     QString fileToRead =selectedDir.append("/films.csv");
//     refreshTable(global_data.getRecords());
// }

// //void MainWindow::refreshTable(const AccountData &data){
// //
// //}

// void MainWindow::refreshTable(const QList<Record*> &idList){
//     QListWidget* table = this->ui->tabela;
//     table->clear();

//     for(int i = 0; i<idList.length(); i++){
//         Film* loadedFilm;
//         loadedFilm = dynamic_cast<Film*>(idList[i]);
//         QString displayText = loadedFilm->getName() + " (" + loadedFilm->getYear() + ")" + " Dir. " + loadedFilm->getDirector();
//         if(loadedFilm->tags.length()!=0){
//             displayText.append("   Tags: ");
//         }
//         for(QString tag : loadedFilm->tags){
//             displayText.append(tag + ", ");
//         }
//         table->addItem(displayText);
//     }
// }


// void MainWindow::on_NewFilm_clicked()
// {
//     AddFilm form(this);
//     form.exec();
//     Film newFilm = Film();
//     newFilm = (form.getData(global_data.freeId()));
//     for(QString tag : form.getTags()){
//         newFilm.addTag(tag);
//     }
//     global_data.addRecord(&newFilm);
//     this->refreshTable(global_data.getRecords());
// }


// void MainWindow::on_pushButton_clicked()
// {
//     global_data.writeToFile("/films.csv");
// }


void MainWindow::on_buttonDelete_clicked()
{

}

