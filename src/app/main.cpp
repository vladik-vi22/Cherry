#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <iostream>

#include <bigint/BigIntCalculator.h>
#include <generators/PRBgenerators.h>
#include <rpn/RPNgenerator.h>
#include <crypto/RSAcryptosystem.h>
#include <crypto/CompactLWE.h>
#include <ciphers/EDHcryptorVizhener.h>
#include <ciphers/EDHcryptorAffine.h>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    qmlRegisterType<BigIntCalculator>("BigIntLibrary", 2, 0, "BigIntNumbersBases");
    qmlRegisterType<PRBgenerators>("PRBgenerators", 1, 0, "PRBgenerators");
    qmlRegisterType<Vizhener>("VizhenerTextKey", 1, 0, "VTextKey");
    qmlRegisterType<Affine>("AffineTextKeys", 1, 0, "ATextKeys");

    QQmlApplicationEngine engine;

    // Qt6 qt_add_qml_module uses URI-based resource paths
    const QUrl url(QStringLiteral("qrc:/qt/qml/Cherry/qml/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl) {
            qCritical() << "Failed to load QML from:" << url;
            QCoreApplication::exit(-1);
        }
    }, Qt::QueuedConnection);
    engine.load(url);

    if (engine.rootObjects().isEmpty()) {
        qCritical() << "No root objects loaded. Check QML path.";
        return -1;
    }

    return app.exec();
}

