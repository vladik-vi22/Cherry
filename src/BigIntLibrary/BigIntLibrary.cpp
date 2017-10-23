#include "BigIntLibrary.h"

const int BigInt::baseBinary = 2;
const int BigInt::baseDecimal = 10;
const int BigInt::baseHexadecimal = 16;
const std::string BigInt::usedSymbolsBinary = "01";
const std::string BigInt::usedSymbolsDecimal = "0123456789";
const std::string BigInt::usedSymbolsHexadecimal = "0123456789abcdefABCDEF";
const uint64_t BigInt::basisCalcSysBinHex = (uint64_t)UINT32_MAX + (uint64_t)1; // 2^32 // 4294967296
const uint32_t BigInt::maxNumCellBinHex = UINT32_MAX; // 2^32 - 1 // 4294967295
const uint32_t BigInt::basisCalcSysDec = 1000000000;
const uint32_t BigInt::maxNumCellDec = 999999999;
const uint32_t BigInt::powOfBasisBinHex = 32;
const int BigInt::sizeOfCellBin = 32;
const int BigInt::sizeOfCellDec = 9;
const int BigInt::sizeOfCellHex = 8;

int BigInt::base = baseDecimal;
std::string BigInt::usedSymbols = base == baseBinary ? usedSymbolsBinary : (base == baseDecimal ? usedSymbolsDecimal : usedSymbolsHexadecimal);
int BigInt::sizeOfCell = base == baseBinary ? sizeOfCellBin : (base == baseDecimal ? sizeOfCellDec : sizeOfCellHex);

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
    while(bigNumberString.length() % sizeOfCell != 0)
    {
        bigNumberString.insert(0, 1, '0');
    }
    int sizeOfArr = bigNumberString.length() / sizeOfCell;
    bigNumArr.reserve(sizeOfArr);
    for(int indexBigNumArr = 0; indexBigNumArr < sizeOfArr; ++indexBigNumArr)
    {
        bigNumArr.insert(bigNumArr.begin(), 1, std::stoul(bigNumberString.substr(indexBigNumArr * sizeOfCell, sizeOfCell), nullptr, base));
    }
}

BigInt::BigInt(std::vector<uint32_t> bigNumberVector, bool isPositive)
{
    bigNumArr = bigNumberVector;
    positive = isPositive;
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

BigInt BigInt::operator + (BigInt addend)
{
    BigInt sum;
    BigInt augend = *this;
    if((augend.positive && addend.positive) || (!augend.positive && !addend.positive))
    {
        sum.positive = augend.positive && addend.positive;
        augend.alignTo(addend);
        sum.bigNumArr.reserve(augend.bigNumArr.size() + 1);
        uint32_t carry = 0;
        if(base == baseHexadecimal || base == baseBinary)
        {
            for(std::vector<uint32_t>::iterator iteratorAugend = augend.bigNumArr.begin(), iteratorAddend = addend.bigNumArr.begin(); iteratorAugend != augend.bigNumArr.end(); ++iteratorAugend, ++iteratorAddend)
            {
                uint64_t sum_temp = (uint64_t)*iteratorAugend + (uint64_t)*iteratorAddend + (uint64_t)carry;
                sum.bigNumArr.push_back(sum_temp & maxNumCellBinHex);
                carry = sum_temp >> powOfBasisBinHex;
            }
        }
        else // base == baseDecimal
        {
            for(std::vector<uint32_t>::iterator iteratorAugend = augend.bigNumArr.begin(), iteratorAddend = addend.bigNumArr.begin(); iteratorAugend != augend.bigNumArr.end(); ++iteratorAugend, ++iteratorAddend)
            {
                uint32_t sum_temp = *iteratorAugend + *iteratorAddend + carry;
                sum.bigNumArr.push_back(sum_temp % basisCalcSysDec);
                carry = sum_temp / basisCalcSysDec;
            }
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

BigInt BigInt::operator - (BigInt subtrahend)
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
            uint64_t basis = base == (baseBinary || baseHexadecimal) ? (uint64_t)basisCalcSysBinHex : (uint64_t)basisCalcSysDec;
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
                    difference_temp += basis;
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

BigInt BigInt::operator * (uint32_t multiplier)
{
    BigInt product;
    BigInt multiplicand = *this;
    product.positive = multiplicand.positive;
    product.bigNumArr.reserve(multiplicand.bigNumArr.size() + 1);
    uint32_t carry = 0;
    if(base == baseHexadecimal || base == baseBinary)
    {
        for(std::vector<uint32_t>::iterator iteratorMultiplicand = multiplicand.bigNumArr.begin(); iteratorMultiplicand != multiplicand.bigNumArr.end(); ++iteratorMultiplicand)
        {
            uint64_t product_temp = (uint64_t)*iteratorMultiplicand * (uint64_t)multiplier + (uint64_t)carry;
            product.bigNumArr.push_back(product_temp & maxNumCellBinHex);
            carry = product_temp >> powOfBasisBinHex;
        }
    }
    else // base == baseDecimal
    {
        for(std::vector<uint32_t>::iterator iteratorMultiplicand = multiplicand.bigNumArr.begin(); iteratorMultiplicand != multiplicand.bigNumArr.end(); ++iteratorMultiplicand)
        {
            uint64_t product_temp = (uint64_t)*iteratorMultiplicand * (uint64_t)multiplier + (uint64_t)carry;
            product.bigNumArr.push_back(product_temp % basisCalcSysDec);
            carry = product_temp / basisCalcSysDec;
        }
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

BigInt BigInt::operator * (BigInt multiplier)
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

bool BigInt::operator == (BigInt rightComparable)
{
    BigInt leftComparable = *this;
    if(leftComparable.bigNumArr.size() != rightComparable.bigNumArr.size() || leftComparable.positive != rightComparable.positive)
    {
        return false;
    }
    else // leftComparable.bigNumArr.size() == rightComparable.bigNumArr.size() && leftComparable.positive == rightComparable.positive)
    {
        for(std::vector<uint32_t>::iterator iteratorLeftComparable = leftComparable.bigNumArr.end() - 1, iteratorRightComparable = rightComparable.bigNumArr.end() - 1; iteratorLeftComparable >= leftComparable.bigNumArr.begin(); --iteratorLeftComparable, --iteratorRightComparable)
        {
            if(*iteratorLeftComparable != *iteratorRightComparable)
            {
                return false;
            }
        }
        return true;
    }
}

bool BigInt::operator > (BigInt rightComparable)
{
    BigInt leftComparable = *this;
    if(leftComparable.positive && !rightComparable.positive)
    {
        return true;
    }
    else if(!leftComparable.positive && rightComparable.positive)
    {
        return false;
    }
    else if(!leftComparable.positive && !rightComparable.positive)
    {
        leftComparable = leftComparable.abs();
        rightComparable = rightComparable.abs();
        return leftComparable < rightComparable;
    }
    else // leftComparable.positive && rightComparable.posistive
    {
        if(leftComparable.bigNumArr.size() > rightComparable.bigNumArr.size())
        {
            return true;
        }
        else if(leftComparable.bigNumArr.size() < rightComparable.bigNumArr.size())
        {
            return false;
        }
        else // leftComparable.bigNumArr.size == rightComparable.BigNumArr.size()
        {
            for(std::vector<uint32_t>::iterator iteratorLeftComparable = leftComparable.bigNumArr.end() - 1, iteratorRightComparable = rightComparable.bigNumArr.end() - 1; iteratorLeftComparable >= leftComparable.bigNumArr.begin(); --iteratorLeftComparable, --iteratorRightComparable)
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

bool BigInt::operator >= (BigInt rightComparable)
{
    BigInt leftComparable = *this;
    return (leftComparable == rightComparable || leftComparable > rightComparable);
}

bool BigInt::operator < (BigInt rightComparable)
{
    BigInt leftComparable = *this;
    if(leftComparable.positive && !rightComparable.positive)
    {
        return false;
    }
    else if(!leftComparable.positive && rightComparable.positive)
    {
        return true;
    }
    else if(!leftComparable.positive && !rightComparable.positive)
    {
        leftComparable = leftComparable.abs();
        rightComparable = rightComparable.abs();
        return leftComparable > rightComparable;
    }
    else // leftComparable.positive && rightComparable.posistive
    {
        if(leftComparable.bigNumArr.size() > rightComparable.bigNumArr.size())
        {
            return false;
        }
        else if(leftComparable.bigNumArr.size() < rightComparable.bigNumArr.size())
        {
            return true;
        }
        else // leftComparable.bigNumArr.size() == rightComparable.BigNumArr.size()
        {
            for(std::vector<uint32_t>::iterator iteratorLeftComparable = leftComparable.bigNumArr.end() - 1, iteratorRightComparable = rightComparable.bigNumArr.end() - 1; iteratorLeftComparable >= leftComparable.bigNumArr.begin(); --iteratorLeftComparable, --iteratorRightComparable)
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

bool BigInt::operator <= (BigInt rightComparable)
{
    BigInt leftComparable = *this;
    return (leftComparable == rightComparable || leftComparable < rightComparable);
}

bool BigInt::operator != (BigInt rightComparable)
{
    BigInt leftComparable = *this;
    return !(leftComparable == rightComparable);
}

BigInt BigInt::shiftBitsToHigh(uint32_t shift)
{
    BigInt shifted;
    BigInt shifting = *this;
    shifted.positive = shifting.positive;
    if(shift == 1)
    {
        shifted.bigNumArr.reserve(shifting.bigNumArr.size() + 1);
        uint32_t carry = 0;
        if(base == baseBinary || base == baseHexadecimal)
        {
            for(std::vector<uint32_t>::iterator iteratorShifting = shifting.bigNumArr.begin(); iteratorShifting != shifting.bigNumArr.end(); ++iteratorShifting)
            {
                uint32_t shifted_temp = *iteratorShifting << shift;
                shifted_temp |= carry;
                carry = *iteratorShifting >> (powOfBasisBinHex - shift);
                shifted.bigNumArr.push_back(shifted_temp);
            }
        }
        else // base == baseDecimal
        {
            for(std::vector<uint32_t>::iterator iteratorShifting = shifting.bigNumArr.begin(); iteratorShifting != shifting.bigNumArr.end(); ++iteratorShifting)
            {
                uint32_t shifted_temp = *iteratorShifting << shift;
                shifted_temp += carry;
                carry = shifted_temp / basisCalcSysDec;
                shifted_temp = shifted_temp % basisCalcSysDec;
                shifted.bigNumArr.push_back(shifted_temp);
            }
        }
        if(carry != 0)
        {
            shifted.bigNumArr.push_back(carry);
        }
    }
    else
    {
        shifted = shifting;
        for(uint32_t indexShift = 0; indexShift < shift; ++indexShift)
        {
            shifted = shifted.shiftBitsToHigh(1);
        }
    }

    return shifted;
}

BigInt BigInt::shiftBitsToLow(uint32_t shift)
{
    BigInt shifted;
    BigInt shifting = *this;
    shifted.positive = shifting.positive;
    if(shift == 1)
    {
        shifted.bigNumArr.reserve(shifting.bigNumArr.size());
        uint32_t carry = 0;
        if(base == baseBinary || base == baseHexadecimal)
        {
            for(std::vector<uint32_t>::iterator iteratorShifting = shifting.bigNumArr.end() - 1; iteratorShifting >= shifting.bigNumArr.begin(); --iteratorShifting)
            {
                uint32_t shifted_temp = *iteratorShifting >> shift;
                shifted_temp |= carry;
                carry = (*iteratorShifting & 1) << (powOfBasisBinHex - shift);
                shifted.bigNumArr.insert(shifted.bigNumArr.begin(), 1, shifted_temp);
            }
        }
        else // base == baseDecimal
        {
            for(std::vector<uint32_t>::iterator iteratorShifting = shifting.bigNumArr.end() - 1; iteratorShifting >= shifting.bigNumArr.begin(); --iteratorShifting)
            {
                uint32_t shifted_temp = *iteratorShifting >> shift;
                shifted_temp += carry >> shift;
                carry = (*iteratorShifting % 2) * basisCalcSysDec;
                shifted.bigNumArr.insert(shifted.bigNumArr.begin(), 1, shifted_temp);
            }
        }
    }
    else
    {
        shifted = shifting;
        for(uint32_t indexShift = 0; indexShift < shift; ++indexShift)
        {
            shifted = shifted.shiftBitsToLow(1);
        }
    }

    return shifted;
}

BigInt BigInt::shiftDigitsToHigh(uint32_t shift)
{
    BigInt shifted = *this;
    shifted.bigNumArr.reserve(shifted.bigNumArr.size() + shift);
    shifted.bigNumArr.insert(shifted.bigNumArr.begin(), shift, 0);

    return shifted;
}

BigInt BigInt::shiftDigitsToLow(uint32_t shift)
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

/*std::pair<BigInt, BigInt> BigInt::DivMod(BigInt divisor)
{
    BigInt fraction;
    BigInt remainder;
}*/

BigInt BigInt::abs()
{
    BigInt absolute = *this;
    absolute.positive = true;
    return absolute;
}

BigInt abs(BigInt bigNum)
{
    return bigNum.abs();
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

void BigInt::print()
{
    qDebug() << positive;
    for(std::vector<uint32_t>::iterator iterator = bigNumArr.end() - 1; iterator >= bigNumArr.begin(); --iterator)
    {
        qDebug() << *iterator;
    }
}

void print(BigInt BigNum)
{
    BigNum.print();
}
