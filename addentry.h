#ifndef ADDENTRY_H
#define ADDENTRY_H

#include <QDialog>
#include "entry.h"

namespace Ui {
class AddEntry;
}

class AddEntry : public QDialog
{
    Q_OBJECT
public:
    explicit AddEntry(QWidget *parent = nullptr);
    explicit AddEntry(Film *film, QWidget *parent = nullptr);
    ~AddEntry();

    Entry getData(int filmId, int entryId);


private slots:
    void on_buttonBox_rejected();

    void on_fromWatchlist_clicked();

    void on_buttonBox_accepted();

private:
    Ui::AddEntry *ui;
    bool canceled = 1;

    QString name;
    QString director;
    QString year;
    QStringList tags;
    Film* film = nullptr;
    int stars;
    QString review;
    QDate date;
};

#endif // ADDENTRY_H
