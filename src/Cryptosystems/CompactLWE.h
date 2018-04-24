#ifndef CompactLWE_H
#define CompactLWE_H

#include <QObject>
#include <QQuickItem>
#include "../BigIntLibrary/BigIntLibrary.h"
#include "../PRBgenerators/PRBgenerators.h"

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

class CompactLWE : public QObject
{
    Q_OBJECT

private:
    Paramethers::PublicParamethers publicParamethers;
    Paramethers::PrivateParamethers privateParamethers;
    Keys::PrivateKey privateKey;
    Keys::PublicKey publicKey;

public:
    explicit CompactLWE(QObject *parent = 0);
    ~CompactLWE();

    Paramethers::PublicParamethers getPublicParamethers() const;
    Keys::PublicKey getPublicKey() const;
    void generatePrivateKey();
    void generatePublicKey();
    BigInt basicEncrypt(const BigInt& plaintext, const CompactLWE& to);
};

#endif // CompactLWE_H
