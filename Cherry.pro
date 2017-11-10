TEMPLATE = app

CONFIG += c++11
CONFIG += CONSOLE

QT += qml quick widgets

SOURCES += src/main.cpp\
    src/EDHcryptor/EDHcryptorAffine.cpp \
    src/EDHcryptor/EDHcryptorVizhener.cpp \
    src/PRBgenerators/PRBgeneratorsBuiltInCPP.cpp \
    src/PRBgenerators/PRBgenerators.cpp \
    src/BigIntLibrary/BigIntLibrary.cpp \
    src/BigIntLibrary/BigIntCalculator.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    src/EDHcryptor/EDHcryptorAffine.h \
    src/EDHcryptor/EDHcryptorVizhener.h \
    src/PRBgenerators/PRBgeneratorsBuiltInCPP.h \
    src/PRBgenerators/PRBgenerators.h \
    src/BigIntLibrary/BigIntLibrary.h \
    src/BigIntLibrary/BigIntCalculator.h

