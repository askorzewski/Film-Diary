#ifndef ACCOUNTDATA_H
#define ACCOUNTDATA_H
#include "database.h"
/**
 * @brief Klasa AccountData dziediczy z Database, służy do obsługi danych dla poszczególnego konta
 */
class AccountData : public Database
{
    QList<Record*> watchlist;
public:
    AccountData(int id);

    QString getName() const;
};

#endif // ACCOUNTDATA_H
