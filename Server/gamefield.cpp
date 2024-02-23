#include "gamefield.h"
#include "qdebug.h"
#include "unocard.h"
#include "unospecialcard.h"
#include "unospecialcardtype.h"

Gamefield::Gamefield(QObject *parent)
    : QObject{parent}
{
    drawStack.append(new UnoSpecialCard(1, "black", UnoSpecialCardType::DrawFour));
    drawStack.append(new UnoCard(2, "yellow", 8));

    UnoCardBase *first = drawStack.first();

    if(UnoSpecialCard *card = dynamic_cast<UnoSpecialCard*>(first))
    {
        qDebug() << card->getId() << card->getColor();
    }
}