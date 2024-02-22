#ifndef GAMEFIELD_H
#define GAMEFIELD_H

#include <QObject>
#include <QList>
#include "unocardbase.h"

class Gamefield : public QObject
{
    Q_OBJECT
public:
    explicit Gamefield(QObject *parent = nullptr);
private:
    QList<UnoCardBase*> drawStack;

signals:
};

#endif // GAMEFIELD_H
