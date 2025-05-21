#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include "FilmData.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    refreshTable(global_data);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_przyciskWczytaj_clicked()
{
    //Wybieranie folderu z plikami - później automatycznie przy wyborze konta
    QFileDialog dialog(this);
    QStringList* selectedDirList = new QStringList;
    dialog.setFileMode(QFileDialog::Directory);
    if (dialog.exec())
            *selectedDirList = dialog.selectedFiles();
    QString selectedDir = selectedDirList->constFirst();
    delete selectedDirList;

    //Tworzenie listy plików na podstawie wybranego folderu
    QString fileToRead =selectedDir.append("/films.csv");
    refreshTable(global_data);
}

void MainWindow::refreshTable(const FilmData &data){
    QList<Film*> list = data.getFilms();
    QListWidget* table = this->ui->tabela;
    table->clear();

    for(const Film* loadedFilm : list){ //Ogarnij później wskaćniki żeby zmienić Record na Film
        QString displayText = loadedFilm->getName() + " (" + loadedFilm->getYear() + ")" + " Dir. " + loadedFilm->getDirector();
        if(loadedFilm->tags.length()!=0){
            displayText.append("   Tags: ");
        }
        for(QString tag : loadedFilm->tags){
            displayText.append(tag + ", ");
        }
        table->addItem(displayText);
    }
}

void MainWindow::on_NewFilm_clicked()
{
    AddFilm form(this);
    form.exec();
    Film newFilm = Film();
    newFilm = (form.getData(global_data.assignId()));
    global_data.addRecord(&newFilm);
    this->refreshTable(global_data);
}

