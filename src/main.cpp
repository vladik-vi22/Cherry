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

    BigInt t1("1234567891234567899876543213456783457618340576314957863457863764534538425963984", 10);
    BigInt t2("123456789222222222222342342343242", 10);
    BigInt t3("123456789123", 10);
    BigInt t4("AA974A9FC15a781496F1E50AB871A6EDB4F011EA15A4D24F820B9A0CBEA2195D0", 16);
    BigInt t5("6163E66885CEAC8F3D86CF07A4A", 16);
    BigInt t6("1CBE991A83", 16);
    BigInt t7("263130836933693530167218012159999999 ", 10);
    BigInt t8("-8683317618811886495518194401279999999 ", 10);
    BigInt resTest;
    //resTest = UINT64_MAX;
    qDebug() << t8;
    return app.exec();
}

