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
    const uint8_t qBitLenght = PublicParamethers::q.bitLenght();
    std::cout << "qBitLenght         " << uint16_t(qBitLenght) << "\n";
    std::cout << "q                  " << PublicParamethers::q << "\n";
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
    std::cout << "privateKey.k       " << privateKey.k << "\n";
    do
    {
        prbGenerator.generateL20();
        privateKey.kPrime = BigInt(prbGenerator.getGeneratedPRBS());
    }
    while(!(isCoprime(PublicParamethers::q, privateKey.kPrime) && privateKey.ckPrime < PublicParamethers::q));
    std::cout << "privateKey.kPrime  " << privateKey.kPrime << "\n";
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
    std::cout << "privateKey.p       " << privateKey.p << "\n";
    std::cout << "pBitLenght         " << uint16_t(pBitLenght) << "\n";
    prbGenerator.setNumberOfBit(pBitLenght);
    do
    {
        prbGenerator.generateL20();
        privateKey.ck = BigInt(prbGenerator.getGeneratedPRBS());
    }
    while(privateKey.ck >= privateKey.p);
    std::cout << "privateKey.ck      " << privateKey.ck << "\n";
    do
    {
        prbGenerator.generateL20();
        privateKey.ckPrime = BigInt(prbGenerator.getGeneratedPRBS());
    }
    while(!(isCoprime(privateKey.ckPrime, privateKey.p) && privateKey.ckPrime < privateKey.p));
    std::cout << "privateKey.ckPrime " << privateKey.ckPrime << "\n";
    const uint8_t sk_maxBitLenght = PrivateParamethers::sk_max.bitLenght();
    std::cout << "sk_maxBitLenght    " << uint16_t(sk_maxBitLenght) << "\n";
    prbGenerator.setNumberOfBit(sk_maxBitLenght);
    do
    {
        prbGenerator.generateBlumBlumShubBit();
        privateKey.sk = BigInt(prbGenerator.getGeneratedPRBS());
        prbGenerator.generateBlumBlumShubBit();
        privateKey.skPrime = BigInt(prbGenerator.getGeneratedPRBS());
    }
    while(!(isCoprime(privateKey.sk * privateKey.ck + privateKey.skPrime * privateKey.ckPrime, privateKey.p) && (privateKey.sk < PrivateParamethers::sk_max) && (privateKey.skPrime < PrivateParamethers::sk_max)));
    std::cout << "privateKey.sk      " << privateKey.sk << "\n";
    std::cout << "privateKey.skPrime " << privateKey.skPrime << "\n";
}

void CompactLWE::generatePublicKey()
{
    PRBgenerators prbGenerator;
    BigInt e;
    BigInt ePrime;
    BigInt r;
    BigInt rPrime;
    const uint8_t bBitLenght = PublicParamethers::b.bitLenght();
    const uint8_t bPrimeBitLenght = PublicParamethers::bPrime.bitLenght();
    const uint8_t e_minBitLenght = PrivateParamethers::e_min.bitLenght();
    const uint8_t e_maxBitLenght = PrivateParamethers::e_max.bitLenght();
    for(std::array<Keys::PublicKeySample, PublicParamethers::m>::iterator iteratorPublicKey = publicKey.begin(); iteratorPublicKey != publicKey.end(); ++iteratorPublicKey)
    {
        for(std::array<BigInt, PublicParamethers::n>::iterator iteratorA = iteratorPublicKey->a.begin(); iteratorA != iteratorPublicKey->a.end(); ++iteratorA)
        {
            prbGenerator.setNumberOfBit(std::rand() % bBitLenght);
            prbGenerator.generateBlumBlumShubBit();
            *iteratorA = BigInt(prbGenerator.getGeneratedPRBS());
        }
        prbGenerator.setNumberOfBit(std::rand() % bPrimeBitLenght);
        prbGenerator.generateL20();
        iteratorPublicKey->u = BigInt(prbGenerator.getGeneratedPRBS());
        do
        {
            prbGenerator.setNumberOfBit(std::rand() % (e_maxBitLenght - e_minBitLenght + 1) + e_minBitLenght);
            prbGenerator.generateBlumBlumShubBit();
            e = BigInt(prbGenerator.getGeneratedPRBS());
        }
        while(e < PrivateParamethers::e_min || e > PrivateParamethers::e_max);
        do
        {
            prbGenerator.setNumberOfBit(std::rand() % (e_maxBitLenght - e_minBitLenght + 1) + e_minBitLenght);
            prbGenerator.generateBlumBlumShubBit();
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
        std::cout << "privateKey.ck      " <<  privateKey.ck << "\n";
        std::cout << "privateKey.ckPrime " << privateKey.ckPrime << "\n";
        std::cout << "privateKey.p       " << privateKey.p << "\n";
        std::cout << "r                  " << r << "\n";
        std::cout << "rPrime             " << rPrime << "\n";
        std::cout << "222test222         " << (privateKey.ck * r + privateKey.ckPrime * rPrime) % privateKey.p << "\n";
    }
}
