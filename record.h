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

    virtual ~Record();
    /**
     * @brief toText Przygotowuje dane jednego rekordu do zapisu w pliku .csv
     * @return Tekst gowowy do zapisu w pliku jako jedna linijka
     */
    QString virtual toText() = 0;

    /**
     * @brief getLabel
     * @return Tekst który pojawia się na przycisku rekordu w programie. Format: Tytuł(Rok).
     */
    QString virtual getLabel() const = 0;

    /**
     * @brief getId
     * @return id rekordu
     */
    int getId() const;

    /**
     * @brief getKeywords
     * @return Lista słów kluczowych dzięki którym można znaleźć rekord w pasu wyszukiwania w programie (tytuł podzielony , imie/nazwisko reżysera, tagi)
     */
    QStringList virtual getKeywords() const = 0;

protected:
    int id;
};

#endif // RECORD_H
