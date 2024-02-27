#ifndef UNOSPECIALCARD_H
#define UNOSPECIALCARD_H

#include "unocardbase.h"
#include "Shared_global.h"

class SHARED_EXPORT UnoSpecialCard : public UnoCardBase
{
public:
    enum Type
    {
        DrawFour,
        DrawTwo,
        Wildcard,
        Reverse,
        Skip
    };
    Q_ENUM(Type);

    explicit UnoSpecialCard(const int id, const QString color, const Type type, QObject *parent = nullptr);
    static UnoSpecialCard* fromJsonObj(QJsonObject &json);
    static UnoSpecialCard* fromJsonDoc(QJsonDocument &document);
    static UnoSpecialCard* fromJsonStr(QString string);
    void toJsonObj(QJsonObject &json) const;
    Type getType() const;

private:
    const Type type;
};

#endif // UNOSPECIALCARD_H
