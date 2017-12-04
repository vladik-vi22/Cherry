#ifndef PRBgenerators_H
#define PRBgenerators_H

#include <QObject>
#include <QQuickItem>
#include <time.h>
#include <QDir>
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
    Q_INVOKABLE void generateLibrarian(const uint32_t& numberOfBit);
    Q_INVOKABLE void generateBlumMikaliBit(const uint32_t& numberOfBit);
    Q_INVOKABLE void generateBlumMikaliByte(const uint32_t& numberOfBit);
    Q_INVOKABLE void generateBlumBlumShubBit(const uint32_t& numberOfBit);
    Q_INVOKABLE void generateBlumBlumShubByte(const uint32_t& numberOfBit);

    Q_INVOKABLE bool testOfGoodnessOfFit(const std::vector<uint8_t>& stdVectorUint8_t);
    Q_INVOKABLE bool testOfHomogeneity(const std::vector<uint8_t>& stdVectorUint8_t);
    Q_INVOKABLE bool testOfIndependence(const std::vector<uint8_t>& stdVectorUint8_t);

private:
    std::vector<uint8_t> m_generatedBuiltInCPP;
    std::vector<uint8_t> m_generatedLehmerLow;
    std::vector<uint8_t> m_generatedLehmerHigh;
    std::vector<uint8_t> m_generatedL20;
    std::vector<uint8_t> m_generatedL89;
    std::vector<uint8_t> m_generatedGeffe;
    std::vector<uint8_t> m_generatedWolfram;
    std::vector<uint8_t> m_generatedLibrarian;
    std::vector<uint8_t> m_generatedBlumMikaliBit;
    std::vector<uint8_t> m_generatedBlumMikaliByte;
    std::vector<uint8_t> m_generatedBlumBlumShubBit;
    std::vector<uint8_t> m_generatedBlumBlumShubByte;
};

std::vector<uint8_t> StdVectorBoolToStdVectorUint8_t(const std::vector<bool>& stdVectorBool);
std::vector<uint16_t> StdVectorUint8_tToStdVectorUint16_t(const std::vector<uint8_t>& stdVectorUint8_t);

#endif // PRBgenerators_H
