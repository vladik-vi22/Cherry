#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "src/BigIntLibrary/BigIntCalculator.h"
#include "src/PRBgenerators/PRBgenerators.h"
#include "src/EDHcryptor/EDHcryptorVizhener.h"
#include "src/EDHcryptor/EDHcryptorAffine.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    qmlRegisterType<BigIntCalculator>("BigIntLibrary", 2, 0, "BigIntNumbersBases");
    qmlRegisterType<PRBgenerators>("PRBgenerators", 1, 0, "PRBgenerators");
    qmlRegisterType<Vizhener>("VizhenerTextKey", 1, 0, "VTextKey");
    qmlRegisterType<Affine>("AffineTextKeys", 1, 0, "ATextKeys");

    QQmlApplicationEngine engine;
//    engine.load(QUrl(QStringLiteral("qrc:/src/qml_production/main.qml")));
//    return app.exec();

    PRBgenerators test;
    test.generateBuiltInCPP(2097152);
    test.generateLehmerLow(2097152);
    test.generateLehmerHigh(2097152);
    test.generateL20(2097152);
    test.generateL89(2097152);
    test.generateGeffe(2097152);
    test.generateWolfram(2097152);
    test.generateLibrarian(2097152);
    test.generateBlumMikaliBit(128);
    test.generateBlumMikaliByte(128);
    test.generateBlumBlumShubBit(128);
    test.generateBlumBlumShubByte(128);
    return 0;
}

