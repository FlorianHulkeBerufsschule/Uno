#ifndef UNOCARD_H
#define UNOCARD_H

#include "unocardbase.h"
#include "Shared_global.h"

class SHARED_EXPORT UnoCard : public UnoCardBase
{
public:
    explicit UnoCard(const int id, const UnoCardColor color, const int value, QObject *parent = nullptr);
    static UnoCard* fromJsonObj(QJsonObject object);
    static UnoCard* fromJsonDoc(QJsonDocument document);
    static UnoCard* fromJsonStr(QString str);
    QJsonObject toJsonObj() const;
    int getValue() const;
private:
    const int m_value;
};

#endif // UNOCARD_H
