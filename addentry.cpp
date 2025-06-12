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
        tag = tag.trimmed();
        tags.append(tag + ",");
    }
    ui->inTags->setText(tags);
    ui->inTags->setEnabled(false);
}

AddEntry::AddEntry(Entry *entry, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AddEntry)
{
    ui->setupUi(this);
    Film *editedFilm = entry->getFilm();
    ui->inName->setText(editedFilm->getName());
    ui->inDir->setText(editedFilm->getDirector());
    ui->inYear->setText(editedFilm->getYear());
    QString tagList;
    for(QString tag : editedFilm->tags){
        tagList.push_back(tag + ",");
    }
    ui->inTags->setText(tagList);
    ui->inStars->setValue(entry->getStars().toInt());
    ui->inReview->setPlainText(entry->getReview());
    ui->inDate->setDate(entry->getDate());
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
        for(QString tag : tags){
            film->addTag(tag);
        }
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


