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
    //engine.load(QUrl(QStringLiteral("qrc:/src/qml_production/main.qml")));

    BigInt t1("1234567891234567899876543213456783457618340576314957863457863764534538425963984");
    BigInt t2("123456789222222222222342342343242");
    BigInt t3("123456789123");
//    BigInt t1("AA974A9FC15A781496F1E50AB871A6EDB4F011EA15A4D24F820B9A0CBEA2195D0");
//    BigInt t2("6163E66885CEAC8F3D86CF07A4A");
//    BigInt t3("1CBE991A83");
    BigInt resTest;
    resTest = t3.shiftBitsToHigh(71);
    print(resTest);
    return app.exec();
}

