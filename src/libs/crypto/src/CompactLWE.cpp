#include <crypto/CompactLWE.h>
#include <numeric>
#include <algorithm>
#include <functional>
#include <random>

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

void CompactLWE::generateKeys()
{
    generatePrivateKey();
    generatePublicKey();
}

void CompactLWE::generatePrivateKey()
{
    const BigInt p_min = (publicParamethers.w + publicParamethers.wPrime) * publicParamethers.bPrime;
    const BigInt p_max = p_min + privateParamethers.p_size;
    const BigInt sk_maxMULbPrime = privateParamethers.sk_max * publicParamethers.bPrime;
    const BigInt qDIVwADDwPrime = publicParamethers.q / (publicParamethers.w + publicParamethers.wPrime);
    PRBgenerators prbGenerator;
    prbGenerator.setNumberOfBits(publicParamethers.q.bitLenght());
    privateKey.s.clear();
    privateKey.s.reserve(publicParamethers.n);
    while(privateKey.s.size() < publicParamethers.n)
    {
        prbGenerator.generateL20();
        const BigInt sElement(prbGenerator.getGeneratedPRBS());
        if(sElement < publicParamethers.q)
        {
            privateKey.s.emplace_back(sElement);
        }
    }
    privateKey.sPrime.clear();
    privateKey.sPrime.reserve(publicParamethers.n);
    while(privateKey.sPrime.size() < publicParamethers.n)
    {
        prbGenerator.generateL20();
        if(BigInt(prbGenerator.getGeneratedPRBS()) < publicParamethers.q)
        {
            privateKey.sPrime.emplace_back(BigInt(prbGenerator.getGeneratedPRBS()));
        }
    }
    do
    {
        prbGenerator.generateL20();
        privateKey.k = BigInt(prbGenerator.getGeneratedPRBS());
    }
    while(!((privateKey.k < publicParamethers.q) && isCoprime(privateKey.k, publicParamethers.q)));
    do
    {
        prbGenerator.generateL20();
        privateKey.kPrime = BigInt(prbGenerator.getGeneratedPRBS());
    }
    while(!((privateKey.kPrime < publicParamethers.q) && isCoprime(privateKey.kPrime, publicParamethers.q)));
    prbGenerator.setNumberOfBits(privateParamethers.p_size.bitLenght());
    do
    {
        prbGenerator.generateL20();
        privateKey.p = p_min + (BigInt(prbGenerator.getGeneratedPRBS()) % privateParamethers.p_size);
    }
    while(!((privateKey.p >= p_min) && (privateKey.p <= p_max) && isCoprime(privateKey.p, publicParamethers.q) && (sk_maxMULbPrime + privateKey.p + privateParamethers.e_max * privateKey.p < qDIVwADDwPrime)));
    prbGenerator.setNumberOfBits(privateKey.p.bitLenght());
    do
    {
        prbGenerator.generateL20();
        privateKey.ck = BigInt(prbGenerator.getGeneratedPRBS());
    }
    while(!((privateKey.ck < privateKey.p) && isCoprime(privateKey.ck, privateKey.p)));
    do
    {
        prbGenerator.generateL20();
        privateKey.ckPrime = BigInt(prbGenerator.getGeneratedPRBS());
    }
    while(!((privateKey.ckPrime < privateKey.p) && isCoprime(privateKey.ckPrime, privateKey.p)));
    prbGenerator.setNumberOfBits(privateParamethers.sk_max.bitLenght());
    do
    {
        prbGenerator.generateL20();
        privateKey.sk = BigInt(prbGenerator.getGeneratedPRBS());
        prbGenerator.generateL20();
        privateKey.skPrime = BigInt(prbGenerator.getGeneratedPRBS());
    }
    while(!((privateKey.sk < privateParamethers.sk_max) && (privateKey.skPrime < privateParamethers.sk_max) && isCoprime(privateKey.sk * privateKey.ck + privateKey.skPrime * privateKey.ckPrime, privateKey.p)));
}

void CompactLWE::generatePublicKey()
{
    const size_t qBitLenght = publicParamethers.q.bitLenght();
    const size_t bBitLenght = publicParamethers.b.bitLenght();
    const size_t bPrimeBitLenght = publicParamethers.bPrime.bitLenght();
    const size_t e_maxBitLenght = privateParamethers.e_max.bitLenght();
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
    publicKey.clear();
    publicKey.reserve(publicParamethers.m);
    publicKeySample.a.reserve(publicParamethers.n);
    while(publicKey.size() < publicParamethers.m)
    {
        publicKeySample.a.clear();
        prbGenerator.setNumberOfBits(bBitLenght);
        while(publicKeySample.a.size() < publicParamethers.n)
        {
            prbGenerator.generateL20();
            if(BigInt(prbGenerator.getGeneratedPRBS()) < publicParamethers.b)
            {
                publicKeySample.a.emplace_back(BigInt(prbGenerator.getGeneratedPRBS()));
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
        while(!((kq < publicParamethers.q) && isCoprime(kq, publicParamethers.q)));
        kqInverse = inversemod(kq, publicParamethers.q);
        do
        {
            prbGenerator.generateL20();
            kqPrime = BigInt(prbGenerator.getGeneratedPRBS());
        }
        while(!((kqPrime < publicParamethers.q) && isCoprime(kqPrime, publicParamethers.q)));
        kqPrimeInverse = inversemod(kqPrime, publicParamethers.q);
        publicKeySample.pk = (std::inner_product(publicKeySample.a.cbegin(), publicKeySample.a.cend(), privateKey.s.cbegin(), constants::ZERO)
                              + kqInverse * (privateKey.sk * publicKeySample.u + r + e * privateKey.p)) % publicParamethers.q;
        publicKeySample.pkPrime = (std::inner_product(publicKeySample.a.cbegin(), publicKeySample.a.cend(), privateKey.sPrime.cbegin(), constants::ZERO)
                                   + kqPrimeInverse * (privateKey.skPrime * publicKeySample.u + rPrime + ePrime * privateKey.p)) % publicParamethers.q;
        publicKey.emplace_back(publicKeySample);
    }
}

std::vector<BigInt> CompactLWE::basicEncrypt(const BigInt& plaintext, const CompactLWE& to)
{
    std::vector<BigInt> ciphertext;
    const std::vector<BigInt> l = generateL(to);
    std::vector<BigInt>::const_iterator iteratorL = l.cbegin();
    std::vector<Keys::PublicKeySample>::const_iterator iteratorToPublicKey = to.publicKey.cbegin();
    std::vector<BigInt> productLA;
    BigInt innerProductLU(0);
    BigInt innerProductLPk(0);
    BigInt innerProductLPkPrime(0);
    ciphertext.reserve(to.publicParamethers.n + 3);
    ciphertext.resize(to.getPublicParamethers().n, constants::ZERO);
    productLA.reserve(to.getPublicParamethers().n);
    productLA.resize(to.getPublicParamethers().n, constants::ZERO);
    while(iteratorL != l.cend() && iteratorToPublicKey != to.getPublicKey().cend())
    {
        std::transform(iteratorToPublicKey->a.cbegin(), iteratorToPublicKey->a.cend(), productLA.begin(),
                       [&](const BigInt& val) { return *iteratorL * val; });
        std::transform(ciphertext.begin(), ciphertext.end(), productLA.cbegin(), ciphertext.begin(),
                       std::plus<BigInt>());
        innerProductLU += *iteratorL * iteratorToPublicKey->u;
        innerProductLPk += *iteratorL * iteratorToPublicKey->pk;
        innerProductLPkPrime += *iteratorL * iteratorToPublicKey->pkPrime;
        ++iteratorL;
        ++iteratorToPublicKey;
    }
    const BigInt u(innerProductLU % to.getPublicParamethers().t);
    BigInt uPrime(innerProductLU / to.getPublicParamethers().t);
    while(!isCoprime(uPrime, to.getPublicParamethers().t))
    {
        ++uPrime;
    }
    ciphertext.emplace_back((plaintext ^ u.leftCircularShift(log2(to.getPublicParamethers().t) >> 1)) * uPrime % to.getPublicParamethers().t);
    ciphertext.emplace_back(innerProductLPk % to.getPublicParamethers().q);
    ciphertext.emplace_back(innerProductLPkPrime % to.getPublicParamethers().q);
    return ciphertext;
}

std::vector<BigInt> CompactLWE::generalEncrypt(const BigInt& plaintext, const CompactLWE& to)
{
    std::vector<BigInt> ciphertext;
    PRBgenerators prbGenerator;
    prbGenerator.setNumberOfBytes(256);
    prbGenerator.generateL20();
    std::vector<uint8_t> encodedPlaintext = encode(plaintext.toStdVectorUint8_t(), prbGenerator.getGeneratedPRBS(), to);
    size_t blockSize = log2(to.getPublicParamethers().t);
    while(encodedPlaintext.size() % blockSize)
    {
        encodedPlaintext.emplace_back(0);
    }
    size_t numberOfBlocks = encodedPlaintext.size() / blockSize;
    ciphertext.reserve((to.getPublicParamethers().n + 3) * numberOfBlocks);
    for(size_t indexBlock = 0; indexBlock < numberOfBlocks; ++indexBlock)
    {
        std::vector<uint8_t> block(encodedPlaintext.cbegin() + static_cast<long>(indexBlock * blockSize), encodedPlaintext.cbegin() + static_cast<long>((indexBlock + 1) * blockSize - 1));
        while(block.back() == 0)
        {
            block.pop_back();
        }
        std::vector<BigInt> encryptedBlock = basicEncrypt(BigInt(block), to);
        ciphertext.insert(ciphertext.end(), encryptedBlock.cbegin(), encryptedBlock.cend());
    }
    return ciphertext;
}

BigInt CompactLWE::basicDecrypt(const std::vector<BigInt>& ciphertext)
{
    const BigInt d1 = (*std::prev(ciphertext.cend(), 2) - std::inner_product(ciphertext.cbegin(), std::prev(ciphertext.cend(), 3), privateKey.s.cbegin(), constants::ZERO)) * privateKey.k % publicParamethers.q;
    const BigInt d1Prime = (ciphertext.back() - std::inner_product(ciphertext.cbegin(), std::prev(ciphertext.cend(), 3), privateKey.sPrime.cbegin(), constants::ZERO)) * privateKey.kPrime % publicParamethers.q;
    const BigInt d2 = (privateKey.ck * d1 + privateKey.ckPrime * d1Prime) % privateKey.p;
    const BigInt d3 = inversemod(privateKey.sk * privateKey.ck + privateKey.skPrime * privateKey.ckPrime, privateKey.p) * d2 % privateKey.p;
    const BigInt u = d3 % publicParamethers.t;
    BigInt uPrime = d3 / publicParamethers.t;
    while(!isCoprime(uPrime, publicParamethers.t))
    {
        ++uPrime;
    }
    return (inversemod(uPrime, publicParamethers.t) * *std::prev(ciphertext.cend(), 3) % publicParamethers.t) ^ u.leftCircularShift(log2(publicParamethers.t) >> 1);
}

BigInt CompactLWE::generalDecrypt(const std::vector<BigInt>& ciphertext)
{
    std::vector<BigInt> decryptedCiphertext;
    decryptedCiphertext.reserve(ciphertext.size() / (publicParamethers.n + 3));
    for(std::vector<BigInt>::const_iterator iteratorCiphettext = ciphertext.cbegin(); iteratorCiphettext != ciphertext.cend(); iteratorCiphettext += publicParamethers.n + 3)
    {
        decryptedCiphertext.emplace_back(basicDecrypt(std::vector<BigInt>(iteratorCiphettext, iteratorCiphettext + publicParamethers.n + 2)));
    }
    std::vector<uint8_t> decodedDecryptedCiphertext;
    decodedDecryptedCiphertext.reserve(decryptedCiphertext.size() * (publicParamethers.l - 2));
    PRBgenerators prbGenerator;
    prbGenerator.setNumberOfBytes(256);
    prbGenerator.generateL20();
    for(std::vector<BigInt>::const_iterator iteratorDecryptedCiphertext = decryptedCiphertext.cbegin(); iteratorDecryptedCiphertext != decryptedCiphertext.cend(); ++iteratorDecryptedCiphertext)
    {
        const std::vector<uint8_t> decodedDecryptedCiphertextBlock(decode(iteratorDecryptedCiphertext->toStdVectorUint8_t(), prbGenerator.getGeneratedPRBS()));
        decodedDecryptedCiphertext.insert(decodedDecryptedCiphertext.end(), decodedDecryptedCiphertextBlock.cbegin(), decodedDecryptedCiphertextBlock.cend());
    }
    return BigInt(decodedDecryptedCiphertext);
}

std::vector<uint8_t> CompactLWE::encode(const std::vector<uint8_t>& m, const std::vector<uint8_t>& I, const CompactLWE& to)
{
    std::vector<uint8_t> mPrime = m;
    const size_t lenM = m.size();
    const size_t pl = log2(to.getPublicParamethers().t) * (1 + ((8 * (lenM + to.getPublicParamethers().l) - 1) / log2(to.getPublicParamethers().t))) / 8 - lenM;
    mPrime.reserve(lenM + pl);
    mPrime.resize(lenM + pl - 2, UINT8_MAX);
    srand(static_cast<unsigned int>(time(NULL)));
    uint8_t r = std::rand() & UINT8_MAX; // & UINT8_MAX = & 255 = % 256
    uint8_t rPrime = std::rand() & UINT8_MAX;
    uint8_t x = I[r];
    uint8_t r_ori = r;
    std::vector<uint8_t>::iterator iteratorMPrime = mPrime.begin();
    while(iteratorMPrime != mPrime.end())
    {
        *iteratorMPrime ^= x;
        x ^= I[(*iteratorMPrime + r_ori) & UINT8_MAX];
        r ^= (*iteratorMPrime * rPrime) & UINT8_MAX;
        ++iteratorMPrime;
    }
    x = I[rPrime];
    r_ori = rPrime;
    do
    {
        --iteratorMPrime;
        *iteratorMPrime ^= x;
        x = I[(*iteratorMPrime + r_ori) & UINT8_MAX];
        rPrime ^= (*iteratorMPrime * r) & UINT8_MAX;
    }
    while(iteratorMPrime != mPrime.begin());
    mPrime.emplace_back(r);
    mPrime.emplace_back(rPrime);
    return mPrime;
}

std::vector<uint8_t> CompactLWE::decode(const std::vector<uint8_t>& mPrime, const std::vector<uint8_t>& I)
{
    std::vector<uint8_t> m;
    const size_t l = mPrime.size();
    m.reserve(l - 2);
    uint8_t rPrime = mPrime.back();
    uint8_t r = *std::prev(mPrime.cend(), 2);
    for(std::vector<uint8_t>::const_iterator iteratorMPrime = mPrime.cbegin(); iteratorMPrime != std::prev(mPrime.cend(), 3); ++iteratorMPrime)
    {
        rPrime ^= (*iteratorMPrime * r) & UINT8_MAX; // & UINT8_MAX = & 255 = % 256
    }
    uint8_t x = I[rPrime];
    for(std::vector<uint8_t>::const_reverse_iterator iteratorMPrime = std::next(mPrime.crbegin(), 2); iteratorMPrime != mPrime.crend(); ++iteratorMPrime)
    {
        m.emplace_back(x ^ *iteratorMPrime);
        x = I[(*iteratorMPrime + rPrime) & UINT8_MAX];
    }
    for(std::vector<uint8_t>::const_iterator iteratorM = m.cbegin(); iteratorM != m.cend(); ++iteratorM)
    {
        r ^= (*iteratorM * rPrime) & UINT8_MAX;
    }
    x = I[r];
    for(std::vector<uint8_t>::iterator iteratorM = m.begin(); iteratorM != m.end(); ++iteratorM)
    {
        uint8_t y = *iteratorM;
        *iteratorM ^= x;
        x = I[(y + r) & UINT8_MAX];
    }
    return m;
}

std::vector<BigInt> CompactLWE::generateL(const CompactLWE& to)
{
    const BigInt wPlusWPrime = to.getPublicParamethers().w + to.getPublicParamethers().wPrime;
    const size_t lAverageBitLenght = ((wPlusWPrime + to.getPublicParamethers().wPrime) / BigInt(to.getPublicParamethers().m)).bitLenght();
    std::vector<BigInt> l;
    BigInt sumL(0);
    BigInt innerProductLU;
    PRBgenerators prbGenerator;
    l.reserve(to.getPublicParamethers().m);
    prbGenerator.setNumberOfBits(lAverageBitLenght);
    while(sumL <= wPlusWPrime && l.size() <= to.getPublicParamethers().m)
    {
        prbGenerator.generateL20();
        l.emplace_back(++BigInt(prbGenerator.getGeneratedPRBS()));
        sumL += l.back();
    }
    l.pop_back();
    sumL = constants::ZERO;
    while(sumL >= -to.getPublicParamethers().wPrime && l.size() <= to.getPublicParamethers().m)
    {
        prbGenerator.generateL20();
        l.emplace_back(-(++BigInt(prbGenerator.getGeneratedPRBS())));
        sumL += l.back();
    }
    l.pop_back();
    l.resize(to.getPublicParamethers().m, constants::ZERO);
    static std::random_device rd;
    static std::mt19937 rng(rd());
    do
    {
        std::shuffle(l.begin(), l.end(), rng);
        std::vector<BigInt>::const_iterator iteratorL = l.cbegin();
        std::vector<Keys::PublicKeySample>::const_iterator iteratorToPublicKey = to.publicKey.cbegin();
        innerProductLU = constants::ZERO;
        while(iteratorL != l.cend() && iteratorToPublicKey != to.getPublicKey().cend())
        {
            innerProductLU += *iteratorL * iteratorToPublicKey->u;
            ++iteratorL;
            ++iteratorToPublicKey;
        }
    }
    while(innerProductLU <= constants::ZERO);
    return l;
}
