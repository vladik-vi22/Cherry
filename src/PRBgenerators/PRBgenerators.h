#ifndef PRBgenerators_H
#define PRBgenerators_H

#include <QQuickItem>
#include <QObject>
#include <QBitArray>
#include <QByteArray>
#include <QString>
#include <QList>
#include <QPair>
#include <QDataStream>
#include <QtMath>
#include <QtAlgorithms>

class PRBgenerators: public QObject
{
    Q_OBJECT
    Q_PROPERTY(QBitArray number_bit_arr READ getNumberBitArr WRITE setNumberBitArr NOTIFY numberBitArrChanged)
    Q_PROPERTY(QByteArray number_byte_arr READ getNumberByteArr WRITE setNumberByteArr NOTIFY numberByteArrChanged)
    Q_PROPERTY(QString number_str READ getNumberStr WRITE setNumberStr NOTIFY numberStrChanged)
    Q_PROPERTY(QList<qint16> number_list_int READ getNumberListInt WRITE setNumberListInt NOTIFY numberListIntChanged)

public:
    explicit PRBgenerators(QObject *parent = 0);
    ~PRBgenerators();

    QBitArray getNumberBitArr() const;
    QByteArray getNumberByteArr() const;
    QString getNumberStr() const;
    QList<qint16> getNumberListInt() const;
    void setNumberBitArr(const QBitArray &new_number_bit_arr);
    void setNumberByteArr(const QByteArray &new_number_byte_arr);
    void setNumberStr(const QString &new_number_str);
    void setNumberListInt(const QList<qint16> &new_number_list_int);

    Q_INVOKABLE virtual void generate(){}

signals:
    void numberBitArrChanged();
    void numberByteArrChanged();
    void numberStrChanged();
    void numberListIntChanged();

protected:

    QBitArray m_number_bit_arr;
    QByteArray m_number_byte_arr;
    QString m_number_str;
    QList<qint16> m_number_list_int;


};

#endif // PRBgenerators_H
