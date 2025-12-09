#ifndef PRBgenerators_H
#define PRBgenerators_H

#include <QObject>
#include <QQuickItem>
#include <time.h>
#include <QDir>
#include <bigint/BigIntLibrary.h>

class PRBgenerators: public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString numberOfBits READ getNumberOfBits WRITE setNumberOfBits NOTIFY numberOfBitsChanged)
    Q_PROPERTY(QString alpha READ getAlpha WRITE setAlpha NOTIFY alphaChanged)
    Q_PROPERTY(QString numberOfSegments READ getNumberOfSegments WRITE setNumberOfSegments NOTIFY numberOfSegmentsChanged)

    static double Z_1minusAlpha;

public:
    explicit PRBgenerators(QObject *parent = 0);
    ~PRBgenerators();

    QString getNumberOfBits() const;
    QString getAlpha() const;
    QString getNumberOfSegments() const;
    std::vector<uint8_t> getGeneratedPRBS() const;
    uint8_t getUint8_tGeneratedPRBS() const;
    uint16_t getUint16_tGeneratedPRBS() const;
    uint32_t getUint32_tGeneratedPRBS() const;
    uint64_t getUint64_tGeneratedPRBS() const;
    void setNumberOfBits(const QString& new_numberOfBits);
    void setNumberOfBits(const size_t new_numberOfBits);
    void setNumberOfBytes(const size_t new_numberOfBytes);
    void setAlpha(const QString& new_alpha);
    void setNumberOfSegments(const QString& new_numberOfSegments);

signals:
    void numberOfBitsChanged();
    void alphaChanged();
    void numberOfSegmentsChanged();

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
    size_t m_numberOfBits;
    double m_alpha;
    size_t m_numberOfSegments;
};

std::vector<uint8_t> StdVectorBoolToStdVectorUint8_t(const std::vector<bool>& stdVectorBool);
QString StdVectorUint8_tToQString(const std::vector<uint8_t>& stdVectorUint8_t);

#endif // PRBgenerators_H
