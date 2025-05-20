#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "film.h"
#include "database.h"
#include "addfilm.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_przyciskWczytaj_clicked();

    void refreshTable(const Database &account);

    void on_NewFilm_clicked();

private:
    Database global_data = Database(0);
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
