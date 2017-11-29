#include "PRBgenerators.h"

PRBgenerators::PRBgenerators(QObject* parent): QObject(parent)
{
}

PRBgenerators::~PRBgenerators()
{
}

void PRBgenerators::generateBuiltInCPP(const uint32_t& numberOfBit)
{
    std::vector<uint16_t> bigNumberStdVectorUint16_t;
    srand(time(NULL));
    bigNumberStdVectorUint16_t.reserve(numberOfBit % 16 == 0 ? numberOfBit / 16 : numberOfBit / 16 + 1);
    for(uint32_t indexBigNumberStdVectorUint16_t = 0; indexBigNumberStdVectorUint16_t < (numberOfBit % 16 == 0 ? numberOfBit / 16 : numberOfBit / 16 + 1); ++indexBigNumberStdVectorUint16_t)
    {
        bigNumberStdVectorUint16_t.push_back(rand());
    }
    m_generatedBuiltInCPP = bigNumberStdVectorUint16_t;
    std::cout << m_generatedBuiltInCPP.toStdString(2) << std::endl;
}

void PRBgenerators::generateLehmerLow(const uint32_t& numberOfBit)
{
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
    while (iteratorBigNumberStdVectorUint8_t != bigNumberStdVectorUint8_t.end())
    {
        *iteratorBigNumberStdVectorUint32_t = a * *std::prev(iteratorBigNumberStdVectorUint32_t) + c;
        *iteratorBigNumberStdVectorUint8_t = *iteratorBigNumberStdVectorUint32_t & 255;
        ++iteratorBigNumberStdVectorUint32_t;
        ++iteratorBigNumberStdVectorUint8_t;
    }
    m_generatedLehmerLow = bigNumberStdVectorUint8_t;
    std::cout << m_generatedLehmerLow.toStdString(2) << std::endl;
}

void PRBgenerators::generateLehmerHigh(const uint32_t& numberOfBit)
{
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
    while (iteratorBigNumberStdVectorUint8_t != bigNumberStdVectorUint8_t.end())
    {
        *iteratorBigNumberStdVectorUint32_t = a * *std::prev(iteratorBigNumberStdVectorUint32_t) + c;
        *iteratorBigNumberStdVectorUint8_t = *iteratorBigNumberStdVectorUint32_t >> 24;
        ++iteratorBigNumberStdVectorUint32_t;
        ++iteratorBigNumberStdVectorUint8_t;
    }
    m_generatedLehmerHigh = bigNumberStdVectorUint8_t;
    std::cout << m_generatedLehmerHigh.toStdString(2) << std::endl;
}

void PRBgenerators::generateL20(const uint32_t& numberOfBit)
{
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
    std::cout << m_generatedL20.toStdString(2) << std::endl;
}

void PRBgenerators::generateL89(const uint32_t& numberOfBit)
{
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
    std::cout << m_generatedL89.toStdString(2) << std::endl;
}

void PRBgenerators::generateGeffe(const uint32_t& numberOfBit)
{
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
    std::cout << m_generatedGeffe.toStdString(2) << std::endl;
}

void PRBgenerators::generateWolfram(const uint32_t& numberOfBit)
{
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
    std::cout << m_generatedWolfram.toStdString(2) << std::endl;
}

void PRBgenerators::generateBlumMikali(const uint32_t& numberOfBit)
{
    std::vector<bool> bigNumberStdVectorBool;
    const BigInt p("CEA42B987C44FA642D80AD9F51F10457690DEF10C83D0BC1BCEE12FC3B6093E3", 16); // p = 2 * q + 1
    const BigInt a("5B88C41246790891C095E2878880342E88C79974303BD0400B090FE38A688356", 16);
    const BigInt q("675215CC3E227D3216C056CFA8F8822BB486F788641E85E0DE77097E1DB049F1", 16); // q = (p - 1) / 2
    BigInt T;
    srand(time(NULL));
    std::cout << "0" << std::endl;
    T = rand();
    std::cout << "1" << std::endl;
    for(uint32_t indexBit = 0; indexBit < numberOfBit; ++indexBit)
    {
        std::cout << indexBit << std::endl;
        bigNumberStdVectorBool.push_back(T < q);
        T = pow(a, T) % p;
    }
    m_generatedBlumMikali = bigNumberStdVectorBool;
    std::cout << m_generatedBlumMikali.toStdString(2) << std::endl;
}
