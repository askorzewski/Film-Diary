#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "filmdata.h"
#include "accountdata.h"

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

    void refreshTable(const QList<Record*> &idList);

    void on_NewFilm_clicked();

    void on_pushButton_clicked();

private:
    FilmData global_data = FilmData();
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
