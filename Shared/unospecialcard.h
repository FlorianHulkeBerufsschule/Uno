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
    static UnoSpecialCard* fromJsonObj(QJsonObject object);
    static UnoSpecialCard* fromJsonDoc(QJsonDocument document);
    static UnoSpecialCard* fromJsonStr(QString string);
    QJsonObject toJsonObj() const;
    Type getType() const;

private:
    const Type m_type;
};

#endif // UNOSPECIALCARD_H
