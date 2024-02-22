#include "unocardbase.h"

UnoCardBase::UnoCardBase(const int id, const QString color, QObject *parent)
    : QObject{parent}, id(id), color(color)
{}

int UnoCardBase::getId() const
{
    return this->id;
}

QString UnoCardBase::getColor() const
{
    return this->color;
}
