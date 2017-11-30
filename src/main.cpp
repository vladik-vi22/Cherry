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
    qmlRegisterType<Vizhener>("VizhenerTextKey", 1, 0, "VTextKey");
    qmlRegisterType<Affine>("AffineTextKeys", 1, 0, "ATextKeys");

    QQmlApplicationEngine engine;
    //engine.load(QUrl(QStringLiteral("qrc:/src/qml_production/main.qml")));
    //return app.exec();

    PRBgenerators test;
    test.generateBuiltInCPP(128);
    test.generateLehmerLow(128);
    test.generateLehmerHigh(128);
    test.generateL20(128);
    test.generateL89(128);
    test.generateGeffe(128);
    test.generateWolfram(128);
    test.generateBlumMikaliBit(128);
    test.generateBlumMikaliByte(128);
    test.generateBlumBlumShubBit(128);
    test.generateBlumBlumShubByte(128);
    return 0;
}

