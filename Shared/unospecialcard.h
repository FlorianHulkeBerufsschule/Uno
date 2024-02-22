#ifndef UNOSPECIALCARD_H
#define UNOSPECIALCARD_H

#include "unocardbase.h"
#include "unospecialcardtype.h"
#include "Shared_global.h"

class SHARED_EXPORT UnoSpecialCard : public UnoCardBase
{
public:
    explicit UnoSpecialCard(QObject *parent = nullptr);
    void setType(UnoSpecialCardType type);
private:
    UnoSpecialCardType type;
};

#endif // UNOSPECIALCARD_H
