#include "BigIntLibrary.h"

const uint8_t BigInt::baseBinary = 2;
const uint8_t BigInt::baseDecimal = 10;
const uint8_t BigInt::baseHexadecimal = 16;
const uint64_t BigInt::basisCalcSys = 4294967296; // 2^32

uint8_t BigInt::baseInput = baseDecimal;
uint8_t BigInt::baseOutput = baseDecimal;

BigInt::BigInt()
{
}

BigInt::BigInt(const BigInt& bigNumber)
{
    bigNumArr = bigNumber.bigNumArr;
    positive = bigNumber.positive;
}

BigInt::BigInt(const std::string& bigNumberStdString, const int base)
{
    const uint8_t sizeOfCell = base == baseHexadecimal ? (sizeof(uint32_t) * 2) : (sizeof(uint32_t) * 8);
    std::string bigNumberStdStringInput = bigNumberStdString;
    if(bigNumberStdStringInput[0] == '-')
    {
        positive = false;
        bigNumberStdStringInput.erase(0, 1);
    }
    else
    {
        positive = true;
    }
    if(base == baseDecimal)
    {
        bigNumberStdStringInput = strDec2strBin(bigNumberStdStringInput);
    }
    while(bigNumberStdStringInput.length() % sizeOfCell)
    {
        bigNumberStdStringInput.insert(0, 1, '0');
    }
    uint32_t sizeOfArr = bigNumberStdStringInput.length() / sizeOfCell;
    bigNumArr.reserve(sizeOfArr);
    for(uint32_t indexBigNumArr = 0; indexBigNumArr < sizeOfArr; ++indexBigNumArr)
    {
        bigNumArr.insert(bigNumArr.begin(), 1, std::stoul(bigNumberStdStringInput.substr(indexBigNumArr * sizeOfCell, sizeOfCell), nullptr, base == baseHexadecimal ? baseHexadecimal : baseBinary));
    }
}

BigInt::BigInt(const std::vector<uint32_t>& bigNumberStdVectorUint32_t, const bool isPositive)
{
    bigNumArr = bigNumberStdVectorUint32_t;
    std::reverse(bigNumArr.begin(), bigNumArr.end());
    deleteZeroHighOrderDigit();
    positive = isPositive;
}

BigInt::BigInt(const std::vector<uint16_t>& bigNumberStdVectorUint16_t, const bool isPositive)
{
    bigNumArr.reserve(bigNumberStdVectorUint16_t.size() & 1 ? (bigNumberStdVectorUint16_t.size() >> 1) + 1 : bigNumberStdVectorUint16_t.size() >> 1);
    std::vector<uint16_t>::const_reverse_iterator iteratorBigNumberStdVectorUint16_t = bigNumberStdVectorUint16_t.crbegin();
    for(uint32_t indexBigNumArr = 0; indexBigNumArr < (bigNumberStdVectorUint16_t.size() >> 1); ++indexBigNumArr)
    {
        bigNumArr.push_back((uint32_t)*iteratorBigNumberStdVectorUint16_t | *(++iteratorBigNumberStdVectorUint16_t) << 16);
        ++iteratorBigNumberStdVectorUint16_t;
    }
    if(bigNumberStdVectorUint16_t.size() & 1)
    {
        bigNumArr.push_back(*iteratorBigNumberStdVectorUint16_t);
    }
    deleteZeroHighOrderDigit();
    positive = isPositive;
}

BigInt::BigInt(const std::vector<uint8_t>& bigNumberStdVectorUint8_t, const bool isPositive)
{
    bigNumArr.reserve(bigNumberStdVectorUint8_t.size() & 3 ? (bigNumberStdVectorUint8_t.size() >> 2) + 1 : bigNumberStdVectorUint8_t.size() >> 2);
    std::vector<uint8_t>::const_reverse_iterator iteratorBigNumberStdVectorUint8_t = bigNumberStdVectorUint8_t.crbegin();
    for(uint32_t indexBigNumArr = 0; indexBigNumArr < (bigNumberStdVectorUint8_t.size() >> 2); ++indexBigNumArr)
    {
        bigNumArr.push_back((uint32_t)*iteratorBigNumberStdVectorUint8_t | *(++iteratorBigNumberStdVectorUint8_t) << 8 | *(++iteratorBigNumberStdVectorUint8_t) << 16 | *(++iteratorBigNumberStdVectorUint8_t) << 24);
        ++iteratorBigNumberStdVectorUint8_t;
    }
    if((bigNumberStdVectorUint8_t.size() & 3) == 3)
    {
        bigNumArr.push_back((uint32_t)*iteratorBigNumberStdVectorUint8_t | *(++iteratorBigNumberStdVectorUint8_t) << 8 | *(++iteratorBigNumberStdVectorUint8_t) << 16);
    }
    else if((bigNumberStdVectorUint8_t.size() & 3) == 2)
    {
        bigNumArr.push_back((uint32_t)*iteratorBigNumberStdVectorUint8_t | *(++iteratorBigNumberStdVectorUint8_t) << 8);
    }
    else if((bigNumberStdVectorUint8_t.size() & 3) == 1)
    {
        bigNumArr.push_back(*iteratorBigNumberStdVectorUint8_t);
    }
    deleteZeroHighOrderDigit();
    positive = isPositive;
}

BigInt::BigInt(const std::vector<bool>& bigNumberStdVectorBool, const bool isPositive)
{
    bigNumArr.reserve(bigNumberStdVectorBool.size() & 31 ? (bigNumberStdVectorBool.size() >> 5) + 1 : bigNumberStdVectorBool.size() >> 5);
    uint32_t bigNumArr_temp;
    std::vector<bool>::const_reverse_iterator iteratorBigNumberStdVectorBool = bigNumberStdVectorBool.crbegin();
    for(uint32_t indexBigNumArr = 0; indexBigNumArr < (bigNumberStdVectorBool.size() >> 5); ++indexBigNumArr)
    {
        bigNumArr_temp = 0;
        for(uint8_t indexBit = 0; indexBit < 32; ++indexBit)
        {
            bigNumArr_temp |= *iteratorBigNumberStdVectorBool << indexBit;
            ++iteratorBigNumberStdVectorBool;
        }
        bigNumArr.push_back(bigNumArr_temp);
    }
    if(bigNumberStdVectorBool.size() & 31)
    {
        bigNumArr_temp = 0;
        for(uint8_t indexBit = 0; indexBit < (bigNumberStdVectorBool.size() & 31); ++indexBit)
        {
            bigNumArr_temp |= *iteratorBigNumberStdVectorBool << indexBit;
            ++iteratorBigNumberStdVectorBool;
        }
        bigNumArr.push_back(bigNumArr_temp);
    }
    deleteZeroHighOrderDigit();
    positive = isPositive;
}

BigInt::BigInt(const uint32_t numberUint32_t, const bool isPositive)
{
    bigNumArr.push_back(numberUint32_t);
    positive = isPositive;
}

BigInt::BigInt(const uint64_t numberUint64_t, const bool isPositive)
{
    bigNumArr.push_back(numberUint64_t & UINT32_MAX);
    bigNumArr.push_back(numberUint64_t >> 32);
    positive = isPositive;
}

BigInt::BigInt(const int numberInt)
{
    bigNumArr.push_back(std::abs(numberInt));
    positive = (numberInt >= 0);
}

BigInt::BigInt(const long long numberLongLong)
{
    bigNumArr.push_back(std::abs(numberLongLong) & UINT32_MAX);
    bigNumArr.push_back(std::abs(numberLongLong) >> 32);
    positive = (numberLongLong >= 0);
}

BigInt::~BigInt()
{
}

BigInt& BigInt::operator = (const BigInt& equal)
{
    bigNumArr = equal.bigNumArr;
    positive = equal.positive;
    return *this;
}

BigInt BigInt::operator +() const
{
    return *this;
}

BigInt BigInt::operator + (const BigInt& addend) const
{
    if(positive && addend.positive)
    {
        BigInt sum;
        bool augendGreater = (bigNumArr.size() >= addend.bigNumArr.size());
        sum.bigNumArr.reserve(augendGreater ? bigNumArr.size() + 1 : addend.bigNumArr.size() + 1);
        std::vector<uint32_t>::const_iterator iteratorAugend = augendGreater ? bigNumArr.cbegin() : addend.bigNumArr.cbegin();
        std::vector<uint32_t>::const_iterator iteratorAddend = augendGreater ? addend.bigNumArr.cbegin() : bigNumArr.cbegin();
        std::vector<uint32_t>::const_iterator iteratorAugendEnd = augendGreater ? bigNumArr.cend() : addend.bigNumArr.cend();
        std::vector<uint32_t>::const_iterator iteratorAddendEnd = augendGreater ? addend.bigNumArr.cend() : bigNumArr.cend();
        uint32_t carry = 0;
        while(iteratorAddend != iteratorAddendEnd)
        {
            uint64_t sum_temp = (uint64_t) *iteratorAugend + *iteratorAddend + carry;
            sum.bigNumArr.push_back(sum_temp & UINT32_MAX);
            carry = sum_temp >> 32;
            ++iteratorAugend;
            ++iteratorAddend;
        }
        while(iteratorAugend != iteratorAugendEnd)
        {
            uint64_t sum_temp = (uint64_t) *iteratorAugend + carry;
            sum.bigNumArr.push_back(sum_temp & UINT32_MAX);
            carry = sum_temp >> 32;
            ++iteratorAugend;
        }
        if(carry)
        {
            sum.bigNumArr.push_back(carry);
        }
        sum.positive = true;

        return sum;
    }
    else if(positive && !addend.positive)
    {
        return *this - abs(addend);
    }
    else if(!positive && addend.positive)
    {
        return addend - abs(*this);
    }
    else // !positive && !addend.positive
    {
        return -(abs(*this) + abs(addend));
    }
}

BigInt& BigInt::operator += (const BigInt& augend)
{
    *this = *this + augend;
    return *this;
}

BigInt& BigInt::operator ++()
{
    *this += ConstBigInt::ONE;
    return *this;
}

BigInt BigInt::operator ++(int)
{
    const BigInt bigNum = *this;
    ++(*this);
    return bigNum;
}

BigInt BigInt::operator -() const
{
    BigInt negative = *this;
    negative.positive = !positive;
    return negative;
}

BigInt BigInt::operator - (const BigInt& subtrahend) const
{
    if(positive && subtrahend.positive)
    {
        if(*this >= subtrahend)
        {
            BigInt difference;
            difference.bigNumArr.reserve(bigNumArr.size());
            std::vector<uint32_t>::const_iterator iteratorMinuend = bigNumArr.cbegin();
            std::vector<uint32_t>::const_iterator iteratorSubtrahend = subtrahend.bigNumArr.cbegin();
            uint32_t borrow = 0;
            while(iteratorSubtrahend != subtrahend.bigNumArr.cend())
            {
                int64_t difference_temp = (int64_t) *iteratorMinuend - *iteratorSubtrahend - borrow;
                if(difference_temp >= 0)
                {
                    difference.bigNumArr.push_back(difference_temp);
                    borrow = 0;
                }
                else // difference_temp < 0
                {
                    difference_temp += basisCalcSys;
                    difference.bigNumArr.push_back(difference_temp);
                    borrow = 1;
                }
                ++iteratorMinuend;
                ++iteratorSubtrahend;
            }
            while(iteratorMinuend != bigNumArr.cend())
            {
                int64_t difference_temp = (int64_t) *iteratorMinuend - borrow;
                if(difference_temp >= 0)
                {
                    difference.bigNumArr.push_back(difference_temp);
                    borrow = 0;
                }
                else // difference_temp < 0
                {
                    difference_temp += basisCalcSys;
                    difference.bigNumArr.push_back(difference_temp);
                    borrow = 1;
                }
                ++iteratorMinuend;
            }
            difference.deleteZeroHighOrderDigit();
            difference.positive = true;

            return difference;
        }
        else // minuend < subtrahend
        {
            return -(subtrahend - *this);
        }
    }
    else if(!positive && subtrahend.positive)
    {
        return -(abs(*this) + subtrahend);
    }
    else if(positive && !subtrahend.positive)
    {
        return *this + abs(subtrahend);
    }
    else // !positive && !subtrahend.positive
    {
        return abs(subtrahend) - abs(*this);
    }
}

BigInt& BigInt::operator -= (const BigInt& subtrahend)
{
    *this = *this - subtrahend;
    return *this;
}

BigInt& BigInt::operator -- ()
{
    *this -= ConstBigInt::ONE;
    return *this;
}

BigInt BigInt::operator -- (int)
{
    const BigInt bigNum = *this;
    --(*this);
    return bigNum;
}

BigInt BigInt::operator * (const uint32_t multiplier) const
{
    BigInt product;
    product.bigNumArr.reserve(bigNumArr.size() + 1);
    uint32_t carry = 0;
    for(std::vector<uint32_t>::const_iterator iteratorMultiplicand = bigNumArr.cbegin(); iteratorMultiplicand != bigNumArr.cend(); ++iteratorMultiplicand)
    {
        uint64_t product_temp = (uint64_t) *iteratorMultiplicand * multiplier + carry;
        product.bigNumArr.push_back(product_temp & UINT32_MAX);
        carry = product_temp >> 32;
    }
    if(carry)
    {
        product.bigNumArr.push_back(carry);
    }
    product.positive = positive;

    return product;
}

BigInt& BigInt::operator *= (const uint32_t multiplier)
{
    *this = *this * multiplier;
    return *this;
}

BigInt BigInt::operator * (const BigInt& multiplier) const
{
    BigInt product(0);
    product.bigNumArr.reserve(bigNumArr.size() + multiplier.bigNumArr.size());
    uint32_t shift = 0;
    for(std::vector<uint32_t>::const_iterator iteratorMultiplier = multiplier.bigNumArr.cbegin(); iteratorMultiplier != multiplier.bigNumArr.cend(); ++iteratorMultiplier, ++shift)
    {
        product += (*this * *iteratorMultiplier).shiftDigitsToHigh(shift);
    }
    product.positive = positive == multiplier.positive;

    return product;
}

BigInt& BigInt::operator *= (const BigInt& multiplier)
{
    *this = *this * multiplier;
    return *this;
}

std::pair<BigInt, BigInt> BigInt::DivMod(const BigInt& divisor) const
{
    const uint32_t bitLenghtDivisor = divisor.bitLenght();
    BigInt fraction(0);
    fraction.bigNumArr.reserve(bigNumArr.size());
    BigInt remainder = abs(*this);
    while(remainder >= abs(divisor))
    {
        uint32_t differenceRemainderNDivisorBitLenght = remainder.bitLenght() - bitLenghtDivisor;
        BigInt borrow = abs(divisor) << differenceRemainderNDivisorBitLenght;
        if(remainder < borrow)
        {
            borrow = abs(divisor) << --differenceRemainderNDivisorBitLenght;
        }
        remainder -= borrow;
        fraction += ConstBigInt::ONE << differenceRemainderNDivisorBitLenght; // 1 << n = 2 ^ n
    }
    fraction.positive = positive == divisor.positive;
    remainder.positive = positive;

    return std::make_pair(fraction, remainder);
}

BigInt BigInt::operator / (const BigInt& divisor) const
{
    return DivMod(divisor).first;
}

BigInt& BigInt::operator /= (const BigInt& divisor)
{
    *this = DivMod(divisor).first;
    return *this;
}

BigInt BigInt::operator % (const BigInt& divisor) const
{
    return DivMod(divisor).second;
}

BigInt& BigInt::operator %= (const BigInt& divisor)
{
    *this = DivMod(divisor).second;
    return *this;
}

BigInt pow(const BigInt& base, const BigInt& exponent)
{
    if(!exponent.positive)
    {
        return ConstBigInt::ZERO;
    }
    BigInt power(1);
    power.bigNumArr.reserve(base.bigNumArr.size() * exponent.toUint32_t());
    for(uint32_t indexBitExponent = exponent.bitLenght() - 1; indexBitExponent > 0; --indexBitExponent)
    {
        if(exponent.bigNumArr[indexBitExponent >> 5] & (1 << (indexBitExponent & 31)))
        {
            power *= base;
        }
        power *= power;
    }
    if(exponent.isOdd())
    {
        power *= base;
    }
    if(!base.positive)
    {
        power.positive = exponent.isEven();
    }
    return power;
}

uint32_t log2(const BigInt& antilogarithm)
{
    return antilogarithm.bitLenght() - 1;
}

/*BigInt powmod(BigInt base, const BigInt& exponent, const BigInt& divisor)
{
    BigInt power(1);
    power.bigNumArr.reserve(divisor.bigNumArr.size());
    const BigInt mu = power.shiftDigitsToHigh(divisor.bigNumArr.size() * 2) / divisor;
    const uint32_t bitLenghtExponent = exponent.bitLenght();
    for(uint32_t indexBitExponent = 0; indexBitExponent < bitLenghtExponent; ++indexBitExponent)
    {
        if(exponent.bigNumArr[indexBitExponent >> 5] & (1 << (indexBitExponent & 31)))
        {
            power = BarrettReduction(power * base, divisor, mu);
        }
        base = BarrettReduction(base * base, divisor, mu);
    }
    return power;
}*/

BigInt powmod(const BigInt& base, const BigInt& exponent, const BigInt& divisor)
{
    BigInt power(1);
    power.bigNumArr.reserve(divisor.bigNumArr.size());
    for(uint32_t indexBitExponent = exponent.bitLenght() - 1; indexBitExponent != UINT32_MAX; --indexBitExponent)
    {
        power = (power * power) % divisor;
        if(exponent.bigNumArr[indexBitExponent >> 5] & (1 << (indexBitExponent & 31)))
        {
            power = (power * base) % divisor;
        }
    }
    return power;
}

BigInt inversemod(BigInt dividend, const BigInt& divisor)
{
    if(divisor.isZero() || !isCoprime(dividend, divisor))
    {
        return ConstBigInt::ZERO;
    }
    BigInt divisor_copy(divisor);
    BigInt x0(0);
    BigInt x1(1);
    while (dividend > ConstBigInt::ONE)
    {
        BigInt fraction(dividend / divisor_copy);
        BigInt temp(divisor_copy);
        divisor_copy = dividend % divisor_copy;
        dividend = temp;
        temp = x0;
        x0 = x1 - (fraction * x0);
        x1 = temp;
    }
    if(!x1.positive)
    {
        x1 += divisor;
    }
    return x1;
}

bool congruencemod(const BigInt& dividend1, const BigInt& dividend2, const BigInt divisor)
{
    BigInt remainder1(dividend1 % divisor);
    BigInt remainder2(dividend2 % divisor);
    while(!remainder1.positive)
    {
        remainder1 += divisor;
    }
    while(remainder1 > divisor)
    {
        remainder1 -= divisor;
    }
    while(!remainder2.positive)
    {
        remainder2 += divisor;
    }
    while(remainder2 > divisor)
    {
        remainder2 -= divisor;
    }
    return remainder1 == remainder2;
}

bool isCoprime(const BigInt& bigNum1, const BigInt& bigNum2)
{
    return gcd(bigNum1, bigNum2) == ConstBigInt::ONE;
}

int8_t symbolJacobi(BigInt bigNum1, BigInt bigNum2)
{
    if(!isCoprime(bigNum1, bigNum2))
    {
        return 0;
    }
    int8_t symbolJacobi = 1;
    if(!bigNum1.positive)
    {
        bigNum1.positive = true;
        if(bigNum2 % ConstBigInt::FOUR == ConstBigInt::THREE)
        {
            symbolJacobi = -symbolJacobi;
        }
    }
    while(!bigNum1.isZero())
    {
        uint32_t iterator = 0;
        while(bigNum1.isEven())
        {
            bigNum1 >>= 1;
            ++iterator;
        }
        if(iterator % 2)
        {
            if(bigNum2 % ConstBigInt::EIGHT == ConstBigInt::THREE || bigNum2 % ConstBigInt::EIGHT == ConstBigInt::FIVE)
            {
                symbolJacobi = -symbolJacobi;
            }
        }
        if(bigNum1 % ConstBigInt::FOUR == ConstBigInt::THREE && bigNum2 % ConstBigInt::FOUR == ConstBigInt::THREE)
        {
            symbolJacobi = -symbolJacobi;
        }
        BigInt bigNum3(bigNum1);
        bigNum1 = bigNum2 % bigNum3;
        bigNum2 = bigNum3;
    }
    return symbolJacobi;
}

BigInt BigInt::operator ~() const
{
    return -*this - ConstBigInt::ONE;
}

BigInt BigInt::operator & (const BigInt& rightBitwiseAND) const
{
    if(positive && rightBitwiseAND.positive)
    {
        BigInt bitwiseAND;
        bitwiseAND.bigNumArr.reserve(std::min(bigNumArr.size(), rightBitwiseAND.bigNumArr.size()));
        std::vector<uint32_t>::const_iterator iteratorLeftBitwiseAND = bigNumArr.cbegin();
        std::vector<uint32_t>::const_iterator iteratorRightBitwiseAND = rightBitwiseAND.bigNumArr.cbegin();
        while(iteratorLeftBitwiseAND != bigNumArr.cend() && iteratorRightBitwiseAND != rightBitwiseAND.bigNumArr.cend())
        {
            bitwiseAND.bigNumArr.push_back(*iteratorLeftBitwiseAND & *iteratorRightBitwiseAND);
            ++iteratorLeftBitwiseAND;
            ++iteratorRightBitwiseAND;
        }
        bitwiseAND.positive = true;
        return bitwiseAND;
    }
    else if(!positive && !rightBitwiseAND.positive)
    {
        return -(~*this | ~rightBitwiseAND) - ConstBigInt::ONE;
    }
    else if(positive && !rightBitwiseAND.positive)
    {
        return (*this | ~rightBitwiseAND) + rightBitwiseAND + ConstBigInt::ONE;
    }
    else // !positive && rightBitwiseAnd.positive
    {
        return (~*this | rightBitwiseAND) + *this + ConstBigInt::ONE;
    }
}

BigInt& BigInt::operator &= (const BigInt& rightBitwiseAND)
{
    *this = *this & rightBitwiseAND;
    return *this;
}

BigInt BigInt::operator | (const BigInt& rightBitwiseOR) const
{
    if(positive && rightBitwiseOR.positive)
    {
        BigInt bitwiseOR;
        const bool leftBitwiseORGreater = (bigNumArr.size() >= rightBitwiseOR.bigNumArr.size());
        bitwiseOR.bigNumArr.reserve(leftBitwiseORGreater ? bigNumArr.size() + 1 : rightBitwiseOR.bigNumArr.size() + 1);
        std::vector<uint32_t>::const_iterator iteratorLeftBitwiseOR = leftBitwiseORGreater ? bigNumArr.cbegin() : rightBitwiseOR.bigNumArr.cbegin();
        std::vector<uint32_t>::const_iterator iteratorRightBitwiseOR = leftBitwiseORGreater ? rightBitwiseOR.bigNumArr.cbegin() : bigNumArr.cbegin();
        std::vector<uint32_t>::const_iterator iteratorLeftBitwiseOREnd = leftBitwiseORGreater ? bigNumArr.cend() : rightBitwiseOR.bigNumArr.cend();
        std::vector<uint32_t>::const_iterator iteratorRightBitwiseOREnd = leftBitwiseORGreater ? rightBitwiseOR.bigNumArr.cend() : bigNumArr.cend();
        while(iteratorRightBitwiseOR != iteratorRightBitwiseOREnd)
        {
            bitwiseOR.bigNumArr.push_back(*iteratorLeftBitwiseOR | *iteratorRightBitwiseOR);
            ++iteratorLeftBitwiseOR;
            ++iteratorRightBitwiseOR;
        }
        while(iteratorLeftBitwiseOR != iteratorLeftBitwiseOREnd)
        {
            bitwiseOR.bigNumArr.push_back(*iteratorLeftBitwiseOR);
            ++iteratorLeftBitwiseOR;
        }
        bitwiseOR.positive = true;
        return bitwiseOR;
    }
    else if(!positive && !rightBitwiseOR.positive)
    {
        return -(~*this & ~rightBitwiseOR) - ConstBigInt::ONE;
    }
    else if(positive && !rightBitwiseOR.positive)
    {
        return (*this & ~rightBitwiseOR) + rightBitwiseOR;
    }
    else // !positive && rightBitwiseOR.positive
    {
        return (~*this & rightBitwiseOR) + *this;
    }
}

BigInt& BigInt::operator |= (const BigInt& rightBitwiseOR)
{
    *this = *this | rightBitwiseOR;
    return *this;
}

BigInt BigInt::operator ^ (const BigInt& rightBitwiseXOR) const
{
    if(positive && rightBitwiseXOR.positive)
    {
        BigInt bitwiseXOR;
        const bool leftBitwiseXORGreater = (bigNumArr.size() >= rightBitwiseXOR.bigNumArr.size());
        bitwiseXOR.bigNumArr.reserve(leftBitwiseXORGreater ? bigNumArr.size() + 1 : rightBitwiseXOR.bigNumArr.size() + 1);
        std::vector<uint32_t>::const_iterator iteratorLeftBitwiseXOR = leftBitwiseXORGreater ? bigNumArr.cbegin() : rightBitwiseXOR.bigNumArr.cbegin();
        std::vector<uint32_t>::const_iterator iteratorRightBitwiseXOR = leftBitwiseXORGreater ? rightBitwiseXOR.bigNumArr.cbegin() : bigNumArr.cbegin();
        std::vector<uint32_t>::const_iterator iteratorLeftBitwiseXOREnd = leftBitwiseXORGreater ? bigNumArr.cend() : rightBitwiseXOR.bigNumArr.cend();
        std::vector<uint32_t>::const_iterator iteratorRightBitwiseXOREnd = leftBitwiseXORGreater ? rightBitwiseXOR.bigNumArr.cend() : bigNumArr.cend();
        while(iteratorRightBitwiseXOR != iteratorRightBitwiseXOREnd)
        {
            bitwiseXOR.bigNumArr.push_back(*iteratorLeftBitwiseXOR ^ *iteratorRightBitwiseXOR);
            ++iteratorLeftBitwiseXOR;
            ++iteratorRightBitwiseXOR;
        }
        while(iteratorLeftBitwiseXOR != iteratorLeftBitwiseXOREnd)
        {
            bitwiseXOR.bigNumArr.push_back(*iteratorLeftBitwiseXOR);
            ++iteratorLeftBitwiseXOR;
        }
        bitwiseXOR.positive = true;
        return bitwiseXOR;
    }
    else // !positive || !rightBitwiseXOR.positive
    {
        return (*this | rightBitwiseXOR) & (~*this | ~rightBitwiseXOR);
    }
}

BigInt& BigInt::operator ^= (const BigInt& rightBitwiseXOR)
{
    *this = *this ^ rightBitwiseXOR;
    return *this;
}

BigInt BigInt::operator << (const uint32_t shift) const
{
    if(!shift)
    {
        return *this;
    }
    BigInt shifted;
    shifted.positive = positive;
    if(shift < 32)
    {
        shifted.bigNumArr.reserve(bigNumArr.size() + 1);
        uint32_t carry = 0;
        for(std::vector<uint32_t>::const_iterator iteratorShifting = bigNumArr.cbegin(); iteratorShifting != bigNumArr.cend(); ++iteratorShifting)
        {
            uint32_t shifted_temp = (*iteratorShifting << shift) | carry;
            carry = *iteratorShifting >> (32 - shift);
            shifted.bigNumArr.push_back(shifted_temp);
        }
        if(carry)
        {
            shifted.bigNumArr.push_back(carry);
        }

        return shifted;
    }
    else // shift >= 32
    {
        shifted = *this;
        for(uint32_t indexShift = 0; indexShift < shift / (32 - 1); ++indexShift)
        {
            shifted <<= (32 - 1);
        }
        shifted <<= (shift % (32 - 1));

        return shifted;
    }
}

BigInt& BigInt::operator <<= (const uint32_t shift)
{
    *this = *this << shift;
    return *this;
}

BigInt BigInt::operator >> (const uint32_t shift) const
{
    if(!shift)
    {
        return *this;
    }
    BigInt shifted;
    shifted.positive = positive;
    if(shift < 32)
    {
        shifted.bigNumArr.reserve(bigNumArr.size());
        uint32_t carry = 0;
        for(std::vector<uint32_t>::const_reverse_iterator iteratorShifting = bigNumArr.crbegin(); iteratorShifting != bigNumArr.crend(); ++iteratorShifting)
        {
            uint32_t shifted_temp = (*iteratorShifting >> shift) | carry;
            carry = (*iteratorShifting & 1) << (32 - shift);
            shifted.bigNumArr.insert(shifted.bigNumArr.begin(), 1, shifted_temp);
        }
        shifted.deleteZeroHighOrderDigit();

        return shifted;
    }
    else // shift >= 32
    {
        shifted = *this;
        for(uint32_t indexShift = 0; indexShift < shift / (32 - 1); ++indexShift)
        {
            shifted >>= (32 - 1);
        }
        shifted >>= (shift % (32 - 1));
        shifted.deleteZeroHighOrderDigit();

        return shifted;
    }
}

BigInt& BigInt::operator >>= (const uint32_t shift)
{
    *this = *this >> shift;
    return *this;
}

BigInt BigInt::leftCircularShift(const uint32_t shift) const
{
    return (*this << shift) | (*this >> (bitLenght() - shift));
}

BigInt BigInt::rightCircularShift(const uint32_t shift) const
{
    return (*this >> shift) | (*this << (bitLenght() - shift));
}

bool BigInt::operator !() const
{
    return isZero();
}

bool BigInt::operator && (const BigInt& rightAND) const
{
    return !isZero() && !rightAND.isZero();
}

bool BigInt::operator || (const BigInt& rightOR) const
{
    return !isZero() || !rightOR.isZero();
}

bool BigInt::operator == (const BigInt& rightComparable) const
{
    return (bigNumArr == rightComparable.bigNumArr && positive == rightComparable.positive);
}

bool BigInt::operator != (const BigInt& rightComparable) const
{
    return (positive != rightComparable.positive || bigNumArr != rightComparable.bigNumArr);
}

bool BigInt::operator < (const BigInt& rightComparable) const
{
    if(positive && rightComparable.positive)
    {
        if(bigNumArr.size() > rightComparable.bigNumArr.size())
        {
            return false;
        }
        else if(bigNumArr.size() < rightComparable.bigNumArr.size())
        {
            return true;
        }
        else // bigNumArr.size() == rightComparable.BigNumArr.size()
        {
            for(std::vector<uint32_t>::const_reverse_iterator iteratorLeftComparable = bigNumArr.crbegin(), iteratorRightComparable = rightComparable.bigNumArr.crbegin() ; iteratorLeftComparable != bigNumArr.crend(); ++iteratorLeftComparable, ++iteratorRightComparable)
            {
                if(*iteratorLeftComparable != *iteratorRightComparable)
                {
                    return *iteratorLeftComparable < *iteratorRightComparable;
                }
            }
            return false;
        }
    }
    else if(positive && !rightComparable.positive)
    {
        return false;
    }
    else if(!positive && rightComparable.positive)
    {
        return true;
    }
    else // !positive && !rightComparable.positive
    {
        return abs(*this) > abs(rightComparable);
    }
}

bool BigInt::operator > (const BigInt& rightComparable) const
{
    if(positive && rightComparable.positive)
    {
        if(bigNumArr.size() > rightComparable.bigNumArr.size())
        {
            return true;
        }
        else if(bigNumArr.size() < rightComparable.bigNumArr.size())
        {
            return false;
        }
        else // bigNumArr.size == rightComparable.BigNumArr.size()
        {
            for(std::vector<uint32_t>::const_reverse_iterator iteratorLeftComparable = bigNumArr.crbegin(), iteratorRightComparable = rightComparable.bigNumArr.crbegin(); iteratorLeftComparable != bigNumArr.crend(); ++iteratorLeftComparable, ++iteratorRightComparable)
            {
                if(*iteratorLeftComparable != *iteratorRightComparable)
                {
                    return *iteratorLeftComparable > *iteratorRightComparable;
                }
            }
            return false;
        }
    }
    else if(positive && !rightComparable.positive)
    {
        return true;
    }
    else if(!positive && rightComparable.positive)
    {
        return false;
    }
    else // !positive && !rightComparable.positive
    {
        return abs(*this) < abs(rightComparable);
    }
}

bool BigInt::operator <= (const BigInt& rightComparable) const
{
    return (*this == rightComparable || *this < rightComparable);
}

bool BigInt::operator >= (const BigInt& rightComparable) const
{
    return (*this == rightComparable || *this > rightComparable);
}

BigInt abs(const BigInt& bigNum)
{
    BigInt absolute = bigNum;
    absolute.positive = true;
    return absolute;
}

BigInt gcd(BigInt bigNum1, BigInt bigNum2)
{
    if(bigNum1.isZero())
    {
        return bigNum2;
    }
    else if(bigNum2.isZero())
    {
        return bigNum1;
    }
    bigNum1.positive = true;
    bigNum2.positive = true;
    BigInt greatestCommonDivisor(1);
    while(bigNum1.isEven() && bigNum2.isEven())
    {
        bigNum1 >>= 1;
        bigNum2 >>= 1;
        greatestCommonDivisor <<= 1;
    }
    while(bigNum1.isEven())
    {
        bigNum1 >>= 1;
    }
    while(!bigNum2.isZero())
    {
        while(bigNum2.isEven())
        {
            bigNum2 >>= 1;
        }
        const BigInt bigNum1_temp = bigNum1;
        bigNum1 = min(bigNum1, bigNum2);
        bigNum2 = abs(bigNum1_temp - bigNum2);
    }
    greatestCommonDivisor *= bigNum1;

    return greatestCommonDivisor;
}

BigInt lcm(BigInt bigNum1, BigInt bigNum2)
{
    return (bigNum1 * bigNum2) / gcd(bigNum1, bigNum2);
}

const BigInt& max(const BigInt& bigNum1, const BigInt& bigNum2)
{
    return bigNum1 > bigNum2 ? bigNum1 : bigNum2;
}

const BigInt& min(const BigInt& bigNum1, const BigInt& bigNum2)
{
    return bigNum1 < bigNum2 ? bigNum1 : bigNum2;
}

std::ostream& operator << (std::ostream& out, const BigInt& bigNum)
{
    std::string bigNumberString = bigNum.toStdString(BigInt::baseOutput);
    out << bigNumberString;
    return out;
}

QDebug operator << (QDebug out, const BigInt& bigNum)
{
    std::string bigNumberString = bigNum.toStdString(BigInt::baseOutput);
    out << QString::fromStdString(bigNumberString);
    return out;
}

std::istream& operator >> (std::istream& in, BigInt& bigNum)
{
    std::string bigNumberString;
    in >> bigNumberString;
    bigNum = BigInt(bigNumberString);
    return in;
}

BigInt BarrettReduction(const BigInt& dividend, const BigInt& divisor, const BigInt& mu)
{
    BigInt remainder = dividend - ((dividend.shiftDigitsToLow(divisor.bigNumArr.size() - 1) * mu).shiftDigitsToLow(divisor.bigNumArr.size() + 1) * divisor);
    while(remainder >= divisor)
    {
        remainder -= divisor;
    }
    return remainder;
}

std::string BigInt::toStdString(const int base) const
{
    std::stringstream bigNumberStringStream;
    std::string bigNumberString;
    if(!bigNumArr.size())
    {
        return "NULL";
    }
    else if(isZero())
    {
        return "0";
    }
    if(!positive)
    {
        bigNumberStringStream << '-';
    }
    if(base == baseBinary)
    {
        for(std::vector<uint32_t>::const_reverse_iterator iterator = bigNumArr.crbegin(); iterator != bigNumArr.crend(); ++iterator)
        {
            bigNumberStringStream << std::bitset<sizeof(uint32_t) * 8>(*iterator);
        }
    }
    else if(base == baseHexadecimal)
    {
        for(std::vector<uint32_t>::const_reverse_iterator iterator = bigNumArr.crbegin(); iterator != bigNumArr.crend(); ++iterator)
        {
            bigNumberStringStream << std::hex << std::setw(8) << std::setfill('0') << *iterator;
        }
    }
    else // base == baseDecimal
    {
        const BigInt bigNumberDec = toBigIntDec();
        for(std::vector<uint32_t>::const_reverse_iterator iterator = bigNumberDec.bigNumArr.crbegin(); iterator != bigNumberDec.bigNumArr.crend(); ++iterator)
        {
            bigNumberStringStream << std::dec << std::setw(9) << std::setfill('0') << *iterator;
        }
    }
    bigNumberString = bigNumberStringStream.str();
    bigNumberString.erase(positive ? 0 : 1, bigNumberString.find_first_not_of("-0") - (positive ? 0 : 1));
    return bigNumberString;
}

std::vector<uint32_t> BigInt::toStdVectorUint32_t() const
{
    std::vector<uint32_t> bigNumberStdVectorUint32_t = bigNumArr;
    std::reverse(bigNumberStdVectorUint32_t.begin(), bigNumberStdVectorUint32_t.end());
    return bigNumberStdVectorUint32_t;
}

uint64_t BigInt::toUint64_t() const
{
    if(bigNumArr.size() == 2)
    {
        return (uint64_t(bigNumArr.back()) << 32) | bigNumArr.front();
    }
    else if (bigNumArr.size() == 1)
    {
        return bigNumArr.front();
    }
    else
    {
        return 0;
    }
}

uint32_t BigInt::toUint32_t() const
{
    if(bigNumArr.size() == 1)
    {
        return bigNumArr.front();
    }
    else
    {
        return 0;
    }
}

uint32_t BigInt::bitLenght() const
{
    if(isZero())
    {
        return 1;
    }
    uint32_t bitLenght = (bigNumArr.size() - 1) * sizeof(uint32_t) * 8;
    uint32_t highOrderDigit = bigNumArr.back();
    uint32_t bitLenghtHighOrderDigit = 0;
    while(highOrderDigit)
    {
        highOrderDigit >>= 1;
        ++bitLenghtHighOrderDigit;
    }
    bitLenght += bitLenghtHighOrderDigit;
    return bitLenght;
}

bool BigInt::isEven() const
{
    return !(bigNumArr.front() & 1);
}

bool BigInt::isOdd() const
{
    return bigNumArr.front() & 1;
}

bool BigInt::isZero() const
{
    for(std::vector<uint32_t>::const_iterator iteratorBigNumArr = bigNumArr.cbegin(); iteratorBigNumArr != bigNumArr.cend(); ++iteratorBigNumArr)
    {
        if(*iteratorBigNumArr != 0)
        {
            return false;
        }
    }
    return true;
}

bool BigInt::isPositive() const
{
    return positive;
}

bool BigInt::isNegative() const
{
    return !positive;
}

void BigInt::alignTo(BigInt& aligned)
{
    if(bigNumArr.size() > aligned.bigNumArr.size())
    {
        aligned.bigNumArr.reserve(bigNumArr.size());
        aligned.bigNumArr.resize(bigNumArr.size(), 0);
    }
    else if(aligned.bigNumArr.size() > bigNumArr.size())
    {
        bigNumArr.reserve(aligned.bigNumArr.size());
        bigNumArr.resize(aligned.bigNumArr.size(), 0);
    }
}

void BigInt::deleteZeroHighOrderDigit()
{
    while(!bigNumArr.back() && bigNumArr.size() > 1)
    {
        bigNumArr.pop_back();
    }
}

BigInt BigInt::shiftDigitsToHigh(const uint32_t shift) const
{
    BigInt shifted = *this;
    shifted.bigNumArr.insert(shifted.bigNumArr.begin(), shift, 0);

    return shifted;
}

BigInt BigInt::shiftDigitsToLow(const uint32_t shift) const
{
    BigInt shifted = *this;
    if(shifted.bigNumArr.size() > shift)
    {
        shifted.bigNumArr.erase(shifted.bigNumArr.begin(), shifted.bigNumArr.begin() + shift);
    }
    else // shifted.bigNumArr.size() <= shift
    {
        shifted.bigNumArr.clear();
        shifted.bigNumArr.push_back(0);
        shifted.positive = true;
    }

    return shifted;
}

BigInt BigInt::toBigIntDec() const
{
    const BigInt basisCalcSysDec(1000000000);
    BigInt bigNumber = *this;
    BigInt bigNumberDec;
    std::pair<BigInt, BigInt> BigNumberDivModBasisCalcSysDec;
    bigNumberDec.positive = positive;
    bigNumberDec.bigNumArr.reserve(bigNumArr.size() + 1);
    while(!bigNumber.isZero())
    {
        BigNumberDivModBasisCalcSysDec = bigNumber.DivMod(basisCalcSysDec);
        bigNumberDec.bigNumArr.push_back(BigNumberDivModBasisCalcSysDec.second.bigNumArr.front());
        bigNumber = BigNumberDivModBasisCalcSysDec.first;
    }
    return bigNumberDec;
}

std::string strDec2strBin(std::string strDec)
{
    if(strDec == "0")
    {
        return "0";
    }
    const uint8_t sizeOfCell = 9;
    const uint32_t basisCalc = 1000000000;
    std::string strBin;
    std::vector<uint32_t> bigNumArr;
    while(strDec.length() % sizeOfCell)
    {
        strDec.insert(0, 1, '0');
    }
    uint32_t sizeOfArr = strDec.length() / sizeOfCell;
    bigNumArr.reserve(sizeOfArr);
    for(uint32_t indexBigNumArr = 0; indexBigNumArr < sizeOfArr; ++indexBigNumArr)
    {
        bigNumArr.push_back(std::stoul(strDec.substr(indexBigNumArr * sizeOfCell, sizeOfCell), nullptr, 10));
    }
    std::vector<uint32_t> zeroArr;
    zeroArr.resize(bigNumArr.size(), 0);
    while(bigNumArr != zeroArr)
    {
        uint8_t carryNext = 0;
        for(std::vector<uint32_t>::iterator iteratorShifting = bigNumArr.begin(); iteratorShifting != bigNumArr.end(); ++iteratorShifting)
        {
            uint8_t carryCurrent = carryNext;
            carryNext = (*iteratorShifting & 1);
            *iteratorShifting = (*iteratorShifting + (uint32_t)carryCurrent * basisCalc) >> 1;
        }
        char charBin = carryNext ? '1' : '0';
        strBin.insert(strBin.begin(), 1, charBin);
    }
    return strBin;
}
