#include "unospecialcard.h"
#include <QJsonObject>
#include <QJsonDocument>

UnoSpecialCard::UnoSpecialCard(const int id, const UnoCardColor color, const Type type, QObject *parent)
    : UnoCardBase{id, color, parent}, m_type(type)
{}

UnoSpecialCard *UnoSpecialCard::fromJsonObj(QJsonObject object) {
    int id;
    UnoCardColor color;
    Type type;

    if (object.contains("id") && object["id"].isDouble())
        id = object["id"].toInt();
    else throw "JSON object doesn't contain 'id'";

    if (object.contains("color") && object["color"].isDouble())
        color = static_cast<UnoCardColor>(object["color"].toInt());
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

QJsonObject UnoSpecialCard::toJsonObj() const
{
    QJsonObject json;
    json["id"] = m_id;
    json["color"] = static_cast<int>(m_color);
    json["type"] = m_type;
    return json;
}

UnoSpecialCard::Type UnoSpecialCard::getType() const
{
    return m_type;
}
