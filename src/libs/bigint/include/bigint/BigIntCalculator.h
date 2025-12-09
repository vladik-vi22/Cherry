#ifndef BigIntCalculator_H
#define BigIntCalculator_H

#include <QObject>
#include <QQuickItem>
#include <bigint/BigIntLibrary.h>

class BigIntCalculator : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString bigNumber1 READ getBigNumber1 WRITE setBigNumber1 NOTIFY bigNumber1Changed)
    Q_PROPERTY(QString bigNumber2 READ getBigNumber2 WRITE setBigNumber2 NOTIFY bigNumber2Changed)
    Q_PROPERTY(QString calculationsResult READ getCalculationsResult WRITE setCalculationsResult NOTIFY calculationsResultChanged)
    Q_PROPERTY(int baseInput READ getBaseInput WRITE setBaseInput NOTIFY baseInputChanged)
    Q_PROPERTY(int baseOutput READ getBaseOutput WRITE setBaseOutput NOTIFY baseOutputChanged)

    static const QString usedCharsBinary; // "01"
    static const QString usedCharsDecimal; // "0123456789"
    static const QString usedCharsHexadecimal; // "0123456789abcdefABCDEF"

public:
    explicit BigIntCalculator(QObject *parent = 0);
    ~BigIntCalculator();

private:
    QString getBigNumber1() const;
    QString getBigNumber2() const;
    QString getCalculationsResult() const;
    uint8_t getBaseInput() const;
    uint8_t getBaseOutput() const;
    void setBigNumber1(const QString& new_bigNumber1);
    void setBigNumber2(const QString& new_bigNumber2);
    void setCalculationsResult(const QString& new_calculationsResult);
    void setBaseInput(const uint8_t& new_baseInput);
    void setBaseOutput(const uint8_t& new_baseOutput);

    bool isCorrect(const QString& bigNumberQString) const;

public:
    Q_INVOKABLE void calculate(const QString& operation);

signals:
    void bigNumber1Changed();
    void bigNumber2Changed();
    void calculationsResultChanged();
    void baseInputChanged();
    void baseOutputChanged();

private:
    QString m_bigNumber1;
    QString m_bigNumber2;
    QString m_calculationsResult;
    uint8_t m_baseInput;
    uint8_t m_baseOutput;

};

#endif // BigIntCalculator_H
