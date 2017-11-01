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

BigInt::BigInt()
{
}

BigInt::BigInt(const BigInt& bigNumber)
{
    bigNumArr = bigNumber.bigNumArr;
    positive = bigNumber.positive;
}

BigInt::BigInt(const std::string& bigNumberString, const int base)
{
    const std::string usedSymbols = base == baseBinary ? usedSymbolsBinary : (baseInput == baseDecimal ? usedSymbolsDecimal : usedSymbolsHexadecimal);
    const int sizeOfCell = base == baseHexadecimal ? sizeOfCellHex : sizeOfCellBin;
    std::string bigNumberStringInput = bigNumberString;
    if(bigNumberStringInput[0] == '-')
    {
        positive = false;
        bigNumberStringInput.erase(0, 1);
    }
    else
    {
        positive = true;
    }
    if(base == baseDecimal)
    {
        bigNumberStringInput = strDec2strBin(bigNumberStringInput);
    }
    while(bigNumberStringInput.length() % sizeOfCell != 0)
    {
        bigNumberStringInput.insert(0, 1, '0');
    }
    int sizeOfArr = bigNumberStringInput.length() / sizeOfCell;
    bigNumArr.clear();
    bigNumArr.reserve(sizeOfArr);
    for(int indexBigNumArr = 0; indexBigNumArr < sizeOfArr; ++indexBigNumArr)
    {
        bigNumArr.insert(bigNumArr.begin(), 1, std::stoul(bigNumberStringInput.substr(indexBigNumArr * sizeOfCell, sizeOfCell), nullptr, base == baseHexadecimal ? baseHexadecimal : baseBinary));
    }
}

BigInt::BigInt(const std::vector<uint32_t>& bigNumberVector, const bool isPositive)
{
    bigNumArr = bigNumberVector;
    positive = isPositive;
}

BigInt::BigInt(const uint32_t numberUint32_t, const bool isPositive)
{
    bigNumArr.clear();
    bigNumArr.reserve(1);
    bigNumArr.push_back(numberUint32_t);
    positive = isPositive;
}

BigInt::BigInt(const int numberInt)
{
    bigNumArr.clear();
    bigNumArr.reserve(1);
    bigNumArr.push_back(std::abs(numberInt));
    positive = (numberInt >= 0);
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

BigInt& BigInt::operator ++ ()
{
    *this += BigInt(1);
    return *this;
}

BigInt BigInt::operator ++ (int)
{
    const BigInt bigNum = *this;
    ++(*this);
    return bigNum;
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
    *this -= BigInt(1);
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
    uint32_t bitLenghtDivisor = divisor.BitLenght();
    BigInt fraction(0);
    BigInt remainder = *this;
    while(remainder >= divisor)
    {
        uint32_t bitLenghtRemainder = remainder.BitLenght();
        BigInt borrow = divisor << (bitLenghtRemainder - bitLenghtDivisor);
        if(remainder < borrow)
        {
            --bitLenghtRemainder;
            borrow = divisor << (bitLenghtRemainder - bitLenghtDivisor);
        }
        remainder -= borrow;
        fraction += BigInt(1) << (bitLenghtRemainder - bitLenghtDivisor); // 1 << n = 2 ^ n
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
    BigInt power(1);
    uint32_t bitLenghtExponent = exponent.BitLenght();
    for(uint32_t indexBitExponent = bitLenghtExponent - 1; indexBitExponent > 0; --indexBitExponent)
    {
        if((exponent.bigNumArr[indexBitExponent / BigInt::powOfBasis] >> (indexBitExponent % BigInt::powOfBasis)) & 1)
        {
            power *= base;
        }
        power *= power;
    }
    if((exponent.bigNumArr[0] >> (BigInt::powOfBasis - 1)) & 1)
    {
        power *= base;
    }
    return power;
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

    return shifted;
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

BigInt abs(const BigInt& bigNum)
{
    BigInt absolute = bigNum;
    absolute.positive = true;
    return absolute;
}

uint32_t BigInt::BitLenght() const
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
    if(bigNumArr.size() > 1)
    {
        while(bigNumArr.back() == 0)
        {
            bigNumArr.pop_back();
        }
    }
}

void print(const BigInt& bigNum)
{
    if(bigNum.bigNumArr.size() > 0)
    {
        qDebug() << bigNum.positive;
        for(std::vector<uint32_t>::const_iterator iterator = std::prev(bigNum.bigNumArr.end()); iterator >= bigNum.bigNumArr.begin(); --iterator)
        {
            qDebug() << *iterator;
        }
    }
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
