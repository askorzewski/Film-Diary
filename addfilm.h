#ifndef ADDFILM_H
#define ADDFILM_H

#include <QDialog>
#include "film.h"

namespace Ui {
class AddFilm;
}

/**
 * @brief Klasa AddFilm okno dialogowe do dodawania nowych filmów
 */
class AddFilm : public QDialog
{
    Q_OBJECT
public:
    explicit AddFilm(QWidget *parent);
    explicit AddFilm(Film* film, QWidget *parent = nullptr);
    ~AddFilm();
    /**
     * @brief getData Funcja służąca do przekazania danych z formularza jako gotowy obiekt klasy Entry.
     * @param id Id filmu.
     * @return Objekt Film powstały na podstawie wprowadzonych w formularzu danych.
     */
    Film getData(int id) const;

    QStringList getTags() const;

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::AddFilm *ui;

    QString name;
    QString director;
    QString year;
    QStringList tags;

    bool canceled;
};

#endif // ADDFILM_H
