#ifndef UNOCARD_H
#define UNOCARD_H

#include "unocardbase.h"
#include "Shared_global.h"

class SHARED_EXPORT UnoCard : public UnoCardBase
{
public:
    explicit UnoCard(const int id, const QString color, const int value, QObject *parent = nullptr);
    static UnoCard* fromJsonObj(QJsonObject object);
    static UnoCard* fromJsonDoc(QJsonDocument document);
    static UnoCard* fromJsonStr(QString str);
    void toJsonObj(QJsonObject &json) const;
    int getValue() const;
private:
    const int value;
};

#endif // UNOCARD_H
