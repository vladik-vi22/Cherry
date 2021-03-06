#include "RPNgenerator.h"
#define TRACK_TIME false

RPNgenerator::RPNgenerator(QObject* parent): QObject(parent)
{
    srand(static_cast<unsigned int>(time(NULL)));
}

RPNgenerator::~RPNgenerator()
{
}

BigInt RPNgenerator::generatePrimeNumber(const uint32_t numberOfBits)
{
#if TRACK_TIME
    std::clock_t begin_time = std::clock();
#endif
    PRBgenerators generator;
    generator.setNumberOfBits(numberOfBits);
    while(true)
    {
        generator.generateL20();
        BigInt primeNumber(generator.getGeneratedPRBS());
        if(divisibilityRulePascal(primeNumber))
        {
            if(primalityTestMillerRabin(primeNumber))
            {
                return primeNumber;
            }
        }
    }
#if TRACK_TIME
    std::cout << "time to generate prime number on " << m_numberOfBits << " bits = " << float(std::clock() - begin_time) / CLOCKS_PER_SEC << std::endl;
#endif
}

bool RPNgenerator::pseudoprimeTest(const BigInt& oddNumber, const BigInt& base)
{
    return (isCoprime(base, oddNumber) && congruencemod(powmod(base, oddNumber - ConstBigInt::ONE, oddNumber), ConstBigInt::ONE, oddNumber));
}

bool RPNgenerator::pseudoprimeTestEulerJacobi(const BigInt& oddNumber, const BigInt& base)
{
    return (isCoprime(base, oddNumber) && congruencemod(BigInt(symbolJacobi(base, oddNumber)), powmod(base, (oddNumber - ConstBigInt::ONE) >> size_t(1), oddNumber), oddNumber));
}

bool RPNgenerator::divisibilityRulePascal(const BigInt& bigNum)
{
    const std::vector<uint8_t> firstPrimeNumbers = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79};
    const std::vector<uint32_t> stdVectorUint32_t = bigNum.toStdVectorUint32_t();
    const uint64_t B = uint64_t(UINT32_MAX + 1);
    for(std::vector<uint8_t>::const_iterator iteratorPrimeNumber = firstPrimeNumbers.cbegin(); iteratorPrimeNumber != firstPrimeNumbers.cend(); ++iteratorPrimeNumber)
    {
        std::vector<uint8_t> r;
        r.reserve(stdVectorUint32_t.size());
        r.emplace_back(1);
        while(r.size() != stdVectorUint32_t.size())
        {
            r.emplace_back((uint64_t(r.back()) * B) % *iteratorPrimeNumber);
        }
        std::vector<uint32_t>::const_reverse_iterator iteratorNumber = stdVectorUint32_t.crbegin();
        std::vector<uint8_t>::const_iterator iteratorR = r.cbegin();
        BigInt sum;
        while(iteratorNumber != stdVectorUint32_t.crend())
        {
            sum += BigInt(uint64_t(*iteratorNumber * *iteratorR));
            ++iteratorNumber;
            ++iteratorR;
        }
        if(!(sum % BigInt(*iteratorPrimeNumber)))
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
        prbGenerator.setNumberOfBits(2 + (static_cast<size_t>(rand()) % (bigNum.bitLenght() - 2)));
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
        prbGenerator.setNumberOfBits(2 + (static_cast<size_t>(rand()) % (bigNum.bitLenght() - 2)));
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
    BigInt dividendBy2 = bigNum - ConstBigInt::ONE;
    uint32_t powerOf2 = 0;
    while(dividendBy2.isEven())
    {
        dividendBy2 >>= 1;
        ++powerOf2;
    }
    for(uint8_t k = 0; k < 16; ++k)
    {
        prbGenerator.setNumberOfBits(2 + (static_cast<size_t>(rand()) % (bigNum.bitLenght() - 2)));
        prbGenerator.generateBlumBlumShubByte();
        BigInt x(prbGenerator.getGeneratedPRBS());
        if(!isCoprime(x, bigNum))
        {
            return false;
        }
        x = powmod(x, dividendBy2, bigNum);
        bool strongPseudoprime = false;
        if(congruencemod(x, ConstBigInt::ONE, bigNum) || congruencemod(x, bigNum - ConstBigInt::ONE, bigNum))
        {
            strongPseudoprime = true;
        }
        else
        {
            for(uint32_t r = 1; r < powerOf2; ++r)
            {
                x = powmod(x, ConstBigInt::TWO, bigNum);
                if(congruencemod(x, bigNum - ConstBigInt::ONE, bigNum))
                {
                    strongPseudoprime = true;
                    break;
                }
                else if(congruencemod(x, ConstBigInt::ONE, bigNum))
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
