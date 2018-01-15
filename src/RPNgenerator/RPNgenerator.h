#ifndef RPNgenerator_H
#define RPNgenerator_H

#include <QObject>
#include <QQuickItem>
#include "../BigIntLibrary/BigIntLibrary.h"
#include "../PRBgenerators/PRBgenerators.h"

class RPNgenerator: public QObject
{
    Q_OBJECT

public:
    explicit RPNgenerator(QObject *parent = 0);
    ~RPNgenerator();

signals:

public:
    BigInt generatePrimeNumber(const uint32_t& numberOfBit);

private:
    bool pseudoprimeTest(const BigInt& oddNumber, const BigInt& base);
    bool pseudoprimeTestEulerJacobi(const BigInt& oddNumber, const BigInt& base);
    bool divisibilityRulePascal(const BigInt& bigNum);
    bool primalityTestPherma(const BigInt& bigNum);
    bool primalityTestSolovayStrassen(const BigInt& bigNum);
    bool primalityTestMillerRabin(const BigInt& bigNum);
};

#endif // RPNgenerator_H
