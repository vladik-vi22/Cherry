#ifndef BigIntLibrary_H
#define BigIntLibrary_H

#include <iostream>
#include <vector>
#include <bitset>
#include <array>
#include <string>
#include <QDebug>
#include <bitset>
#include <sstream>
#include <iomanip>

class BigInt
{
    static const uint8_t baseBinary; // 2
    static const uint8_t baseDecimal; // 10
    static const uint8_t baseHexadecimal; // 16
    static const uint64_t basisCalcSys; // 2^32 // 4294967296

    static uint8_t baseInput;
    static uint8_t baseOutput;

private:
    bool positive;
    std::vector<uint32_t> bigNumArr;

public:
    BigInt();
    BigInt(const BigInt& bigNumber);
    explicit BigInt(const std::string& bigNumberStdString, const int& base = baseInput);
    explicit BigInt(const std::vector<uint32_t>& bigNumberStdVectorUint32_t, const bool& isPositive = true);
    explicit BigInt(const std::vector<uint16_t>& bigNumberStdVectorUint16_t, const bool& isPositive = true);
    explicit BigInt(const std::vector<uint8_t>& bigNumberStdVectorUint8_t, const bool& isPositive = true);
    explicit BigInt(const std::vector<bool>& bigNumberStdVectorBool, const bool& isPositive = true);
    explicit BigInt(const uint32_t& numberUint32_t, const bool& isPositive = true);
    explicit BigInt(const uint64_t& numberUint64_t, const bool& isPositive = true);
    explicit BigInt(const int& numberInt);
    explicit BigInt(const long long& numberLongLong);
    template<size_t size>
    explicit BigInt(const std::array<uint32_t, size>& bigNumberStdArrayUint32_t, const bool& isPositive = true)
    {
        bigNumArr = std::vector<uint32_t>(bigNumberStdArrayUint32_t.crbegin(), bigNumberStdArrayUint32_t.crend());
        positive = isPositive;
    }
    ~BigInt();

    BigInt& operator = (const BigInt& equal); // simple assignment

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

    BigInt operator * (const uint32_t& multiplier) const; // multiplication
    BigInt& operator *= (const uint32_t& multiplier); // multiplication assignment
    BigInt operator * (const BigInt& multiplier) const; // multiplication
    BigInt& operator *= (const BigInt& multiplier); // multiplication assignment

    BigInt operator / (const BigInt& divisor) const; // division
    BigInt& operator /= (const BigInt& divisor); // division assignment

    BigInt operator % (const BigInt& divisor) const; // modulo
    BigInt& operator %= (const BigInt& divisor); // modulo assignment

    friend BigInt pow(const BigInt& base, const BigInt& exponent); // power

    //    friend BigInt powmod(BigInt base, const BigInt& exponent, const BigInt& divisor); // power by modulo
    friend BigInt powmod(const BigInt& base, const BigInt& exponent, const BigInt& divisor); // power by modulo
    friend BigInt inversemod(BigInt dividend, const BigInt& divisor); // inverse by modulo // gcd(dividend, divisor) = 1
    friend bool congruencemod(const BigInt& dividend1, const BigInt& dividend2, const BigInt divisor); // congruence by modulo
    friend bool isCoprime(const BigInt& bigNum1, const BigInt& bigNum2);

    friend int8_t symbolJacobi(BigInt bigNum1, BigInt bigNum2);

    BigInt operator ~() const; // bitwise NOT
    BigInt operator & (const BigInt& rightBitwiseAND) const; // bitwise AND
    BigInt& operator &= (const BigInt& rightBitwiseAND); // bitwise AND assignment
    BigInt operator | (const BigInt& rightBitwiseOR) const; // bitwise OR
    BigInt& operator |= (const BigInt& rightBitwiseOR); // bitwise OR assignment
    BigInt operator ^ (const BigInt& rightBitwiseXOR) const; // bitwise XOR
    BigInt& operator ^= (const BigInt& rightBitwiseXOR); // bitwise XOR assignment

    BigInt operator << (const uint32_t& shift) const; // bitwise left shift
    BigInt& operator <<= (const uint32_t& shift); // bitwise left shift assignment
    BigInt operator >> (const uint32_t& shift) const; // bitwise right shift
    BigInt& operator >>= (const uint32_t& shift); // bitwise right shift assignment

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
    friend BigInt lcm(BigInt bigNum1, BigInt bigNum2); // least common multiple

    friend const BigInt& max(const BigInt& bigNum1, const BigInt& bigNum2);
    friend const BigInt& min(const BigInt& bigNum1, const BigInt& bigNum2);

    friend std::ostream& operator << (std::ostream& out, const BigInt& bigNum);
    friend QDebug operator << (QDebug out, const BigInt& bigNum);
    friend std::istream& operator >> (std::istream& in, BigInt& bigNum);

    std::string toStdString(const int& base = baseOutput) const;
    std::vector<uint32_t> toStdVectorUint32_t() const;
    uint64_t toUint64_t() const; // if bigNumArr.size <= 2
    uint32_t toUint32_t() const; // if bigNumArr.size == 1
    uint32_t bitLenght() const;
    bool isEven() const;
    bool isOdd() const;
    bool isZero() const;
    bool isPositive() const;
    bool isNegative() const;

private:
    std::pair<BigInt, BigInt> DivMod(const BigInt& divisor) const;
    friend BigInt BarrettReduction(const BigInt& dividend, const BigInt& divisor, const BigInt& mu);
    void alignTo(BigInt& aligned);
    void deleteZeroHighOrderDigit();
    BigInt shiftDigitsToHigh(const uint32_t& shift) const;
    BigInt shiftDigitsToLow(const uint32_t& shift) const;
    BigInt toBigIntDec() const;
};

std::string strDec2strBin(std::string strDec);

#endif // BigIntLibrary_H
