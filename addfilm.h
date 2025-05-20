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
    explicit AddFilm(QWidget *parent = nullptr);
    ~AddFilm();

    Film getData(int id) const;

private slots:
    void on_buttonBox_accepted();

private:
    Ui::AddFilm *ui;

    QString name;
    QString director;
    QString year;
};

#endif // ADDFILM_H
