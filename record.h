#ifndef RECORD_H
#define RECORD_H
#include <QString>

/**
 * @brief Klasa Record służy do przechowywania danych w bazie danych
 */
class Record
{
public:
    Record(int id);

    QString virtual toText() = 0;

    QString virtual getLabel() = 0;

    int getId() const;

protected:
    int id;
};

#endif // RECORD_H
