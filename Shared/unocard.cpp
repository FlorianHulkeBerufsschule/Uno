#include "unocard.h"
#include <QJsonObject>
#include <QJsonDocument>

UnoCard::UnoCard(const int id, const UnoCardColor color, const int value, QObject *parent)
    : UnoCardBase{id, color, parent}, m_value(value)
{}

UnoCard *UnoCard::fromJsonObj(QJsonObject object) {
    int id;
    UnoCardColor color;
    int value;

    if (object.contains("id") && object["id"].isDouble())
        id = object["id"].toInt();
    else throw "JSON object doesn't contain 'id'";

    if (object.contains("color") && object["color"].isDouble())
        color = static_cast<UnoCardColor>(object["color"].toInt());
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

QJsonObject UnoCard::toJsonObj() const
{
    QJsonObject json;
    json["id"] = m_id;
    json["color"] = static_cast<int>(m_color);
    json["value"] = m_value;
    return json;
}

int UnoCard::getValue() const
{
    return m_value;
}
