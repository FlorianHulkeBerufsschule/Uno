#include "unospecialcard.h"
#include <QJsonObject>

UnoSpecialCard::UnoSpecialCard(const int id, const QString color, const Type type, QObject *parent)
    : UnoCardBase{id, color, parent}, type(type)
{}

UnoSpecialCard::Type UnoSpecialCard::getType() const
{
    return this->type;
}

void UnoSpecialCard::toJson(QJsonObject &json) const
{
    json["id"] = this->id;
    json["color"] = this->color;
    json["type"] = this->type;
}
