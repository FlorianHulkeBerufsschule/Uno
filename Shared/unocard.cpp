#include "unocard.h"

UnoCard::UnoCard(const int id, const QString color, const int value, QObject *parent)
    : UnoCardBase{id, color, parent}, value(value)
{}

int UnoCard::getValue() const
{
    return this->value;
}
