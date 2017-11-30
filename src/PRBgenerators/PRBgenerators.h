#ifndef PRBgenerators_H
#define PRBgenerators_H

#include <QObject>
#include <QQuickItem>
#include <time.h>
#include "../BigIntLibrary/BigIntLibrary.h"

class PRBgenerators: public QObject
{
    Q_OBJECT

public:
    explicit PRBgenerators(QObject *parent = 0);
    ~PRBgenerators();

    Q_INVOKABLE void generateBuiltInCPP(const uint32_t& numberOfBit);
    Q_INVOKABLE void generateLehmerLow(const uint32_t& numberOfBit);
    Q_INVOKABLE void generateLehmerHigh(const uint32_t& numberOfBit);
    Q_INVOKABLE void generateL20(const uint32_t& numberOfBit);
    Q_INVOKABLE void generateL89(const uint32_t& numberOfBit);
    Q_INVOKABLE void generateGeffe(const uint32_t& numberOfBit);
    Q_INVOKABLE void generateWolfram(const uint32_t& numberOfBit);
    Q_INVOKABLE void generateBlumMikaliBit(const uint32_t& numberOfBit);
    Q_INVOKABLE void generateBlumMikaliByte(const uint32_t& numberOfBit);
    Q_INVOKABLE void generateBlumBlumShubBit(const uint32_t& numberOfBit);
    Q_INVOKABLE void generateBlumBlumShubByte(const uint32_t& numberOfBit);

private:
    BigInt m_generatedBuiltInCPP;
    BigInt m_generatedLehmerLow;
    BigInt m_generatedLehmerHigh;
    BigInt m_generatedL20;
    BigInt m_generatedL89;
    BigInt m_generatedGeffe;
    BigInt m_generatedWolfram;
    BigInt m_generatedBlumMikaliBit;
    BigInt m_generatedBlumMikaliByte;
    BigInt m_generatedBlumBlumShubBit;
    BigInt m_generatedBlumBlumShubByte;
};

#endif // PRBgenerators_H
