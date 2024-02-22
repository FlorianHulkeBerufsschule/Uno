#include "unospecialcard.h"

UnoSpecialCard::UnoSpecialCard(QObject *parent)
    : UnoCardBase{parent}
{}

void UnoSpecialCard::setType(UnoSpecialCardType type){
    this->type = type;
}
