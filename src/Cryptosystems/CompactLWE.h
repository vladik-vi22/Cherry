#ifndef CompactLWE_H
#define CompactLWE_H

#include <QObject>
#include <QQuickItem>
#include "../BigIntLibrary/BigIntLibrary.h"
#include "../PRBgenerators/PRBgenerators.h"

namespace PublicParamethers
{
    const BigInt q(std::vector<uint32_t>{1, 0, 0}, true); // 2^64
    const uint64_t t = 4294967296; // 2^32
    const uint8_t n = 8;
    const uint8_t m = 128;
    const BigInt w(224);
    const BigInt wPrime(32);
    const BigInt b(16);
    const BigInt bPrime(uint64_t(68719476736));
    const uint8_t l = 8;
}

namespace PrivateParamethers
{
    const BigInt sk_max(229119);
    const BigInt p_size(16777216);
    const BigInt e_min(457);
    const BigInt e_max(3200);
}

namespace Keys
{
struct PrivateKey
{
    std::array<BigInt, PublicParamethers::n> s;
    BigInt k;
    BigInt sk;
    BigInt ck;
    std::array<BigInt, PublicParamethers::n> sPrime;
    BigInt kPrime;
    BigInt skPrime;
    BigInt ckPrime;
    BigInt p;
};

struct PublicKeySample
{
    std::array<BigInt, PublicParamethers::n> a;
    BigInt u;
    BigInt pk;
    BigInt pkPrime;
};

typedef std::array<Keys::PublicKeySample, 1/*PublicParamethers::m*/> PublicKey;
}

class CompactLWE : public QObject
{
    Q_OBJECT

private:
    Keys::PrivateKey privateKey;
    Keys::PublicKey publicKey;

public:
    explicit CompactLWE(QObject *parent = 0);
    ~CompactLWE();

    void generatePrivateKey();
    void generatePublicKey();
};

#endif // CompactLWE_H
