#include "unocard.h"
#include "unocardbase.h"
#include "unospecialcard.h"
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

UnoCardBase *UnoCardBase::fromJsonObj(QJsonObject object)
{
    if (object.contains("value"))
    {
        return UnoCard::fromJsonObj(object);
    }
    return UnoSpecialCard::fromJsonObj(object);
}

UnoCardBase *UnoCardBase::fromJsonDoc(QJsonDocument document)
{
    QJsonObject obj = document.object();
    return fromJsonObj(obj);
}

UnoCardBase *UnoCardBase::fromJsonStr(QString string)
{
    QJsonDocument doc = QJsonDocument::fromJson(string.toUtf8());
    return fromJsonDoc(doc);
}
