#ifndef CompactLWE_H
#define CompactLWE_H

#include <bigint/BigIntLibrary.h>
#include <generators/PRBgenerators.h>

namespace Paramethers
{

struct PublicParamethers
{
    BigInt q;
    BigInt t;
    uint8_t n;
    uint8_t m;
    BigInt w;
    BigInt wPrime;
    BigInt b;
    BigInt bPrime;
    uint8_t l;
};

struct PrivateParamethers
{
    BigInt sk_max;
    BigInt p_size;
    BigInt e_min;
    BigInt e_max;
};

}

namespace Keys
{

struct PrivateKey
{
    std::vector<BigInt> s;
    BigInt k;
    BigInt sk;
    BigInt ck;
    std::vector<BigInt> sPrime;
    BigInt kPrime;
    BigInt skPrime;
    BigInt ckPrime;
    BigInt p;
};

struct PublicKeySample
{
    std::vector<BigInt> a;
    BigInt u;
    BigInt pk;
    BigInt pkPrime;
};

typedef std::vector<Keys::PublicKeySample> PublicKey;

}

class CompactLWE
{

private:
    Paramethers::PublicParamethers publicParamethers;
    Paramethers::PrivateParamethers privateParamethers;
    Keys::PrivateKey privateKey;
    Keys::PublicKey publicKey;

public:
    CompactLWE();
    ~CompactLWE();

    Paramethers::PublicParamethers getPublicParamethers() const;
    Keys::PublicKey getPublicKey() const;
    void generateKeys();
    std::vector<BigInt> basicEncrypt(const BigInt& plaintext, const CompactLWE& to);
    std::vector<BigInt> generalEncrypt(const BigInt& plaintext, const CompactLWE& to);
    BigInt basicDecrypt(const std::vector<BigInt>& ciphertext);
    BigInt generalDecrypt(const std::vector<BigInt>& ciphertext);

private:
    void generatePrivateKey();
    void generatePublicKey();
    std::vector<BigInt> generateL(const CompactLWE& to);
    std::vector<uint8_t> encode(const std::vector<uint8_t>& m, const std::vector<uint8_t>& I, const CompactLWE& to);
    std::vector<uint8_t> decode(const std::vector<uint8_t>& mPrime, const std::vector<uint8_t>& I);
};

#endif // CompactLWE_H
