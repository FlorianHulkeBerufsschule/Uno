#include "gamefield.h"
#include "player.h"
#include "unocard.h"
#include "unospecialcard.h"
#include <QMetaEnum>

Gamefield::Gamefield(QList<QWebSocket *> clients, QObject *parent)
    : QObject{parent}
{
    initDrawStack();
    initPlayers(clients);
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
            m_drawStack.append(new UnoCard(id++, "red", i));
            m_drawStack.append(new UnoCard(id++, "yellow", i));
            m_drawStack.append(new UnoCard(id++, "green", i));
            m_drawStack.append(new UnoCard(id++, "blue", i));
        }
    }

    // Initialisiere die Spezialkarten (5 unterschiedliche Typen)
    for (int i = 0; i <= 4; i++)
    {
        if (i == UnoSpecialCard::DrawTwo || i == UnoSpecialCard::Reverse || i == UnoSpecialCard::Skip)
        {
            for (int j = 0; j <= 1; j++)
            {
                m_drawStack.append(new UnoSpecialCard(id++, "red", static_cast<UnoSpecialCard::Type>(i)));
                m_drawStack.append(new UnoSpecialCard(id++, "yellow", static_cast<UnoSpecialCard::Type>(i)));
                m_drawStack.append(new UnoSpecialCard(id++, "green", static_cast<UnoSpecialCard::Type>(i)));
                m_drawStack.append(new UnoSpecialCard(id++, "blue", static_cast<UnoSpecialCard::Type>(i)));
            }
        }
        else
        {
            // Von DrawFor und Wildcard brauchen wir jeweils 4
            for (int j = 0; j <= 3; j++)
            {
                m_drawStack.append(new UnoSpecialCard(id++, "balck", static_cast<UnoSpecialCard::Type>(i)));
            }
        }
    }

    qDebug() << "Initialized" << m_drawStack.length() << "game cards";
}

void Gamefield::initPlayers(QList<QWebSocket *> clients)
{
    for (QWebSocket *client : clients)
    {
        m_players.append(new Player(client));
    }

    qDebug() << "Starting game with" << m_players.length() << "players";
}
