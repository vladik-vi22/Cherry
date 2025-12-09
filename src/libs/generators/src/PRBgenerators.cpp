#include <generators/PRBgenerators.h>
#define TRACK_TIME false

double PRBgenerators::Z_1minusAlpha;

PRBgenerators::PRBgenerators(QObject* parent): QObject(parent)
{
    srand(static_cast<unsigned int>(time(NULL)));
}

PRBgenerators::~PRBgenerators()
{
}

QString PRBgenerators::getNumberOfBits() const
{
    return QString::number(m_numberOfBits);
}

QString PRBgenerators::getAlpha() const
{
    return QString::number(m_alpha);
}

QString PRBgenerators::getNumberOfSegments() const
{
    return QString::number(m_numberOfSegments);
}

std::vector<uint8_t> PRBgenerators::getGeneratedPRBS() const
{
    return m_generatedPRBS;
}

uint8_t PRBgenerators::getUint8_tGeneratedPRBS() const
{
    if(m_generatedPRBS.size() == 1)
    {
        return m_generatedPRBS.front();
    }
    else
    {
        return 0;
    }
}

uint16_t PRBgenerators::getUint16_tGeneratedPRBS() const
{
    if(m_generatedPRBS.size() == 2)
    {
        return static_cast<uint16_t>((static_cast<uint16_t>(m_generatedPRBS.front()) << 8)) | static_cast<uint16_t>(m_generatedPRBS.back());
    }
    else if(m_generatedPRBS.size() == 1)
    {
        return static_cast<uint16_t>(m_generatedPRBS.front());
    }
    else
    {
        return 0;
    }
}

uint32_t PRBgenerators::getUint32_tGeneratedPRBS() const
{
    uint32_t result = 0;
    if(m_generatedPRBS.size() <= 4)
    {
        for(uint8_t indexByte = 0; indexByte < m_generatedPRBS.size(); ++indexByte)
        {
            result |= (uint32_t(m_generatedPRBS[indexByte]) << ((m_generatedPRBS.size() - indexByte - 1) * 8));
        }
        return result;
    }
    else
    {
        return 0;
    }
}

uint64_t PRBgenerators::getUint64_tGeneratedPRBS() const
{
    uint64_t result = 0;
    if(m_generatedPRBS.size() <= 8)
    {
        for(uint8_t indexByte = 0; indexByte < m_generatedPRBS.size(); ++indexByte)
        {
            result |= (uint64_t(m_generatedPRBS[indexByte]) << ((m_generatedPRBS.size() - indexByte - 1) * 8));
        }
        return result;
    }
    else
    {
        return 0;
    }
}

void PRBgenerators::setNumberOfBits(const QString& new_numberOfBits)
{
    if(QString::number(m_numberOfBits) != new_numberOfBits)
    {
        m_numberOfBits = new_numberOfBits.toULong();
        emit numberOfBitsChanged();
    }
}

void PRBgenerators::setNumberOfBits(const size_t new_numberOfBits)
{
    if(m_numberOfBits != new_numberOfBits)
    {
        m_numberOfBits = new_numberOfBits;
        emit numberOfBitsChanged();
    }
}

void PRBgenerators::setNumberOfBytes(const size_t new_numberOfBytes)
{
    if(m_numberOfBits != new_numberOfBytes * 8)
    {
        m_numberOfBits = new_numberOfBytes * 8;
        emit numberOfBitsChanged();
    }
}

void PRBgenerators::setAlpha(const QString& new_alpha)
{
    if(QString::number(m_alpha) != new_alpha)
    {
        m_alpha = new_alpha.toDouble();
        switch(static_cast<int>(m_alpha * 100.1))
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
        default: // m_alpha = 0.05
            Z_1minusAlpha = 1.645;
            break;
        }
        emit alphaChanged();
    }
}

void PRBgenerators::setNumberOfSegments(const QString& new_numberOfSegments)
{
    if(QString::number(m_numberOfSegments) != new_numberOfSegments)
    {
        m_numberOfSegments = new_numberOfSegments.toULong();
        emit numberOfSegmentsChanged();
    }
}

QString PRBgenerators::getQStringGeneratedPRBS() const
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

void PRBgenerators::generateBuiltInCPPBit()
{
#if TRACK_TIME
    std::clock_t begin_time = std::clock();
#endif
    std::vector<bool> stdVectorBool;
    stdVectorBool.reserve(m_numberOfBits);
    for(uint32_t indexBit = 0; indexBit < m_numberOfBits; ++indexBit)
    {
        stdVectorBool.emplace_back(std::rand() & 1);
    }
    m_generatedPRBS = StdVectorBoolToStdVectorUint8_t(stdVectorBool);
#if TRACK_TIME
    std::cout << "time to generate BuiltInCPPBit on " << m_numberOfBits << " bits = " << float(std::clock() - begin_time) / CLOCKS_PER_SEC << std::endl;
#endif
}

void PRBgenerators::generateBuiltInCPPByte()
{
#if TRACK_TIME
    std::clock_t begin_time = std::clock();
#endif
    m_generatedPRBS.clear();
    size_t numberOfBytes = m_numberOfBits & 7 ? (m_numberOfBits >> 3) + 1 : m_numberOfBits >> 3;
    m_generatedPRBS.reserve(numberOfBytes);
    for(size_t indexByte = 0; indexByte < numberOfBytes; ++indexByte)
    {
        m_generatedPRBS.emplace_back(std::rand() & UINT8_MAX);
    }
#if TRACK_TIME
    std::cout << "time to generate BuiltInCPPByte on " << m_numberOfBits << " bits = " << float(std::clock() - begin_time) / CLOCKS_PER_SEC << std::endl;
#endif
}

void PRBgenerators::generateLehmerLow()
{
#if TRACK_TIME
    std::clock_t begin_time = std::clock();
#endif
    m_generatedPRBS.clear();
    const uint32_t a = 65537;
    const uint32_t c = 119;
    size_t numberOfBytes = m_numberOfBits & 7 ? (m_numberOfBits >> 3) + 1 : m_numberOfBits >> 3;
    m_generatedPRBS.reserve(numberOfBytes);
    uint32_t lehmerUint32_t = static_cast<uint32_t>(std::rand() + 1);
    for(size_t indexByte = 0; indexByte < numberOfBytes; ++indexByte)
    {
        m_generatedPRBS.emplace_back(lehmerUint32_t & UINT8_MAX);
        lehmerUint32_t = a * lehmerUint32_t + c;
    }
#if TRACK_TIME
    std::cout << "time to generate LehmerLow on " << m_numberOfBits << " bits = " << float(std::clock() - begin_time) / CLOCKS_PER_SEC << std::endl;
#endif
}

void PRBgenerators::generateLehmerHigh()
{
#if TRACK_TIME
    std::clock_t begin_time = std::clock();
#endif
    m_generatedPRBS.clear();
    const uint32_t a = 65537;
    const uint32_t c = 119;
    size_t numberOfBytes = m_numberOfBits & 7 ? (m_numberOfBits >> 3) + 1 : m_numberOfBits >> 3;
    m_generatedPRBS.reserve(numberOfBytes);
    uint32_t lehmerUint32_t = static_cast<uint32_t>(std::rand() + 1);
    for(size_t indexByte = 0; indexByte < numberOfBytes; ++indexByte)
    {
        m_generatedPRBS.emplace_back(lehmerUint32_t >> 24);
        lehmerUint32_t = a * lehmerUint32_t + c;
    }
#if TRACK_TIME
    std::cout << "time to generate LehmerHigh on " << m_numberOfBits << " bits = " << float(std::clock() - begin_time) / CLOCKS_PER_SEC << std::endl;
#endif
}

void PRBgenerators::generateL20()
{
#if TRACK_TIME
    std::clock_t begin_time = std::clock();
#endif
    if(m_numberOfBits < 20)
    {
        generateBuiltInCPPBit();
        return;
    }
    std::vector<bool> stdVectorBool;
    stdVectorBool.reserve(m_numberOfBits);
    stdVectorBool.resize(m_numberOfBits);
    std::vector<bool>::iterator iteratorStdVectorBool = stdVectorBool.begin();
    for(uint8_t indexFirst20Bit = 0; indexFirst20Bit < 20; ++indexFirst20Bit)
    {
        *iteratorStdVectorBool = std::rand() & 1;
        ++iteratorStdVectorBool;
    }
    while(iteratorStdVectorBool != stdVectorBool.end())
    {
        *iteratorStdVectorBool = *(iteratorStdVectorBool - 3) ^ *(iteratorStdVectorBool - 5) ^ *(iteratorStdVectorBool - 9) ^ *(iteratorStdVectorBool - 20);
        ++iteratorStdVectorBool;
    }
    m_generatedPRBS = StdVectorBoolToStdVectorUint8_t(stdVectorBool);
#if TRACK_TIME
    std::cout << "time to generate L20 on " << m_numberOfBits << " bits = " << float(std::clock() - begin_time) / CLOCKS_PER_SEC << std::endl;
#endif
}

void PRBgenerators::generateL89()
{
#if TRACK_TIME
    std::clock_t begin_time = std::clock();
#endif
    if(m_numberOfBits < 89)
    {
        generateBuiltInCPPBit();
        return;
    }
    std::vector<bool> stdVectorBool;
    stdVectorBool.reserve(m_numberOfBits);
    stdVectorBool.resize(m_numberOfBits);
    std::vector<bool>::iterator iteratorStdVectorBool = stdVectorBool.begin();
    for(uint8_t indexFirst89Bit = 0; indexFirst89Bit < 89; ++indexFirst89Bit)
    {
        *iteratorStdVectorBool = std::rand() & 1;
        ++iteratorStdVectorBool;
    }
    while(iteratorStdVectorBool != stdVectorBool.end())
    {
        *iteratorStdVectorBool = *(iteratorStdVectorBool - 38) ^ *(iteratorStdVectorBool - 89);
        ++iteratorStdVectorBool;
    }
    m_generatedPRBS = StdVectorBoolToStdVectorUint8_t(stdVectorBool);
#if TRACK_TIME
    std::cout << "time to generate L89 on " << m_numberOfBits << " bits = " << float(std::clock() - begin_time) / CLOCKS_PER_SEC << std::endl;
#endif
}

void PRBgenerators::generateGeffe()
{
#if TRACK_TIME
    std::clock_t begin_time = std::clock();
#endif
    if(m_numberOfBits < 11)
    {
        generateBuiltInCPPBit();
        return;
    }
    std::vector<bool> stdVectorBool;
    std::vector<bool> stdVectorBoolL9;
    std::vector<bool> stdVectorBoolL10;
    std::vector<bool> stdVectorBoolL11;
    stdVectorBool.reserve(m_numberOfBits);
    stdVectorBool.resize(m_numberOfBits);
    stdVectorBoolL9.reserve(m_numberOfBits);
    stdVectorBoolL9.resize(m_numberOfBits);
    stdVectorBoolL10.reserve(m_numberOfBits);
    stdVectorBoolL10.resize(m_numberOfBits);
    stdVectorBoolL11.reserve(m_numberOfBits);
    stdVectorBoolL11.resize(m_numberOfBits);
    std::vector<bool>::iterator iteratorStdVectorBool = stdVectorBool.begin();
    std::vector<bool>::iterator iteratorStdVectorBoolL9 = stdVectorBoolL9.begin();
    std::vector<bool>::iterator iteratorStdVectorBoolL10 = stdVectorBoolL10.begin();
    std::vector<bool>::iterator iteratorStdVectorBoolL11 = stdVectorBoolL11.begin();
    for(uint8_t indexFirst9Bit = 0; indexFirst9Bit < 9; ++indexFirst9Bit)
    {
        *iteratorStdVectorBoolL9 = std::rand() & 1;
        *iteratorStdVectorBoolL10 = std::rand() & 1;
        *iteratorStdVectorBoolL11 = std::rand() & 1;
        *iteratorStdVectorBool = (*iteratorStdVectorBoolL10 & *iteratorStdVectorBoolL11) ^ ((1 ^ *iteratorStdVectorBoolL10) & *iteratorStdVectorBoolL9);
        ++iteratorStdVectorBool;
        ++iteratorStdVectorBoolL9;
        ++iteratorStdVectorBoolL10;
        ++iteratorStdVectorBoolL11;
    }

    *iteratorStdVectorBoolL9 = *(iteratorStdVectorBoolL9 - 9) ^ *(iteratorStdVectorBoolL9 - 8) ^ *(iteratorStdVectorBoolL9 - 6) ^ *(iteratorStdVectorBoolL9 - 5);
    *iteratorStdVectorBoolL10 = std::rand() & 1;
    *iteratorStdVectorBoolL11 = std::rand() & 1;
    *iteratorStdVectorBool = (*iteratorStdVectorBoolL10 & *iteratorStdVectorBoolL11) ^ ((1 ^ *iteratorStdVectorBoolL10) & *iteratorStdVectorBoolL9);
    ++iteratorStdVectorBool;
    ++iteratorStdVectorBoolL9;
    ++iteratorStdVectorBoolL10;
    ++iteratorStdVectorBoolL11;

    *iteratorStdVectorBoolL9 = *(iteratorStdVectorBoolL9 - 9) ^ *(iteratorStdVectorBoolL9 - 8) ^ *(iteratorStdVectorBoolL9 - 6) ^ *(iteratorStdVectorBoolL9 - 5);
    *iteratorStdVectorBoolL10 = *(iteratorStdVectorBoolL10 - 10) ^ *(iteratorStdVectorBoolL10 - 7);
    *iteratorStdVectorBoolL11 = std::rand() & 1;
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
    m_generatedPRBS = StdVectorBoolToStdVectorUint8_t(stdVectorBool);
#if TRACK_TIME
    std::cout << "time to generate Geffe on " << m_numberOfBits << " bits = " << float(std::clock() - begin_time) / CLOCKS_PER_SEC << std::endl;
#endif
}

void PRBgenerators::generateWolfram()
{
#if TRACK_TIME
    std::clock_t begin_time = std::clock();
#endif
    std::vector<bool> stdVectorBool;
    stdVectorBool.reserve(m_numberOfBits);
    uint32_t r = static_cast<uint32_t>(std::rand() + 1);
    for(uint32_t indexBit = 0; indexBit < m_numberOfBits; ++indexBit)
    {
        stdVectorBool.emplace_back(r & 1);
        r = (r << 1 | r >> 31) ^ (r | (r >> 1 | r << 31));
    }
    m_generatedPRBS = StdVectorBoolToStdVectorUint8_t(stdVectorBool);
#if TRACK_TIME
    std::cout << "time to generate Wolfram on " << m_numberOfBits << " bits = " << float(std::clock() - begin_time) / CLOCKS_PER_SEC << std::endl;
#endif
}

void PRBgenerators::generateLibrarian()
{
#if TRACK_TIME
    std::clock_t begin_time = std::clock();
#endif
    m_generatedPRBS.clear();
    size_t numberOfBytes = m_numberOfBits & 7 ? (m_numberOfBits >> 3) + 1 : m_numberOfBits >> 3;
    m_generatedPRBS.reserve(numberOfBytes);
    std::string randomStdString;
    QFile fileRandomString("../Cherry/src/PRBgenerators/generateLibrarian.txt");
    if(fileRandomString.open(QFile::ReadOnly))
    {
        QString randomQString = fileRandomString.readLine();
        randomStdString = randomQString.toStdString();
        fileRandomString.close();
    }

    for(size_t indexByte = 0; indexByte < numberOfBytes; ++indexByte)
    {
        m_generatedPRBS.emplace_back(static_cast<uint8_t>(randomStdString[indexByte]));
    }
#if TRACK_TIME
    std::cout << "time to generate Librarian on " << m_numberOfBits << " bits = " << float(std::clock() - begin_time) / CLOCKS_PER_SEC << std::endl;
#endif
}

void PRBgenerators::generateBlumMicaliBit()
{
#if TRACK_TIME
    std::clock_t begin_time = std::clock();
#endif
    const BigInt a("5B88C41246790891C095E2878880342E88C79974303BD0400B090FE38A688356", 16);
    const BigInt p("CEA42B987C44FA642D80AD9F51F10457690DEF10C83D0BC1BCEE12FC3B6093E3", 16); // p = 2 * q + 1
    const BigInt q("675215CC3E227D3216C056CFA8F8822BB486F788641E85E0DE77097E1DB049F1", 16); // q = (p - 1) / 2
    std::vector<bool> stdVectorBool;
    stdVectorBool.reserve(m_numberOfBits);
    BigInt T(rand());
    for(uint32_t indexBit = 0; indexBit < m_numberOfBits; ++indexBit)
    {
        stdVectorBool.emplace_back(T < q);
        T = powmod(a, T, p);
    }
    m_generatedPRBS = StdVectorBoolToStdVectorUint8_t(stdVectorBool);
#if TRACK_TIME
    std::cout << "time to generate BlumMicaliBit on " << m_numberOfBits << " bits = " << float(std::clock() - begin_time) / CLOCKS_PER_SEC << std::endl;
#endif
}

void PRBgenerators::generateBlumMicaliByte()
{
#if TRACK_TIME
    std::clock_t begin_time = std::clock();
#endif
    m_generatedPRBS.clear();
    const BigInt a("5B88C41246790891C095E2878880342E88C79974303BD0400B090FE38A688356", 16);
    const BigInt p("CEA42B987C44FA642D80AD9F51F10457690DEF10C83D0BC1BCEE12FC3B6093E3", 16); // p = 2 * q + 1
    const BigInt q("675215CC3E227D3216C056CFA8F8822BB486F788641E85E0DE77097E1DB049F1", 16); // q = (p - 1) / 2
    size_t numberOfBytes = m_numberOfBits & 7 ? (m_numberOfBits >> 3) + 1 : m_numberOfBits >> 3;
    m_generatedPRBS.reserve(numberOfBytes);
    BigInt T(rand());
    for(size_t indexByte = 0; indexByte < numberOfBytes; ++indexByte)
    {
        m_generatedPRBS.emplace_back(static_cast<uint8_t>(((T << size_t(7)) / q) - constants::ONE)); // T << 7 = T * 128
        T = powmod(a, T, p);
    }
#if TRACK_TIME
    std::cout << "time to generate BlumMicaliByte on " << m_numberOfBits << " bits = " << float(std::clock() - begin_time) / CLOCKS_PER_SEC << std::endl;
#endif
}

void PRBgenerators::generateBlumBlumShubBit()
{
#if TRACK_TIME
    std::clock_t begin_time = std::clock();
#endif
    std::vector<bool> stdVectorBool;
    //const BigInt p("D5BBB96D30086EC484EBA3D7F9CAEB07", 16);
    //const BigInt q("425D2B9BFDB25B9CF6C416CC6E37B59C1F", 16);
    const BigInt n("37682f6947aaab110517c20b76df64781da78b3e87eb58379085d3395793bdb9d9", 16); // p * q
    stdVectorBool.reserve(m_numberOfBits);
    BigInt r(rand() + 2);
    for(uint32_t indexBit = 0; indexBit < m_numberOfBits; ++indexBit)
    {
        stdVectorBool.emplace_back(r.isOdd());
        r = powmod(r, constants::TWO, n);
    }
    m_generatedPRBS = StdVectorBoolToStdVectorUint8_t(stdVectorBool);
#if TRACK_TIME
    std::cout << "time to generate BlumBlumShubBit on " << m_numberOfBits << " bits = " << float(std::clock() - begin_time) / CLOCKS_PER_SEC << std::endl;
#endif
}

void PRBgenerators::generateBlumBlumShubByte()
{
#if TRACK_TIME
    std::clock_t begin_time = std::clock();
#endif
    m_generatedPRBS.clear();
    //const BigInt p("D5BBB96D30086EC484EBA3D7F9CAEB07", 16);
    //const BigInt q("425D2B9BFDB25B9CF6C416CC6E37B59C1F", 16);
    const BigInt n("37682f6947aaab110517c20b76df64781da78b3e87eb58379085d3395793bdb9d9", 16); // p * q
    size_t numberOfBytes = m_numberOfBits & 7 ? (m_numberOfBits >> 3) + 1 : m_numberOfBits >> 3;
    m_generatedPRBS.reserve(numberOfBytes);
    BigInt r(rand() + 2);
    for(size_t indexByte = 0; indexByte < numberOfBytes; ++indexByte)
    {
        m_generatedPRBS.emplace_back(static_cast<uint8_t>(r & BigInt(UINT8_MAX))); // r & 255 = r % 256
        r = powmod(r, constants::TWO, n);
    }
#if TRACK_TIME
    std::cout << "time to generate BlumBlumShubByte on " << m_numberOfBits << " bits = " << float(std::clock() - begin_time) / CLOCKS_PER_SEC << std::endl;
#endif
}

bool PRBgenerators::testOfGoodnessOfFit() const
{
    const double n = m_generatedPRBS.size() / 256;
    std::vector<uint32_t> byteFrequency;
    byteFrequency.resize(UINT8_MAX + 1, 0);
    for(std::vector<uint8_t>::const_iterator iteratorStdVectorUint8_t = m_generatedPRBS.cbegin(); iteratorStdVectorUint8_t != m_generatedPRBS.cend(); ++iteratorStdVectorUint8_t)
    {
        ++byteFrequency[*iteratorStdVectorUint8_t];
    }
    double ChiSquare = 0;
    uint8_t byte = 0;
    do
    {
        ChiSquare += std::pow(byteFrequency[byte] - n, 2) / n;
    }
    while(++byte);
    double ChiSquare_1minusAlpha = std::sqrt(2 * UINT8_MAX) * Z_1minusAlpha + UINT8_MAX;
    std::cout << "ChiSquare             = " << ChiSquare << std::endl;
    std::cout << "ChiSquare_1minusAlpha = " << ChiSquare_1minusAlpha << std::endl;
    return ChiSquare <= ChiSquare_1minusAlpha;
}

bool PRBgenerators::testOfHomogeneity() const
{
    if(m_generatedPRBS.size() >= m_numberOfSegments)
    {
        const size_t lenghtOfSegment = m_generatedPRBS.size() / m_numberOfSegments;
        const size_t numberOfBytes = m_numberOfSegments * lenghtOfSegment;
        std::vector<uint32_t> byteFrequency;
        byteFrequency.resize(UINT8_MAX + 1, 0);
        for(std::vector<uint8_t>::const_iterator iteratorStdVectorUint8_t = m_generatedPRBS.cbegin(); iteratorStdVectorUint8_t != m_generatedPRBS.cend(); ++iteratorStdVectorUint8_t)
        {
            ++byteFrequency[*iteratorStdVectorUint8_t];
        }
        double ChiSquare = 0;
        uint8_t byte = 0;
        do
        {
            std::vector<uint8_t>::const_iterator iteratorStdVectorUint8_t = m_generatedPRBS.cbegin();
            for(uint32_t indexSegment = 0; indexSegment < m_numberOfSegments; ++indexSegment)
            {
                ChiSquare += (std::pow(std::count(iteratorStdVectorUint8_t, iteratorStdVectorUint8_t + static_cast<long>(lenghtOfSegment - 1), byte), 2) * numberOfBytes) / (byteFrequency[byte] * lenghtOfSegment);
                iteratorStdVectorUint8_t += static_cast<long>(lenghtOfSegment);
            }
        }
        while(++byte);
        ChiSquare -= numberOfBytes;
        double ChiSquare_1minusAlpha = std::sqrt(2 * UINT8_MAX * (m_numberOfSegments - 1)) * Z_1minusAlpha + UINT8_MAX * (m_numberOfSegments - 1);
        std::cout << "ChiSquare             = " << ChiSquare << std::endl;
        std::cout << "ChiSquare_1minusAlpha = " << ChiSquare_1minusAlpha << std::endl;
        return ChiSquare <= ChiSquare_1minusAlpha;
    }
    else
    {
        return false;
    }
}

bool PRBgenerators::testOfIndependence() const
{
    const size_t numberOfBytePairs = m_generatedPRBS.size() >> 1;
    std::vector<uint32_t> bytePairFrequency;
    std::vector<uint32_t> byteFirstFrequency;
    std::vector<uint32_t> byteSecondFrequency;
    bytePairFrequency.resize(UINT16_MAX + 1, 0);
    byteFirstFrequency.resize(UINT8_MAX + 1, 0);
    byteSecondFrequency.resize(UINT8_MAX + 1, 0);
    for(std::vector<uint8_t>::const_iterator iteratorStdVectorUint8_t = m_generatedPRBS.cbegin(); iteratorStdVectorUint8_t != (m_generatedPRBS.size() & 1 ? std::prev(m_generatedPRBS.cend()) : m_generatedPRBS.cend()); iteratorStdVectorUint8_t += 2)
    {
        ++byteFirstFrequency[*iteratorStdVectorUint8_t];
        ++byteSecondFrequency[*(iteratorStdVectorUint8_t + 1)];
        ++bytePairFrequency[static_cast<size_t>((static_cast<uint16_t>(*iteratorStdVectorUint8_t) << 8) | static_cast<uint16_t>(*(iteratorStdVectorUint8_t + 1)))];
    }
    double ChiSquare = 0;
    uint16_t bytePair = 0;
    do
    {
        ChiSquare += (std::pow(bytePairFrequency[bytePair], 2) * numberOfBytePairs) / (byteFirstFrequency[bytePair >> 8] * byteSecondFrequency[bytePair & UINT8_MAX]);
    }
    while(++bytePair);
    ChiSquare -= numberOfBytePairs;
    double ChiSquare_1minusAlpha = std::sqrt(2) * UINT8_MAX * Z_1minusAlpha + std::pow(UINT8_MAX, 2);
    std::cout << "ChiSquare             = " << ChiSquare << std::endl;
    std::cout << "ChiSquare_1minusAlpha = " << ChiSquare_1minusAlpha << std::endl;
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
        stdVectorUint8_t.emplace_back(byte);
    }
    while(iteratorStdVectorBool != stdVectorBool.end())
    {
        uint8_t byte = 0;
        for(uint32_t indexBit = 0; indexBit < 8; ++indexBit)
        {
            byte |= *iteratorStdVectorBool << (7 - indexBit);
            ++iteratorStdVectorBool;
        }
        stdVectorUint8_t.emplace_back(byte);
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
