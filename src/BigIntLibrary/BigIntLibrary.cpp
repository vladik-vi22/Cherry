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

int BigInt::base = baseDecimal;
std::string BigInt::usedSymbols = base == baseBinary ? usedSymbolsBinary : (base == baseDecimal ? usedSymbolsDecimal : usedSymbolsHexadecimal);
int BigInt::sizeOfCell = base == baseHexadecimal ? sizeOfCellHex : sizeOfCellBin;

BigInt::BigInt()
{
}

BigInt::BigInt(std::string bigNumberString)
{
    if(bigNumberString[0] == '-')
    {
        positive = false;
        bigNumberString.erase(0, 1);
    }
    else
    {
        positive = true;
    }
    if(base == baseDecimal)
    {
        bigNumberString = strDec2strBin(bigNumberString);
    }
    while(bigNumberString.length() % sizeOfCell != 0)
    {
        bigNumberString.insert(0, 1, '0');
    }
    int sizeOfArr = bigNumberString.length() / sizeOfCell;
    bigNumArr.clear();
    bigNumArr.reserve(sizeOfArr);
    for(int indexBigNumArr = 0; indexBigNumArr < sizeOfArr; ++indexBigNumArr)
    {
        bigNumArr.insert(bigNumArr.begin(), 1, std::stoul(bigNumberString.substr(indexBigNumArr * sizeOfCell, sizeOfCell), nullptr, base == baseHexadecimal ? baseHexadecimal : baseBinary));
    }
}

BigInt::BigInt(std::vector<uint32_t> bigNumberVector, bool isPositive)
{
    bigNumArr = bigNumberVector;
    positive = isPositive;
}

BigInt::BigInt(uint32_t numberUint32_t, bool isPositive)
{
    bigNumArr.clear();
    bigNumArr.reserve(1);
    bigNumArr.push_back(numberUint32_t);
    positive = isPositive;
}

BigInt::BigInt(int numberInt)
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

BigInt BigInt::operator + (BigInt addend) const
{
    BigInt sum;
    BigInt augend = *this;
    if((augend.positive && addend.positive) || (!augend.positive && !addend.positive))
    {
        sum.positive = augend.positive && addend.positive;
        augend.alignTo(addend);
        sum.bigNumArr.reserve(augend.bigNumArr.size() + 1);
        uint32_t carry = 0;
        for(std::vector<uint32_t>::iterator iteratorAugend = augend.bigNumArr.begin(), iteratorAddend = addend.bigNumArr.begin(); iteratorAugend != augend.bigNumArr.end(); ++iteratorAugend, ++iteratorAddend)
        {
            uint64_t sum_temp = (uint64_t)*iteratorAugend + (uint64_t)*iteratorAddend + (uint64_t)carry;
            sum.bigNumArr.push_back(sum_temp & maxNumCell);
            carry = sum_temp >> powOfBasis;
        }
        if(carry != 0)
        {
            sum.bigNumArr.push_back(carry);
        }

        return sum;
    }
    else if(augend.positive) //  && !addend.positive
    {
        addend = addend.abs();
        sum = augend - addend;
        return sum;
    }
    else // !augend.positive && addend.positive
    {
        augend = augend.abs();
        sum = addend - augend;
        return sum;
    }
}

BigInt& BigInt::operator += (BigInt augend)
{
    *this = *this + augend;
    return *this;
}

BigInt BigInt::operator - (BigInt subtrahend) const
{
    BigInt difference;
    BigInt minuend = *this;
    if(minuend.positive && subtrahend.positive)
    {
        if(minuend >= subtrahend)
        {
            difference.positive = true;
            minuend.alignTo(subtrahend);
            difference.bigNumArr.reserve(minuend.bigNumArr.size());
            uint32_t borrow = 0;
            for(std::vector<uint32_t>::iterator iteratorMinuend = minuend.bigNumArr.begin(), iteratorSubtrahend = subtrahend.bigNumArr.begin(); iteratorMinuend != minuend.bigNumArr.end(); ++iteratorMinuend, ++iteratorSubtrahend)
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
            }

            return difference;
        }
        else // minuend < subtrahend
        {
            difference = subtrahend - minuend;
            difference.positive = false;
            return difference;
        }
    }
    else if(subtrahend.positive) // && !minuend.positive
    {
        minuend = minuend.abs();
        difference = minuend + subtrahend;
        difference.positive = false;
        return difference;
    }
    else if(minuend.positive) // && !subtrahend.positive
    {
        subtrahend = subtrahend.abs();
        difference = minuend + subtrahend;
        return difference;
    }
    else // !minuend.positive && !subtrahend.positive
    {
        minuend = minuend.abs();
        subtrahend = subtrahend.abs();
        difference = subtrahend - minuend;
        return difference;
    }
}

BigInt& BigInt::operator -= (BigInt subtrahend)
{
    *this = *this - subtrahend;
    return *this;
}

BigInt BigInt::operator * (uint32_t multiplier) const
{
    BigInt product;
    BigInt multiplicand = *this;
    product.positive = multiplicand.positive;
    product.bigNumArr.reserve(multiplicand.bigNumArr.size() + 1);
    uint32_t carry = 0;
    for(std::vector<uint32_t>::iterator iteratorMultiplicand = multiplicand.bigNumArr.begin(); iteratorMultiplicand != multiplicand.bigNumArr.end(); ++iteratorMultiplicand)
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

BigInt& BigInt::operator *= (uint32_t multiplier)
{
    *this = *this * multiplier;
    return *this;
}

BigInt BigInt::operator * (BigInt multiplier) const
{
    BigInt product;
    BigInt multiplicand = *this;
    product.positive = multiplicand.positive == multiplier.positive;
    multiplicand.alignTo(multiplier);
    uint32_t shift = 0;
    for(std::vector<uint32_t>::iterator iteratorMultiplier = multiplier.bigNumArr.begin(); iteratorMultiplier != multiplier.bigNumArr.end(); ++iteratorMultiplier, ++shift)
    {
        BigInt product_temp = multiplicand * *iteratorMultiplier;
        product_temp = product_temp.shiftDigitsToHigh(shift);
        product += product_temp;
    }

    return product;
}

BigInt& BigInt::operator *= (BigInt multiplier)
{
    *this = *this * multiplier;
    return *this;
}

std::pair<BigInt, BigInt> BigInt::DivMod(const BigInt& divisor) const
{
    uint32_t bitLenghtDivisor = divisor.bigNumArr.size() * sizeof(uint32_t) * 8; // byte contains 8 bits
    BigInt fraction(0);
    BigInt remainder = *this;
    while (remainder >= divisor)
    {
        uint32_t bitLenghtRemainder = remainder.bigNumArr.size() * sizeof(uint32_t) * 8; // byte contains 8 bits
        BigInt C = divisor.shiftBitsToHigh(bitLenghtRemainder - bitLenghtDivisor);
        if(remainder < C)
        {
            C = divisor.shiftBitsToHigh(--bitLenghtRemainder - bitLenghtDivisor);
        }
        remainder -= C;
        fraction += BigInt(1 << (bitLenghtRemainder - bitLenghtDivisor)); // 1 << n = 2 ^ n
    }
    return std::make_pair(fraction, remainder);
}

BigInt BigInt::operator / (BigInt divisor)
{
    return DivMod(divisor).first;
}

BigInt& BigInt::operator /= (BigInt divisor)
{
    *this = DivMod(divisor).first;
    return *this;
}

BigInt BigInt::operator % (BigInt divisor)
{
    return DivMod(divisor).second;
}

BigInt& BigInt::operator %= (BigInt divisor)
{
    *this = DivMod(divisor).second;
    return *this;
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
        BigInt rightComparableAbs = rightComparable.abs();
        return abs() < rightComparableAbs;
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
                if(*iteratorLeftComparable > *iteratorRightComparable)
                {
                    return true;
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
        BigInt rightComparableAbs = rightComparable.abs();
        return abs() > rightComparableAbs;
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
                if(*iteratorLeftComparable < *iteratorRightComparable)
                {
                    return true;
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

BigInt BigInt::shiftBitsToHigh(uint32_t shift) const
{
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
            shifted = shifted.shiftBitsToHigh(powOfBasis - 1);
        }
        shifted = shifted.shiftBitsToHigh(shift % (powOfBasis - 1));
    }

    return shifted;
}

BigInt BigInt::shiftBitsToLow(uint32_t shift) const
{
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
            shifted = shifted.shiftBitsToLow(powOfBasis - 1);
        }
        shifted = shifted.shiftBitsToLow(shift % (powOfBasis - 1));
    }

    return shifted;
}

BigInt BigInt::shiftDigitsToHigh(uint32_t shift) const
{
    BigInt shifted = *this;
    shifted.bigNumArr.reserve(shifted.bigNumArr.size() + shift);
    shifted.bigNumArr.insert(shifted.bigNumArr.begin(), shift, 0);

    return shifted;
}

BigInt BigInt::shiftDigitsToLow(uint32_t shift) const
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

BigInt BigInt::abs() const
{
    BigInt absolute = *this;
    absolute.positive = true;
    return absolute;
}

BigInt abs(const BigInt& bigNum)
{
    return bigNum.abs();
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

void BigInt::print() const
{
    qDebug() << positive;
    for(std::vector<uint32_t>::const_iterator iterator = std::prev(bigNumArr.end()); iterator >= bigNumArr.begin(); --iterator)
    {
        qDebug() << *iterator;
    }
}

void print(const BigInt& BigNum)
{
    BigNum.print();
}

std::string strDec2strBin(std::string strDec)
{
    const int sizeOfCell = 9;
    const int basisCalc = 1000000000;
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
