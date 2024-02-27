#include "unocardbase.h"
#include <QJsonObject>
#include <QJsonDocument>

UnoCardBase::UnoCardBase(const int id, const QString color, QObject *parent)
    : QObject{parent}, id(id), color(color)
{}

QJsonDocument UnoCardBase::toJsonDoc() const
{
    QJsonObject json;
    this->toJsonObj(json);

    return *new QJsonDocument(json);
}

QString UnoCardBase::toJsonStr() const
{
    return this->toJsonDoc().toJson(QJsonDocument::Compact);
}

int UnoCardBase::getId() const
{
    return this->id;
}

QString UnoCardBase::getColor() const
{
    return this->color;
}
