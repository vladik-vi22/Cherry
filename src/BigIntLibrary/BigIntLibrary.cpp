#include "BigIntLibrary.h"

const int BigInt::baseBinary = 2;
const int BigInt::baseDecimal = 10;
const int BigInt::baseHexadecimal = 16;
const std::string BigInt::usedSymbolsBinary = "01";
const std::string BigInt::usedSymbolsDecimal = "0123456789";
const std::string BigInt::usedSymbolsHexadecimal = "0123456789abcdefABCDEF";
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

BigInt::BigInt(const std::string& bigNumberStdString, const int base)
{
    const std::string usedSymbols = base == baseBinary ? usedSymbolsBinary : (baseInput == baseDecimal ? usedSymbolsDecimal : usedSymbolsHexadecimal);
    const int sizeOfCell = base == baseHexadecimal ? sizeOfCellHex : sizeOfCellBin;
    std::string bigNumberStdStringInput = bigNumberStdString;
    qDebug() << bigNumberStdStringInput.find_first_not_of(usedSymbols);
    qDebug() << bigNumberStdStringInput.length();
    if(bigNumberStdStringInput.find_first_not_of(usedSymbols) >= bigNumberStdStringInput.length())
    {
        positive = true;
        bigNumArr.push_back(0);
        return;
    }
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

BigInt::BigInt(const std::vector<uint32_t>& bigNumberStdVectorUint32_t, const bool isPositive)
{
    bigNumArr = bigNumberStdVectorUint32_t;
    positive = isPositive;
}

BigInt::BigInt(const std::vector<std::bitset<32> > &bigNumberStdVectorBitset32, const bool isPositive)
{
    bigNumArr.reserve(bigNumberStdVectorBitset32.size());
    for(std::vector<std::bitset<32> >::const_iterator iterator = bigNumberStdVectorBitset32.begin(); iterator != bigNumberStdVectorBitset32.end(); ++iterator)
    {
        bigNumArr.push_back(iterator->to_ulong());
    }
    positive = isPositive;
}

BigInt::BigInt(const uint32_t numberUint32_t, const bool isPositive)
{
    bigNumArr.clear();
    bigNumArr.reserve(1);
    bigNumArr.push_back(numberUint32_t);
    positive = isPositive;
}

BigInt::BigInt(const uint64_t numberUint64_t, const bool isPositive)
{
    bigNumArr.clear();
    bigNumArr.reserve(2);
    bigNumArr.push_back(numberUint64_t % basisCalcSys);
    bigNumArr.push_back(numberUint64_t / basisCalcSys);
    positive = isPositive;
}

BigInt::BigInt(const int numberInt)
{
    bigNumArr.clear();
    bigNumArr.reserve(1);
    bigNumArr.push_back(std::abs(numberInt));
    positive = (numberInt >= 0);
}

BigInt::BigInt(const long long numberLongLong)
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
    if(this == &equal)
    {
        return *this;
    }
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
    if(bigNumArr == equal)
    {
        return *this;
    }
    bigNumArr = equal;
    positive = true;
    return *this;
}

BigInt& BigInt::operator = (const std::vector<std::bitset<32> >& equal)
{
    *this = BigInt(equal, true);
    return *this;
}

BigInt& BigInt::operator = (const uint32_t equal)
{
    if(bigNumArr.size() == 1 && bigNumArr.front() == equal)
    {
        return *this;
    }
    bigNumArr.clear();
    bigNumArr.push_back(equal);
    positive = true;
    return *this;
}

BigInt& BigInt::operator = (const uint64_t equal)
{
    if(bigNumArr.size() == 2 && bigNumArr.front() == equal % basisCalcSys && bigNumArr.back() == equal / basisCalcSys)
    {
        return *this;
    }
    bigNumArr.clear();
    bigNumArr.reserve(2);
    bigNumArr.push_back(equal % basisCalcSys);
    bigNumArr.push_back(equal / basisCalcSys);
    positive = true;
    return *this;
}

BigInt& BigInt::operator = (const int equal)
{
    if(bigNumArr.size() == 1 && positive == (equal >= 0) && bigNumArr.front() == (uint32_t)std::abs(equal))
    {
        return *this;
    }
    bigNumArr.clear();
    bigNumArr.push_back(std::abs(equal));
    positive = (equal >= 0);
    return *this;
}

BigInt& BigInt::operator = (const long long equal)
{
    if(bigNumArr.size() == 2 && positive == (equal >= 0) && bigNumArr.front() == std::abs(equal) % basisCalcSys && bigNumArr.back() == std::abs(equal) / basisCalcSys)
    {
        return *this;
    }
    bigNumArr.clear();
    bigNumArr.reserve(2);
    bigNumArr.push_back(std::abs(equal) % basisCalcSys);
    bigNumArr.push_back(std::abs(equal) / basisCalcSys);
    positive = (equal >= 0);
    return *this;
}

BigInt BigInt::operator +() const
{
    return abs(*this);
}

BigInt BigInt::operator + (const BigInt& addend) const
{
    BigInt sum;
    if((positive && addend.positive) || (!positive && !addend.positive))
    {
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
    else if(positive) //  && !addend.positive
    {
        sum = *this - abs(addend);

        return sum;
    }
    else // !augend.positive && addend.positive
    {
        sum = addend - abs(*this);

        return sum;
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
    negative.positive = false;
    return negative;
}

BigInt BigInt::operator - (const BigInt& subtrahend) const
{
    BigInt difference;
    if(positive && subtrahend.positive)
    {
        if(*this >= subtrahend)
        {
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
            difference = subtrahend - *this;
            difference.positive = false;

            return difference;
        }
    }
    else if(!positive && subtrahend.positive)
    {
        difference = abs(*this) + subtrahend;
        difference.positive = false;

        return difference;
    }
    else if(positive && !subtrahend.positive)
    {
        difference = *this + abs(subtrahend);

        return difference;
    }
    else // !positive && !subtrahend.positive
    {
        difference = abs(subtrahend) - abs(*this);

        return difference;
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

BigInt BigInt::operator * (const uint32_t multiplier) const
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

BigInt& BigInt::operator *= (const uint32_t multiplier)
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
    else if(exponent == 1)
    {
        return base;
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
    BigInt bitwiseNOT = *this + 1;
    bitwiseNOT.positive = !positive;
    return bitwiseNOT;
}

BigInt BigInt::operator & (const BigInt& rightBitwiseAND) const
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

BigInt& BigInt::operator &= (const BigInt& rightBitwiseAND)
{
    *this = *this & rightBitwiseAND;
    return *this;
}

BigInt BigInt::operator | (const BigInt& rightBitwiseOR) const
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

BigInt& BigInt::operator |= (const BigInt& rightBitwiseOR)
{
    *this = *this | rightBitwiseOR;
    return *this;
}

BigInt BigInt::operator ^ (const BigInt& rightBitwiseXOR) const
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

BigInt& BigInt::operator ^= (const BigInt& rightBitwiseXOR)
{
    *this = *this ^ rightBitwiseXOR;
    return *this;
}

BigInt BigInt::operator << (const uint32_t shift) const
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
    }
    else // shift >= powOfBasis
    {
        shifted = *this;
        for(uint32_t indexShift = 0; indexShift < shift / (powOfBasis - 1); ++indexShift)
        {
            shifted = shifted << (powOfBasis - 1);
        }
        shifted = shifted << (shift % (powOfBasis - 1));
    }

    return shifted;
}

BigInt& BigInt::operator <<= (const uint32_t shift)
{
    *this = *this << shift;
    return *this;
}

BigInt BigInt::operator >> (const uint32_t shift) const
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
            shifted = shifted >> (powOfBasis - 1);
        }
        shifted = shifted >> (shift % (powOfBasis - 1));
    }
    shifted.deleteZeroHighOrderDigit();

    return shifted;
}

BigInt& BigInt::operator >>= (const uint32_t shift)
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

bool BigInt::operator >= (const BigInt& rightComparable) const
{
    return (*this == rightComparable || *this > rightComparable);
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

bool BigInt::operator <= (const BigInt& rightComparable) const
{
    return (*this == rightComparable || *this < rightComparable);
}

bool BigInt::operator != (const BigInt& rightComparable) const
{
    return (positive != rightComparable.positive || bigNumArr != rightComparable.bigNumArr);
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

std::string BigInt::toStdString(const int base) const
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

BigInt BigInt::shiftDigitsToHigh(const uint32_t shift) const
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

BigInt BigInt::shiftDigitsToLow(const uint32_t shift) const
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
