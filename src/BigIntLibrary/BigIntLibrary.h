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
    static int base;
    static const std::string usedSymbolsBinary;
    static const std::string usedSymbolsDecimal;
    static const std::string usedSymbolsHexadecimal;
    static std::string usedSymbols;
    static const uint64_t basisCalcSysBinHex; // UINT32_MAX + 1 // 2^32 // 4294967296
    static const uint32_t maxNumCellBinHex; // UINT32_MAX // 4294967295
    static const uint32_t basisCalcSysDec; // 1000000000
    static const uint32_t maxNumCellDec; // 999999999
    static const uint32_t powOfBasisBinHex; // 32
    static const int sizeOfCellBin;
    static const int sizeOfCellDec;
    static const int sizeOfCellHex;
    static int sizeOfCell;

private:
    bool positive;
    std::vector<uint32_t> bigNumArr;

public:
    BigInt();
    BigInt(std::string bigNumStr);
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
    std::pair<BigInt, BigInt> DivMod(BigInt divisor);
};

BigInt abs(BigInt bigNum);
void print(BigInt BigNum);

#endif // BigIntLibrary_H
