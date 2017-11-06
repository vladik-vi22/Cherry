#ifndef BigIntLibrary_H
#define BigIntLibrary_H

#include <iostream>
#include <vector>
#include <string>
#include <QDebug>
#include <bitset>
#include <sstream>
#include <iomanip>

class BigInt
{
    static const int baseBinary; // 2
    static const int baseDecimal; // 10
    static const int baseHexadecimal; // 16
    static const std::string usedSymbolsBinary; // "01"
    static const std::string usedSymbolsDecimal; // "0123456789"
    static const std::string usedSymbolsHexadecimal; // "0123456789abcdefABCDEF"
    static const uint64_t basisCalcSys; // UINT32_MAX + 1 // 2^32 // 4294967296
    static const uint32_t maxNumCell; // UINT32_MAX // 4294967295
    static const uint32_t powOfBasis; // 32
    static const int sizeOfCellBin; // 32
    static const int sizeOfCellHex; // 8

    static int baseInput;
    static int baseOutput;

private:
    bool positive;
    std::vector<uint32_t> bigNumArr;

public:
    BigInt();
    BigInt(const BigInt& bigNumber);
    BigInt(const std::string& bigNumberStdString, const int base = baseInput);
    BigInt(const std::vector<uint32_t>& bigNumberStdVectorUint32_t, const bool isPositive = true);
    BigInt(const std::vector<std::bitset<32> >& bigNumberStdVectorBitset32, const bool isPositive = true);
    BigInt(const uint32_t numberUint32_t, const bool isPositive = true);
    BigInt(const uint64_t numberUint64_t, const bool isPositive = true);
    BigInt(const int numberInt);
    BigInt(const long long numberLongLong);
    ~BigInt();

    BigInt& operator = (const BigInt& equal); // simple assignment
    BigInt& operator = (const std::string& equal); // simple assignment
    BigInt& operator = (const std::vector<uint32_t>& equal); // simple assignment
    BigInt& operator = (const std::vector<std::bitset<32> >& equal); // simple assignment
    BigInt& operator = (const uint32_t equal); // simple assignment
    BigInt& operator = (const uint64_t equal); // simple assignment
    BigInt& operator = (const int equal); // simple assignment
    BigInt& operator = (const long long equal); // simple assignment

    BigInt operator +() const; // unary plus
    BigInt operator + (const BigInt& addend) const; // addition
    BigInt& operator += (const BigInt& addend); // addition assignment
    BigInt& operator ++(); // pre-increment
    BigInt operator ++(int); // post-increment

    BigInt operator -() const; // unary minus
    BigInt operator - (const BigInt& subtrahend) const; // subtraction
    BigInt& operator -= (const BigInt& subtrahend); // subtraction assignment
    BigInt& operator --(); // pre-decrement
    BigInt operator --(int); // post-decrement

    BigInt operator * (const uint32_t multiplier) const; // multiplication
    BigInt& operator *= (const uint32_t multiplier); // multiplication assignment
    BigInt operator * (const BigInt& multiplier) const; // multiplication
    BigInt& operator *= (const BigInt& multiplier); // multiplication assignment

    BigInt operator / (const BigInt& divisor) const; // division
    BigInt& operator /= (const BigInt& divisor); // division assignment

    BigInt operator % (const BigInt& divisor) const; // modulo
    BigInt& operator %= (const BigInt& divisor); // modulo assignment

    friend BigInt pow(const BigInt& base, const BigInt& exponent); // power

    BigInt operator ~() const; // bitwise NOT
    BigInt operator & (const BigInt& rightBitwiseAND) const; // bitwise AND // TODO with negative
    BigInt& operator &= (const BigInt& rightBitwiseAND); // bitwise AND assignment
    BigInt operator | (const BigInt& rightBitwiseOR) const; // bitwise OR // TODO with negative
    BigInt& operator |= (const BigInt& rightBitwiseOR); // bitwise OR assignment
    BigInt operator ^ (const BigInt& rightBitwiseXOR) const; // bitwise XOR // TODO with negative
    BigInt& operator ^= (const BigInt& rightBitwiseXOR); // bitwise XOR assignment

    BigInt operator << (const uint32_t shift) const; // bitwise left shift
    BigInt& operator <<= (const uint32_t shift); // bitwise left shift assignment
    BigInt operator >> (const uint32_t shift) const; // bitwise right shift
    BigInt& operator >>= (const uint32_t shift); // bitwise right shift assignment

    bool operator !() const; // negation
    bool operator && (const BigInt& rightAND) const; // AND
    bool operator || (const BigInt& rightOR) const; // inclusive OR

    bool operator == (const BigInt& rightComparable) const; // equal to
    bool operator != (const BigInt& rightComparable) const; // not equal to
    bool operator < (const BigInt& rightComparable) const; // less than
    bool operator > (const BigInt& rightComparable) const; // greater than
    bool operator <= (const BigInt& rightComparable) const; // less than or equal to
    bool operator >= (const BigInt& rightComparable) const; // greater than or equal to

    friend BigInt abs(const BigInt& bigNum); // absolute value
    friend BigInt gcd(BigInt bigNum1, BigInt bigNum2); // greatest common divisor

    friend const BigInt& max(const BigInt& bigNum1, const BigInt& bigNum2);
    friend const BigInt& min(const BigInt& bigNum1, const BigInt& bigNum2);

    friend std::ostream& operator << (std::ostream& out, const BigInt& bigNum);
    friend QDebug operator << (QDebug out, const BigInt& bigNum);
    friend std::istream& operator >> (std::istream& in, BigInt& bigNum);

    std::string toStdString(const int base = baseOutput) const;

private:
    std::pair<BigInt, BigInt> DivMod(const BigInt& divisor) const;
    uint32_t bitLenght() const;
    bool isEven() const;
    bool isOdd() const;
    void alignTo(BigInt& aligned);
    void deleteZeroHighOrderDigit();
    BigInt shiftDigitsToHigh(const uint32_t shift) const;
    BigInt shiftDigitsToLow(const uint32_t shift) const;
    BigInt toBigIntDec() const;
};

std::string strDec2strBin(std::string strDec);

#endif // BigIntLibrary_H
