#include "unospecialcard.h"
#include <QJsonObject>

UnoSpecialCard::UnoSpecialCard(const int id, const QString color, const Type type, QObject *parent)
    : UnoCardBase{id, color, parent}, type(type)
{}

UnoSpecialCard *UnoSpecialCard::fromJson(QJsonObject &json) {
    int id;
    QString color;
    Type type;

    if (json.contains("id") && json["id"].isDouble())
        id = json["id"].toInt();
    else throw "JSON object doesn't contain 'id'";

    if (json.contains("color") && json["color"].isString())
        color = json["color"].toString();
    else throw "JSON object doesn't contain 'color'";

    if (json.contains("type") && json["type"].isDouble())
        type = static_cast<UnoSpecialCard::Type>(json["type"].toInt());
    else throw "JSON object doesn't contain 'type'";

    return new UnoSpecialCard(id, color, type);
}

void UnoSpecialCard::toJson(QJsonObject &json) const
{
    json["id"] = this->id;
    json["color"] = this->color;
    json["type"] = this->type;
}

UnoSpecialCard::Type UnoSpecialCard::getType() const
{
    return this->type;
}
