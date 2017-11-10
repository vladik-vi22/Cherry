#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "src/BigIntLibrary/BigIntLibrary.h"
#include "src/EDHcryptor/EDHcryptorVizhener.h"
#include "src/EDHcryptor/EDHcryptorAffine.h"
#include "src/PRBgenerators/PRBgeneratorsBuiltInCPP.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    qmlRegisterType<Vizhener>("VizhenerTextKey", 1, 0, "VTextKey");
    qmlRegisterType<Affine>("AffineTextKeys", 1, 0, "ATextKeys");
    //qmlRegisterType<BuiltInCPP>("BuiltInCPPNumber", 1, 0, "BICPPNumber");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/src/qml_production/main.qml")));

    return app.exec();
}

