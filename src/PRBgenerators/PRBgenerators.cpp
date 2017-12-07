#include "PRBgenerators.h"

float PRBgenerators::Z_1minusAlpha;

PRBgenerators::PRBgenerators(QObject* parent): QObject(parent)
{
    m_alpha = 0.05;
    Z_1minusAlpha = 1.645;
}

PRBgenerators::~PRBgenerators()
{
}

QString PRBgenerators::getNumberOfBit() const
{
    return QString::number(m_numberOfBit);
}

QString PRBgenerators::getAlpha() const
{
    return QString::number(m_alpha);
}

void PRBgenerators::setNumberOfBit(const QString& new_numberOfBit)
{
    if(QString::number(m_numberOfBit) != new_numberOfBit)
    {
        m_numberOfBit = new_numberOfBit.toULong();
        emit numberOfBitChanged();
    }
}

void PRBgenerators::setAlpha(const QString& new_alpha)
{
    if(QString::number(m_alpha) != new_alpha)
    {
        m_alpha = new_alpha.toFloat();
        switch((int)m_alpha * 100)
        {
        case 1:
            Z_1minusAlpha = 2.326;
            break;
        case 2:
            Z_1minusAlpha = 2.054;
            break;
        case 3:
            Z_1minusAlpha = 1.881;
            break;
        case 4:
            Z_1minusAlpha = 1.751;
            break;
        case 5:
            Z_1minusAlpha = 1.645;
            break;
        case 6:
            Z_1minusAlpha = 1.555;
            break;
        case 7:
            Z_1minusAlpha = 1.476;
            break;
        case 8:
            Z_1minusAlpha = 1.405;
            break;
        case 9:
            Z_1minusAlpha = 1.341;
            break;
        case 10:
            Z_1minusAlpha = 1.282;
            break;
        default:
            Z_1minusAlpha = 1.645;
            break;
        }
        emit alphaChanged();
    }
}

QString PRBgenerators::getQStringGeneratedPRBS()
{
    QString QStringGeneratedPRBS = StdVectorUint8_tToQString(m_generatedPRBS);
    if(QStringGeneratedPRBS.size() <= 16384)
    {
        return QStringGeneratedPRBS;
    }
    else
    {
        QStringGeneratedPRBS.resize(16384);
        return QStringGeneratedPRBS;
    }
}

void PRBgenerators::generateBuiltInCPP()
{
    m_generatedBuiltInCPP.clear();
    std::clock_t begin_time = std::clock();
    uint32_t numberOfByte = m_numberOfBit & 7 ? (m_numberOfBit >> 3) + 1 : m_numberOfBit >> 3;
    m_generatedBuiltInCPP.reserve(numberOfByte);
    srand(time(NULL));
    for(uint32_t indexByte = 0; indexByte < numberOfByte; ++indexByte)
    {
        m_generatedBuiltInCPP.push_back(rand() & UINT8_MAX);
    }
    std::cout << "time to generate BuiltInCPP on " << m_numberOfBit << " bit = " << float(std::clock() - begin_time) / CLOCKS_PER_SEC << std::endl;
    m_generatedPRBS = m_generatedBuiltInCPP;
}

void PRBgenerators::generateLehmerLow()
{
    m_generatedLehmerLow.clear();
    std::clock_t begin_time = std::clock();
    const uint32_t a = 65537;
    const uint32_t c = 119;
    uint32_t numberOfByte = m_numberOfBit & 7 ? (m_numberOfBit >> 3) + 1 : m_numberOfBit >> 3;
    m_generatedLehmerLow.reserve(numberOfByte);
    srand(time(NULL));
    uint32_t lehmerUint32_t = rand() + 1;
    for(uint32_t indexByte = 0; indexByte < numberOfByte; ++indexByte)
    {
        m_generatedLehmerLow.push_back(lehmerUint32_t & UINT8_MAX);
        lehmerUint32_t = a * lehmerUint32_t + c;
    }
    std::cout << "time to generate LehmerLow on " << m_numberOfBit << " bit = " << float(std::clock() - begin_time) / CLOCKS_PER_SEC << std::endl;
    m_generatedPRBS = m_generatedLehmerLow;
}

void PRBgenerators::generateLehmerHigh()
{
    m_generatedLehmerHigh.clear();
    std::clock_t begin_time = std::clock();
    const uint32_t a = 65537;
    const uint32_t c = 119;
    uint32_t numberOfByte = m_numberOfBit & 7 ? (m_numberOfBit >> 3) + 1 : m_numberOfBit >> 3;
    m_generatedLehmerHigh.reserve(numberOfByte);
    srand(time(NULL));
    uint32_t lehmerUint32_t = rand() + 1;
    for(uint32_t indexByte = 0; indexByte < numberOfByte; ++indexByte)
    {
        m_generatedLehmerHigh.push_back(lehmerUint32_t >> 24);
        lehmerUint32_t = a * lehmerUint32_t + c;
    }
    std::cout << "time to generate LehmerHigh on " << m_numberOfBit << " bit = " << float(std::clock() - begin_time) / CLOCKS_PER_SEC << std::endl;
    m_generatedPRBS = m_generatedLehmerHigh;
}

void PRBgenerators::generateL20()
{
    std::clock_t begin_time = std::clock();
    std::vector<bool> stdVectorBool;
    stdVectorBool.reserve(m_numberOfBit);
    stdVectorBool.resize(m_numberOfBit);
    std::vector<bool>::iterator iteratorStdVectorBool = stdVectorBool.begin();
    srand(time(NULL));
    for(uint8_t indexFirst20Bit = 0; indexFirst20Bit < 20; ++indexFirst20Bit)
    {
        *iteratorStdVectorBool = rand() & 1;
        ++iteratorStdVectorBool;
    }
    while(iteratorStdVectorBool != stdVectorBool.end())
    {
        *iteratorStdVectorBool = *(iteratorStdVectorBool - 3) ^ *(iteratorStdVectorBool - 5) ^ *(iteratorStdVectorBool - 9) ^ *(iteratorStdVectorBool - 20);
        ++iteratorStdVectorBool;
    }
    m_generatedL20 = StdVectorBoolToStdVectorUint8_t(stdVectorBool);
    std::cout << "time to generate L20 on " << m_numberOfBit << " bit = " << float(std::clock() - begin_time) / CLOCKS_PER_SEC << std::endl;
    m_generatedPRBS = m_generatedL20;
}

void PRBgenerators::generateL89()
{
    std::clock_t begin_time = std::clock();
    std::vector<bool> stdVectorBool;
    stdVectorBool.reserve(m_numberOfBit);
    stdVectorBool.resize(m_numberOfBit);
    std::vector<bool>::iterator iteratorStdVectorBool = stdVectorBool.begin();
    srand(time(NULL));
    for(uint8_t indexFirst89Bit = 0; indexFirst89Bit < 89; ++indexFirst89Bit)
    {
        *iteratorStdVectorBool = rand() & 1;
        ++iteratorStdVectorBool;
    }
    while(iteratorStdVectorBool != stdVectorBool.end())
    {
        *iteratorStdVectorBool = *(iteratorStdVectorBool - 38) ^ *(iteratorStdVectorBool - 89);
        ++iteratorStdVectorBool;
    }
    m_generatedL89 = StdVectorBoolToStdVectorUint8_t(stdVectorBool);
    std::cout << "time to generate L89 on " << m_numberOfBit << " bit = " << float(std::clock() - begin_time) / CLOCKS_PER_SEC << std::endl;
    m_generatedPRBS = m_generatedL89;
}

void PRBgenerators::generateGeffe()
{
    std::clock_t begin_time = std::clock();
    std::vector<bool> stdVectorBool;
    std::vector<bool> stdVectorBoolL9;
    std::vector<bool> stdVectorBoolL10;
    std::vector<bool> stdVectorBoolL11;
    stdVectorBool.reserve(m_numberOfBit);
    stdVectorBool.resize(m_numberOfBit);
    stdVectorBoolL9.reserve(m_numberOfBit);
    stdVectorBoolL9.resize(m_numberOfBit);
    stdVectorBoolL10.reserve(m_numberOfBit);
    stdVectorBoolL10.resize(m_numberOfBit);
    stdVectorBoolL11.reserve(m_numberOfBit);
    stdVectorBoolL11.resize(m_numberOfBit);
    std::vector<bool>::iterator iteratorStdVectorBool = stdVectorBool.begin();
    std::vector<bool>::iterator iteratorStdVectorBoolL9 = stdVectorBoolL9.begin();
    std::vector<bool>::iterator iteratorStdVectorBoolL10 = stdVectorBoolL10.begin();
    std::vector<bool>::iterator iteratorStdVectorBoolL11 = stdVectorBoolL11.begin();
    srand(time(NULL));
    for(uint8_t indexFirst9Bit = 0; indexFirst9Bit < 9; ++indexFirst9Bit)
    {
        *iteratorStdVectorBoolL9 = rand() & 1;
        *iteratorStdVectorBoolL10 = rand() & 1;
        *iteratorStdVectorBoolL11 = rand() & 1;
        *iteratorStdVectorBool = (*iteratorStdVectorBoolL10 & *iteratorStdVectorBoolL11) ^ ((1 ^ *iteratorStdVectorBoolL10) & *iteratorStdVectorBoolL9);
        ++iteratorStdVectorBool;
        ++iteratorStdVectorBoolL9;
        ++iteratorStdVectorBoolL10;
        ++iteratorStdVectorBoolL11;
    }

    *iteratorStdVectorBoolL9 = *(iteratorStdVectorBoolL9 - 9) ^ *(iteratorStdVectorBoolL9 - 8) ^ *(iteratorStdVectorBoolL9 - 6) ^ *(iteratorStdVectorBoolL9 - 5);
    *iteratorStdVectorBoolL10 = rand() & 1;
    *iteratorStdVectorBoolL11 = rand() & 1;
    *iteratorStdVectorBool = (*iteratorStdVectorBoolL10 & *iteratorStdVectorBoolL11) ^ ((1 ^ *iteratorStdVectorBoolL10) & *iteratorStdVectorBoolL9);
    ++iteratorStdVectorBool;
    ++iteratorStdVectorBoolL9;
    ++iteratorStdVectorBoolL10;
    ++iteratorStdVectorBoolL11;

    *iteratorStdVectorBoolL9 = *(iteratorStdVectorBoolL9 - 9) ^ *(iteratorStdVectorBoolL9 - 8) ^ *(iteratorStdVectorBoolL9 - 6) ^ *(iteratorStdVectorBoolL9 - 5);
    *iteratorStdVectorBoolL10 = *(iteratorStdVectorBoolL10 - 10) ^ *(iteratorStdVectorBoolL10 - 7);
    *iteratorStdVectorBoolL11 = rand() & 1;
    *iteratorStdVectorBool = (*iteratorStdVectorBoolL10 & *iteratorStdVectorBoolL11) ^ ((1 ^ *iteratorStdVectorBoolL10) & *iteratorStdVectorBoolL9);
    ++iteratorStdVectorBool;
    ++iteratorStdVectorBoolL9;
    ++iteratorStdVectorBoolL10;
    ++iteratorStdVectorBoolL11;

    while(iteratorStdVectorBool != stdVectorBool.end())
    {
        *iteratorStdVectorBoolL9 = *(iteratorStdVectorBoolL9 - 9) ^ *(iteratorStdVectorBoolL9 - 8) ^ *(iteratorStdVectorBoolL9 - 6) ^ *(iteratorStdVectorBoolL9 - 5);
        *iteratorStdVectorBoolL10 = *(iteratorStdVectorBoolL10 - 10) ^ *(iteratorStdVectorBoolL10 - 7);
        *iteratorStdVectorBoolL11 = *(iteratorStdVectorBoolL11 - 11) ^ *(iteratorStdVectorBoolL11 - 9);
        *iteratorStdVectorBool = (*iteratorStdVectorBoolL10 & *iteratorStdVectorBoolL11) ^ ((1 ^ *iteratorStdVectorBoolL10) & *iteratorStdVectorBoolL9);
        ++iteratorStdVectorBool;
        ++iteratorStdVectorBoolL9;
        ++iteratorStdVectorBoolL10;
        ++iteratorStdVectorBoolL11;
    }
    m_generatedGeffe = StdVectorBoolToStdVectorUint8_t(stdVectorBool);
    std::cout << "time to generate Geffe on " << m_numberOfBit << " bit = " << float(std::clock() - begin_time) / CLOCKS_PER_SEC << std::endl;
    m_generatedPRBS = m_generatedGeffe;
}

void PRBgenerators::generateWolfram()
{
    std::clock_t begin_time = std::clock();
    std::vector<bool> stdVectorBool;
    stdVectorBool.reserve(m_numberOfBit);
    srand(time(NULL));
    uint32_t r = rand() + 1;
    for(uint32_t indexBit = 0; indexBit < m_numberOfBit; ++indexBit)
    {
        stdVectorBool.push_back(r & 1);
        r = (r << 1 | r >> 31) ^ (r | (r >> 1 | r << 31));
    }
    m_generatedWolfram = StdVectorBoolToStdVectorUint8_t(stdVectorBool);
    std::cout << "time to generate Wolfram on " << m_numberOfBit << " bit = " << float(std::clock() - begin_time) / CLOCKS_PER_SEC << std::endl;
    m_generatedPRBS = m_generatedWolfram;
}

void PRBgenerators::generateLibrarian()
{
    m_generatedLibrarian.clear();
    std::clock_t begin_time = std::clock();
    uint32_t numberOfByte = m_numberOfBit & 7 ? (m_numberOfBit >> 3) + 1 : m_numberOfBit >> 3;
    m_generatedLibrarian.reserve(numberOfByte);
    std::string randomStdString;
    QFile fileRandomString("../Cherry/src/PRBgenerators/generateLibrarian.txt");
    if(fileRandomString.open(QFile::ReadOnly))
    {
        QString randomQString = fileRandomString.readLine();
        randomStdString = randomQString.toStdString();
        fileRandomString.close();
    }
    for(uint32_t indexByte = 0; indexByte < numberOfByte; ++indexByte)
    {
        m_generatedLibrarian.push_back(randomStdString[indexByte]);
    }
    std::cout << "time to generate Librarian on " << m_numberOfBit << " bit = " << float(std::clock() - begin_time) / CLOCKS_PER_SEC << std::endl;
    m_generatedPRBS = m_generatedLibrarian;
}

void PRBgenerators::generateBlumMicaliBit()
{
    std::clock_t begin_time = std::clock();
    const BigInt a("5B88C41246790891C095E2878880342E88C79974303BD0400B090FE38A688356", 16);
    const BigInt p("CEA42B987C44FA642D80AD9F51F10457690DEF10C83D0BC1BCEE12FC3B6093E3", 16); // p = 2 * q + 1
    const BigInt q("675215CC3E227D3216C056CFA8F8822BB486F788641E85E0DE77097E1DB049F1", 16); // q = (p - 1) / 2
    std::vector<bool> stdVectorBool;
    stdVectorBool.reserve(m_numberOfBit);
    srand(time(NULL));
    BigInt T(rand());
    for(uint32_t indexBit = 0; indexBit < m_numberOfBit; ++indexBit)
    {
        stdVectorBool.push_back(T < q);
        T = powmod(a, T, p);
    }
    m_generatedBlumMicaliBit = StdVectorBoolToStdVectorUint8_t(stdVectorBool);
    std::cout << "time to generate BlumMicaliBit on " << m_numberOfBit << " bit = " << float(std::clock() - begin_time) / CLOCKS_PER_SEC << std::endl;
    m_generatedPRBS = m_generatedBlumMicaliBit;
}

void PRBgenerators::generateBlumMicaliByte()
{
    m_generatedBlumMicaliByte.clear();
    std::clock_t begin_time = std::clock();
    const BigInt a("5B88C41246790891C095E2878880342E88C79974303BD0400B090FE38A688356", 16);
    const BigInt p("CEA42B987C44FA642D80AD9F51F10457690DEF10C83D0BC1BCEE12FC3B6093E3", 16); // p = 2 * q + 1
    const BigInt q("675215CC3E227D3216C056CFA8F8822BB486F788641E85E0DE77097E1DB049F1", 16); // q = (p - 1) / 2
    uint32_t numberOfByte = m_numberOfBit & 7 ? (m_numberOfBit >> 3) + 1 : m_numberOfBit >> 3;
    m_generatedBlumMicaliByte.reserve(numberOfByte);
    srand(time(NULL));
    BigInt T(rand());
    for(uint32_t indexByte = 0; indexByte < numberOfByte; ++indexByte)
    {
        m_generatedBlumMicaliByte.push_back((((T << 7) / q) - BigInt(1)).toUint32_t()); // T << 7 = T * 128
        T = powmod(a, T, p);
    }
    std::cout << "time to generate BlumMicaliByte on " << m_numberOfBit << " bit = " << float(std::clock() - begin_time) / CLOCKS_PER_SEC << std::endl;
    m_generatedPRBS = m_generatedBlumMicaliByte;
}

void PRBgenerators::generateBlumBlumShubBit()
{
    std::clock_t begin_time = std::clock();
    //const BigInt p("D5BBB96D30086EC484EBA3D7F9CAEB07", 16);
    //const BigInt q("425D2B9BFDB25B9CF6C416CC6E37B59C1F", 16);
    const BigInt n("37682f6947aaab110517c20b76df64781da78b3e87eb58379085d3395793bdb9d9", 16); // p * q
    std::vector<bool> stdVectorBool;
    stdVectorBool.reserve(m_numberOfBit);
    srand(time(NULL));
    BigInt r(rand() + 2);
    for(uint32_t indexBit = 0; indexBit < m_numberOfBit; ++indexBit)
    {
        stdVectorBool.push_back(r.isOdd());
        r = powmod(r, BigInt(2), n);
    }
    m_generatedBlumBlumShubBit = StdVectorBoolToStdVectorUint8_t(stdVectorBool);
    std::cout << "time to generate BlumBlumShubBit on " << m_numberOfBit << " bit = " << float(std::clock() - begin_time) / CLOCKS_PER_SEC << std::endl;
    m_generatedPRBS = m_generatedBlumBlumShubBit;
}

void PRBgenerators::generateBlumBlumShubByte()
{
    m_generatedBlumBlumShubByte.clear();
    std::clock_t begin_time = std::clock();
    //const BigInt p("D5BBB96D30086EC484EBA3D7F9CAEB07", 16);
    //const BigInt q("425D2B9BFDB25B9CF6C416CC6E37B59C1F", 16);
    const BigInt n("37682f6947aaab110517c20b76df64781da78b3e87eb58379085d3395793bdb9d9", 16); // p * q
    uint32_t numberOfByte = m_numberOfBit & 7 ? (m_numberOfBit >> 3) + 1 : m_numberOfBit >> 3;
    m_generatedBlumBlumShubByte.reserve(numberOfByte);
    srand(time(NULL));
    BigInt r(rand() + 2);
    for(uint32_t indexByte = 0; indexByte < numberOfByte; ++indexByte)
    {
        m_generatedBlumBlumShubByte.push_back((r & BigInt(UINT8_MAX)).toUint32_t()); // r & 255 = r % 256
        r = powmod(r, BigInt(2), n);
    }
    std::cout << "time to generate BlumBlumShubByte on " << m_numberOfBit << " bit = " << float(std::clock() - begin_time) / CLOCKS_PER_SEC << std::endl;
    m_generatedPRBS = m_generatedBlumBlumShubByte;
}

bool PRBgenerators::testOfGoodnessOfFit() const
{
    const float n = m_generatedPRBS.size() / 256;
    std::vector<uint32_t> byteFrequency;
    byteFrequency.resize(UINT8_MAX + 1, 0);
    for(std::vector<uint8_t>::const_iterator iteratorStdVectorUint8_t = m_generatedPRBS.cbegin(); iteratorStdVectorUint8_t != m_generatedPRBS.cend(); ++iteratorStdVectorUint8_t)
    {
        ++byteFrequency[*iteratorStdVectorUint8_t];
    }
    float ChiSquare = 0.0;
    uint8_t byte = 0;
    do
    {
        ChiSquare += std::pow(byteFrequency[byte] - n, 2) / n;
    }
    while(++byte);
    float ChiSquare_1minusAlpha = std::sqrt(2 * UINT8_MAX) * Z_1minusAlpha + UINT8_MAX;
    return ChiSquare <= ChiSquare_1minusAlpha;
}

bool PRBgenerators::testOfHomogeneity() const
{
    const uint32_t numberOfSegment = 16;
    const uint32_t lenghtOfSegment = m_generatedPRBS.size() / numberOfSegment;
    const uint32_t numberOfByte = numberOfSegment * lenghtOfSegment;
    std::vector<uint32_t> byteFrequency;
    byteFrequency.resize(UINT8_MAX + 1, 0);
    for(std::vector<uint8_t>::const_iterator iteratorStdVectorUint8_t = m_generatedPRBS.cbegin(); iteratorStdVectorUint8_t != m_generatedPRBS.cend(); ++iteratorStdVectorUint8_t)
    {
        ++byteFrequency[*iteratorStdVectorUint8_t];
    }
    float ChiSquare = 0.0;
    uint8_t byte = 0;
    do
    {
        std::vector<uint8_t>::const_iterator iteratorStdVectorUint8_t = m_generatedPRBS.cbegin();
        for(uint32_t indexSegment = 0; indexSegment < numberOfSegment; ++indexSegment)
        {
            ChiSquare += (std::pow(std::count(iteratorStdVectorUint8_t, iteratorStdVectorUint8_t + lenghtOfSegment - 1, byte), 2) * numberOfByte) / (byteFrequency[byte] * lenghtOfSegment);
            iteratorStdVectorUint8_t += lenghtOfSegment;
        }
    }
    while(++byte);
    ChiSquare -= numberOfByte;
    float ChiSquare_1minusAlpha = std::sqrt(2 * UINT8_MAX * (numberOfSegment - 1)) * Z_1minusAlpha + UINT8_MAX * (numberOfSegment - 1);
    return ChiSquare <= ChiSquare_1minusAlpha;
}

bool PRBgenerators::testOfIndependence() const
{
    const uint32_t numberOfBytePair = m_generatedPRBS.size() >> 1;
    std::vector<uint32_t> bytePairFrequency;
    std::vector<uint32_t> byteFirstFrequency;
    std::vector<uint32_t> byteSecondFrequency;
    bytePairFrequency.resize(UINT16_MAX + 1, 0);
    byteFirstFrequency.resize(UINT8_MAX + 1, 0);
    byteSecondFrequency.resize(UINT8_MAX + 1, 0);
    for(std::vector<uint8_t>::const_iterator iteratorStdVectorUint8_t = m_generatedPRBS.cbegin(); iteratorStdVectorUint8_t != (m_generatedPRBS.size() & 1 ? std::prev(m_generatedPRBS.cend()) : m_generatedPRBS.cend()); ++iteratorStdVectorUint8_t)
    {
        ++byteFirstFrequency[*iteratorStdVectorUint8_t];
        ++byteSecondFrequency[*(iteratorStdVectorUint8_t + 1)];
        ++bytePairFrequency[(uint16_t)(*iteratorStdVectorUint8_t << 8) | *(iteratorStdVectorUint8_t + 1)];
        ++iteratorStdVectorUint8_t;
    }
    float ChiSquare = 0;
    uint16_t bytePair = 0;
    do
    {
        ChiSquare += (std::pow(bytePairFrequency[bytePair], 2) * numberOfBytePair) / (byteFirstFrequency[bytePair >> 8] * byteSecondFrequency[bytePair & UINT8_MAX]);
    }
    while(++bytePair);
    ChiSquare -= numberOfBytePair;
    float ChiSquare_1minusAlpha = std::sqrt(2) * UINT8_MAX * Z_1minusAlpha + std::pow(UINT8_MAX, 2);
    return ChiSquare <= ChiSquare_1minusAlpha;
}

std::vector<uint8_t> StdVectorBoolToStdVectorUint8_t(const std::vector<bool>& stdVectorBool)
{
    std::vector<uint8_t> stdVectorUint8_t;
    stdVectorUint8_t.reserve(stdVectorBool.size() & 7 ? (stdVectorBool.size() >> 3) + 1 : stdVectorBool.size() >> 3);
    std::vector<bool>::const_iterator iteratorStdVectorBool = stdVectorBool.begin();
    uint8_t carry = stdVectorBool.size() & 7;
    if(carry)
    {
        uint8_t byte = 0;
        while(carry)
        {
            byte |= *iteratorStdVectorBool << --carry;
            ++iteratorStdVectorBool;
        }
        stdVectorUint8_t.push_back(byte);
    }
    while(iteratorStdVectorBool != stdVectorBool.end())
    {
        uint8_t byte = 0;
        for(uint32_t indexBit = 0; indexBit < 8; ++indexBit)
        {
            byte |= *iteratorStdVectorBool << (7 - indexBit);
            ++iteratorStdVectorBool;
        }
        stdVectorUint8_t.push_back(byte);
    }
    return stdVectorUint8_t;
}

QString StdVectorUint8_tToQString(const std::vector<uint8_t>& stdVectorUint8_t)
{
    QString qStringPRBS;
    for(std::vector<uint8_t>::const_iterator iteratorStdVectorUint8_t = stdVectorUint8_t.cbegin(); iteratorStdVectorUint8_t != stdVectorUint8_t.cend(); ++iteratorStdVectorUint8_t)
    {
        qStringPRBS.append(QString::number(*iteratorStdVectorUint8_t, 2));
    }
    return qStringPRBS;
}
