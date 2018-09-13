#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <iostream>

#include "src/BigIntLibrary/BigIntCalculator.h"
#include "src/PRBgenerators/PRBgenerators.h"
#include "src/RPNgenerator/RPNgenerator.h"
#include "src/Cryptosystems/RSAcryptosystem.h"
#include "src/Cryptosystems/CompactLWE.h"
#include "src/EDHcryptor/EDHcryptorVizhener.h"
#include "src/EDHcryptor/EDHcryptorAffine.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    qmlRegisterType<BigIntCalculator>("BigIntLibrary", 2, 0, "BigIntNumbersBases");
    qmlRegisterType<PRBgenerators>("PRBgenerators", 1, 0, "PRBgenerators");
    qmlRegisterType<Vizhener>("VizhenerTextKey", 1, 0, "VTextKey");
    qmlRegisterType<Affine>("AffineTextKeys", 1, 0, "ATextKeys");

    BigInt a("11111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111", 2);
    /*BigInt b("2222222222222222222222222222222222222222222222222222", 10);
    BigInt c(a + b);*/
    std::cout << (a << static_cast<size_t>(100)).toStdString(2) << std::endl;
    return 0;

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/src/qml_production/main.qml")));
    return app.exec();
}

