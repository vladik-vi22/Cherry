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
    const BigInt q = BigInt(std::vector<uint32_t>{1, 0, 0}, true); // 2^64
    const uint64_t t = 4294967296; // 2^32
    const uint8_t n = 8;
    const uint8_t m = 128;
    const uint8_t w = 224;
    const uint8_t wPrime = 32;
    const uint8_t b = 16;
    const uint64_t bPrime = 68719476736;
    const uint8_t l = 8;
};

struct PrivateParamethers
{
    const uint32_t sk_max = 229119;
    const uint32_t p_size = 16777216;
    const uint16_t e_min = 457;
    const uint16_t e_max = 3200;
};
}

namespace Keys
{
struct PrivateKey
{
    std::vector<uint64_t> s;
    uint64_t k;
    uint32_t sk;
    uint64_t ck;
    std::vector<uint64_t> sPrime;
    uint64_t kPrime;
    uint32_t skPrime;
    uint64_t ckPrime;
    uint64_t p;
};
}

class CompactLWE : public QObject
{
    Q_OBJECT

private:
    Keys::PrivateKey privateKey;
    Paramethers::PublicParamethers publicParamethers;
    Paramethers::PrivateParamethers privateParamethers;

public:
    explicit CompactLWE(QObject *parent = 0);
    ~CompactLWE();

    void generatePrivateKey();
    void generatePublicKey();
};

#endif // CompactLWE_H
