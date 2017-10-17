#ifndef Affine_H
#define Affine_H

#include <QQuickItem>
#include <QObject>
#include <QString>
#include <QList>
#include <QPair>
#include <QtMath>
#include <QtAlgorithms>

class Affine: public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString text READ getText WRITE setText NOTIFY textChanged)
    Q_PROPERTY(qint32 key1 READ getKey1 WRITE setKey1 NOTIFY key1Changed)
    Q_PROPERTY(qint32 key2 READ getKey2 WRITE setKey2 NOTIFY key2Changed)
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
    explicit Affine(QObject *parent = 0);
    ~Affine();

    QString getText() const;
    qint32 getKey1() const;
    qint32 getKey2() const;
    QString getLanguage() const;
    void setText(const QString &new_text);
    void setKey1(const qint32 &new_key1);
    void setKey2(const qint32 &new_key2);
    void setLanguage(const QString &new_language);

    Q_INVOKABLE void encrypt();
    Q_INVOKABLE void decrypt();
    Q_INVOKABLE void hack();

signals:
    void textChanged();
    void key1Changed();
    void key2Changed();
    void languageChanged();

private:
    QString m_text;
    qint32 m_key1;
    qint32 m_key2;
    QString m_language;

    bool isEnglishLanguage();
    void changeText();
    bool isKeyCorrect();
    QList<QPair<int, int> > findKeys();

    int gcd(int number1, int number2);
    int inverseModulo(int number, int modulo);
    QList<int> comparisonByModule(int number1, int number2, int modulo);

    struct QPairSecondComparer
    {
        template<typename T1, typename T2>
        bool operator()(const QPair<T1,T2> & a, const QPair<T1,T2> & b) const
        {
            return a.second > b.second;
        }
    };

};

#endif // Affine_H
