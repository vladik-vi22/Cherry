#ifndef BigIntLibrary_H
#define BigIntLibrary_H

#include <iostream>
#include <vector>
#include <string>
#include <cstdint>
#include <QDebug>

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
    BigInt(const std::string& bigNumberString, const int base = baseInput);
    BigInt(const std::vector<uint32_t>& bigNumberVector, const bool isPositive = true);
    BigInt(const uint32_t numberUint32_t, const bool isPositive = true);
    BigInt(const uint64_t numberUint64_t, const bool isPositive = true);
    BigInt(const int numberInt);
    BigInt(const long long numberLongLong);
    ~BigInt();

    BigInt& operator = (const BigInt& equal);
    BigInt& operator = (const std::string& equal);
    BigInt& operator = (const std::vector<uint32_t>& equal);
    BigInt& operator = (const uint32_t equal);
    BigInt& operator = (const uint64_t equal);
    BigInt& operator = (const int equal);
    BigInt& operator = (const long long equal);

    BigInt operator + (const BigInt& addend) const;
    BigInt& operator += (const BigInt& addend);
    BigInt& operator ++ ();
    BigInt operator ++ (int);

    BigInt operator - (const BigInt& subtrahend) const;
    BigInt& operator -= (const BigInt& subtrahend);
    BigInt& operator -- ();
    BigInt operator -- (int);

    BigInt operator * (const uint32_t multiplier) const;
    BigInt& operator *= (const uint32_t multiplier);
    BigInt operator * (const BigInt& multiplier) const;
    BigInt& operator *= (const BigInt& multiplier);

    BigInt operator / (const BigInt& divisor) const;
    BigInt& operator /= (const BigInt& divisor);

    BigInt operator % (const BigInt& divisor) const;
    BigInt& operator %= (const BigInt& divisor);

    friend BigInt pow(const BigInt& base, const BigInt& exponent);

    BigInt operator << (const uint32_t shift) const;
    BigInt& operator <<= (const uint32_t shift);
    BigInt operator >> (const uint32_t shift) const;
    BigInt& operator >>= (const uint32_t shift);

    bool operator == (const BigInt& rightComparable) const;
    bool operator > (const BigInt& rightComparable) const;
    bool operator >= (const BigInt& rightComparable) const;
    bool operator < (const BigInt& rightComparable) const;
    bool operator <= (const BigInt& rightComparable) const;
    bool operator != (const BigInt& rightComparable) const;

    friend BigInt abs(const BigInt& bigNum);
    friend BigInt gcd(BigInt bigNum1, BigInt bigNum2);

    friend const BigInt& max(const BigInt& bigNum1, const BigInt& bigNum2);
    friend const BigInt& min(const BigInt& bigNum1, const BigInt& bigNum2);

    friend std::ostream& operator << (std::ostream& out, const BigInt& bigNum);
    friend QDebug operator << (QDebug out, const BigInt& bigNum);
    friend std::istream& operator >> (std::istream& in, BigInt& bigNum);

private:
    std::pair<BigInt, BigInt> DivMod(const BigInt& divisor) const;
    uint32_t bitLenght() const;
    bool isEven() const;
    bool isOdd() const;
    void alignTo(BigInt& aligned);
    void deleteZeroHighOrderDigit();
    BigInt shiftDigitsToHigh(const uint32_t shift) const;
    BigInt shiftDigitsToLow(const uint32_t shift) const;
};

std::string strDec2strBin(std::string strDec);

#endif // BigIntLibrary_H
