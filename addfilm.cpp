#include "addfilm.h"
#include "ui_addfilm.h"
#include "mainwindow.h"

AddFilm::AddFilm(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AddFilm)
{
    ui->setupUi(this);
}

AddFilm::~AddFilm()
{
    delete ui;
}

void AddFilm::on_buttonBox_accepted()
{
    this->name = this->ui->inName->text();
    this->director = this->ui->inDir->text();
    this->year = this->ui->inYear->text();

    QString tagString = this->ui->inTags->text();
    tags = tagString.split(",");
}

Film AddFilm::getData(int id) const{
    return Film(id, name, director, year);
}

QStringList AddFilm::getTags() const {
    return tags;
}
