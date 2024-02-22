#include "unospecialcard.h"

UnoSpecialCard::UnoSpecialCard(const int id, const QString color, const UnoSpecialCardType type, QObject *parent)
    : UnoCardBase{id, color, parent}, type(type)
{}

UnoSpecialCardType UnoSpecialCard::getType() const
{
    return this->type;
}
