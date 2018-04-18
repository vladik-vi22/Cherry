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
    prbGenerator.setNumberOfBit(QString::number(std::rand() % 64));
    privateKey.s.reserve(publicParamethers.n);
    privateKey.sPrime.reserve(publicParamethers.n);
    for(uint8_t indexS = 0; indexS < publicParamethers.n; ++indexS)
    {
        prbGenerator.generateL20();
        privateKey.s.push_back(BigInt(prbGenerator.getGeneratedPRBS()).toUint64_t());
        prbGenerator.generateL20();
        privateKey.sPrime.push_back(BigInt(prbGenerator.getGeneratedPRBS()).toUint64_t());
    }
    BigInt K;
    do
    {
        prbGenerator.generateL20();
        K = BigInt(prbGenerator.getGeneratedPRBS());
    }
    while(!isCoprime(publicParamethers.q, K));
    privateKey.k = K.toUint64_t();
    do
    {
        prbGenerator.generateL20();
        K = BigInt(prbGenerator.getGeneratedPRBS());
    }
    while(!isCoprime(publicParamethers.q, K));
    privateKey.kPrime = K.toUint64_t();
    const BigInt p_min = BigInt((publicParamethers.w + publicParamethers.wPrime) * publicParamethers.bPrime);
    const BigInt p_max =BigInt((publicParamethers.w + publicParamethers.wPrime) * publicParamethers.bPrime + privateParamethers.p_size);
    const BigInt sk_maxMULbPrime = BigInt(privateParamethers.sk_max) * BigInt(publicParamethers.bPrime);
    const BigInt qDIVwADDwPrime = publicParamethers.q / BigInt(publicParamethers.w + publicParamethers.wPrime);
    BigInt& P = K;
    do
    {
        prbGenerator.generateL20();
        P = BigInt(prbGenerator.getGeneratedPRBS());
    }
    while(!((P >= p_min) && (P <= p_max) && isCoprime(publicParamethers.q, P) && (sk_maxMULbPrime + P + BigInt(privateParamethers.e_max) * P < qDIVwADDwPrime)));
    privateKey.p = P.toUint64_t();
    BigInt CK;
    do
    {
        prbGenerator.generateL20();
        CK = BigInt(prbGenerator.getGeneratedPRBS());
    }
    while(!(CK < P));
    privateKey.ck = CK.toUint64_t();
    BigInt CKPrime;
    do
    {
        prbGenerator.generateL20();
        CKPrime = BigInt(prbGenerator.getGeneratedPRBS());
    }
    while(!(isCoprime(CKPrime, P) && (CKPrime < P)));
    privateKey.ckPrime = CKPrime.toUint64_t();
    const BigInt SK_MAX = BigInt(privateParamethers.sk_max);
    BigInt SK;
    BigInt SKPrime;
    do
    {
        prbGenerator.generateL20();
        SK = BigInt(prbGenerator.getGeneratedPRBS());
        prbGenerator.generateL20();
        SKPrime = BigInt(prbGenerator.getGeneratedPRBS());
    }
    while(!((SK < SK_MAX) && (SKPrime < SK_MAX) && isCoprime(SK * CK + SKPrime * CKPrime, P)));
}

void CompactLWE::generatePublicKey()
{

}
