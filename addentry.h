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
    /**
     * @brief AddEntry Konstruktor tworzący zarówno nowy obiekt Entry jak i nowy obiekt Film.
     * @param parent Okno rodzic (MainWindow)
     */
    explicit AddEntry(QWidget *parent = nullptr);
    /**
     * @brief AddEntry Konstruktor który do stworzenia obiektu klasy Enty wykorzystuje istniejący film z watchlisty (który zostanie z niej usunięty).
     * @param film Wskaźnik do filmu z watchlisty
     * @param parent Okno rodzic (MainWindow)
     */
    explicit AddEntry(Film *film, QWidget *parent = nullptr);
    /**
     * @brief AddEntry Konstruktor służący do edycji istniejącego wpisu
     * @param entry Wskaźnik do wpisu który bedzie edytowany
     * @param parent Okno rodzic (MainWindow)
     */
    explicit AddEntry(Entry *entry, QWidget *parent = nullptr);
    ~AddEntry();
    /**
     * @brief getData Medota służąca do przekazania danych z formularza jako gotowy obiekt klasy Entry. Id muszą zostać podane z zewnątrz gdyż są potrzebne do konstukcji obiektów Entry i Film, a klasa AddEntry nie ma dostępu do wykorzystanych już numerów.
     * @param filmId Id Filmu.
     * @param entryId Id Wpisu.
     * @return Objekt Film powstały na podstawie wprowadzonych w formularzu danych.
     */
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
