#ifndef BigIntLibrary_H
#define BigIntLibrary_H

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
    static std::string usedSymbols;
    static int sizeOfCell;

private:
    bool positive;
    std::vector<uint32_t> bigNumArr;

public:
    BigInt();
    BigInt(std::string bigNumberString);
    BigInt(std::vector<uint32_t> bigNumberVector, bool isPositive);
    BigInt(uint32_t numberUint32_t, bool isPositive);
    BigInt(int numberInt);
    ~BigInt();

    BigInt& operator = (const BigInt& equal);

    BigInt operator + (const BigInt& addend) const;
    BigInt& operator += (const BigInt& addend);

    BigInt operator - (const BigInt& subtrahend) const;
    BigInt& operator -= (const BigInt& subtrahend);

    BigInt operator * (const uint32_t multiplier) const;
    BigInt& operator *= (const uint32_t multiplier);
    BigInt operator * (const BigInt& multiplier) const;
    BigInt& operator *= (const BigInt& multiplier);

    BigInt operator / (const BigInt& divisor) const;
    BigInt& operator /= (const BigInt& divisor);

    BigInt operator % (const BigInt& divisor) const;
    BigInt& operator %= (const BigInt& divisor);

    BigInt operator ^ (const BigInt& exponent) const;
    BigInt operator ^= (const BigInt& exponent);

    bool operator == (const BigInt& rightComparable) const;
    bool operator > (const BigInt& rightComparable) const;
    bool operator >= (const BigInt& rightComparable) const;
    bool operator < (const BigInt& rightComparable) const;
    bool operator <= (const BigInt& rightComparable) const;
    bool operator != (const BigInt& rightComparable) const;

    BigInt shiftBitsToHigh(const uint32_t shift) const;
    BigInt shiftBitsToLow(const uint32_t shift) const;
    BigInt shiftDigitsToHigh(const uint32_t shift) const;
    BigInt shiftDigitsToLow(const uint32_t shift) const;

    BigInt abs() const;
    void print() const;
    uint32_t BitLenght() const;

private:
    std::pair<BigInt, BigInt> DivMod(const BigInt& divisor) const;
    void alignTo(BigInt& aligned);
    void deleteZeroHighOrderDigit();
};

BigInt abs(const BigInt& bigNum);
void print(const BigInt& BigNum);
std::string strDec2strBin(std::string strDec);

#endif // BigIntLibrary_H
