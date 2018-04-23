#include "CompactLWE.h"
#include <numeric>

CompactLWE::CompactLWE(QObject* parent): QObject(parent)
{

}

CompactLWE::~CompactLWE()
{

}

void CompactLWE::generatePrivateKey()
{
    PRBgenerators prbGenerator;
    const uint8_t qBitLenght = PublicParamethers::q.bitLenght();
    prbGenerator.setNumberOfBit(qBitLenght);
    for(std::array<BigInt, PublicParamethers::n>::iterator iteratorS = privateKey.s.begin(); iteratorS != privateKey.s.end(); ++iteratorS)
    {
        prbGenerator.generateL20();
        *iteratorS = BigInt(prbGenerator.getGeneratedPRBS());
        if(*iteratorS >= PublicParamethers::q)
        {
            --iteratorS;
        }
    }
    for(std::array<BigInt, PublicParamethers::n>::iterator iteratorSPrime = privateKey.sPrime.begin(); iteratorSPrime != privateKey.sPrime.end(); ++iteratorSPrime)
    {
        prbGenerator.generateL20();
        *iteratorSPrime = BigInt(prbGenerator.getGeneratedPRBS());
        if(*iteratorSPrime >= PublicParamethers::q)
        {
            --iteratorSPrime;
        }
    }
    do
    {
        prbGenerator.generateL20();
        privateKey.k = BigInt(prbGenerator.getGeneratedPRBS());
    }
    while(!(isCoprime(PublicParamethers::q, privateKey.k) && privateKey.k < PublicParamethers::q));
    do
    {
        prbGenerator.generateL20();
        privateKey.kPrime = BigInt(prbGenerator.getGeneratedPRBS());
    }
    while(!(isCoprime(PublicParamethers::q, privateKey.kPrime) && privateKey.ckPrime < PublicParamethers::q));
    const BigInt p_min = (PublicParamethers::w + PublicParamethers::wPrime) * PublicParamethers::bPrime;
    //    const uint8_t p_minBitLenght = p_min.bitLenght();
    const BigInt p_max = p_min + PrivateParamethers::p_size;
    //    const uint8_t p_maxBitLenght = p_max.bitLenght();
    const BigInt sk_maxMULbPrime = PrivateParamethers::sk_max * PublicParamethers::bPrime;
    const BigInt qDIVwADDwPrime = PublicParamethers::q / (PublicParamethers::w + PublicParamethers::wPrime);
    privateKey.p = p_min;
    do
    {
        /*prbGenerator.setNumberOfBit(std::rand() % (p_maxBitLenght - p_minBitLenght + 1) + p_minBitLenght);
        prbGenerator.generateBlumBlumShubBit();
        privateKey.p = BigInt(prbGenerator.getGeneratedPRBS());*/
        ++privateKey.p;
    }
    while(!((privateKey.p >= p_min) && (privateKey.p <= p_max) && isCoprime(PublicParamethers::q, privateKey.p) && (sk_maxMULbPrime + privateKey.p + PrivateParamethers::e_max * privateKey.p < qDIVwADDwPrime)));
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
    const uint8_t sk_maxBitLenght = PrivateParamethers::sk_max.bitLenght();
    prbGenerator.setNumberOfBit(sk_maxBitLenght);
    do
    {
        prbGenerator.generateBlumBlumShubBit();
        privateKey.sk = BigInt(prbGenerator.getGeneratedPRBS());
        prbGenerator.generateBlumBlumShubBit();
        privateKey.skPrime = BigInt(prbGenerator.getGeneratedPRBS());
    }
    while(!(isCoprime(privateKey.sk * privateKey.ck + privateKey.skPrime * privateKey.ckPrime, privateKey.p) && (privateKey.sk < PrivateParamethers::sk_max) && (privateKey.skPrime < PrivateParamethers::sk_max)));
}

void CompactLWE::generatePublicKey()
{
    PRBgenerators prbGenerator;
    BigInt e;
    BigInt ePrime;
    BigInt r;
    BigInt rPrime;
    BigInt k;
    BigInt kInverse;
    BigInt kPrime;
    BigInt kPrimeInverse;
    const uint8_t qBitLenght = PublicParamethers::q.bitLenght();
    const uint8_t bBitLenght = PublicParamethers::b.bitLenght();
    const uint8_t bPrimeBitLenght = PublicParamethers::bPrime.bitLenght();
    const uint8_t e_maxBitLenght = PrivateParamethers::e_max.bitLenght();
    for(std::array<Keys::PublicKeySample, PublicParamethers::m>::iterator iteratorPublicKey = publicKey.begin(); iteratorPublicKey != publicKey.end(); ++iteratorPublicKey)
    {
        prbGenerator.setNumberOfBit(bBitLenght);
        for(std::array<BigInt, PublicParamethers::n>::iterator iteratorA = iteratorPublicKey->a.begin(); iteratorA != iteratorPublicKey->a.end(); ++iteratorA)
        {
            prbGenerator.generateBlumBlumShubBit();
            *iteratorA = BigInt(prbGenerator.getGeneratedPRBS());
            if(*iteratorA >= PublicParamethers::b)
            {
                --iteratorA;
            }
        }
        prbGenerator.setNumberOfBit(bPrimeBitLenght);
        do
        {
            prbGenerator.generateL20();
            iteratorPublicKey->u = BigInt(prbGenerator.getGeneratedPRBS());
        }
        while(iteratorPublicKey->u >= PublicParamethers::bPrime);
        prbGenerator.setNumberOfBit(e_maxBitLenght);
        do
        {
            prbGenerator.generateL20();
            e = BigInt(prbGenerator.getGeneratedPRBS());
        }
        while(e < PrivateParamethers::e_min || e > PrivateParamethers::e_max);
        do
        {
            prbGenerator.generateL20();
            ePrime = BigInt(prbGenerator.getGeneratedPRBS());
        }
        while(ePrime < PrivateParamethers::e_min || ePrime > PrivateParamethers::e_max);
        //CK * R + CKPrime * RPrime = 0 mod P
        r = inversemod(privateKey.ck, privateKey.p);
        rPrime = -inversemod(privateKey.ckPrime, privateKey.p) + privateKey.p;
        /*if(rPrime.isNegative())
        {
            rPrime += (-rPrime / privateKey.p + BigInt(1)) * privateKey.p;
        }*/
        std::cout << "privateKey.p       " << privateKey.p << "\n";
        std::cout << "r                  " << r << "\n";
        std::cout << "rPrime             " << rPrime << "\n";
        std::cout << "222test222         " << (privateKey.ck * r + privateKey.ckPrime * rPrime) % privateKey.p << "\n";
        prbGenerator.setNumberOfBit(qBitLenght);
        do
        {
            prbGenerator.generateL20();
            k = BigInt(prbGenerator.getGeneratedPRBS());
        }
        while(!isCoprime(k, PublicParamethers::q));
        kInverse = inversemod(k, PublicParamethers::q);
        do
        {
            prbGenerator.generateL20();
            kPrime = BigInt(prbGenerator.getGeneratedPRBS());
        }
        while(!isCoprime(kPrime, PublicParamethers::q));
        kPrimeInverse = inversemod(kPrime, PublicParamethers::q);
        iteratorPublicKey->pk = (std::inner_product(iteratorPublicKey->a.cbegin(), iteratorPublicKey->a.cend(), privateKey.s.cbegin(), BigInt(0)) + kInverse * (privateKey.sk * iteratorPublicKey->u + r + e * privateKey.p)) % PublicParamethers::q;
        iteratorPublicKey->pkPrime = (std::inner_product(iteratorPublicKey->a.cbegin(), iteratorPublicKey->a.cend(), privateKey.sPrime.cbegin(), BigInt(0)) + kPrimeInverse * (privateKey.skPrime * iteratorPublicKey->u + rPrime + ePrime * privateKey.p)) % PublicParamethers::q;
        std::cout << "pk                  " << iteratorPublicKey->pk << "\n";
        std::cout << "pkPrime             " << iteratorPublicKey->pkPrime << "\n";
    }
}
