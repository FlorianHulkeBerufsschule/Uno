#include "unocard.h"
#include <QJsonObject>

UnoCard::UnoCard(const int id, const QString color, const int value, QObject *parent)
    : UnoCardBase{id, color, parent}, value(value)
{}

int UnoCard::getValue() const
{
    return this->value;
}

void UnoCard::toJson(QJsonObject &json) const
{
    json["id"] = this->id;
    json["color"] = this->color;
    json["value"] = this->value;
}
