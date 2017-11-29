#include "BigIntLibrary.h"

const int BigInt::baseBinary = 2;
const int BigInt::baseDecimal = 10;
const int BigInt::baseHexadecimal = 16;
const std::string BigInt::usedCharsBinary = "01";
const std::string BigInt::usedCharsDecimal = "0123456789";
const std::string BigInt::usedCharsHexadecimal = "0123456789abcdefABCDEF";
const uint64_t BigInt::basisCalcSys = (uint64_t)UINT32_MAX + (uint64_t)1; // 2^32 // 4294967296
const uint32_t BigInt::maxNumCell = UINT32_MAX; // 2^32 - 1 // 4294967295
const uint32_t BigInt::powOfBasis = 32;
const int BigInt::sizeOfCellBin = 32;
const int BigInt::sizeOfCellHex = 8;

int BigInt::baseInput = baseDecimal;
int BigInt::baseOutput = baseDecimal;

BigInt::BigInt()
{
}

BigInt::BigInt(const BigInt& bigNumber)
{
    bigNumArr = bigNumber.bigNumArr;
    positive = bigNumber.positive;
}

BigInt::BigInt(const std::string& bigNumberStdString, const int& base)
{
    bigNumArr.clear();
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
    const std::string usedChars = base == baseBinary ? usedCharsBinary : (base == baseDecimal ? usedCharsDecimal : usedCharsHexadecimal);
    if(bigNumberStdStringInput.find_first_not_of(usedChars) != std::string::npos)
    {
        positive = true;
        bigNumArr.push_back(0);
        return;
    }
    const int sizeOfCell = base == baseHexadecimal ? sizeOfCellHex : sizeOfCellBin;
    if(base == baseDecimal)
    {
        bigNumberStdStringInput = strDec2strBin(bigNumberStdStringInput);
    }
    while(bigNumberStdStringInput.length() % sizeOfCell != 0)
    {
        bigNumberStdStringInput.insert(0, 1, '0');
    }
    int sizeOfArr = bigNumberStdStringInput.length() / sizeOfCell;
    bigNumArr.clear();
    bigNumArr.reserve(sizeOfArr);
    for(int indexBigNumArr = 0; indexBigNumArr < sizeOfArr; ++indexBigNumArr)
    {
        bigNumArr.insert(bigNumArr.begin(), 1, std::stoul(bigNumberStdStringInput.substr(indexBigNumArr * sizeOfCell, sizeOfCell), nullptr, base == baseHexadecimal ? baseHexadecimal : baseBinary));
    }
}

BigInt::BigInt(const std::vector<uint32_t>& bigNumberStdVectorUint32_t, const bool& isPositive)
{
    bigNumArr.clear();
    bigNumArr.reserve(bigNumberStdVectorUint32_t.size());
    bigNumArr = bigNumberStdVectorUint32_t;
    positive = isPositive;
}

BigInt::BigInt(const std::vector<uint16_t>& bigNumberStdVectorUint16_t, const bool& isPositive)
{
    bigNumArr.clear();
    bigNumArr.reserve(bigNumberStdVectorUint16_t.size() % 2 == 0 ? bigNumberStdVectorUint16_t.size() / 2 : bigNumberStdVectorUint16_t.size() / 2 + 1);
    std::vector<uint16_t>::const_iterator iteratorBigNumberStdVectorUint16_t = bigNumberStdVectorUint16_t.begin();
    for(uint32_t indexBigNumArr = 0; indexBigNumArr < bigNumberStdVectorUint16_t.size() / 2; ++indexBigNumArr)
    {
        bigNumArr.push_back((uint32_t)*iteratorBigNumberStdVectorUint16_t << 16 | *(++iteratorBigNumberStdVectorUint16_t));
        ++iteratorBigNumberStdVectorUint16_t;
    }
    if(bigNumberStdVectorUint16_t.size() % 2 == 1)
    {
        bigNumArr.push_back(*iteratorBigNumberStdVectorUint16_t);
    }
    positive = isPositive;
}

BigInt::BigInt(const std::vector<uint8_t>& bigNumberStdVectorUint8_t, const bool& isPositive)
{
    bigNumArr.clear();
    bigNumArr.reserve(bigNumberStdVectorUint8_t.size() % 4 == 0 ? bigNumberStdVectorUint8_t.size() / 4 : bigNumberStdVectorUint8_t.size() / 4 + 1);
    std::vector<uint8_t>::const_iterator iteratorBigNumberStdVectorUint8_t = bigNumberStdVectorUint8_t.begin();
    for(uint32_t indexBigNumArr = 0; indexBigNumArr < bigNumberStdVectorUint8_t.size() / 4; ++indexBigNumArr)
    {
        bigNumArr.push_back((uint32_t)*iteratorBigNumberStdVectorUint8_t << 24 | *(++iteratorBigNumberStdVectorUint8_t) << 16 | *(++iteratorBigNumberStdVectorUint8_t) << 8 | *(++iteratorBigNumberStdVectorUint8_t));
        ++iteratorBigNumberStdVectorUint8_t;
    }
    if(bigNumberStdVectorUint8_t.size() % 4 == 3)
    {
        bigNumArr.push_back((uint32_t)*iteratorBigNumberStdVectorUint8_t << 16 | *(++iteratorBigNumberStdVectorUint8_t) << 8 | *(++iteratorBigNumberStdVectorUint8_t));
    }
    else if(bigNumberStdVectorUint8_t.size() % 4 == 2)
    {
        bigNumArr.push_back((uint32_t)*iteratorBigNumberStdVectorUint8_t << 8 | *(++iteratorBigNumberStdVectorUint8_t));
    }
    else if(bigNumberStdVectorUint8_t.size() % 4 == 1)
    {
        bigNumArr.push_back(*iteratorBigNumberStdVectorUint8_t);
    }
    positive = isPositive;
}

BigInt::BigInt(const std::vector<bool> &bigNumberStdVectorBool, const bool &isPositive)
{
    bigNumArr.clear();
    bigNumArr.reserve(bigNumberStdVectorBool.size() % 32 == 0 ? bigNumberStdVectorBool.size() / 32 : bigNumberStdVectorBool.size() / 32 + 1);
    std::cout << bigNumberStdVectorBool.size() << std::endl;
    std::cout << bigNumArr.capacity() << std::endl;
    uint32_t bigNumArr_temp;
    std::vector<bool>::const_iterator iteratorBigNumberStdVectorBool = bigNumberStdVectorBool.begin();
    for(uint32_t indexBigNumArr = 0; indexBigNumArr < bigNumberStdVectorBool.size() / 32; ++indexBigNumArr)
    {
        bigNumArr_temp = 0;
        for(int indexBit = 31; indexBit >= 0; --indexBit)
        {
            bigNumArr_temp |= *iteratorBigNumberStdVectorBool << indexBit;
            ++iteratorBigNumberStdVectorBool;
        }
        bigNumArr.push_back(bigNumArr_temp);
        std::cout << "push" << bigNumArr_temp << std::endl;
    }
    if(bigNumberStdVectorBool.size() % 32 != 0)
    {
        bigNumArr_temp = 0;
        for(int indexBit = bigNumberStdVectorBool.size() % 32 - 1; indexBit >= 0; --indexBit)
        {
            bigNumArr_temp |= *iteratorBigNumberStdVectorBool << indexBit;
            ++iteratorBigNumberStdVectorBool;
        }
        bigNumArr.push_back(bigNumArr_temp);
        std::cout << "push" << bigNumArr_temp << std::endl;
    }
    positive = isPositive;
}

BigInt::BigInt(const uint32_t& numberUint32_t, const bool& isPositive)
{
    bigNumArr.clear();
    bigNumArr.reserve(1);
    bigNumArr.push_back(numberUint32_t);
    positive = isPositive;
}

BigInt::BigInt(const uint64_t& numberUint64_t, const bool& isPositive)
{
    bigNumArr.clear();
    bigNumArr.reserve(2);
    bigNumArr.push_back(numberUint64_t % basisCalcSys);
    bigNumArr.push_back(numberUint64_t / basisCalcSys);
    positive = isPositive;
}

BigInt::BigInt(const int& numberInt)
{
    bigNumArr.clear();
    bigNumArr.reserve(1);
    bigNumArr.push_back(std::abs(numberInt));
    positive = (numberInt >= 0);
}

BigInt::BigInt(const long long& numberLongLong)
{
    bigNumArr.clear();
    bigNumArr.reserve(2);
    bigNumArr.push_back(std::abs(numberLongLong) % basisCalcSys);
    bigNumArr.push_back(std::abs(numberLongLong) / basisCalcSys);
    positive = (numberLongLong >= 0);
}

BigInt::~BigInt()
{
}

BigInt& BigInt::operator = (const BigInt& equal)
{
    bigNumArr.clear();
    bigNumArr.reserve(equal.bigNumArr.size());
    bigNumArr = equal.bigNumArr;
    positive = equal.positive;
    return *this;
}

BigInt& BigInt::operator = (const std::string& equal)
{
    *this = BigInt(equal, baseInput);
    return *this;
}

BigInt& BigInt::operator = (const std::vector<uint32_t>& equal)
{
    bigNumArr.clear();
    bigNumArr.reserve(equal.size());
    bigNumArr = equal;
    positive = true;
    return *this;
}

BigInt& BigInt::operator = (const std::vector<uint16_t>& equal)
{
    bigNumArr.clear();
    bigNumArr.reserve(equal.size() % 2 == 0 ? equal.size() / 2 : equal.size() / 2 + 1);
    std::vector<uint16_t>::const_iterator iteratorBigNumberStdVectorUint16_t = equal.begin();
    for(uint32_t indexBigNumArr = 0; indexBigNumArr < equal.size() / 2; ++indexBigNumArr)
    {
        bigNumArr.push_back((uint32_t)*iteratorBigNumberStdVectorUint16_t << 16 | *(++iteratorBigNumberStdVectorUint16_t));
        ++iteratorBigNumberStdVectorUint16_t;
    }
    if(equal.size() % 2 == 1)
    {
        bigNumArr.push_back(*iteratorBigNumberStdVectorUint16_t);
    }
    positive = true;
    return *this;
}

BigInt& BigInt::operator = (const std::vector<uint8_t>& equal)
{
    bigNumArr.clear();
    bigNumArr.reserve(equal.size() % 4 == 0 ? equal.size() / 4 : equal.size() / 4 + 1);
    std::vector<uint8_t>::const_iterator iteratorBigNumberStdVectorUint8_t = equal.begin();
    for(uint32_t indexBigNumArr = 0; indexBigNumArr < equal.size() / 4; ++indexBigNumArr)
    {
        bigNumArr.push_back((uint32_t)*iteratorBigNumberStdVectorUint8_t << 24 | *(++iteratorBigNumberStdVectorUint8_t) << 16 | *(++iteratorBigNumberStdVectorUint8_t) << 8 | *(++iteratorBigNumberStdVectorUint8_t));
        ++iteratorBigNumberStdVectorUint8_t;
    }
    if(equal.size() % 4 == 3)
    {
        bigNumArr.push_back((uint32_t)*iteratorBigNumberStdVectorUint8_t << 16 | *(++iteratorBigNumberStdVectorUint8_t) << 8 | *(++iteratorBigNumberStdVectorUint8_t));
    }
    else if(equal.size() % 4 == 2)
    {
        bigNumArr.push_back((uint32_t)*iteratorBigNumberStdVectorUint8_t << 8 | *(++iteratorBigNumberStdVectorUint8_t));
    }
    else if(equal.size() % 4 == 1)
    {
        bigNumArr.push_back(*iteratorBigNumberStdVectorUint8_t);
    }
    positive = true;
    return *this;
}

BigInt& BigInt::operator = (const std::vector<bool>& equal)
{

    bigNumArr.clear();
    bigNumArr.reserve(equal.size() % 32 == 0 ? equal.size() / 32 : equal.size() / 32 + 1);
    uint32_t bigNumArr_temp;
    std::vector<bool>::const_iterator iteratorBigNumberStdVectorBool = equal.begin();
    for(uint32_t indexBigNumArr = 0; indexBigNumArr < equal.size() / 32; ++indexBigNumArr)
    {
        bigNumArr_temp = 0;
        for(int indexBit = 31; indexBit >= 0; --indexBit)
        {
            bigNumArr_temp |= *iteratorBigNumberStdVectorBool << indexBit;
            ++iteratorBigNumberStdVectorBool;
        }
        bigNumArr.push_back(bigNumArr_temp);
    }
    if(equal.size() % 32 != 0)
    {
        bigNumArr_temp = 0;
        for(int indexBit = equal.size() % 32 - 1; indexBit >= 0; --indexBit)
        {
            bigNumArr_temp |= *iteratorBigNumberStdVectorBool << indexBit;
            ++iteratorBigNumberStdVectorBool;
        }
        bigNumArr.push_back(bigNumArr_temp);
    }
    positive = true;
    return *this;
}

BigInt& BigInt::operator = (const uint32_t& equal)
{
    bigNumArr.clear();
    bigNumArr.push_back(equal);
    positive = true;
    return *this;
}

BigInt& BigInt::operator = (const uint64_t& equal)
{
    bigNumArr.clear();
    bigNumArr.reserve(2);
    bigNumArr.push_back(equal % basisCalcSys);
    bigNumArr.push_back(equal / basisCalcSys);
    positive = true;
    return *this;
}

BigInt& BigInt::operator = (const int& equal)
{
    bigNumArr.clear();
    bigNumArr.push_back(std::abs(equal));
    positive = (equal >= 0);
    return *this;
}

BigInt& BigInt::operator = (const long long& equal)
{
    bigNumArr.clear();
    bigNumArr.reserve(2);
    bigNumArr.push_back(std::abs(equal) % basisCalcSys);
    bigNumArr.push_back(std::abs(equal) / basisCalcSys);
    positive = (equal >= 0);
    return *this;
}

BigInt BigInt::operator +() const
{
    return *this;
}

BigInt BigInt::operator + (const BigInt& addend) const
{
    if((positive && addend.positive) || (!positive && !addend.positive))
    {
        BigInt sum;
        sum.positive = positive && addend.positive;
        bool augendGreater = (bigNumArr.size() >= addend.bigNumArr.size());
        sum.bigNumArr.reserve(augendGreater ? bigNumArr.size() + 1 : addend.bigNumArr.size() + 1);
        std::vector<uint32_t>::const_iterator iteratorAugend = augendGreater ? bigNumArr.begin() : addend.bigNumArr.begin();
        std::vector<uint32_t>::const_iterator iteratorAddend = augendGreater ? addend.bigNumArr.begin() : bigNumArr.begin();
        std::vector<uint32_t>::const_iterator iteratorAugendEnd = augendGreater ? bigNumArr.end() : addend.bigNumArr.end();
        std::vector<uint32_t>::const_iterator iteratorAddendEnd = augendGreater ? addend.bigNumArr.end() : bigNumArr.end();
        uint32_t carry = 0;
        while(iteratorAddend != iteratorAddendEnd)
        {
            uint64_t sum_temp = (uint64_t)*iteratorAugend + (uint64_t)*iteratorAddend + (uint64_t)carry;
            sum.bigNumArr.push_back(sum_temp & maxNumCell);
            carry = sum_temp >> powOfBasis;
            ++iteratorAugend;
            ++iteratorAddend;
        }
        while(iteratorAugend != iteratorAugendEnd)
        {
            uint64_t sum_temp = (uint64_t)*iteratorAugend + (uint64_t)carry;
            sum.bigNumArr.push_back(sum_temp & maxNumCell);
            carry = sum_temp >> powOfBasis;
            ++iteratorAugend;
        }
        if(carry != 0)
        {
            sum.bigNumArr.push_back(carry);
        }

        return sum;
    }
    else if(positive && !addend.positive)
    {
        return *this - abs(addend);
    }
    else // !positive && addend.positive
    {
        return addend - abs(*this);
    }
}

BigInt& BigInt::operator += (const BigInt& augend)
{
    *this = *this + augend;
    return *this;
}

BigInt& BigInt::operator ++()
{
    *this += 1;
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
            difference.positive = true;
            difference.bigNumArr.reserve(bigNumArr.size());
            std::vector<uint32_t>::const_iterator iteratorMinuend = bigNumArr.begin();
            std::vector<uint32_t>::const_iterator iteratorSubtrahend = subtrahend.bigNumArr.begin();
            uint32_t borrow = 0;
            while(iteratorSubtrahend != subtrahend.bigNumArr.end())
            {
                int64_t difference_temp = (int64_t)*iteratorMinuend - (int64_t)*iteratorSubtrahend - (int64_t)borrow;
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
            while(iteratorMinuend != bigNumArr.end())
            {
                int64_t difference_temp = (int64_t)*iteratorMinuend - (int64_t)borrow;
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
    *this -= 1;
    return *this;
}

BigInt BigInt::operator -- (int)
{
    const BigInt bigNum = *this;
    --(*this);
    return bigNum;
}

BigInt BigInt::operator * (const uint32_t& multiplier) const
{
    if(*this == 0 || multiplier == 0)
    {
        return 0;
    }
    BigInt product;
    product.positive = positive;
    product.bigNumArr.reserve(bigNumArr.size() + 1);
    uint32_t carry = 0;
    for(std::vector<uint32_t>::const_iterator iteratorMultiplicand = bigNumArr.begin(); iteratorMultiplicand != bigNumArr.end(); ++iteratorMultiplicand)
    {
        uint64_t product_temp = (uint64_t)*iteratorMultiplicand * (uint64_t)multiplier + (uint64_t)carry;
        product.bigNumArr.push_back(product_temp & maxNumCell);
        carry = product_temp >> powOfBasis;
    }
    if(carry != 0)
    {
        product.bigNumArr.push_back(carry);
    }

    return product;
}

BigInt& BigInt::operator *= (const uint32_t& multiplier)
{
    *this = *this * multiplier;
    return *this;
}

BigInt BigInt::operator * (const BigInt& multiplier) const
{
    if(*this == 0 || multiplier == 0)
    {
        return 0;
    }
    BigInt product;
    product.positive = positive == multiplier.positive;
    uint32_t shift = 0;
    for(std::vector<uint32_t>::const_iterator iteratorMultiplier = multiplier.bigNumArr.begin(); iteratorMultiplier != multiplier.bigNumArr.end(); ++iteratorMultiplier, ++shift)
    {
        BigInt product_temp = *this * *iteratorMultiplier;
        product_temp = product_temp.shiftDigitsToHigh(shift);
        product += product_temp;
    }

    return product;
}

BigInt& BigInt::operator *= (const BigInt& multiplier)
{
    *this = *this * multiplier;
    return *this;
}

std::pair<BigInt, BigInt> BigInt::DivMod(const BigInt& divisor) const
{
    uint32_t bitLenghtDivisor = divisor.bitLenght();
    BigInt fraction(0);
    BigInt remainder = abs(*this);
    while(remainder >= abs(divisor))
    {
        uint32_t bitLenghtRemainder = remainder.bitLenght();
        BigInt borrow = abs(divisor) << (bitLenghtRemainder - bitLenghtDivisor);
        if(remainder < borrow)
        {
            --bitLenghtRemainder;
            borrow = abs(divisor) << (bitLenghtRemainder - bitLenghtDivisor);
        }
        remainder -= borrow;
        fraction += BigInt(1) << (bitLenghtRemainder - bitLenghtDivisor); // 1 << n = 2 ^ n
    }
    if(fraction != 0)
    {
        fraction.positive = positive == divisor.positive;
    }
    if(remainder != 0)
    {
        remainder.positive = positive;
    }

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
    if(exponent == 0)
    {
        return 1;
    }
    else if(!exponent.positive)
    {
        return 0;
    }
    BigInt power(1);
    uint32_t bitLenghtExponent = exponent.bitLenght();
    for(uint32_t indexBitExponent = bitLenghtExponent - 1; indexBitExponent > 0; --indexBitExponent)
    {
        if(exponent.bigNumArr[indexBitExponent / BigInt::powOfBasis] & (1 << (indexBitExponent % BigInt::powOfBasis)))
        {
            power *= base;
        }
        power *= power;
    }
    if(exponent.bigNumArr.front() & 1)
    {
        power *= base;
    }
    if(!base.positive)
    {
        power.positive = exponent.isEven();
    }
    return power;
}

BigInt BigInt::operator ~() const
{
    return -*this - 1;
}

BigInt BigInt::operator & (const BigInt& rightBitwiseAND) const
{
    if(positive && rightBitwiseAND.positive)
    {
        BigInt bitwiseAND;
        bitwiseAND.bigNumArr.reserve(std::min(bigNumArr.size(), rightBitwiseAND.bigNumArr.size()));
        std::vector<uint32_t>::const_iterator iteratorLeftBitwiseAND = bigNumArr.begin();
        std::vector<uint32_t>::const_iterator iteratorRightBitwiseAND = rightBitwiseAND.bigNumArr.begin();
        while (iteratorLeftBitwiseAND != bigNumArr.end() && iteratorRightBitwiseAND != rightBitwiseAND.bigNumArr.end())
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
        return -(~*this | ~rightBitwiseAND) - 1;
    }
    else if(positive && !rightBitwiseAND.positive)
    {
        return (*this | ~rightBitwiseAND) + rightBitwiseAND + 1;
    }
    else // !positive && rightBitwiseAnd.positive
    {
        return (~*this | rightBitwiseAND) + *this + 1;
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
        std::vector<uint32_t>::const_iterator iteratorLeftBitwiseOR = leftBitwiseORGreater ? bigNumArr.begin() : rightBitwiseOR.bigNumArr.begin();
        std::vector<uint32_t>::const_iterator iteratorRightBitwiseOR = leftBitwiseORGreater ? rightBitwiseOR.bigNumArr.begin() : bigNumArr.begin();
        std::vector<uint32_t>::const_iterator iteratorLeftBitwiseOREnd = leftBitwiseORGreater ? bigNumArr.end() : rightBitwiseOR.bigNumArr.end();
        std::vector<uint32_t>::const_iterator iteratorRightBitwiseOREnd = leftBitwiseORGreater ? rightBitwiseOR.bigNumArr.end() : bigNumArr.end();
        while (iteratorRightBitwiseOR != iteratorRightBitwiseOREnd)
        {
            bitwiseOR.bigNumArr.push_back(*iteratorLeftBitwiseOR | *iteratorRightBitwiseOR);
            ++iteratorLeftBitwiseOR;
            ++iteratorRightBitwiseOR;
        }
        while (iteratorLeftBitwiseOR != iteratorLeftBitwiseOREnd)
        {
            bitwiseOR.bigNumArr.push_back(*iteratorLeftBitwiseOR);
            ++iteratorLeftBitwiseOR;
        }
        bitwiseOR.positive = true;
        return bitwiseOR;
    }
    else if(!positive && !rightBitwiseOR.positive)
    {
        return -(~*this & ~rightBitwiseOR) - 1;
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
        std::vector<uint32_t>::const_iterator iteratorLeftBitwiseXOR = leftBitwiseXORGreater ? bigNumArr.begin() : rightBitwiseXOR.bigNumArr.begin();
        std::vector<uint32_t>::const_iterator iteratorRightBitwiseXOR = leftBitwiseXORGreater ? rightBitwiseXOR.bigNumArr.begin() : bigNumArr.begin();
        std::vector<uint32_t>::const_iterator iteratorLeftBitwiseXOREnd = leftBitwiseXORGreater ? bigNumArr.end() : rightBitwiseXOR.bigNumArr.end();
        std::vector<uint32_t>::const_iterator iteratorRightBitwiseXOREnd = leftBitwiseXORGreater ? rightBitwiseXOR.bigNumArr.end() : bigNumArr.end();
        while (iteratorRightBitwiseXOR != iteratorRightBitwiseXOREnd)
        {
            bitwiseXOR.bigNumArr.push_back(*iteratorLeftBitwiseXOR ^ *iteratorRightBitwiseXOR);
            ++iteratorLeftBitwiseXOR;
            ++iteratorRightBitwiseXOR;
        }
        while (iteratorLeftBitwiseXOR != iteratorLeftBitwiseXOREnd)
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

BigInt BigInt::operator << (const uint32_t& shift) const
{
    if(shift == 0)
    {
        return *this;
    }
    BigInt shifted;
    shifted.positive = positive;
    if(shift < powOfBasis)
    {
        shifted.bigNumArr.reserve(bigNumArr.size() + 1);
        uint32_t carry = 0;
        for(std::vector<uint32_t>::const_iterator iteratorShifting = bigNumArr.begin(); iteratorShifting != bigNumArr.end(); ++iteratorShifting)
        {
            uint32_t shifted_temp = *iteratorShifting << shift;
            shifted_temp |= carry;
            carry = *iteratorShifting >> (powOfBasis - shift);
            shifted.bigNumArr.push_back(shifted_temp);
        }
        if(carry != 0)
        {
            shifted.bigNumArr.push_back(carry);
        }

        return shifted;
    }
    else // shift >= powOfBasis
    {
        shifted = *this;
        for(uint32_t indexShift = 0; indexShift < shift / (powOfBasis - 1); ++indexShift)
        {
            shifted <<= (powOfBasis - 1);
        }
        shifted <<= (shift % (powOfBasis - 1));

        return shifted;
    }
}

BigInt& BigInt::operator <<= (const uint32_t& shift)
{
    *this = *this << shift;
    return *this;
}

BigInt BigInt::operator >> (const uint32_t& shift) const
{
    if(shift == 0)
    {
        return *this;
    }
    BigInt shifted;
    shifted.positive = positive;
    if(shift < powOfBasis)
    {
        shifted.bigNumArr.reserve(bigNumArr.size());
        uint32_t carry = 0;
        for(std::vector<uint32_t>::const_iterator iteratorShifting = std::prev(bigNumArr.end()); iteratorShifting >= bigNumArr.begin(); --iteratorShifting)
        {
            uint32_t shifted_temp = *iteratorShifting >> shift;
            shifted_temp |= carry;
            carry = (*iteratorShifting & 1) << (powOfBasis - shift);
            shifted.bigNumArr.insert(shifted.bigNumArr.begin(), 1, shifted_temp);
        }
    }
    else // shift >= powOfBasis
    {
        shifted = *this;
        for(uint32_t indexShift = 0; indexShift < shift / (powOfBasis - 1); ++indexShift)
        {
            shifted >>= (powOfBasis - 1);
        }
        shifted >>= (shift % (powOfBasis - 1));
    }
    shifted.deleteZeroHighOrderDigit();

    return shifted;
}

BigInt& BigInt::operator >>= (const uint32_t& shift)
{
    *this = *this >> shift;
    return *this;
}

bool BigInt::operator !() const
{
    if(*this == 0)
    {
        return true;
    }
    else // *this != 0
    {
        return false;
    }
}

bool BigInt::operator && (const BigInt& rightAND) const
{
    if(*this == 0 || rightAND == 0)
    {
        return false;
    }
    else // *this != 0 && rightAND != 0
    {
        return true;
    }
}

bool BigInt::operator || (const BigInt& rightOR) const
{
    if(*this == 0 && rightOR == 0)
    {
        return false;
    }
    else // *this != 0 || rightOR != 0
    {
        return true;
    }
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
    if(positive && !rightComparable.positive)
    {
        return false;
    }
    else if(!positive && rightComparable.positive)
    {
        return true;
    }
    else if(!positive && !rightComparable.positive)
    {
        return abs(*this) > abs(rightComparable);
    }
    else // positive && rightComparable.posistive
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
            for(std::vector<uint32_t>::const_iterator iteratorLeftComparable = std::prev(bigNumArr.end()), iteratorRightComparable = std::prev(rightComparable.bigNumArr.end()) ; iteratorLeftComparable >= bigNumArr.begin(); --iteratorLeftComparable, --iteratorRightComparable)
            {
                if(*iteratorLeftComparable != *iteratorRightComparable)
                {
                    return *iteratorLeftComparable < *iteratorRightComparable;
                }
            }
            return false;
        }
    }
}

bool BigInt::operator > (const BigInt& rightComparable) const
{
    if(positive && !rightComparable.positive)
    {
        return true;
    }
    else if(!positive && rightComparable.positive)
    {
        return false;
    }
    else if(!positive && !rightComparable.positive)
    {
        return abs(*this) < abs(rightComparable);
    }
    else // positive && rightComparable.posistive
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
            for(std::vector<uint32_t>::const_iterator iteratorLeftComparable = std::prev(bigNumArr.end()), iteratorRightComparable = std::prev(rightComparable.bigNumArr.end()); iteratorLeftComparable >= bigNumArr.begin(); --iteratorLeftComparable, --iteratorRightComparable)
            {
                if(*iteratorLeftComparable != *iteratorRightComparable)
                {
                    return *iteratorLeftComparable > *iteratorRightComparable;
                }
            }
            return false;
        }
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
    while(bigNum2 != 0)
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
    bigNum = bigNumberString;
    return in;
}

BigInt BarrettReduction(const BigInt& dividend, const BigInt& divisor, const BigInt& mu)
{
    BigInt fraction;
    BigInt remainder;
    fraction = dividend.shiftDigitsToLow(divisor.bigNumArr.size() - 1);
    fraction *= mu;
    fraction = fraction.shiftDigitsToLow(divisor.bigNumArr.size() + 1);
    remainder = dividend - fraction * divisor;
    while (remainder >= divisor)
    {
        remainder -= divisor;
    }
    return remainder;
}

/*BigInt ModPowerBarrett(const BigInt& base, const BigInt& exponent, const BigInt& divisor)
{
    BigInt power = 1;
    return power;
}*/

std::string BigInt::toStdString(const int& base) const
{
    std::stringstream bigNumberStringStream;
    std::string bigNumberString;
    if(bigNumArr.size() == 0 || *this == 0)
    {
        return "0";
    }
    if(!positive)
    {
        bigNumberStringStream << '-';
    }
    if(base == baseBinary)
    {
        for(std::vector<uint32_t>::const_iterator iterator = std::prev(bigNumArr.end()); iterator >= bigNumArr.begin(); --iterator)
        {
            bigNumberStringStream << std::bitset<sizeOfCellBin>(*iterator);
        }
    }
    else if(base == baseHexadecimal)
    {
        for(std::vector<uint32_t>::const_iterator iterator = std::prev(bigNumArr.end()); iterator >= bigNumArr.begin(); --iterator)
        {
            bigNumberStringStream << std::hex << std::setw(8) << std::setfill('0') << *iterator;
        }
    }
    else // base == baseDecimal
    {
        BigInt bigNumberDec = toBigIntDec();
        for(std::vector<uint32_t>::const_iterator iterator = std::prev(bigNumberDec.bigNumArr.end()); iterator >= bigNumberDec.bigNumArr.begin(); --iterator)
        {
            bigNumberStringStream << std::dec << std::setw(9) << std::setfill('0') << *iterator;
        }
    }
    bigNumberString = bigNumberStringStream.str();
    bigNumberString.erase(positive ? 0 : 1, bigNumberString.find_first_not_of("-0") - (positive ? 0 : 1));
    return bigNumberString;
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
    uint32_t bitLenght = 0;
    bitLenght += (bigNumArr.size() - 1) * sizeof(uint32_t) * 8;
    uint32_t highOrderDigit = bigNumArr.back();
    uint32_t bitLenghtHighOrderDigit = 0;
    while(highOrderDigit != 0)
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
    while(bigNumArr.back() == 0 && bigNumArr.size() > 1)
    {
        bigNumArr.pop_back();
    }
}

BigInt BigInt::shiftDigitsToHigh(const uint32_t& shift) const
{
    if(shift == 0)
    {
        return *this;
    }
    BigInt shifted = *this;
    shifted.bigNumArr.reserve(shifted.bigNumArr.size() + shift);
    shifted.bigNumArr.insert(shifted.bigNumArr.begin(), shift, 0);

    return shifted;
}

BigInt BigInt::shiftDigitsToLow(const uint32_t& shift) const
{
    if(shift == 0)
    {
        return *this;
    }
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
    const uint32_t basisCalcSysDec = 1000000000;
    BigInt bigNumber = *this;
    BigInt bigNumberDec;
    bigNumberDec.positive = positive;
    bigNumberDec.bigNumArr.reserve(bigNumArr.size() + 1);
    std::pair<BigInt, BigInt> BigNumberDivModBasisCalcSysDec;
    while(bigNumber != 0)
    {
        BigNumberDivModBasisCalcSysDec = bigNumber.DivMod(basisCalcSysDec);
        bigNumberDec.bigNumArr.push_back(BigNumberDivModBasisCalcSysDec.second.bigNumArr.front());
        bigNumber = BigNumberDivModBasisCalcSysDec.first;
    }
    return bigNumberDec;
}

std::string strDec2strBin(std::string strDec)
{
    const int sizeOfCell = 9;
    const uint32_t basisCalc = 1000000000;
    std::string strBin;
    std::vector<uint32_t> bigNumArr;
    while(strDec.length() % sizeOfCell != 0)
    {
        strDec.insert(0, 1, '0');
    }
    int sizeOfArr = strDec.length() / sizeOfCell;
    bigNumArr.reserve(sizeOfArr);
    for(int indexBigNumArr = 0; indexBigNumArr < sizeOfArr; ++indexBigNumArr)
    {
        bigNumArr.push_back(std::stoul(strDec.substr(indexBigNumArr * sizeOfCell, sizeOfCell), nullptr, 10));
    }
    std::vector<uint32_t> zeroArr;
    zeroArr.resize(bigNumArr.size(), 0);
    while(bigNumArr != zeroArr)
    {
        uint32_t carryNext = 0;
        for(std::vector<uint32_t>::iterator iteratorShifting = bigNumArr.begin(); iteratorShifting != bigNumArr.end(); ++iteratorShifting)
        {
            uint32_t carryCurrent = carryNext;
            carryNext = (*iteratorShifting & 1);
            *iteratorShifting = (*iteratorShifting + carryCurrent * basisCalc) >> 1;
        }
        char charBin = carryNext == 0 ? '0' : '1';
        strBin.insert(strBin.begin(), 1, charBin);
    }
    return strBin;
}
