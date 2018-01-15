#include "RPNgenerator.h"

RPNgenerator::RPNgenerator(QObject* parent): QObject(parent)
{
    srand(time(NULL));
}

RPNgenerator::~RPNgenerator()
{
}

BigInt RPNgenerator::generatePrimeNumber(const uint32_t& numberOfBit)
{
    PRBgenerators generator;
    generator.setNumberOfBit(QString::number(numberOfBit));
    while(true)
    {
        generator.generateL89();
        BigInt primeNumber(generator.getGeneratedPRBS());
        if(divisibilityRulePascal(primeNumber))
        {
            if(primalityTestMillerRabin(primeNumber))
            {
                return primeNumber;
            }
        }
    }
}

bool RPNgenerator::pseudoprimeTest(const BigInt& oddNumber, const BigInt& base)
{
    return (gcd(base, oddNumber) == BigInt(1) && congruencemod(powmod(base, oddNumber - BigInt(1), oddNumber), BigInt(1), oddNumber));
}

bool RPNgenerator::pseudoprimeTestEulerJacobi(const BigInt& oddNumber, const BigInt& base)
{
    return (gcd(base, oddNumber) == BigInt(1) && congruencemod(BigInt(symbolJacobi(base, oddNumber)), powmod(base, (oddNumber - BigInt(1)) >> 1, oddNumber), oddNumber));
}

bool RPNgenerator::divisibilityRulePascal(const BigInt& bigNum)
{
    const std::vector<uint8_t> firstPrimeNumbers = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79};
    const std::vector<uint32_t> stdVectorUint32_t = bigNum.toStdVectorUint32_t();
    const uint64_t B = (uint64_t)UINT32_MAX + 1;
    for(std::vector<uint8_t>::const_iterator iteratorPrimeNumber = firstPrimeNumbers.cbegin(); iteratorPrimeNumber != firstPrimeNumbers.cend(); ++iteratorPrimeNumber)
    {
        std::vector<uint8_t> r;
        r.reserve(stdVectorUint32_t.size());
        r.push_back(1);
        while(r.size() != stdVectorUint32_t.size())
        {
            r.push_back(((uint64_t) r.back() * B) % *iteratorPrimeNumber);
        }
        std::vector<uint32_t>::const_reverse_iterator iteratorNumber = stdVectorUint32_t.crbegin();
        std::vector<uint8_t>::const_iterator iteratorR = r.cbegin();
        BigInt sum;
        while(iteratorNumber != stdVectorUint32_t.crend())
        {
            sum += BigInt((uint64_t) *iteratorNumber * *iteratorR);
            ++iteratorNumber;
            ++iteratorR;
        }
        if((sum % BigInt(*iteratorPrimeNumber)).isZero())
        {
            return false;
        }
    }
    return true;
}

bool RPNgenerator::primalityTestPherma(const BigInt& bigNum)
{
    PRBgenerators prbGenerator;
    for(uint8_t k = 0; k < 16; ++k)
    {
        prbGenerator.setNumberOfBit(QString::number(2 + (rand() % (bigNum.bitLenght() - 2))));
        prbGenerator.generateBlumBlumShubByte();
        BigInt x(prbGenerator.getGeneratedPRBS());
        if(!pseudoprimeTest(bigNum, x))
        {
            return false;
        }
    }
    return true;
}

bool RPNgenerator::primalityTestSolovayStrassen(const BigInt& bigNum)
{
    PRBgenerators prbGenerator;
    for(uint8_t k = 0; k < 16; ++k)
    {
        prbGenerator.setNumberOfBit(QString::number(2 + (rand() % (bigNum.bitLenght() - 2))));
        prbGenerator.generateBlumBlumShubByte();
        BigInt x(prbGenerator.getGeneratedPRBS());
        if(!pseudoprimeTestEulerJacobi(bigNum, x))
        {
            return false;
        }
    }
    return true;
}

bool RPNgenerator::primalityTestMillerRabin(const BigInt& bigNum)
{
    PRBgenerators prbGenerator;
    BigInt dividendBy2 = bigNum - BigInt(1);
    uint32_t powerOf2 = 0;
    while(dividendBy2.isEven())
    {
        dividendBy2 >>= 1;
        ++powerOf2;
    }
    for(uint8_t k = 0; k < 16; ++k)
    {
        prbGenerator.setNumberOfBit(QString::number(2 + (rand() % (bigNum.bitLenght() - 2))));
        prbGenerator.generateBlumBlumShubByte();
        BigInt x(prbGenerator.getGeneratedPRBS());
        if(gcd(x, bigNum) != BigInt(1))
        {
            return false;
        }
        x = powmod(x, dividendBy2, bigNum);
        bool strongPseudoprime = false;
        if(congruencemod(x, BigInt(1), bigNum) || congruencemod(x, bigNum - BigInt(1), bigNum))
        {
            strongPseudoprime = true;
        }
        else
        {
            for(uint32_t r = 1; r < powerOf2; ++r)
            {
                x = powmod(x, BigInt(2), bigNum);
                if(congruencemod(x, bigNum - BigInt(1), bigNum))
                {
                    strongPseudoprime = true;
                    break;
                }
                else if(congruencemod(x, BigInt(1), bigNum))
                {
                    return false;
                }
            }
        }
        if(!strongPseudoprime)
        {
            return false;
        }
    }
    return true;
}
