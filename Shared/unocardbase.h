#ifndef UNOCARDBASE_H
#define UNOCARDBASE_H

#include <QObject>
#include "Shared_global.h"

class SHARED_EXPORT UnoCardBase : public QObject
{
    Q_OBJECT
public:
    explicit UnoCardBase(QObject *parent = nullptr);
protected:
    int id;
    QString color;

signals:
};

#endif // UNOCARDBASE_H
