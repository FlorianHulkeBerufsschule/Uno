#include "gamefield.h"
#include "unospecialcard.h"
#include "unospecialcardtype.h"

Gamefield::Gamefield(QObject *parent)
    : QObject{parent}
{
    UnoSpecialCard *card = new UnoSpecialCard;
    card->setType(UnoSpecialCardType::DrawFour);
    drawStack.append(card);
}
