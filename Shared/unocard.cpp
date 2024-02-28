#include "unocard.h"
#include <QJsonObject>
#include <QJsonDocument>

UnoCard::UnoCard(const int id, const QString color, const int value, QObject *parent)
    : UnoCardBase{id, color, parent}, value(value)
{}

UnoCard *UnoCard::fromJsonObj(QJsonObject object) {
    int id;
    QString color;
    int value;

    if (object.contains("id") && object["id"].isDouble())
        id = object["id"].toInt();
    else throw "JSON object doesn't contain 'id'";

    if (object.contains("color") && object["color"].isString())
        color = object["color"].toString();
    else throw "JSON object doesn't contain 'color'";

    if (object.contains("value") && object["value"].isDouble())
        value = object["value"].toInt();
    else throw "JSON object doesn't contain 'value'";

    return new UnoCard(id, color, value);
}

UnoCard *UnoCard::fromJsonDoc(QJsonDocument document)
{
    return fromJsonObj(document.object());
}

UnoCard *UnoCard::fromJsonStr(QString string)
{
    return fromJsonDoc(QJsonDocument::fromJson(string.toUtf8()));
}

void UnoCard::toJsonObj(QJsonObject &json) const
{
    json["id"] = this->id;
    json["color"] = this->color;
    json["value"] = this->value;
}

int UnoCard::getValue() const
{
    return this->value;
}
