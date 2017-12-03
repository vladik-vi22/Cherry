#include "PRBgenerators.h"

PRBgenerators::PRBgenerators(QObject* parent): QObject(parent)
{
}

PRBgenerators::~PRBgenerators()
{
}

void PRBgenerators::generateBuiltInCPP(const uint32_t& numberOfBit)
{
    m_generatedBuiltInCPP.clear();
    std::clock_t begin_time = std::clock();
    uint32_t numberOfByte = numberOfBit & 7 ? (numberOfBit >> 3) + 1 : numberOfBit >> 3;
    m_generatedBuiltInCPP.reserve(numberOfByte);
    srand(time(NULL));
    for(uint32_t indexByte = 0; indexByte < numberOfByte; ++indexByte)
    {
        m_generatedBuiltInCPP.push_back(rand() & UINT8_MAX);
    }
    std::cout << "time to generate BuiltInCPP on " << numberOfBit << " bit = " << float(std::clock() - begin_time) / CLOCKS_PER_SEC << std::endl;
    std::cout << "testEquiprobabilityByte " << testEquiprobabilityByte(m_generatedBuiltInCPP) << std::endl;
    std::cout << "testIndependenceByte    " << testIndependenceByte(m_generatedBuiltInCPP) << std::endl;
    std::cout << "testHomogeneity         " << testHomogeneity(m_generatedBuiltInCPP) << std::endl;
}

void PRBgenerators::generateLehmerLow(const uint32_t& numberOfBit)
{
    m_generatedLehmerLow.clear();
    std::clock_t begin_time = std::clock();
    const uint32_t a = 65537;
    const uint32_t c = 119;
    uint32_t numberOfByte = numberOfBit & 7 ? (numberOfBit >> 3) + 1 : numberOfBit >> 3;
    m_generatedLehmerLow.reserve(numberOfByte);
    srand(time(NULL));
    uint32_t lehmerUint32_t = rand() + 1;
    for(uint32_t indexByte = 0; indexByte < numberOfByte; ++indexByte)
    {
        m_generatedLehmerLow.push_back(lehmerUint32_t & UINT8_MAX);
        lehmerUint32_t = a * lehmerUint32_t + c;
    }
    std::cout << "time to generate LehmerLow on " << numberOfBit << " bit = " << float(std::clock() - begin_time) / CLOCKS_PER_SEC << std::endl;
    std::cout << "testEquiprobabilityByte " << testEquiprobabilityByte(m_generatedLehmerLow) << std::endl;
    std::cout << "testIndependenceByte    " << testIndependenceByte(m_generatedLehmerLow) << std::endl;
    std::cout << "testHomogeneity         " << testHomogeneity(m_generatedLehmerLow) << std::endl;
}

void PRBgenerators::generateLehmerHigh(const uint32_t& numberOfBit)
{
    m_generatedLehmerHigh.clear();
    std::clock_t begin_time = std::clock();
    const uint32_t a = 65537;
    const uint32_t c = 119;
    uint32_t numberOfByte = numberOfBit & 7 ? (numberOfBit >> 3) + 1 : numberOfBit >> 3;
    m_generatedLehmerHigh.reserve(numberOfByte);
    srand(time(NULL));
    uint32_t lehmerUint32_t = rand() + 1;
    for(uint32_t indexByte = 0; indexByte < numberOfByte; ++indexByte)
    {
        m_generatedLehmerHigh.push_back(lehmerUint32_t >> 24);
        lehmerUint32_t = a * lehmerUint32_t + c;
    }
    std::cout << "time to generate LehmerHigh on " << numberOfBit << " bit = " << float(std::clock() - begin_time) / CLOCKS_PER_SEC << std::endl;
    std::cout << "testEquiprobabilityByte " << testEquiprobabilityByte(m_generatedLehmerHigh) << std::endl;
    std::cout << "testIndependenceByte    " << testIndependenceByte(m_generatedLehmerHigh) << std::endl;
    std::cout << "testHomogeneity         " << testHomogeneity(m_generatedLehmerHigh) << std::endl;
}

void PRBgenerators::generateL20(const uint32_t& numberOfBit)
{
    std::clock_t begin_time = std::clock();
    std::vector<bool> stdVectorBool;
    stdVectorBool.reserve(numberOfBit);
    stdVectorBool.resize(numberOfBit);
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
    std::cout << "time to generate L20 on " << numberOfBit << " bit = " << float(std::clock() - begin_time) / CLOCKS_PER_SEC << std::endl;
    std::cout << "testEquiprobabilityByte " << testEquiprobabilityByte(m_generatedL20) << std::endl;
    std::cout << "testIndependenceByte    " << testIndependenceByte(m_generatedL20) << std::endl;
    std::cout << "testHomogeneity         " << testHomogeneity(m_generatedL20) << std::endl;
}

void PRBgenerators::generateL89(const uint32_t& numberOfBit)
{
    std::clock_t begin_time = std::clock();
    std::vector<bool> stdVectorBool;
    stdVectorBool.reserve(numberOfBit);
    stdVectorBool.resize(numberOfBit);
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
    std::cout << "time to generate L89 on " << numberOfBit << " bit = " << float(std::clock() - begin_time) / CLOCKS_PER_SEC << std::endl;
    std::cout << "testEquiprobabilityByte " << testEquiprobabilityByte(m_generatedL89) << std::endl;
    std::cout << "testIndependenceByte    " << testIndependenceByte(m_generatedL89) << std::endl;
    std::cout << "testHomogeneity         " << testHomogeneity(m_generatedL89) << std::endl;
}

void PRBgenerators::generateGeffe(const uint32_t& numberOfBit)
{
    std::clock_t begin_time = std::clock();
    std::vector<bool> stdVectorBool;
    std::vector<bool> stdVectorBoolL9;
    std::vector<bool> stdVectorBoolL10;
    std::vector<bool> stdVectorBoolL11;
    stdVectorBool.reserve(numberOfBit);
    stdVectorBool.resize(numberOfBit);
    stdVectorBoolL9.reserve(numberOfBit);
    stdVectorBoolL9.resize(numberOfBit);
    stdVectorBoolL10.reserve(numberOfBit);
    stdVectorBoolL10.resize(numberOfBit);
    stdVectorBoolL11.reserve(numberOfBit);
    stdVectorBoolL11.resize(numberOfBit);
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
        *iteratorStdVectorBool = (*iteratorStdVectorBoolL10 * *iteratorStdVectorBoolL11) ^ ((1 ^ *iteratorStdVectorBoolL10) * *iteratorStdVectorBoolL9);
        ++iteratorStdVectorBool;
        ++iteratorStdVectorBoolL9;
        ++iteratorStdVectorBoolL10;
        ++iteratorStdVectorBoolL11;
    }
    m_generatedGeffe = StdVectorBoolToStdVectorUint8_t(stdVectorBool);
    std::cout << "time to generate Geffe on " << numberOfBit << " bit = " << float(std::clock() - begin_time) / CLOCKS_PER_SEC << std::endl;
    std::cout << "testEquiprobabilityByte " << testEquiprobabilityByte(m_generatedGeffe) << std::endl;
    std::cout << "testIndependenceByte    " << testIndependenceByte(m_generatedGeffe) << std::endl;
    std::cout << "testHomogeneity         " << testHomogeneity(m_generatedGeffe) << std::endl;
}

void PRBgenerators::generateWolfram(const uint32_t& numberOfBit)
{
    std::clock_t begin_time = std::clock();
    std::vector<bool> stdVectorBool;
    stdVectorBool.reserve(numberOfBit);
    srand(time(NULL));
    uint32_t r = rand() + 1;
    for(uint32_t indexBit = 0; indexBit < numberOfBit; ++indexBit)
    {
        stdVectorBool.push_back(r & 1);
        r = (r << 1) ^ (r | (r >> 1));
    }
    m_generatedWolfram = StdVectorBoolToStdVectorUint8_t(stdVectorBool);
    std::cout << "time to generate Wolfram on " << numberOfBit << " bit = " << float(std::clock() - begin_time) / CLOCKS_PER_SEC << std::endl;
    std::cout << "testEquiprobabilityByte " << testEquiprobabilityByte(m_generatedWolfram) << std::endl;
    std::cout << "testIndependenceByte    " << testIndependenceByte(m_generatedWolfram) << std::endl;
    std::cout << "testHomogeneity         " << testHomogeneity(m_generatedWolfram) << std::endl;
}

void PRBgenerators::generateLibrarian(const uint32_t& numberOfBit)
{
    m_generatedLibrarian.clear();
    std::clock_t begin_time = std::clock();
    uint32_t numberOfByte = numberOfBit & 7 ? (numberOfBit >> 3) + 1 : numberOfBit >> 3;
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
    std::cout << "time to generate Librarian on " << numberOfBit << " bit = " << float(std::clock() - begin_time) / CLOCKS_PER_SEC << std::endl;
    std::cout << "testEquiprobabilityByte " << testEquiprobabilityByte(m_generatedLibrarian) << std::endl;
    std::cout << "testIndependenceByte    " << testIndependenceByte(m_generatedLibrarian) << std::endl;
    std::cout << "testHomogeneity         " << testHomogeneity(m_generatedLibrarian) << std::endl;
}

void PRBgenerators::generateBlumMikaliBit(const uint32_t& numberOfBit)
{
    std::clock_t begin_time = std::clock();
    const BigInt a("5B88C41246790891C095E2878880342E88C79974303BD0400B090FE38A688356", 16);
    const BigInt p("CEA42B987C44FA642D80AD9F51F10457690DEF10C83D0BC1BCEE12FC3B6093E3", 16); // p = 2 * q + 1
    const BigInt q("675215CC3E227D3216C056CFA8F8822BB486F788641E85E0DE77097E1DB049F1", 16); // q = (p - 1) / 2
    std::vector<bool> stdVectorBool;
    stdVectorBool.reserve(numberOfBit);
    srand(time(NULL));
    BigInt T(rand());
    for(uint32_t indexBit = 0; indexBit < numberOfBit; ++indexBit)
    {
        stdVectorBool.push_back(T < q);
        T = powmod(a, T, p);
    }
    m_generatedBlumMikaliBit = StdVectorBoolToStdVectorUint8_t(stdVectorBool);
    std::cout << "time to generate BlumMikaliBit on " << numberOfBit << " bit = " << float(std::clock() - begin_time) / CLOCKS_PER_SEC << std::endl;
    std::cout << "testEquiprobabilityByte " << testEquiprobabilityByte(m_generatedBlumMikaliBit) << std::endl;
    std::cout << "testIndependenceByte    " << testIndependenceByte(m_generatedBlumMikaliBit) << std::endl;
    std::cout << "testHomogeneity         " << testHomogeneity(m_generatedBlumMikaliBit) << std::endl;
}

void PRBgenerators::generateBlumMikaliByte(const uint32_t& numberOfBit)
{
    m_generatedBlumMikaliByte.clear();
    std::clock_t begin_time = std::clock();
    const BigInt a("5B88C41246790891C095E2878880342E88C79974303BD0400B090FE38A688356", 16);
    const BigInt p("CEA42B987C44FA642D80AD9F51F10457690DEF10C83D0BC1BCEE12FC3B6093E3", 16); // p = 2 * q + 1
    const BigInt q("675215CC3E227D3216C056CFA8F8822BB486F788641E85E0DE77097E1DB049F1", 16); // q = (p - 1) / 2
    uint32_t numberOfByte = numberOfBit & 7 ? (numberOfBit >> 3) + 1 : numberOfBit >> 3;
    m_generatedBlumMikaliByte.reserve(numberOfByte);
    srand(time(NULL));
    BigInt T(rand());
    for(uint32_t indexByte = 0; indexByte < numberOfByte; ++indexByte)
    {
        m_generatedBlumMikaliByte.push_back((((T << 7) / q) - BigInt(1)).toUint32_t()); // T << 7 = T * 128
        T = powmod(a, T, p);
    }
    std::cout << "time to generate BlumMikaliByte on " << numberOfBit << " bit = " << float(std::clock() - begin_time) / CLOCKS_PER_SEC << std::endl;
    std::cout << "testEquiprobabilityByte " << testEquiprobabilityByte(m_generatedBlumMikaliByte) << std::endl;
    std::cout << "testIndependenceByte    " << testIndependenceByte(m_generatedBlumMikaliByte) << std::endl;
    std::cout << "testHomogeneity         " << testHomogeneity(m_generatedBlumMikaliByte) << std::endl;
}

void PRBgenerators::generateBlumBlumShubBit(const uint32_t& numberOfBit)
{
    std::clock_t begin_time = std::clock();
    //const BigInt p("D5BBB96D30086EC484EBA3D7F9CAEB07", 16);
    //const BigInt q("425D2B9BFDB25B9CF6C416CC6E37B59C1F", 16);
    const BigInt n("37682f6947aaab110517c20b76df64781da78b3e87eb58379085d3395793bdb9d9", 16); // p * q
    std::vector<bool> stdVectorBool;
    stdVectorBool.reserve(numberOfBit);
    srand(time(NULL));
    BigInt r(rand() + 2);
    for(uint32_t indexBit = 0; indexBit < numberOfBit; ++indexBit)
    {
        stdVectorBool.push_back(r.isOdd());
        r = powmod(r, BigInt(2), n);
    }
    m_generatedBlumBlumShubBit = StdVectorBoolToStdVectorUint8_t(stdVectorBool);
    std::cout << "time to generate BlumBlumShubBit on " << numberOfBit << " bit = " << float(std::clock() - begin_time) / CLOCKS_PER_SEC << std::endl;
    std::cout << "testEquiprobabilityByte " << testEquiprobabilityByte(m_generatedBlumBlumShubBit) << std::endl;
    std::cout << "testIndependenceByte    " << testIndependenceByte(m_generatedBlumBlumShubBit) << std::endl;
    std::cout << "testHomogeneity         " << testHomogeneity(m_generatedBlumBlumShubBit) << std::endl;
}

void PRBgenerators::generateBlumBlumShubByte(const uint32_t& numberOfBit)
{
    m_generatedBlumBlumShubByte.clear();
    std::clock_t begin_time = std::clock();
    //const BigInt p("D5BBB96D30086EC484EBA3D7F9CAEB07", 16);
    //const BigInt q("425D2B9BFDB25B9CF6C416CC6E37B59C1F", 16);
    const BigInt n("37682f6947aaab110517c20b76df64781da78b3e87eb58379085d3395793bdb9d9", 16); // p * q
    uint32_t numberOfByte = numberOfBit & 7 ? (numberOfBit >> 3) + 1 : numberOfBit >> 3;
    m_generatedBlumBlumShubByte.reserve(numberOfByte);
    srand(time(NULL));
    BigInt r(rand() + 2);
    for(uint32_t indexByte = 0; indexByte < numberOfByte; ++indexByte)
    {
        m_generatedBlumBlumShubByte.push_back((r & BigInt(UINT8_MAX)).toUint32_t()); // r & 255 = r % 256
        r = powmod(r, BigInt(2), n);
    }
    std::cout << "time to generate BlumBlumShubByte on " << numberOfBit << " bit = " << float(std::clock() - begin_time) / CLOCKS_PER_SEC << std::endl;
    std::cout << "testEquiprobabilityByte " << testEquiprobabilityByte(m_generatedBlumBlumShubByte) << std::endl;
    std::cout << "testIndependenceByte    " << testIndependenceByte(m_generatedBlumBlumShubByte) << std::endl;
    std::cout << "testHomogeneity         " << testHomogeneity(m_generatedBlumBlumShubByte) << std::endl;
}

bool PRBgenerators::testEquiprobabilityByte(const std::vector<uint8_t>& stdVectorUint8_t)
{
    const uint32_t n = stdVectorUint8_t.size() >> 8;
    const float Z_1minusAlpha = 0.3389; // alpha = 0.01;
    //const float Z_1minusAlpha = 0.3289; // alpha = 0.05;
    //const float Z_1minusAlpha = 0.3159; // alpha = 0.1;
    float ChiSquare = 0;
    uint8_t byte = 0;
    do
    {
        ChiSquare += std::pow(std::count(stdVectorUint8_t.begin(), stdVectorUint8_t.end(), byte) - n, 2) / n;
    }
    while(++byte);
    float ChiSquare_1minusAlpha = std::sqrt(2 * UINT8_MAX) * Z_1minusAlpha + UINT8_MAX;
    return ChiSquare <= ChiSquare_1minusAlpha;
}

bool PRBgenerators::testIndependenceByte(const std::vector<uint8_t>& stdVectorUint8_t)
{
    const std::vector<uint16_t> stdVectorUint16_t = StdVectorUint8_tToStdVectorUint16_t(stdVectorUint8_t);
    const uint32_t numberOfBytePair = stdVectorUint16_t.size();
    const float Z_1minusAlpha = 0.3389; // alpha = 0.01;
    //const float Z_1minusAlpha = 0.3289; // alpha = 0.05;
    //const float Z_1minusAlpha = 0.3159; // alpha = 0.1;
    float ChiSquare = 0;
    uint16_t bytePair = 0;
    do
    {
        ChiSquare += std::pow(std::count(stdVectorUint16_t.begin(), stdVectorUint16_t.end(), bytePair), 2)
                / (std::count_if(stdVectorUint16_t.begin(), stdVectorUint16_t.end(), [&bytePair](uint16_t byteFirst){return (byteFirst >> 8) == (bytePair >> 8);})
                * std::count_if(stdVectorUint16_t.begin(), stdVectorUint16_t.end(), [&bytePair](uint16_t byteSecond){return (byteSecond & UINT8_MAX) == (bytePair & UINT8_MAX);}));
    }
    while(++bytePair);
    --ChiSquare *= numberOfBytePair;
    float ChiSquare_1minusAlpha = std::sqrt(2) * UINT8_MAX * Z_1minusAlpha + std::pow(UINT8_MAX, 2);
    return ChiSquare <= ChiSquare_1minusAlpha;
}

bool PRBgenerators::testHomogeneity(const std::vector<uint8_t>& stdVectorUint8_t)
{
    const uint32_t numberOfSegment = 8;
    const uint32_t lenghtOfSegment = stdVectorUint8_t.size() / numberOfSegment;
    const uint32_t numberOfByte = numberOfSegment * lenghtOfSegment;
    const float Z_1minusAlpha = 0.3389; // alpha = 0.01;
    //const float Z_1minusAlpha = 0.3289; // alpha = 0.05;
    //const float Z_1minusAlpha = 0.3159; // alpha = 0.1;
    float ChiSquare = 0;
    uint8_t byte = 0;
    do
    {
        std::vector<uint8_t>::const_iterator iteratorStdVectorUint8_t = stdVectorUint8_t.begin();
        for(uint32_t indexSegment = 0; indexSegment < numberOfSegment; ++indexSegment)
        {
            ChiSquare += std::pow(std::count(iteratorStdVectorUint8_t, iteratorStdVectorUint8_t + lenghtOfSegment - 1, byte), 2)
                    / (std::count(stdVectorUint8_t.begin(), stdVectorUint8_t.end(), byte) * lenghtOfSegment);
            iteratorStdVectorUint8_t += lenghtOfSegment;
        }
    }
    while(++byte);
    --ChiSquare *= numberOfByte;
    float ChiSquare_1minusAlpha = std::sqrt(2 * UINT8_MAX * (numberOfSegment - 1)) * Z_1minusAlpha + UINT8_MAX * (numberOfSegment - 1);
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

std::vector<uint16_t> StdVectorUint8_tToStdVectorUint16_t(const std::vector<uint8_t>& stdVectorUint8_t)
{
    std::vector<uint16_t> stdVectorUint16_t;
    stdVectorUint16_t.reserve(stdVectorUint8_t.size() & 1 ? (stdVectorUint8_t.size() >> 1) + 1 : stdVectorUint8_t.size() >> 1);
    std::vector<uint8_t>::const_iterator iteratorStdVectorUint8_t = stdVectorUint8_t.begin();
    bool carry = stdVectorUint8_t.size() & 1;
    if(carry)
    {
        stdVectorUint16_t.push_back(*iteratorStdVectorUint8_t);
        ++iteratorStdVectorUint8_t;
    }
    while(iteratorStdVectorUint8_t != stdVectorUint8_t.end())
    {
        stdVectorUint16_t.push_back((*iteratorStdVectorUint8_t << 8) | *(++iteratorStdVectorUint8_t));
        ++iteratorStdVectorUint8_t;
    }
    return stdVectorUint16_t;
}
