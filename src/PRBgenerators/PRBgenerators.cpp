#include "PRBgenerators.h"

PRBgenerators::PRBgenerators(QObject* parent): QObject(parent)
{
}

PRBgenerators::~PRBgenerators()
{
}

void PRBgenerators::generateBuiltInCPP(const uint32_t& numberOfBit)
{
    std::clock_t begin_time = std::clock();
    std::vector<uint16_t> bigNumberStdVectorUint16_t;
    srand(time(NULL));
    bigNumberStdVectorUint16_t.reserve(numberOfBit % 16 == 0 ? numberOfBit / 16 : numberOfBit / 16 + 1);
    for(uint32_t indexBigNumberStdVectorUint16_t = 0; indexBigNumberStdVectorUint16_t < (numberOfBit % 16 == 0 ? numberOfBit / 16 : numberOfBit / 16 + 1); ++indexBigNumberStdVectorUint16_t)
    {
        bigNumberStdVectorUint16_t.push_back(rand());
    }
    m_generatedBuiltInCPP = bigNumberStdVectorUint16_t;
    std::cout << "time to generate BuiltInCPP on " << numberOfBit << " bit = " << float(std::clock() - begin_time) / CLOCKS_PER_SEC << std::endl;
    std::cout << m_generatedBuiltInCPP.toStdString(2) << std::endl;
}

void PRBgenerators::generateLehmerLow(const uint32_t& numberOfBit)
{
    std::clock_t begin_time = std::clock();
    const uint32_t a = 65537;
    const uint32_t c = 119;
    std::vector<uint32_t> bigNumberStdVectorUint32_t;
    std::vector<uint8_t> bigNumberStdVectorUint8_t;
    srand(time(NULL));
    bigNumberStdVectorUint32_t.reserve(numberOfBit % 8 == 0 ? numberOfBit / 8 : numberOfBit / 8 + 1);
    bigNumberStdVectorUint8_t.reserve(numberOfBit % 8 == 0 ? numberOfBit / 8 : numberOfBit / 8 + 1);
    bigNumberStdVectorUint32_t.push_back(rand() + 1);
    bigNumberStdVectorUint8_t.push_back(bigNumberStdVectorUint32_t.front() & 255);
    bigNumberStdVectorUint32_t.resize(bigNumberStdVectorUint32_t.capacity());
    bigNumberStdVectorUint8_t.resize(bigNumberStdVectorUint8_t.capacity());
    std::vector<uint32_t>::iterator iteratorBigNumberStdVectorUint32_t = std::next(bigNumberStdVectorUint32_t.begin());
    std::vector<uint8_t>::iterator iteratorBigNumberStdVectorUint8_t = std::next(bigNumberStdVectorUint8_t.begin());
    while(iteratorBigNumberStdVectorUint8_t != bigNumberStdVectorUint8_t.end())
    {
        *iteratorBigNumberStdVectorUint32_t = a * *std::prev(iteratorBigNumberStdVectorUint32_t) + c;
        *iteratorBigNumberStdVectorUint8_t = *iteratorBigNumberStdVectorUint32_t & 255;
        ++iteratorBigNumberStdVectorUint32_t;
        ++iteratorBigNumberStdVectorUint8_t;
    }
    m_generatedLehmerLow = bigNumberStdVectorUint8_t;
    std::cout << "time to generate LehmerLow on " << numberOfBit << " bit = " << float(std::clock() - begin_time) / CLOCKS_PER_SEC << std::endl;
    std::cout << m_generatedLehmerLow.toStdString(2) << std::endl;
}

void PRBgenerators::generateLehmerHigh(const uint32_t& numberOfBit)
{
    std::clock_t begin_time = std::clock();
    const uint32_t a = 65537;
    const uint32_t c = 119;
    std::vector<uint32_t> bigNumberStdVectorUint32_t;
    std::vector<uint8_t> bigNumberStdVectorUint8_t;
    srand(time(NULL));
    bigNumberStdVectorUint32_t.reserve(numberOfBit % 8 == 0 ? numberOfBit / 8 : numberOfBit / 8 + 1);
    bigNumberStdVectorUint8_t.reserve(numberOfBit % 8 == 0 ? numberOfBit / 8 : numberOfBit / 8 + 1);
    bigNumberStdVectorUint32_t.push_back(rand() + 1);
    bigNumberStdVectorUint8_t.push_back(bigNumberStdVectorUint32_t.front() >> 24);
    bigNumberStdVectorUint32_t.resize(bigNumberStdVectorUint32_t.capacity());
    bigNumberStdVectorUint8_t.resize(bigNumberStdVectorUint8_t.capacity());
    std::vector<uint32_t>::iterator iteratorBigNumberStdVectorUint32_t = std::next(bigNumberStdVectorUint32_t.begin());
    std::vector<uint8_t>::iterator iteratorBigNumberStdVectorUint8_t = std::next(bigNumberStdVectorUint8_t.begin());
    while(iteratorBigNumberStdVectorUint8_t != bigNumberStdVectorUint8_t.end())
    {
        *iteratorBigNumberStdVectorUint32_t = a * *std::prev(iteratorBigNumberStdVectorUint32_t) + c;
        *iteratorBigNumberStdVectorUint8_t = *iteratorBigNumberStdVectorUint32_t >> 24;
        ++iteratorBigNumberStdVectorUint32_t;
        ++iteratorBigNumberStdVectorUint8_t;
    }
    m_generatedLehmerHigh = bigNumberStdVectorUint8_t;
    std::cout << "time to generate LehmerHigh on " << numberOfBit << " bit = " << float(std::clock() - begin_time) / CLOCKS_PER_SEC << std::endl;
    std::cout << m_generatedLehmerHigh.toStdString(2) << std::endl;
}

void PRBgenerators::generateL20(const uint32_t& numberOfBit)
{
    std::clock_t begin_time = std::clock();
    std::vector<bool> bigNumberStdVectorBool;
    bigNumberStdVectorBool.reserve(numberOfBit);
    bigNumberStdVectorBool.resize(numberOfBit, 0);
    srand(time(NULL));
    std::vector<bool>::iterator iteratorBigNumberStdVectorBool = bigNumberStdVectorBool.begin();
    for(uint8_t indexFirstBits = 0; indexFirstBits < 20; ++indexFirstBits)
    {
        *iteratorBigNumberStdVectorBool = rand() & 1;
        ++iteratorBigNumberStdVectorBool;
    }
    while(iteratorBigNumberStdVectorBool != bigNumberStdVectorBool.end())
    {
        *iteratorBigNumberStdVectorBool = *(iteratorBigNumberStdVectorBool - 3) ^ *(iteratorBigNumberStdVectorBool - 5) ^ *(iteratorBigNumberStdVectorBool - 9) ^ *(iteratorBigNumberStdVectorBool - 20);
        ++iteratorBigNumberStdVectorBool;
    }
    m_generatedL20 = bigNumberStdVectorBool;
    std::cout << "time to generate L20 on " << numberOfBit << " bit = " << float(std::clock() - begin_time) / CLOCKS_PER_SEC << std::endl;
    std::cout << m_generatedL20.toStdString(2) << std::endl;
}

void PRBgenerators::generateL89(const uint32_t& numberOfBit)
{
    std::clock_t begin_time = std::clock();
    std::vector<bool> bigNumberStdVectorBool;
    bigNumberStdVectorBool.reserve(numberOfBit);
    bigNumberStdVectorBool.resize(numberOfBit, 0);
    srand(time(NULL));
    std::vector<bool>::iterator iteratorBigNumberStdVectorBool = bigNumberStdVectorBool.begin();
    for(uint8_t indexFirstBits = 0; indexFirstBits < 89; ++indexFirstBits)
    {
        *iteratorBigNumberStdVectorBool = rand() & 1;
        ++iteratorBigNumberStdVectorBool;
    }
    while(iteratorBigNumberStdVectorBool != bigNumberStdVectorBool.end())
    {
        *iteratorBigNumberStdVectorBool = *(iteratorBigNumberStdVectorBool - 38) ^ *(iteratorBigNumberStdVectorBool - 89);
        ++iteratorBigNumberStdVectorBool;
    }
    m_generatedL89 = bigNumberStdVectorBool;
    std::cout << "time to generate L89 on " << numberOfBit << " bit = " << float(std::clock() - begin_time) / CLOCKS_PER_SEC << std::endl;
    std::cout << m_generatedL89.toStdString(2) << std::endl;
}

void PRBgenerators::generateGeffe(const uint32_t& numberOfBit)
{
    std::clock_t begin_time = std::clock();
    std::vector<bool> bigNumberStdVectorBool;
    std::vector<bool> bigNumberStdVectorBoolL9;
    std::vector<bool> bigNumberStdVectorBoolL10;
    std::vector<bool> bigNumberStdVectorBoolL11;
    bigNumberStdVectorBool.reserve(numberOfBit);
    bigNumberStdVectorBool.resize(numberOfBit, 0);
    bigNumberStdVectorBoolL9.reserve(numberOfBit);
    bigNumberStdVectorBoolL9.resize(numberOfBit, 0);
    bigNumberStdVectorBoolL10.reserve(numberOfBit);
    bigNumberStdVectorBoolL10.resize(numberOfBit, 0);
    bigNumberStdVectorBoolL11.reserve(numberOfBit);
    bigNumberStdVectorBoolL11.resize(numberOfBit, 0);
    srand(time(NULL));
    std::vector<bool>::iterator iteratorBigNumberStdVectorBool = bigNumberStdVectorBool.begin();
    std::vector<bool>::iterator iteratorBigNumberStdVectorBoolL9 = bigNumberStdVectorBoolL9.begin();
    std::vector<bool>::iterator iteratorBigNumberStdVectorBoolL10 = bigNumberStdVectorBoolL10.begin();
    std::vector<bool>::iterator iteratorBigNumberStdVectorBoolL11 = bigNumberStdVectorBoolL11.begin();
    for(uint8_t indexFirstBits = 0; indexFirstBits < 9; ++indexFirstBits)
    {
        *iteratorBigNumberStdVectorBoolL9 = rand() & 1;
        *iteratorBigNumberStdVectorBoolL10 = rand() & 1;
        *iteratorBigNumberStdVectorBoolL11 = rand() & 1;
        *iteratorBigNumberStdVectorBool = (*iteratorBigNumberStdVectorBoolL10 & *iteratorBigNumberStdVectorBoolL11) ^ ((1 ^ *iteratorBigNumberStdVectorBoolL10) & *iteratorBigNumberStdVectorBoolL9);
        ++iteratorBigNumberStdVectorBool;
        ++iteratorBigNumberStdVectorBoolL9;
        ++iteratorBigNumberStdVectorBoolL10;
        ++iteratorBigNumberStdVectorBoolL11;
    }

    *iteratorBigNumberStdVectorBoolL9 = *(iteratorBigNumberStdVectorBoolL9 - 9) ^ *(iteratorBigNumberStdVectorBoolL9 - 8) ^ *(iteratorBigNumberStdVectorBoolL9 - 6) ^ *(iteratorBigNumberStdVectorBoolL9 - 5);
    *iteratorBigNumberStdVectorBoolL10 = rand() & 1;
    *iteratorBigNumberStdVectorBoolL11 = rand() & 1;
    *iteratorBigNumberStdVectorBool = (*iteratorBigNumberStdVectorBoolL10 & *iteratorBigNumberStdVectorBoolL11) ^ ((1 ^ *iteratorBigNumberStdVectorBoolL10) & *iteratorBigNumberStdVectorBoolL9);
    ++iteratorBigNumberStdVectorBool;
    ++iteratorBigNumberStdVectorBoolL9;
    ++iteratorBigNumberStdVectorBoolL10;
    ++iteratorBigNumberStdVectorBoolL11;

    *iteratorBigNumberStdVectorBoolL9 = *(iteratorBigNumberStdVectorBoolL9 - 9) ^ *(iteratorBigNumberStdVectorBoolL9 - 8) ^ *(iteratorBigNumberStdVectorBoolL9 - 6) ^ *(iteratorBigNumberStdVectorBoolL9 - 5);
    *iteratorBigNumberStdVectorBoolL10 = *(iteratorBigNumberStdVectorBoolL10 - 10) ^ *(iteratorBigNumberStdVectorBoolL10 - 7);
    *iteratorBigNumberStdVectorBoolL11 = rand() & 1;
    *iteratorBigNumberStdVectorBool = (*iteratorBigNumberStdVectorBoolL10 & *iteratorBigNumberStdVectorBoolL11) ^ ((1 ^ *iteratorBigNumberStdVectorBoolL10) & *iteratorBigNumberStdVectorBoolL9);
    ++iteratorBigNumberStdVectorBool;
    ++iteratorBigNumberStdVectorBoolL9;
    ++iteratorBigNumberStdVectorBoolL10;
    ++iteratorBigNumberStdVectorBoolL11;

    while(iteratorBigNumberStdVectorBool != bigNumberStdVectorBool.end())
    {
        *iteratorBigNumberStdVectorBoolL9 = *(iteratorBigNumberStdVectorBoolL9 - 9) ^ *(iteratorBigNumberStdVectorBoolL9 - 8) ^ *(iteratorBigNumberStdVectorBoolL9 - 6) ^ *(iteratorBigNumberStdVectorBoolL9 - 5);
        *iteratorBigNumberStdVectorBoolL10 = *(iteratorBigNumberStdVectorBoolL10 - 10) ^ *(iteratorBigNumberStdVectorBoolL10 - 7);
        *iteratorBigNumberStdVectorBoolL11 = *(iteratorBigNumberStdVectorBoolL11 - 11) ^ *(iteratorBigNumberStdVectorBoolL11 - 9);
        *iteratorBigNumberStdVectorBool = (*iteratorBigNumberStdVectorBoolL10 * *iteratorBigNumberStdVectorBoolL11) ^ ((1 ^ *iteratorBigNumberStdVectorBoolL10) * *iteratorBigNumberStdVectorBoolL9);
        ++iteratorBigNumberStdVectorBool;
        ++iteratorBigNumberStdVectorBoolL9;
        ++iteratorBigNumberStdVectorBoolL10;
        ++iteratorBigNumberStdVectorBoolL11;
    }
    m_generatedGeffe = bigNumberStdVectorBool;
    std::cout << "time to generate Geffe on " << numberOfBit << " bit = " << float(std::clock() - begin_time) / CLOCKS_PER_SEC << std::endl;
    std::cout << m_generatedGeffe.toStdString(2) << std::endl;
}

void PRBgenerators::generateWolfram(const uint32_t& numberOfBit)
{
    std::clock_t begin_time = std::clock();
    std::vector<bool> bigNumberStdVectorBool;
    bigNumberStdVectorBool.reserve(numberOfBit);
    srand(time(NULL));
    uint32_t r = rand() + 1;
    for(uint32_t indexBit = 0; indexBit < numberOfBit; ++indexBit)
    {
        bigNumberStdVectorBool.push_back(r & 1);
        r = (r << 1) ^ (r | (r >> 1));
    }
    m_generatedWolfram = bigNumberStdVectorBool;
    std::cout << "time to generate Wolfram on " << numberOfBit << " bit = " << float(std::clock() - begin_time) / CLOCKS_PER_SEC << std::endl;
    std::cout << m_generatedWolfram.toStdString(2) << std::endl;
}

void PRBgenerators::generateBlumMikaliBit(const uint32_t& numberOfBit)
{
    std::clock_t begin_time = std::clock();
    std::vector<bool> bigNumberStdVectorBool;
    bigNumberStdVectorBool.reserve(numberOfBit);
    const BigInt a("5B88C41246790891C095E2878880342E88C79974303BD0400B090FE38A688356", 16);
    const BigInt p("CEA42B987C44FA642D80AD9F51F10457690DEF10C83D0BC1BCEE12FC3B6093E3", 16); // p = 2 * q + 1
    const BigInt q("675215CC3E227D3216C056CFA8F8822BB486F788641E85E0DE77097E1DB049F1", 16); // q = (p - 1) / 2
    srand(time(NULL));
    BigInt T = rand();
    for(uint32_t indexBit = 0; indexBit < numberOfBit; ++indexBit)
    {
        bigNumberStdVectorBool.push_back(T < q);
        T = powmod(a, T, p);
    }
    m_generatedBlumMikaliBit = bigNumberStdVectorBool;
    std::cout << "time to generate BlumMikaliBit on " << numberOfBit << " bit = " << float(std::clock() - begin_time) / CLOCKS_PER_SEC << std::endl;
    std::cout << m_generatedBlumMikaliBit.toStdString(2) << std::endl;
}

void PRBgenerators::generateBlumMikaliByte(const uint32_t& numberOfBit)
{
    std::clock_t begin_time = std::clock();
    std::vector<uint8_t> bigNumberStdVectorUint8_t;
    bigNumberStdVectorUint8_t.reserve(numberOfBit % 8 == 0 ? numberOfBit / 8 : numberOfBit / 8 + 1);
    const BigInt a("5B88C41246790891C095E2878880342E88C79974303BD0400B090FE38A688356", 16);
    const BigInt p("CEA42B987C44FA642D80AD9F51F10457690DEF10C83D0BC1BCEE12FC3B6093E3", 16); // p = 2 * q + 1
    const BigInt q("675215CC3E227D3216C056CFA8F8822BB486F788641E85E0DE77097E1DB049F1", 16); // q = (p - 1) / 2
    srand(time(NULL));
    BigInt T = rand();
    for(uint32_t indexByte = 0; indexByte < (numberOfBit % 8 == 0 ? numberOfBit / 8 : numberOfBit / 8 + 1); ++indexByte)
    {
        bigNumberStdVectorUint8_t.push_back((--((T << 7) / q)).toUint32_t()); // T << 7 = T * 128
        T = powmod(a, T, p);
    }
    m_generatedBlumMikaliByte = bigNumberStdVectorUint8_t;
    std::cout << "time to generate BlumMikaliByte on " << numberOfBit << " bit = " << float(std::clock() - begin_time) / CLOCKS_PER_SEC << std::endl;
    std::cout << m_generatedBlumMikaliByte.toStdString(2) << std::endl;
}

void PRBgenerators::generateBlumBlumShubBit(const uint32_t& numberOfBit)
{
    std::clock_t begin_time = std::clock();
    std::vector<bool> bigNumberStdVectorBool;
    bigNumberStdVectorBool.reserve(numberOfBit);
    //const BigInt p("D5BBB96D30086EC484EBA3D7F9CAEB07", 16);
    //const BigInt q("425D2B9BFDB25B9CF6C416CC6E37B59C1F", 16);
    const BigInt n("37682f6947aaab110517c20b76df64781da78b3e87eb58379085d3395793bdb9d9", 16); // p * q
    srand(time(NULL));
    BigInt r = rand() + 2;
    for(uint32_t indexBit = 0; indexBit < numberOfBit; ++indexBit)
    {
        bigNumberStdVectorBool.push_back(r.isOdd());
        r = powmod(r, 2, n);
    }
    m_generatedBlumBlumShubBit = bigNumberStdVectorBool;
    std::cout << "time to generate BlumBlumShubBit on " << numberOfBit << " bit = " << float(std::clock() - begin_time) / CLOCKS_PER_SEC << std::endl;
    std::cout << m_generatedBlumBlumShubBit.toStdString(2) << std::endl;
}

void PRBgenerators::generateBlumBlumShubByte(const uint32_t& numberOfBit)
{
    std::clock_t begin_time = std::clock();
    std::vector<uint8_t> bigNumberStdVectorUint8_t;
    bigNumberStdVectorUint8_t.reserve(numberOfBit % 8 == 0 ? numberOfBit / 8 : numberOfBit / 8 + 1);
    //const BigInt p("D5BBB96D30086EC484EBA3D7F9CAEB07", 16);
    //const BigInt q("425D2B9BFDB25B9CF6C416CC6E37B59C1F", 16);
    const BigInt n("37682f6947aaab110517c20b76df64781da78b3e87eb58379085d3395793bdb9d9", 16); // p * q
    srand(time(NULL));
    BigInt r = rand() + 2;
    for(uint32_t indexByte = 0; indexByte < (numberOfBit % 8 == 0 ? numberOfBit / 8 : numberOfBit / 8 + 1); ++indexByte)
    {
        bigNumberStdVectorUint8_t.push_back((r % 256).toUint32_t()); // r & 511 = r % 256
        r = powmod(r, 2, n);
    }
    m_generatedBlumBlumShubByte = bigNumberStdVectorUint8_t;
    std::cout << "time to generate BlumBlumShubByte on " << numberOfBit << " bit = " << float(std::clock() - begin_time) / CLOCKS_PER_SEC << std::endl;
    std::cout << m_generatedBlumBlumShubByte.toStdString(2) << std::endl;
}
