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

    CompactLWE a;
    a.generatePrivateKey();
    a.generatePublicKey();
    return 0;

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/src/qml_production/main.qml")));
    return app.exec();
}

