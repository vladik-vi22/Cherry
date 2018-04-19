#include "CompactLWE.h"

CompactLWE::CompactLWE(QObject* parent): QObject(parent)
{

}

CompactLWE::~CompactLWE()
{

}

void CompactLWE::generatePrivateKey()
{
    PRBgenerators prbGenerator;
    const uint8_t qBitLenght = publicParamethers.q.bitLenght();
    privateKey.s.reserve(publicParamethers.n);
    privateKey.sPrime.reserve(publicParamethers.n);
    BigInt S;
    while(privateKey.s.size() < publicParamethers.n)
    {
        prbGenerator.setNumberOfBit(std::rand() % qBitLenght);
        prbGenerator.generateL20();
        S = BigInt(prbGenerator.getGeneratedPRBS());
        privateKey.s.push_back(S.toUint64_t());
    }
    while(privateKey.sPrime.size() < publicParamethers.n)
    {
        prbGenerator.setNumberOfBit(std::rand() % qBitLenght);
        prbGenerator.generateL20();
        S = BigInt(prbGenerator.getGeneratedPRBS());
        privateKey.sPrime.push_back(S.toUint64_t());
    }
    BigInt& K = S;
    do
    {
        prbGenerator.setNumberOfBit(std::rand() % qBitLenght);
        prbGenerator.generateL20();
        K = BigInt(prbGenerator.getGeneratedPRBS());
    }
    while(!isCoprime(publicParamethers.q, K));
    privateKey.k = K.toUint64_t();
    do
    {
        prbGenerator.setNumberOfBit(std::rand() % qBitLenght);
        prbGenerator.generateL20();
        K = BigInt(prbGenerator.getGeneratedPRBS());
    }
    while(!isCoprime(publicParamethers.q, K));
    privateKey.kPrime = K.toUint64_t();
    const BigInt p_min = BigInt((publicParamethers.w + publicParamethers.wPrime) * publicParamethers.bPrime);
    //    const uint8_t p_minBitLenght = p_min.bitLenght();
    const BigInt p_max = p_min + BigInt(privateParamethers.p_size);
    //    const uint8_t p_maxBitLenght = p_max.bitLenght();
    const BigInt sk_maxMULbPrime = BigInt(privateParamethers.sk_max) * BigInt(publicParamethers.bPrime);
    const BigInt qDIVwADDwPrime = publicParamethers.q / BigInt(publicParamethers.w + publicParamethers.wPrime);
    BigInt& P = K;
    P = p_min;
    do
    {
        /*prbGenerator.setNumberOfBit(std::rand() % (p_maxBitLenght - p_minBitLenght + 1) + p_minBitLenght);
        prbGenerator.generateBlumBlumShubBit();
        P = BigInt(prbGenerator.getGeneratedPRBS());*/
        ++P;
    }
    while(!((P >= p_min) && (P <= p_max) && isCoprime(publicParamethers.q, P) && (sk_maxMULbPrime + P + BigInt(privateParamethers.e_max) * P < qDIVwADDwPrime)));
    privateKey.p = P.toUint64_t();
    const uint8_t pBitLenght = P.bitLenght();
    BigInt CK;
    prbGenerator.setNumberOfBit(std::rand() % pBitLenght);
    prbGenerator.generateL20();
    CK = BigInt(prbGenerator.getGeneratedPRBS());
    privateKey.ck = CK.toUint64_t();
    BigInt CKPrime;
    do
    {
        prbGenerator.setNumberOfBit(std::rand() % pBitLenght);
        prbGenerator.generateL20();
        CKPrime = BigInt(prbGenerator.getGeneratedPRBS());
    }
    while(!isCoprime(CKPrime, P));
    privateKey.ckPrime = CKPrime.toUint64_t();
    const BigInt SK_MAX = BigInt(privateParamethers.sk_max);
    const uint8_t sk_maxBitLenght = SK_MAX.bitLenght();
    BigInt SK;
    BigInt SKPrime;
    do
    {
        prbGenerator.setNumberOfBit(std::rand() % sk_maxBitLenght);
        prbGenerator.generateBlumBlumShubBit();
        SK = BigInt(prbGenerator.getGeneratedPRBS());
        prbGenerator.setNumberOfBit(std::rand() % sk_maxBitLenght);
        prbGenerator.generateBlumBlumShubBit();
        SKPrime = BigInt(prbGenerator.getGeneratedPRBS());
    }
    while(!isCoprime(SK * CK + SKPrime * CKPrime, P));
    privateKey.sk = SK.toUint32_t();
    privateKey.skPrime = SKPrime.toUint32_t();
}

void CompactLWE::generatePublicKey()
{
    PRBgenerators prbGenerator;
    publicKey.reserve(publicParamethers.m);
    Keys::PublicKeySample publicKeySample;
    uint16_t e;
    uint16_t ePrime;
    uint64_t r;
    BigInt R;
    uint64_t rPrime;
    BigInt RPrime;
    const BigInt P(privateKey.p);
    const BigInt CK(privateKey.ck);
    const BigInt CKPrime(privateKey.ckPrime);
    const uint8_t pBitLenght = P.bitLenght();
    const uint8_t bPrimeBitLenght = BigInt(publicParamethers.bPrime).bitLenght();
    for(uint8_t indexPublicKeySample = 0; indexPublicKeySample < publicParamethers.m; ++indexPublicKeySample)
    {
        for(uint8_t indexA = 0; indexA < publicParamethers.n; ++indexA)
        {
            publicKeySample.a.push_back(std::rand() % publicParamethers.b);
        }
        prbGenerator.setNumberOfBit(std::rand() % bPrimeBitLenght);
        prbGenerator.generateL20();
        publicKeySample.u = BigInt(prbGenerator.getGeneratedPRBS()).toUint64_t();
        do
        {
            e = std::rand() % (privateParamethers.e_max + 1);
        }
        while(e < privateParamethers.e_min || e > privateParamethers.e_max);
        do
        {
            ePrime = std::rand() % (privateParamethers.e_max + 1);
        }
        while(ePrime < privateParamethers.e_min || ePrime > privateParamethers.e_max);
        prbGenerator.setNumberOfBit(pBitLenght);
        do
        {
            prbGenerator.generateL20();
            R = BigInt(prbGenerator.getGeneratedPRBS());
            prbGenerator.generateL20();
            RPrime = BigInt(prbGenerator.getGeneratedPRBS());
        }
        while((CK * R + CKPrime * RPrime) % P != BigInt(0));
    }
}
