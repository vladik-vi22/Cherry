#include "CompactLWE.h"
#include <numeric>

CompactLWE::CompactLWE(QObject* parent): QObject(parent)
{
    publicParamethers.q = BigInt(std::vector<uint32_t>{1, 0, 0}, true); // 2^64
    publicParamethers.t = BigInt(uint64_t(4294967296)); // 2^32
    publicParamethers.n = 8;
    publicParamethers.m = 128;
    publicParamethers.w = BigInt(224);
    publicParamethers.wPrime = BigInt(32);
    publicParamethers.b = BigInt(16);
    publicParamethers.bPrime = BigInt(uint64_t(68719476736));
    publicParamethers.l = 8;

    privateParamethers.sk_max = BigInt(229119);
    privateParamethers.p_size = BigInt(16777216);
    privateParamethers.e_min = BigInt(457);
    privateParamethers.e_max = BigInt(3200);
}

CompactLWE::~CompactLWE()
{
}

Paramethers::PublicParamethers CompactLWE::getPublicParamethers() const
{
    return publicParamethers;
}

Keys::PublicKey CompactLWE::getPublicKey() const
{
    return publicKey;
}

void CompactLWE::generatePrivateKey()
{
    const uint8_t qBitLenght = publicParamethers.q.bitLenght();
    const uint8_t sk_maxBitLenght = privateParamethers.sk_max.bitLenght();
    const BigInt p_min = (publicParamethers.w + publicParamethers.wPrime) * publicParamethers.bPrime;
    const BigInt p_max = p_min + privateParamethers.p_size;
    const BigInt sk_maxMULbPrime = privateParamethers.sk_max * publicParamethers.bPrime;
    const BigInt qDIVwADDwPrime = publicParamethers.q / (publicParamethers.w + publicParamethers.wPrime);
    PRBgenerators prbGenerator;
    prbGenerator.setNumberOfBit(qBitLenght);
    privateKey.s.reserve(publicParamethers.n);
    while(privateKey.s.size() < publicParamethers.n)
    {
        prbGenerator.generateL20();
        if(BigInt(prbGenerator.getGeneratedPRBS()) < publicParamethers.q)
        {
            privateKey.s.push_back(BigInt(prbGenerator.getGeneratedPRBS()));
        }
    }
    while(privateKey.sPrime.size() < publicParamethers.n)
    {
        prbGenerator.generateL20();
        if(BigInt(prbGenerator.getGeneratedPRBS()) < publicParamethers.q)
        {
            privateKey.sPrime.push_back(BigInt(prbGenerator.getGeneratedPRBS()));
        }
    }
    do
    {
        prbGenerator.generateL20();
        privateKey.k = BigInt(prbGenerator.getGeneratedPRBS());
    }
    while(!(isCoprime(publicParamethers.q, privateKey.k) && privateKey.k < publicParamethers.q));
    do
    {
        prbGenerator.generateL20();
        privateKey.kPrime = BigInt(prbGenerator.getGeneratedPRBS());
    }
    while(!(isCoprime(publicParamethers.q, privateKey.kPrime) && privateKey.ckPrime < publicParamethers.q));
    privateKey.p = p_min;
    do
    {
        /*prbGenerator.setNumberOfBit(p_maxBitLenght);
        prbGenerator.generateL20();
        privateKey.p = BigInt(prbGenerator.getGeneratedPRBS());*/
        ++privateKey.p;
    }
    while(!((privateKey.p >= p_min) && (privateKey.p <= p_max) && isCoprime(publicParamethers.q, privateKey.p) && (sk_maxMULbPrime + privateKey.p + privateParamethers.e_max * privateKey.p < qDIVwADDwPrime)));
    const uint8_t pBitLenght = privateKey.p.bitLenght();
    prbGenerator.setNumberOfBit(pBitLenght);
    do
    {
        prbGenerator.generateL20();
        privateKey.ck = BigInt(prbGenerator.getGeneratedPRBS());
    }
    while(privateKey.ck >= privateKey.p);
    do
    {
        prbGenerator.generateL20();
        privateKey.ckPrime = BigInt(prbGenerator.getGeneratedPRBS());
    }
    while(!(isCoprime(privateKey.ckPrime, privateKey.p) && privateKey.ckPrime < privateKey.p));
    prbGenerator.setNumberOfBit(sk_maxBitLenght);
    do
    {
        prbGenerator.generateL20();
        privateKey.sk = BigInt(prbGenerator.getGeneratedPRBS());
        prbGenerator.generateL20();
        privateKey.skPrime = BigInt(prbGenerator.getGeneratedPRBS());
    }
    while(!(isCoprime(privateKey.sk * privateKey.ck + privateKey.skPrime * privateKey.ckPrime, privateKey.p) && (privateKey.sk < privateParamethers.sk_max) && (privateKey.skPrime < privateParamethers.sk_max)));
    qDebug("1");
}

void CompactLWE::generatePublicKey()
{
    const uint8_t qBitLenght = publicParamethers.q.bitLenght();
    const uint8_t bBitLenght = publicParamethers.b.bitLenght();
    const uint8_t bPrimeBitLenght = publicParamethers.bPrime.bitLenght();
    const uint8_t e_maxBitLenght = privateParamethers.e_max.bitLenght();
    BigInt e;
    BigInt r;
    BigInt kq;
    BigInt kqInverse;
    BigInt ePrime;
    BigInt rPrime;
    BigInt kqPrime;
    BigInt kqPrimeInverse;
    PRBgenerators prbGenerator;
    Keys::PublicKeySample publicKeySample;
    publicKey.reserve(publicParamethers.m);
    publicKeySample.a.reserve(publicParamethers.n);
    while(publicKey.size() < 1)//publicParamethers.m)
    {
        prbGenerator.setNumberOfBit(bBitLenght);
        while(publicKeySample.a.size() < publicParamethers.n)
        {
            prbGenerator.generateL20();
            if(BigInt(prbGenerator.getGeneratedPRBS()) < publicParamethers.b)
            {
                publicKeySample.a.push_back(BigInt(prbGenerator.getGeneratedPRBS()));
            }
        }
        prbGenerator.setNumberOfBit(bPrimeBitLenght);
        do
        {
            prbGenerator.generateL20();
            publicKeySample.u = BigInt(prbGenerator.getGeneratedPRBS());
        }
        while(publicKeySample.u >= publicParamethers.bPrime);
        prbGenerator.setNumberOfBit(e_maxBitLenght);
        do
        {
            prbGenerator.generateL20();
            e = BigInt(prbGenerator.getGeneratedPRBS());
        }
        while(e < privateParamethers.e_min || e > privateParamethers.e_max);
        do
        {
            prbGenerator.generateL20();
            ePrime = BigInt(prbGenerator.getGeneratedPRBS());
        }
        while(ePrime < privateParamethers.e_min || ePrime > privateParamethers.e_max);
        r = inversemod(privateKey.ck, privateKey.p);
        rPrime = -inversemod(privateKey.ckPrime, privateKey.p) + privateKey.p;
        prbGenerator.setNumberOfBit(qBitLenght);
        do
        {
            prbGenerator.generateL20();
            kq = BigInt(prbGenerator.getGeneratedPRBS());
        }
        while(!(isCoprime(kq, publicParamethers.q) && kq < publicParamethers.q));
        kqInverse = inversemod(kq, publicParamethers.q);
        do
        {
            prbGenerator.generateL20();
            kqPrime = BigInt(prbGenerator.getGeneratedPRBS());
        }
        while(!(isCoprime(kqPrime, publicParamethers.q) && kqPrime < publicParamethers.q));
        kqPrimeInverse = inversemod(kqPrime, publicParamethers.q);
        publicKeySample.pk = (std::inner_product(publicKeySample.a.cbegin(), publicKeySample.a.cend(), privateKey.s.cbegin(), BigInt(0)) + kqInverse * (privateKey.sk * publicKeySample.u + r + e * privateKey.p)) % publicParamethers.q;
        publicKeySample.pkPrime = (std::inner_product(publicKeySample.a.cbegin(), publicKeySample.a.cend(), privateKey.sPrime.cbegin(), BigInt(0)) + kqPrimeInverse * (privateKey.skPrime * publicKeySample.u + rPrime + ePrime * privateKey.p)) % publicParamethers.q;
        publicKey.push_back(publicKeySample);
    }
    qDebug("2");
}

BigInt CompactLWE::basicEncrypt(const BigInt& plaintext, const CompactLWE& to)
{
    const std::vector<BigInt> l = generateL(to);
    for(uint8_t i = 0; i < l.size(); ++i)
    {
        std::cout << l[i] << " ";
    }
}

std::vector<BigInt> CompactLWE::generateL(const CompactLWE& to)
{
    const BigInt wPlusWPrime = to.getPublicParamethers().w + to.getPublicParamethers().wPrime;
    std::vector<BigInt> l;
    BigInt sum(0);
    PRBgenerators prbGenerator;
    prbGenerator.setNumberOfBit(wPlusWPrime.toUint32_t() / to.getPublicParamethers().m + 1);
    l.reserve(to.getPublicParamethers().m);
    while(sum <= wPlusWPrime && l.size() <= to.getPublicParamethers().m)
    {
        prbGenerator.generateL20();
        l.push_back(BigInt(prbGenerator.getGeneratedPRBS()));
        sum += l.back();
    }
    l.back() = BigInt(0);
    sum = BigInt(0);
    while(sum >= -to.getPublicParamethers().wPrime && l.size() <= to.getPublicParamethers().m)
    {
        prbGenerator.generateL20();
        l.push_back(-BigInt(prbGenerator.getGeneratedPRBS()));
        sum += l.back();
    }
    l.back() = BigInt(0);
    while(l.size() <= to.getPublicParamethers().m)
    {
        l.push_back(BigInt(0));
    }
    std::random_shuffle(l.begin(), l.end());
    /*while(std::inner_product(l.cbegin(), l.cend(), to.getPublicKey().cbegin()->u, BigInt(0)) <= BigInt(0))
    {
        std::random_shuffle(l.begin(), l.end());
    }*/
    return l;
}
