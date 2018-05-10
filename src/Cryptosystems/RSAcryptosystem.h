#ifndef RSAcryptosystem_H
#define RSAcryptosystem_H

#include <QObject>
#include <QQuickItem>
#include "../BigIntLibrary/BigIntLibrary.h"
#include "../RPNgenerator/RPNgenerator.h"

class RSAcryptosystem: public QObject
{
    Q_OBJECT

private:
    BigInt publicModulus;
    BigInt publicExponent;
    BigInt privateKey;

    BigInt sessionKey;
    BigInt signatureFrom;
    bool verification;

public:
    explicit RSAcryptosystem(QObject *parent = 0);
    ~RSAcryptosystem();

signals:

public:
    void generateKeyPair(const uint32_t numberOfBits);
    BigInt getPublicModulus() const;
    BigInt getPublicExponent() const;
    void setPublicModulus(const BigInt& new_publicModulus);
    void setPublicExponent(const BigInt& new_publicExponent);
    void setSessionKey(const BigInt& new_sessionKey);
    void setSignatureFrom(const BigInt& signature);
    BigInt encrypt(const BigInt& plaintext, const RSAcryptosystem& to);
    BigInt decrypt(const BigInt& ciphertext);
    BigInt signature(const BigInt& message);
    bool verify(const BigInt& message, const BigInt& signature, const RSAcryptosystem& from);
    void sendSessionKey(RSAcryptosystem& to);
    void receiveSessionKey(const RSAcryptosystem& from);

private:

};

#endif // RSAcryptosystem_H
