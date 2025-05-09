#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
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

    //Tworzenie listy plikóW na podstawie wybranego folderu
    QStringList filesToRead = {selectedDir.append("/films.csv"), selectedDir.append("/tag_list.csv"), selectedDir.append("/tag_link.csv")};
    films = readFiles(filesToRead);
    loadToTable(films);
}


QList<Film> MainWindow::readFiles(const QStringList & fileNames){
    QFile* filmFile = new QFile(fileNames.at(0));
    QList<Film> filmList;

    if(!filmFile->open(QIODevice::ReadOnly)) { //Sprawdź czy plik był wczytany
        QMessageBox::information(0, "error", filmFile->errorString());
    }

    QTextStream filmData(filmFile); //Wczytaj z pliku do wektora obiektów
    bool firstLine = 1;
    while(!filmData.atEnd()){
        if(firstLine){
            firstLine = 0;
            continue;
        }
        QString line = filmData.readLine();
        QStringList fields = line.split(",");
        Film newFilm(fields.at(0).toInt(), fields.at(1), fields.at(2), fields.at(3));
        filmList.append(newFilm);
    }
    QTextStream(stdout) << fileNames.at(0) << " loaded." << Qt::endl;
    delete filmFile;

    QFile tagList(fileNames.at(1));
    QFile tagLink(fileNames.at(2));
    if(!tagList.open(QIODevice::ReadOnly) || !tagLink.open(QIODevice::ReadOnly)) { //Sprawdź czy plik był wczytany
        QMessageBox::information(0, "error", tagList.errorString());
    }


    return filmList;
}

void MainWindow::loadToTable(const QList<Film> &list){
    QListWidget* table = this->ui->tabela;

    bool firstLine = 1;
    for(const Film &loadedFilm : list){
        if(firstLine){
            firstLine = 0;
            continue;
        }
        QString displayText = loadedFilm.getName() + " (" + loadedFilm.getYear() + ")" + " Dir. " + loadedFilm.getDirector();
        table->addItem(displayText);
    }
}
