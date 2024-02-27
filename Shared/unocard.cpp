#include "unocard.h"
#include <QJsonObject>
#include <QJsonDocument>

UnoCard::UnoCard(const int id, const QString color, const int value, QObject *parent)
    : UnoCardBase{id, color, parent}, value(value)
{}

UnoCard *UnoCard::fromJsonObj(QJsonObject &json) {
    int id;
    QString color;
    int value;

    if (json.contains("id") && json["id"].isDouble())
        id = json["id"].toInt();
    else throw "JSON object doesn't contain 'id'";

    if (json.contains("color") && json["color"].isString())
        color = json["color"].toString();
    else throw "JSON object doesn't contain 'color'";

    if (json.contains("value") && json["value"].isDouble())
        value = json["value"].toInt();
    else throw "JSON object doesn't contain 'value'";

    return new UnoCard(id, color, value);
}

UnoCard *UnoCard::fromJsonDoc(QJsonDocument &document)
{
    QJsonObject obj = document.object();
    return fromJsonObj(obj);
}

UnoCard *UnoCard::fromJsonStr(QString string)
{
    QJsonDocument doc = QJsonDocument::fromJson(string.toUtf8());
    return fromJsonDoc(doc);
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
