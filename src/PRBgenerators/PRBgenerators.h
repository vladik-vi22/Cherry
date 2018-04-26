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
    Q_PROPERTY(QString numberOfBit READ getNumberOfBit WRITE setNumberOfBit NOTIFY numberOfBitChanged)
    Q_PROPERTY(QString alpha READ getAlpha WRITE setAlpha NOTIFY alphaChanged)
    Q_PROPERTY(QString numberOfSegment READ getNumberOfSegment WRITE setNumberOfSegment NOTIFY numberOfSegmentChanged)

    static float Z_1minusAlpha;

public:
    explicit PRBgenerators(QObject *parent = 0);
    ~PRBgenerators();

    QString getNumberOfBit() const;
    QString getAlpha() const;
    QString getNumberOfSegment() const;
    std::vector<uint8_t> getGeneratedPRBS() const;
    uint8_t getUint8_tGeneratedPRBS() const;
    uint16_t getUint16_tGeneratedPRBS() const;
    uint32_t getUint32_tGeneratedPRBS() const;
    uint64_t getUint64_tGeneratedPRBS() const;
    void setNumberOfBit(const QString& new_numberOfBit);
    void setNumberOfBit(const uint32_t& new_numberOfBit);
    void setAlpha(const QString& new_alpha);
    void setNumberOfSegment(const QString& new_numberOfSegment);

signals:
    void numberOfBitChanged();
    void alphaChanged();
    void numberOfSegmentChanged();

public:
    Q_INVOKABLE void generateBuiltInCPPBit();
    Q_INVOKABLE void generateBuiltInCPPByte();
    Q_INVOKABLE void generateLehmerLow();
    Q_INVOKABLE void generateLehmerHigh();
    Q_INVOKABLE void generateL20();
    Q_INVOKABLE void generateL89();
    Q_INVOKABLE void generateGeffe();
    Q_INVOKABLE void generateWolfram();
    Q_INVOKABLE void generateLibrarian();
    Q_INVOKABLE void generateBlumMicaliBit();
    Q_INVOKABLE void generateBlumMicaliByte();
    Q_INVOKABLE void generateBlumBlumShubBit();
    Q_INVOKABLE void generateBlumBlumShubByte();

    Q_INVOKABLE bool testOfGoodnessOfFit() const;
    Q_INVOKABLE bool testOfHomogeneity() const;
    Q_INVOKABLE bool testOfIndependence() const;

    Q_INVOKABLE QString getQStringGeneratedPRBS() const;

private:
    std::vector<uint8_t> m_generatedPRBS;
    uint32_t m_numberOfBit;
    float m_alpha;
    uint32_t m_numberOfSegment;
};

std::vector<uint8_t> StdVectorBoolToStdVectorUint8_t(const std::vector<bool>& stdVectorBool);
QString StdVectorUint8_tToQString(const std::vector<uint8_t>& stdVectorUint8_t);

#endif // PRBgenerators_H
