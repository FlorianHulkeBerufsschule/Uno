#ifndef UNOCARD_H
#define UNOCARD_H

#include "unocardbase.h"
#include "Shared_global.h"

class SHARED_EXPORT UnoCard : public UnoCardBase
{
public:
    explicit UnoCard(QObject *parent = nullptr);
private:
    int value;
};

#endif // UNOCARD_H
