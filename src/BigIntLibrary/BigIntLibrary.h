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
    static const uint64_t basisCalcSysBinHex; // UINT32_MAX + 1 // 2^32 // 4294967296
    static const uint32_t maxNumCellBinHex; // UINT32_MAX // 4294967295
    static const uint32_t basisCalcSysDec; // 1000000000
    static const uint32_t maxNumCellDec; // 999999999
    static const uint32_t powOfBasisBinHex; // 32
    static const int sizeOfCellBin; // 32
    static const int sizeOfCellDec; // 9
    static const int sizeOfCellHex; // 8

    static int base;
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

    BigInt operator + (BigInt addend);
    BigInt& operator += (BigInt addend);
    BigInt operator - (BigInt subtrahend);
    BigInt& operator -= (BigInt subtrahend);

    BigInt operator * (uint32_t multiplier);
    BigInt& operator *= (uint32_t multiplier);
    BigInt operator * (BigInt multiplier);
    BigInt& operator *= (BigInt multiplier);

    BigInt operator / (BigInt divisor);
    BigInt& operator /= (BigInt divisor);

    BigInt operator % (BigInt divisor);
    BigInt& operator %= (BigInt divisor);

    bool operator == (BigInt rightComparable);
    bool operator > (BigInt rightComparable);
    bool operator >= (BigInt rightComparable);
    bool operator < (BigInt rightComparable);
    bool operator <= (BigInt rightComparable);
    bool operator != (BigInt rightComparable);

    BigInt shiftBitsToHigh(uint32_t shift);
    BigInt shiftBitsToLow(uint32_t shift);
    BigInt shiftDigitsToHigh(uint32_t shift);
    BigInt shiftDigitsToLow(uint32_t shift);

    BigInt abs();
    void print();

private:
    std::pair<BigInt, BigInt> DivMod(BigInt divisor);
    void alignTo(BigInt& aligned);
};

BigInt abs(BigInt bigNum);
void print(BigInt BigNum);

#endif // BigIntLibrary_H
