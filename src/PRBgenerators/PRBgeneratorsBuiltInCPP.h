#ifndef BuiltInCPP_H
#define BuiltInCPP_H

#include "PRBgenerators.h"

#include <QQuickItem>
#include <QObject>
#include <QBitArray>
#include <QString>
#include <QList>
#include <QPair>
#include <QDataStream>
#include <QtMath>
#include <QtAlgorithms>

class BuiltInCPP: public PRBgenerators
{

public:
    explicit BuiltInCPP();
    ~BuiltInCPP();

    Q_INVOKABLE void generate();


private:

};

#endif // BuiltInCPP_H
