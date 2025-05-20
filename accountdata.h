#ifndef ACCOUNTDATA_H
#define ACCOUNTDATA_H
#include "database.h"
/**
 * @brief Klasa AccountData dziediczy z Database, służy do obsługi danych dla poszczególnego konta
 */
class AccountData : public Database
{
public:
    AccountData(int id);
};

#endif // ACCOUNTDATA_H
