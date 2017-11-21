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
};

#endif // PRBgenerators_H
