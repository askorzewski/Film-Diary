#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QTextBrowser>
#include <QRegularExpression>
#include <QTabBar>
#include "filmdata.h"
#include "addfilm.h"
#include "addentry.h"


//1366x718

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    loadAccountData();
    ui->mainScreen->tabBar()->setTabVisible(2, false);
    ui->searchBar->setVisible(false);
    reloadStartUi();
}

MainWindow::~MainWindow()
{
    delete ui;
}

/*
 * Start Screen
*/

void MainWindow::loadAccountData(){
    QFile* accountFile = new QFile(dir.path() + "/Data/accounts.csv");

    if(!accountFile->open(QIODevice::ReadOnly)) { //Sprawdź czy plik był wczytany
        QMessageBox::information(0, "error", accountFile->fileName() + ": " + accountFile->errorString());
    }

    QTextStream data(accountFile); //Wczytaj z pliku do wektora obiektów
    while(!data.atEnd()){
        QString line = data.readLine();
        QStringList fields = line.split(",");
        AccountData newAccount = AccountData(&filmData, fields[0].toInt());
        newAccount.setName(fields[1]);
        accounts.append(newAccount);
    }
    delete accountFile;
}


void MainWindow::deleteAccount(QString &name){
    QList<AccountData>::Iterator account = accounts.begin();
    while(account != accounts.end()){
        if(name == account->getName()){
            account->clear();
            accounts.erase(account);
            break;
        }
        account++;
    }

    QString strId = QString::number(account->getId());
    QFile accountFile = QFile(dir.path() + "/Data/accounts.csv");
    QFile temp_file = QFile(dir.path() + "/Data/temp_accounts.csv");

    if(!accountFile.open(QIODevice::ReadOnly)) {
        QMessageBox::information(0, "error", accountFile.fileName() + ": " + accountFile.errorString());
    }
    if(!temp_file.open(QIODevice::WriteOnly)) {
        QMessageBox::information(0, "error", temp_file.fileName() + ": " + temp_file.errorString());
    }

    QTextStream data(&accountFile);
    QTextStream out(&temp_file);
    while(!data.atEnd()){
        QString line = data.readLine();
        QStringList fields = line.split(",");
        if(fields[0]==strId){
        }
        else{
            out<<line<<"/n";
        }
    }
    if(!accountFile.remove()){
       QMessageBox::information(0, "error", accountFile.fileName() + ": " + accountFile.errorString());
    }
    if(!temp_file.rename("Data/accounts.csv")){
        QMessageBox::information(0, "error", temp_file.fileName() + ": " + temp_file.errorString());
    }

}

void MainWindow::reloadStartUi(){
    QList<QPushButton*> existingButtons = ui->verticalLayoutWidget->findChildren<QPushButton*>(NULL);
    for(QPushButton* button : existingButtons){
        button->disconnect();
        button->setVisible(false);
        button->deleteLater();
        button->close();
    }
    for(AccountData account : accounts){
        QPushButton* button = new QPushButton(account.getName());
        ui->verticalLayout->addWidget(button, 40);
        button->setObjectName(account.getName());
        button->setCheckable(true);
        button->setFixedSize(QSize(500, 65));
        button->setFont(QFont("Bahnschrift", 30, QFont::Bold));
        button->show();
        QObject::connect (button,SIGNAL(clicked(bool)),this,SLOT(chooseAccount()));
    }
}


void MainWindow::chooseAccount(){
    if(accountSelected!=" "){
        QPushButton* toggledbutton = findChild<QPushButton*>(accountSelected);
        toggledbutton->toggle();
    }
    QObject* sender = QObject::sender();
    accountSelected = sender->objectName();
    //std::cout<<accountSelected.toStdString()<<std::endl;
}



void MainWindow::on_buttonDelete_clicked()
{
    if(accountSelected == " "){
        return;
    }
    deleteAccount(accountSelected);
    accountSelected = " ";
    reloadStartUi();
}



void MainWindow::on_buttonNew_clicked()
{
    ui->addNazwa->setFixedSize(300,100);
}



void MainWindow::on_buttonBox_accepted()
{
    int freeId;
    if(accounts.empty()){
        freeId = 1;
    }
    else {
        freeId = accounts.last().getId()+1;
    }
    QLineEdit* name_container = ui->addNazwa->findChild<QLineEdit*>(NULL);
    QString name = name_container->text();

    AccountData newAccount(&filmData, freeId);
    newAccount.setName(name);
    accounts.append(newAccount);
    ui->addNazwa->setFixedSize(0,0);

    QFile accountFile = QFile("Data/accounts.csv");
    if(!accountFile.open(QIODevice::Append)){
    }
    QTextStream accountStream(&accountFile);

    accountStream<<QString::number(freeId)<<","<<name<<Qt::endl;
    accountFile.close();
    reloadStartUi();
}


void MainWindow::on_buttonBox_rejected()
{
    ui->addNazwa->setFixedSize(0,0);
}


void MainWindow::on_buttonLoad_clicked()
{
    if(accountSelected == " "){
        return;
    }
    for(AccountData &account : accounts){
        if(accountSelected == account.getName()){
            data = &account;
        }
    }
    ui->startScreen->setFixedSize(0,0); //Tu wszędzie powinno byc setVisible() jakbym wczesniej wiedzial ze mozna
    ui->mainScreen->setFixedSize(1366,718);
    ui->mainUtility->setFixedSize(1310, 100);
    ui->mainScreen->setCurrentIndex(0);
    ui->searchBar->setVisible(true);
    this->refreshTable();
}


void MainWindow::on_actionWyloguj_triggered()
{
    ui->startScreen->setFixedSize(1366,718);
    ui->mainScreen->setFixedSize(0,0);
    ui->mainUtility->setFixedSize(0,0);
    ui->searchBar->setVisible(false);
}



/*
 * Main Screen
*/

void MainWindow::refreshTable(QList<Record*> records)
{
    int tabIndex = ui->mainScreen->currentIndex();
    if(!records.isEmpty() and records[0]==nullptr){
        switch(tabIndex){
        case 0:
            records = data->getRecords();
            break;
        case 1:
            records = data->watchlist.getRecords();
            break;
        case 2:
            return;
        }
    }
    QList<QPushButton*> existingButtons = ui->mainScreen->findChildren<QPushButton*>(QRegularExpression("^[0-9]+$"));
    for(QPushButton* button : existingButtons){
        button->disconnect();
        button->setVisible(false);
        button->deleteLater();
        button->close();
        recordSelected = nullptr;
    }
    if(records.isEmpty()){
        return;
    }
    QString tableName;
    switch(tabIndex){
    case 0:
        tableName = "EntriesTable";
        break;
    case 1:
        tableName = "WatchlistTable";
        break;
    case 2:
        return;
    }
    QVBoxLayout* table = ui->mainScreen->currentWidget()->findChild<QVBoxLayout*>(tableName);
    for(Record* recordData : records){
        if(recordData == nullptr){
            continue;
        }
        QPushButton* recordInTable = new QPushButton();
        table->insertWidget(0, recordInTable);
        recordInTable->setObjectName(QString::number(recordData->getId()));
        recordInTable->setCheckable(true);
        recordInTable->setText(recordData->getLabel());
        recordInTable->resize(recordInTable->sizeHint().width(), (recordInTable->sizeHint().height())+100);
        QObject::connect (recordInTable,SIGNAL(clicked(bool)),this,SLOT(selectRecord()));
    }
}

void MainWindow::selectRecord(){
    if(recordSelected != nullptr){
        QPushButton* toggledbutton = findChild<QPushButton*>(QString::number(recordSelected->getId()));
        toggledbutton->toggle();
    }
    QObject* sender = QObject::sender();
    int recordId = sender->objectName().toInt();
    switch(ui->mainScreen->currentIndex()) {
    case 0:
        recordSelected = data->findRecord(recordId);
        break;
    case 1:
        recordSelected = data->watchlist.findRecord(recordId);
    default:
        return;
    }
}


void MainWindow::on_main_edit_clicked(){
    if(recordSelected==nullptr){
        return;
    }
    int tabIndex = this->ui->mainScreen->currentIndex();
    if(tabIndex == 0){
        int entryId = recordSelected->getId();
        int filmId = static_cast<Entry*>(recordSelected)->getFilm()->getId();
        AddEntry form(static_cast<Entry*>(recordSelected), this);
        form.exec();
        Entry *newEntry = new Entry(form.getData(filmId, entryId));
        filmData.swapRecord(newEntry->getFilm());
        data->swapRecord(newEntry);
    }
    else if(tabIndex == 1){
        int recordId = this->recordSelected->getId();
        AddFilm form(static_cast<Film*>(recordSelected), this);
        form.exec();
        Film *newFilm = new Film(form.getData(recordId));
        for(QString tag : form.getTags()){
            newFilm->addTag(tag);
        }
        if(newFilm->getId() == 0){
            return;
        }
        filmData.swapRecord(newFilm);
        data->watchlist.swapRecord(newFilm);
    }
    refreshTable();
}

void MainWindow::on_actionZapisz_triggered()
{
    data->saveToFiles();
    filmData.saveToFiles();
}


void MainWindow::on_main_new_clicked()
{
    int tabIndex = this->ui->mainScreen->currentIndex();
    switch(tabIndex){
    case 0:
        addNewEntry();
        break;
    case 1:
        addNewFilm();
        break;
    }
}

void MainWindow::addNewEntry(){
    AddEntry form(this);
    form.exec();
    Entry *newEntry = new Entry(form.getData(filmData.freeId(), data->freeId()));
    if(newEntry->getId()==0){
        return;
    }
    filmData.addFilm(*newEntry->getFilm());
    data->addEntry(*newEntry);
    refreshTable();
}

void MainWindow::addNewEntry(Film *film){
    AddEntry form(film, this);
    form.exec();
    Entry *newEntry = new Entry(form.getData(filmData.freeId(), data->freeId()));
    if(newEntry->getId()==0){
        return;
    }
    data->addEntry(*newEntry);
    refreshTable();
}

void MainWindow::addNewFilm(){
    AddFilm form(this);
    form.exec();
    Film *newFilm = new Film(form.getData(filmData.freeId()));
    if(newFilm->getId()==0){
        return;
    }
    for(QString tag : form.getTags()){
        tag = tag.trimmed();
        newFilm->addTag(tag);
    }
    filmData.addFilm(*newFilm);
    data->watchlist.addFilm(*newFilm);
    refreshTable();
}

void MainWindow::on_mainScreen_currentChanged(int index)
{
    switch(index){
    case 0:
        ui->mainUtility->setVisible(true);
        ui->main_open->setVisible(true);
        break;
    case 1:
        ui->mainUtility->setVisible(true);
        ui->main_open->setVisible(false);
        break;
    case 2:
        ui->mainUtility->setVisible(false);
    }
    recordSelected = nullptr;
    refreshTable();
}


void MainWindow::on_main_delete_clicked()
{
    QList<Record*>recordList;
    switch(ui->mainScreen->currentIndex()){
    case 0:
        data->deleteRecord(recordSelected);
        break;
    case 1:
        data->watchlist.deleteRecord(recordSelected);
        break;
    }

    refreshTable();
}


void MainWindow::chooseFromWatchlist()
{
    ui->mainScreen->setCurrentIndex(1);
    refreshTable();
    ui->main_open->setVisible(true);
    ui->main_delete->setDisabled(true);
    ui->main_new->setDisabled(true);
    ui->main_edit->setDisabled(true);
    ui->mainScreen->tabBar()->setEnabled(false);
}

void MainWindow::returnFromChoosingWatchlist()
{
    ui->mainScreen->setCurrentIndex(0);
    refreshTable();
    ui->main_delete->setEnabled(true);
    ui->main_new->setEnabled(true);
    ui->main_edit->setEnabled(true);
    ui->mainScreen->tabBar()->setEnabled(true);
}


void MainWindow::on_main_open_clicked()
{
    if(recordSelected == nullptr){
        return;
    }
    if(ui->mainScreen->currentIndex() == 1){
        Film *film = static_cast<Film*>(recordSelected);
        addNewEntry(film);
        returnFromChoosingWatchlist();
        data->watchlist.deleteRecord(film);
    }
    else if(ui->mainScreen->currentIndex()==0){
        if(ui->mainScreen->tabBar()->isTabVisible(2) == false){
            QTabBar *bar =ui->mainScreen->tabBar();
            bar->setTabVisible(2, true);
            bar->resize(bar->sizeHint().width(), bar->sizeHint().height());
        }
        showEntry(static_cast<Entry*>(recordSelected));
        ui->mainScreen->setCurrentIndex(2);
    }
}

void MainWindow::showEntry(Entry *entry_ptr){
    qDeleteAll(ui->tagSpace->findChildren<QWidget*>());
    if(entry_ptr == nullptr){
        return;
    }
    const Entry entry = *entry_ptr;
    const Film film = *entry.getFilm();
    ui->title->setText(film.getLabel());
    ui->labelDirector->setText(film.getDirector());
    ui->labelYear->setText(film.getYear());
    ui->reviewSpace->setText(entry.getReview());
    ui->labelDate->setText(entry.getDateText());
    ui->starImage->setPixmap(QPixmap("Images/" + entry.getStars() + ".png"));
    for(QString tag : film.tags){
        QLabel* label = new QLabel(tag);
        ui->tagsSpace->addWidget(label);
    }
    ui->tagSpace->setFixedSize(ui->tagSpace->sizeHint().width(), ui->tagSpace->sizeHint().height());
}

void MainWindow::on_searchButton_clicked()
{
    QString searchQuery = ui->searchInput->text().toLower();
    if(searchQuery.isEmpty()){
        refreshTable();
        return;
    }
    QList<Record*> inputRecords;
    QList<Record*> outputRecords = {};
    switch(ui->mainScreen->currentIndex()){
    case 0:
        inputRecords = data->getRecords();
        break;
    case 1:
        inputRecords = data->watchlist.getRecords();
        break;
    case 2:
        return;
    }
    for(Record* record : inputRecords){
        QStringList keywords = record->getKeywords();
        for(QString key : keywords){
            key = key.toLower();
            if(key == searchQuery){
                outputRecords.append(record);
            }
        }
    }
    refreshTable(outputRecords);
}

