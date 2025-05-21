#ifndef RECORD_H
#define RECORD_H
#include <QString>

/**
 * @brief Klasa Record służy do przechowywania danych w bazie danych
 */
class Record
{
public:
    Record();

    QString virtual toText() = 0;

protected:
    int id;

    int getId();
};

#endif // RECORD_H
