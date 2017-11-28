#ifndef PRBgenerators_H
#define PRBgenerators_H

#include <QObject>
#include <QQuickItem>
#include "../BigIntLibrary/BigIntLibrary.h"

class PRBgenerators: public QObject
{
    Q_OBJECT

public:
    explicit PRBgenerators(QObject *parent = 0);
    ~PRBgenerators();

    Q_INVOKABLE void generateBuiltInCPP(const uint32_t& numberOfBit);

private:
    BigInt m_generatedByBuiltInCPP;
};

#endif // PRBgenerators_H
