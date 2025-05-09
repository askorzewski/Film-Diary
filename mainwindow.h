#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "film.h"


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

    QList<Film> readFiles(const QStringList & fileNames);

    void loadToTable(const QList<Film> &list);

private:
    QList<Film> films;
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
