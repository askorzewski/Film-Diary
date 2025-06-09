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

    friend class AccountData;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void loadAccountData();

    void deleteAccount(QString &name);

    void reloadStartUi();

    void chooseAccount();

    void on_buttonDelete_clicked();

    void on_buttonNew_clicked();

    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

    void on_buttonLoad_clicked();

    void on_actionWyloguj_triggered();

    void selectRecord();

    void loadToTable(QList<Record*>);

    void on_actionZapisz_triggered();

    void on_main_new_clicked();

    void on_main_edit_clicked();

    void on_mainScreen_currentChanged(int index);

    void on_main_delete_clicked();

private:
    FilmData filmData = FilmData();

    Ui::MainWindow *ui;

    QList<AccountData> accounts;

    QDir dir = QDir::current();

    QString accountSelected = " ";

    Record* recordSelected = nullptr;

    AccountData* data;
};
#endif // MAINWINDOW_H
