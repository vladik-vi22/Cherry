#include "CompactLWE.h"
#include <numeric>
#include <algorithm>

CompactLWE::CompactLWE()
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
    const uint32_t p_sizeBitLenght = privateParamethers.p_size.bitLenght();
    const BigInt sk_maxMULbPrime = privateParamethers.sk_max * publicParamethers.bPrime;
    const BigInt qDIVwADDwPrime = publicParamethers.q / (publicParamethers.w + publicParamethers.wPrime);
    PRBgenerators prbGenerator;
    prbGenerator.setNumberOfBits(qBitLenght);
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
    do
    {
        prbGenerator.setNumberOfBits(p_sizeBitLenght);
        prbGenerator.generateL20();
        privateKey.p = p_min + (BigInt(prbGenerator.getGeneratedPRBS()) % privateParamethers.p_size);
    }
    while(!((privateKey.p >= p_min) && (privateKey.p <= p_max) && isCoprime(publicParamethers.q, privateKey.p) && (sk_maxMULbPrime + privateKey.p + privateParamethers.e_max * privateKey.p < qDIVwADDwPrime)));
    const uint8_t pBitLenght = privateKey.p.bitLenght();
    prbGenerator.setNumberOfBits(pBitLenght);
    do
    {
        prbGenerator.generateL20();
        privateKey.ck = BigInt(prbGenerator.getGeneratedPRBS());
    }
    while(!(isCoprime(privateKey.ck, privateKey.p) && privateKey.ck < privateKey.p));
    do
    {
        prbGenerator.generateL20();
        privateKey.ckPrime = BigInt(prbGenerator.getGeneratedPRBS());
    }
    while(!(isCoprime(privateKey.ckPrime, privateKey.p) && privateKey.ckPrime < privateKey.p));
    prbGenerator.setNumberOfBits(sk_maxBitLenght);
    do
    {
        prbGenerator.generateL20();
        privateKey.sk = BigInt(prbGenerator.getGeneratedPRBS());
        prbGenerator.generateL20();
        privateKey.skPrime = BigInt(prbGenerator.getGeneratedPRBS());
    }
    while(!(isCoprime(privateKey.sk * privateKey.ck + privateKey.skPrime * privateKey.ckPrime, privateKey.p) && (privateKey.sk < privateParamethers.sk_max) && (privateKey.skPrime < privateParamethers.sk_max)));
    qDebug("private key generated");
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
    while(publicKey.size() < publicParamethers.m)
    {
        prbGenerator.setNumberOfBits(bBitLenght);
        while(publicKeySample.a.size() < publicParamethers.n)
        {
            prbGenerator.generateL20();
            if(BigInt(prbGenerator.getGeneratedPRBS()) < publicParamethers.b)
            {
                publicKeySample.a.push_back(BigInt(prbGenerator.getGeneratedPRBS()));
            }
        }
        prbGenerator.setNumberOfBits(bPrimeBitLenght);
        do
        {
            prbGenerator.generateL20();
            publicKeySample.u = BigInt(prbGenerator.getGeneratedPRBS());
        }
        while(publicKeySample.u >= publicParamethers.bPrime);
        prbGenerator.setNumberOfBits(e_maxBitLenght);
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
        prbGenerator.setNumberOfBits(qBitLenght);
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
        publicKeySample.pk = (std::inner_product(publicKeySample.a.cbegin(), publicKeySample.a.cend(), privateKey.s.cbegin(), BigInt(0))
                              + kqInverse * (privateKey.sk * publicKeySample.u + r + e * privateKey.p)) % publicParamethers.q;
        publicKeySample.pkPrime = (std::inner_product(publicKeySample.a.cbegin(), publicKeySample.a.cend(), privateKey.sPrime.cbegin(), BigInt(0))
                                   + kqPrimeInverse * (privateKey.skPrime * publicKeySample.u + rPrime + ePrime * privateKey.p)) % publicParamethers.q;
        publicKey.push_back(publicKeySample);
    }
    qDebug("public key generated");
}

std::vector<BigInt> CompactLWE::basicEncrypt(const BigInt& plaintext, const CompactLWE& to)
{
    qDebug() << plaintext;
    std::vector<BigInt> ciphertext;
    std::cout<< "l" << '\n';
    const std::vector<BigInt> l = generateL(to);
    for(auto i:l)
        std::cout << i << " ";
    std::vector<BigInt>::const_iterator iteratorL = l.cbegin();
    std::vector<Keys::PublicKeySample>::const_iterator iteratorToPublicKey = to.publicKey.cbegin();
    std::vector<BigInt> productLA;
    BigInt innerProductLU(0);
    BigInt innerProductLPk(0);
    BigInt innerProductLPkPrime(0);
    BigInt u;
    BigInt uPrime;
    ciphertext.reserve(to.publicParamethers.n + 3);
    ciphertext.resize(to.getPublicParamethers().n, ConstBigInt::ZERO);
    productLA.reserve(to.getPublicParamethers().n);
    productLA.resize(to.getPublicParamethers().n, ConstBigInt::ZERO);
    while(iteratorL != l.cend() && iteratorToPublicKey != to.getPublicKey().cend())
    {
        std::transform(iteratorToPublicKey->a.cbegin(), iteratorToPublicKey->a.cend(), productLA.begin(),
                       std::bind1st(std::multiplies<BigInt>(), *iteratorL));
        std::transform(ciphertext.begin(), ciphertext.end(), productLA.cbegin(), ciphertext.begin(), std::plus<BigInt>());
        ++iteratorL;
        ++iteratorToPublicKey;
    }
    iteratorL = l.cbegin();
    iteratorToPublicKey = to.publicKey.cbegin();
    while(iteratorL != l.cend() && iteratorToPublicKey != to.getPublicKey().cend())
    {
        innerProductLU += *iteratorL * iteratorToPublicKey->u;
        ++iteratorL;
        ++iteratorToPublicKey;
    }
    u = innerProductLU % to.getPublicParamethers().t;
    uPrime = innerProductLU / to.getPublicParamethers().t;
    while(!isCoprime(uPrime, to.getPublicParamethers().t))
    {
        ++uPrime;
    }
    ciphertext.push_back((plaintext ^ u.leftCircularShift(log2(to.getPublicParamethers().t) / 2)) * uPrime % to.getPublicParamethers().t);
    iteratorL = l.cbegin();
    iteratorToPublicKey = to.publicKey.cbegin();
    while(iteratorL != l.cend() && iteratorToPublicKey != to.getPublicKey().cend())
    {
        innerProductLPk += *iteratorL * iteratorToPublicKey->pk;
        ++iteratorL;
        ++iteratorToPublicKey;
    }
    ciphertext.push_back(innerProductLPk % to.getPublicParamethers().q);
    iteratorL = l.cbegin();
    iteratorToPublicKey = to.publicKey.cbegin();
    while(iteratorL != l.cend() && iteratorToPublicKey != to.getPublicKey().cend())
    {
        innerProductLPkPrime += *iteratorL * iteratorToPublicKey->pkPrime;
        ++iteratorL;
        ++iteratorToPublicKey;
    }
    ciphertext.push_back(innerProductLPkPrime % to.getPublicParamethers().q);
    qDebug("basic encrypted");
    return ciphertext;
}

std::vector<BigInt> CompactLWE::generalEncrypt(const BigInt& plaintext, const CompactLWE& to)
{
    std::vector<BigInt> ciphertext;
    PRBgenerators prbGenerator;
    prbGenerator.setNumberOfBytes(256);
    prbGenerator.generateL20();
    std::vector<uint8_t> encodedPlaintext = encode(plaintext.toStdVectorUint8_t(), prbGenerator.getGeneratedPRBS(), to);
    uint32_t blockSize = log2(to.getPublicParamethers().t);
    while(encodedPlaintext.size() % blockSize)
    {
        encodedPlaintext.push_back(0);
    }
    uint32_t numberOfBlocks = encodedPlaintext.size() / blockSize;
    for(uint8_t indexBlock = 0; indexBlock < numberOfBlocks; ++indexBlock)
    {
        std::vector<uint8_t> block(encodedPlaintext.cbegin() + indexBlock * blockSize, encodedPlaintext.cbegin() + (indexBlock + 1) * blockSize - 1);
        while(block.back() == 0)
        {
            block.pop_back();
        }
        std::vector<BigInt> encryptedBlock = basicEncrypt(BigInt(block), to);
        ciphertext.insert(ciphertext.end(), encryptedBlock.cbegin(), encryptedBlock.cend());
    }
    qDebug("general encrypted");
    return ciphertext;
}

std::vector<BigInt> CompactLWE::generateL(const CompactLWE& to)
{
    const BigInt wPlusWPrime = to.getPublicParamethers().w + to.getPublicParamethers().wPrime;
    const uint8_t lAverageBitLenght = (wPlusWPrime / BigInt(to.getPublicParamethers().m)).bitLenght();
    std::vector<BigInt> l;
    BigInt sumL(0);
    BigInt innerProductLU;
    PRBgenerators prbGenerator;
    l.reserve(to.getPublicParamethers().m);
    prbGenerator.setNumberOfBits(lAverageBitLenght + (lAverageBitLenght >> 1));
    while(sumL <= wPlusWPrime && l.size() <= to.getPublicParamethers().m)
    {
        prbGenerator.generateL20();
        l.push_back(BigInt(prbGenerator.getGeneratedPRBS()));
        sumL += l.back();
        if(l.back().isZero())
        {
            l.pop_back();
        }
    }
    l.pop_back();
    sumL = ConstBigInt::ZERO;
    while(sumL >= -to.getPublicParamethers().wPrime && l.size() <= to.getPublicParamethers().m)
    {
        prbGenerator.generateL20();
        l.push_back(-BigInt(prbGenerator.getGeneratedPRBS()));
        sumL += l.back();
        if(l.back().isZero())
        {
            l.pop_back();
        }
    }
    l.pop_back();
    l.resize(to.getPublicParamethers().m, ConstBigInt::ZERO);
    do
    {
        std::random_shuffle(l.begin(), l.end());
        std::vector<BigInt>::const_iterator iteratorL = l.cbegin();
        std::vector<Keys::PublicKeySample>::const_iterator iteratorToPublicKey = to.publicKey.cbegin();
        innerProductLU = ConstBigInt::ZERO;
        while(iteratorL != l.cend() && iteratorToPublicKey != to.getPublicKey().cend())
        {
            innerProductLU += *iteratorL * iteratorToPublicKey->u;
            ++iteratorL;
            ++iteratorToPublicKey;
        }
    }
    while(innerProductLU <= ConstBigInt::ZERO);
    return l;
}

std::vector<uint8_t> CompactLWE::encode(const std::vector<uint8_t>& m, const std::vector<uint8_t>& I, const CompactLWE& to)
{
    std::vector<uint8_t> mPrime = m;
    const uint32_t lenM = m.size();
    const uint32_t pl = log2(to.getPublicParamethers().t) * (1 + ((8 * (lenM + to.getPublicParamethers().l) - 1) / log2(to.getPublicParamethers().t))) / 8 - lenM;
    mPrime.reserve(lenM + pl);
    mPrime.resize(lenM + pl - 2, UINT8_MAX);
    srand(time(NULL));
    uint8_t r = std::rand() & UINT8_MAX; // & UINT8_MAX = & 255 = % 256
    uint8_t rPrime = std::rand() & UINT8_MAX;
    uint8_t x = I[r];
    uint8_t r_ori = r;
    uint32_t indexMPrime = 0;
    do
    {
        mPrime[indexMPrime] ^= x;
        x ^= I[(mPrime[indexMPrime] + r_ori) & UINT8_MAX];
        r ^= (mPrime[indexMPrime] * rPrime) & UINT8_MAX;
        ++indexMPrime;
    }
    while(indexMPrime < lenM + pl - 3);
    x = I[rPrime];
    r_ori = rPrime;
    do
    {
        mPrime[indexMPrime] ^= x;
        x = I[(mPrime[indexMPrime] + r_ori) & UINT8_MAX];
        rPrime ^= (mPrime[indexMPrime] * r) & UINT8_MAX;
        --indexMPrime;
    }
    while(indexMPrime);
    mPrime.push_back(r);
    mPrime.push_back(rPrime);
    return mPrime;
}
