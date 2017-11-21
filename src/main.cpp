#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "src/BigIntLibrary/BigIntCalculator.h"
#include "src/EDHcryptor/EDHcryptorVizhener.h"
#include "src/EDHcryptor/EDHcryptorAffine.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    qmlRegisterType<BigIntCalculator>("BigIntLibrary", 2, 0, "BigIntNumbersBases");
    qmlRegisterType<Vizhener>("VizhenerTextKey", 1, 0, "VTextKey");
    qmlRegisterType<Affine>("AffineTextKeys", 1, 0, "ATextKeys");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/src/qml_production/main.qml")));

    return app.exec();
}

