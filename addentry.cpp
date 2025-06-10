#include "addentry.h"
#include "ui_addentry.h"

AddEntry::AddEntry(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AddEntry)
{
    ui->setupUi(this);
    ui->inDate->setDate(QDate::currentDate());
    ui->inDate->setMaximumDate(QDate::currentDate());
    connect(this->ui->fromWatchlist, SIGNAL(clicked()), parent, SLOT(chooseFromWatchlist()));
}

AddEntry::AddEntry(Film *film, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AddEntry)
{
    this->film = film;
    ui->setupUi(this);
    ui->inDate->setDate(QDate::currentDate());
    ui->inDate->setMaximumDate(QDate::currentDate());
    ui->fromWatchlist->setEnabled(false);
    ui->inName->setText(film->getName());
    ui->inName->setEnabled(false);
    ui->inDir->setText(film->getDirector());
    ui->inDir->setEnabled(false);
    ui->inYear->setText(film->getYear());
    ui->inYear->setEnabled(false);
    QString tags;
    for(QString tag : film->tags){
        tags.append(tag + ",");
    }
    ui->inTags->setText(tags);
    ui->inTags->setEnabled(false);
}

AddEntry::~AddEntry()
{
    delete ui;
}


void AddEntry::on_buttonBox_accepted()
{
    canceled = 0;
    name = ui->inName->text();
    director = ui->inDir->text();
    year = ui->inYear->text();
    QString tagString = ui->inTags->text();
    tags = tagString.split(",");

    stars = ui->inStars->value();
    review = ui->inReview->toPlainText();
    date = ui->inDate->date();
}


Entry AddEntry::getData(int filmId, int entryId){
    if(canceled){
        return Entry(0);
    }
    if(film == nullptr){
        this->film = new Film(filmId, name, director, year);
    }
    Entry output = Entry(entryId, film, stars, review, date);
    return output;
}

void AddEntry::on_buttonBox_rejected()
{
    canceled = 1;
}


void AddEntry::on_fromWatchlist_clicked()
{
    this->close();
}


