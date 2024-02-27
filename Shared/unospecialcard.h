#ifndef UNOSPECIALCARD_H
#define UNOSPECIALCARD_H

#include "unocardbase.h"
#include "unospecialcardtype.h"
#include "Shared_global.h"

class SHARED_EXPORT UnoSpecialCard : public UnoCardBase
{
public:
    explicit UnoSpecialCard(const int id, const QString color, const UnoSpecialCardType type, QObject *parent = nullptr);
    UnoSpecialCardType getType() const;
    void toJson(QJsonObject &json) const;
private:
    const UnoSpecialCardType type;
};

#endif // UNOSPECIALCARD_H
