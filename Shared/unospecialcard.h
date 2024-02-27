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
    Type getType() const;
    void toJson(QJsonObject &json) const;

private:
    const Type type;
};

#endif // UNOSPECIALCARD_H
