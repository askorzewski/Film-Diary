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
    explicit AddFilm(QWidget *parent = nullptr, Film *film = nullptr);
    ~AddFilm();
    /**
     * @brief getData
     * @param id - nadane ID
     * @return Objekt Film na podstawie wprowadzonych w formularzu danych.
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
