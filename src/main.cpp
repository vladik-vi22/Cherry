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
    test.generateBuiltInCPP(100);
    test.generateLehmerLow(100);
    test.generateLehmerHigh(100);
    test.generateL20(100);
    test.generateL89(100);
    test.generateGeffe(100);
    test.generateWolfram(100);
    test.generateBlumMikali(100);
    return 0;
}

