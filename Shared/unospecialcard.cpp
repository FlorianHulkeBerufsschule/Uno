#include "unospecialcard.h"
#include <QJsonObject>
#include <QJsonDocument>

UnoSpecialCard::UnoSpecialCard(const int id, const QString color, const Type type, QObject *parent)
    : UnoCardBase{id, color, parent}, type(type)
{}

UnoSpecialCard *UnoSpecialCard::fromJsonObj(QJsonObject object) {
    int id;
    QString color;
    Type type;

    if (object.contains("id") && object["id"].isDouble())
        id = object["id"].toInt();
    else throw "JSON object doesn't contain 'id'";

    if (object.contains("color") && object["color"].isString())
        color = object["color"].toString();
    else throw "JSON object doesn't contain 'color'";

    if (object.contains("type") && object["type"].isDouble())
        type = static_cast<UnoSpecialCard::Type>(object["type"].toInt());
    else throw "JSON object doesn't contain 'type'";

    return new UnoSpecialCard(id, color, type);
}

UnoSpecialCard *UnoSpecialCard::fromJsonDoc(QJsonDocument document)
{
    return fromJsonObj(document.object());
}

UnoSpecialCard *UnoSpecialCard::fromJsonStr(QString string)
{
    return fromJsonDoc(QJsonDocument::fromJson(string.toUtf8()));
}

void UnoSpecialCard::toJsonObj(QJsonObject &json) const
{
    json["id"] = this->id;
    json["color"] = this->color;
    json["type"] = this->type;
}

UnoSpecialCard::Type UnoSpecialCard::getType() const
{
    return this->type;
}
