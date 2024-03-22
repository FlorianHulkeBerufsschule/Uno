#include "unocard.h"
#include "unocardbase.h"
#include "unospecialcard.h"
#include <QJsonObject>
#include <QJsonDocument>

UnoCardBase::UnoCardBase(const int id, const UnoCardColor color, QObject *parent)
    : QObject{parent}, m_id(id), m_color(color)
{}

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
    return fromJsonObj(document.object());
}

UnoCardBase *UnoCardBase::fromJsonStr(QString string)
{
    return fromJsonDoc(QJsonDocument::fromJson(string.toUtf8()));
}

QJsonDocument UnoCardBase::toJsonDoc() const
{
    return QJsonDocument(toJsonObj());
}

QString UnoCardBase::toJsonStr() const
{
    return toJsonDoc().toJson(QJsonDocument::Compact);
}

int UnoCardBase::getId()
{
    return m_id;
}

UnoCardColor UnoCardBase::getColor()
{
    return m_color;
}
