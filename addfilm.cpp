#include "addfilm.h"
#include "ui_addfilm.h"
#include "mainwindow.h"

AddFilm::AddFilm(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AddFilm)
{
    ui->setupUi(this);
}

AddFilm::AddFilm(Film* film, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AddFilm)
{
    ui->setupUi(this);
    ui->inName->setText(film->getName());
    ui->inDir->setText(film->getDirector());
    ui->inYear->setText(film->getYear());
    QString tags;
    for(QString tag : film->tags){
        tags.append(tag + ",");
    }
    ui->inTags->setText(tags);
}

AddFilm::~AddFilm()
{
    delete ui;
}

void AddFilm::on_buttonBox_accepted()
{
    canceled = 0;
    this->name = this->ui->inName->text();
    this->director = this->ui->inDir->text();
    this->year = this->ui->inYear->text();

    QString tagString = this->ui->inTags->text();
    tags = tagString.split(",");
}



Film AddFilm::getData(int id) const{
    if(canceled){
        return Film(0);
    }
    return Film(id, name, director, year);
}

QStringList AddFilm::getTags() const {
    return tags;
}

void AddFilm::on_buttonBox_rejected()
{
    canceled = 1;
}

