#include "gamefield.h"
#include "helper.h"
#include "player.h"
#include "unocard.h"
#include "unospecialcard.h"
#include <QMetaEnum>
#include <QRandomGenerator>

#define DISPLAY_ERROR QString::number(static_cast<int>(ClientAction::DisplayError))

Gamefield::Gamefield(QList<QueueEntry *> queue, bool debug, QObject *parent)
    : QObject{parent}, m_debug(debug)
{
    initDrawStack();
    initPlayers(queue);
    initPlayerCards();
}

void Gamefield::initDrawStack()
{
    int id = 1;

    // Initialisiere die Standartkarten (1 bis 9)
    for (int i = 0; i <= 9; i++)
    {
        // Falls i gleich 0 initialiere j mit 1 ansonsten 0
        for (int j = i == 0 ? 1 : 0; j <= 1; j++)
        {
            m_drawStack.append(new UnoCard(id++, UnoCardColor::Red, i));
            m_drawStack.append(new UnoCard(id++, UnoCardColor::Yellow, i));
            m_drawStack.append(new UnoCard(id++, UnoCardColor::Green, i));
            m_drawStack.append(new UnoCard(id++, UnoCardColor::Blue, i));
        }
    }

    // Initialisiere die Spezialkarten (5 unterschiedliche Typen)
    for (int i = 0; i <= 4; i++)
    {
        if (i == UnoSpecialCard::DrawTwo || i == UnoSpecialCard::Reverse || i == UnoSpecialCard::Skip)
        {
            for (int j = 0; j <= 1; j++)
            {
                m_drawStack.append(new UnoSpecialCard(id++, UnoCardColor::Red, static_cast<UnoSpecialCard::Type>(i)));
                m_drawStack.append(new UnoSpecialCard(id++, UnoCardColor::Yellow, static_cast<UnoSpecialCard::Type>(i)));
                m_drawStack.append(new UnoSpecialCard(id++, UnoCardColor::Green, static_cast<UnoSpecialCard::Type>(i)));
                m_drawStack.append(new UnoSpecialCard(id++, UnoCardColor::Blue, static_cast<UnoSpecialCard::Type>(i)));
            }
        }
        else
        {
            // Von DrawFor und Wildcard brauchen wir jeweils 4
            for (int j = 0; j <= 3; j++)
            {
                m_drawStack.append(new UnoSpecialCard(id++, UnoCardColor::Black, static_cast<UnoSpecialCard::Type>(i)));
            }
        }
    }

    if (m_debug)
        qDebug() << "Initialized" << m_drawStack.length() << "game cards";
}

void Gamefield::initPlayers(QList<QueueEntry *> queue)
{
    for (QueueEntry *entry : queue)
    {
        m_players.append(new Player(entry->getClient()));
    }

    if (m_debug)
        qDebug() << "Starting game with" << m_players.length() << "players";
}

void Gamefield::initPlayerCards()
{
    for (Player *player : qAsConst(m_players))
    {
        drawRandomCard(player->getClient(), 7);

        if(m_debug)
            qDebug() << player << "has" << player->getCards()->size() << "cards";
    }

    if(m_debug)
        qDebug() << m_drawStack.size() << "cards left on the drawstack";
}

void Gamefield::drawRandomCard(QWebSocket *client)
{
    drawRandomCard(client, m_countToDraw);
}

void Gamefield::drawRandomCard(QWebSocket *client, int countToDraw)
{
    Player *player = getPlayer(client);

    for(int i = 0; i < countToDraw; i++)
    {
        if(m_drawStack.isEmpty())
        {
            Helper::displayError(player->getClient(), "Could not draw card: drawstack is empty");
            break;
        }

        const int randomIndex = QRandomGenerator::global()->bounded(m_drawStack.size());
        UnoCardBase *card = m_drawStack[randomIndex];

        if (m_debug)
            qDebug() << player << "draws" << card << "at index" << randomIndex;

        m_drawStack.removeAt(randomIndex);
        player->getCards()->append(card);
    }

    m_countToDraw = 1;
}

Player *Gamefield::getPlayer(QWebSocket *client)
{
    for (Player *player : qAsConst(m_players))
    {
        if(player->getClient() == client)
        {
            return player;
        }
    }
    return nullptr;
}
