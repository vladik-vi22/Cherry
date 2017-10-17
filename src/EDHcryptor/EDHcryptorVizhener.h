#ifndef Vizhener_H
#define Vizhener_H

#include <QQuickItem>
#include <QObject>
#include <QString>
#include <QList>
#include <QPair>
#include <QtMath>
#include <QtAlgorithms>

class Vizhener: public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString text READ getText WRITE setText NOTIFY textChanged)
    Q_PROPERTY(QString key READ getKey WRITE setKey NOTIFY keyChanged)
    Q_PROPERTY(QString language READ getLanguage WRITE setLanguage NOTIFY languageChanged)

    static const QString alphabetEnglish; // "abcdefghijklmnopqrstuvwxyz"
    static const QString alphabetSortedByFrequencyEnglish; // "eariotnslcudpmhgbfywkvxzjq"
    static const QString alphabetRussian; // "абвгдеёжзийклмнопрстуфхцчшщъыьэюя"
    static const QString alphabetSortedByFrequencyRussian; // "оеаинтсрвлкмдпуяыгзбьйчхжюцшфщэёъ"
    static const QString englishLanguage; // "english"
    static const QString russianLanguage; // "russian"
    static const int lenghtAlphabetEnglish; // alphabetEnglish.length() = 26
    static const int lenghtAlphabetRussian; // alphabetRussian.length() = 33
    static const qreal coincidenceIndexEnglish; // 0.0644
    static const qreal coincidenceIndexRussian; // 0.0553
    static const QList<QString> mostFrequentBigramsEnglish; // QList<QString>() << "th" << "he" << "in" << "er" << "an" << "re" << "es" << "on" << "st" << "nt" << "en" << "at"
    static const QList<QString> mostFrequentBigramsRussian; // QList<QString>() << "ст" << "ен" << "ов" << "но" << "ни" << "на" << "ра" << "ко" << "то" << "ро" << "ан" << "ос"
    static const QList<QString> prohibitedBigramsEnglish; // QList<QString>() << "bq" << "cx" << "gx" << "jq" << "jv" << "kx" << "qv" << "qx" << "qz" << "vq" << "xz" << "zq" << "zx"
    static const QList<QString> prohibitedBigramsRussian; // QList<QString>() << "оъ" << "оы" << "оь" << "еъ" << "еы" << "еь" << "аъ" << "аы" << "аь" << "иъ" << "иы" << "иь" << "уъ" << "уы" << "уь" << "яъ" << "яы" << "яь" << "юъ" << "юы" << "юь" << "эъ" << "эы" << "эь" << "йъ" << "йы" << "йь" << "ёъ" << "ёы" << "ёь" << "ыъ" << "ыы" << "ыь" << "ьъ" << "ьы" << "ьь" << "ъъ" << "ъы" << "ъь"
    static QString alphabet;
    static QString alphabetSortedByFrequency;
    static int lenghtAlphabet;
    static qreal coincidenceIndex;
    static QList<QString> mostFrequentBigrams;
    static QList<QString> prohibitedBigrams;
    static int lenghtMostFrequentBigrams;

public:
    explicit Vizhener(QObject *parent = 0);
    ~Vizhener();

    QString getText() const;
    QString getKey() const;
    QString getLanguage() const;
    void setText(const QString &new_text);
    void setKey(const QString &new_key);
    void setLanguage(const QString &new_language);

    Q_INVOKABLE void encrypt();
    Q_INVOKABLE void decrypt();
    Q_INVOKABLE void hack();

signals:
    void textChanged();
    void keyChanged();
    void languageChanged();

private:
    QString m_text;
    QString m_key;
    QString m_language;

    bool isEnglishLanguage();
    void changeTextKey();
    bool isKeyCorrect();
    int findShortLenghtKey();
    int findLongLenghtKey();
    QList<QString> findKeys(int keyLenght);

    struct QPairSecondComparer
    {
        template<typename T1, typename T2>
        bool operator()(const QPair<T1,T2> & a, const QPair<T1,T2> & b) const
        {
            return a.second > b.second;
        }
    };

};

#endif // Vizhener_H
