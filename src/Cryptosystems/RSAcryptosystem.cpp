#include "RSAcryptosystem.h"

RSAcryptosystem::RSAcryptosystem(QObject* parent): QObject(parent)
{

}

RSAcryptosystem::~RSAcryptosystem()
{

}

void RSAcryptosystem::generateKeyPair(const uint32_t numberOfBits)
{
    RPNgenerator rpnGenerator;
    const BigInt p(rpnGenerator.generatePrimeNumber(numberOfBits));
    const BigInt q(rpnGenerator.generatePrimeNumber(numberOfBits));
    publicModulus =  p * q;
    publicExponent = BigInt(65537); // 2^16 + 1
    const BigInt phiPublicModulus((p - ConstBigInt::ONE) * (q - ConstBigInt::ONE));
    privateKey = inversemod(publicExponent, phiPublicModulus);
}

BigInt RSAcryptosystem::getPublicModulus() const
{
    return publicModulus;
}

BigInt RSAcryptosystem::getPublicExponent() const
{
    return publicExponent;
}

void RSAcryptosystem::setPublicModulus(const BigInt& new_publicModulus)
{
    publicModulus = new_publicModulus;
}

void RSAcryptosystem::setPublicExponent(const BigInt &new_publicExponent)
{
    publicExponent = new_publicExponent;
}

void RSAcryptosystem::setSessionKey(const BigInt &new_sessionKey)
{
    sessionKey = new_sessionKey;
}

void RSAcryptosystem::setSignatureFrom(const BigInt &signature)
{
    signatureFrom = signature;
}

BigInt RSAcryptosystem::encrypt(const BigInt& plaintext, const RSAcryptosystem& to)
{
    return powmod(plaintext, to.getPublicExponent(), to.getPublicModulus());
}

BigInt RSAcryptosystem::decrypt(const BigInt& ciphertext)
{
    return powmod(ciphertext, privateKey, publicModulus);
}

BigInt RSAcryptosystem::signature(const BigInt& message)
{
    return powmod(message, privateKey, publicModulus);
}

bool RSAcryptosystem::verify(const BigInt& message, const BigInt& signature, const RSAcryptosystem& from)
{
    return message == powmod(signature, from.getPublicExponent(), from.getPublicModulus());
}

void RSAcryptosystem::sendSessionKey(RSAcryptosystem& to)
{
    while(publicModulus > to.getPublicModulus())
    {
        generateKeyPair(256);
    }
    to.setSessionKey(encrypt(sessionKey, to));
    to.setSignatureFrom(encrypt(signature(sessionKey), to));
}

void RSAcryptosystem::receiveSessionKey(const RSAcryptosystem& from)
{
    sessionKey = decrypt(sessionKey);
    signatureFrom = decrypt(signatureFrom);
    verification = verify(sessionKey, signatureFrom, from);
}
