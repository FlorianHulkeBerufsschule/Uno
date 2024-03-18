#include "gamefield.h"
#include "clientaction.h"
#include "helper.h"
#include "player.h"
#include "unocard.h"
#include "unospecialcard.h"
#include <QMetaEnum>
#include <QRandomGenerator>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>

#define UPDATE_GAMEFIELD QString::number(static_cast<int>(ClientAction::UpdateGamefield))

Gamefield::Gamefield(QList<QueueEntry *> queue, bool debug, QObject *parent)
    : QObject{parent}, m_debug(debug)
{
    initDrawStack();
    initPlayers(queue);
    initPlayerCards();
    initGamefield();
    updatePlayersGamefields();
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
    int id = 1;
    for (QueueEntry *entry : queue)
    {
        m_players.append(new Player(entry->getClient(), id++, entry->getName()));
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

void Gamefield::initGamefield(){
    // Lege eine zufällig Karte in die Mitte
    const int randomCardIndex = QRandomGenerator::global()->bounded(m_drawStack.size());
    UnoCardBase *card = m_drawStack[randomCardIndex];
    m_drawStack.removeAt(randomCardIndex);
    m_lastPlayedCard = card;

    m_stackOrDraw = false;
    m_isClockwise = true;

    const int randomPlayerIndex = QRandomGenerator::global()->bounded(m_players.size());
    m_currentPlayerId = m_players.at(randomPlayerIndex)->getId();
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

void Gamefield::updatePlayersGamefields()
{
    for (Player *player : qAsConst(m_players))
    {
        player->getClient()->sendTextMessage(UPDATE_GAMEFIELD + ";" + getPlayerGamefield(player));
    }
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

QString Gamefield::getPlayerGamefield(Player *player)
{
    QJsonObject playerGamefield;
    QJsonArray enemies;
    QJsonArray cards;

    for (Player *enemie : qAsConst(m_players))
    {
        if(enemie != player)
            enemies.append(QJsonObject{{"id", enemie->getId()}, {"name", enemie->getName()}, {"cardCount", enemie->getCards()->size()}});
    }

    for (UnoCardBase *card : qAsConst(*player->getCards()))
    {
        cards.append(card->toJsonObj());
    }

    playerGamefield.insert("enemies", enemies);
    playerGamefield.insert("cards", cards);
    playerGamefield.insert("lastPlayedCard", m_lastPlayedCard->toJsonObj());
    playerGamefield.insert("currentPlayerId", m_currentPlayerId);
    playerGamefield.insert("playerId", player->getId());
    playerGamefield.insert("isClockwise", m_isClockwise);
    playerGamefield.insert("stackOrDraw", m_stackOrDraw);

    return QJsonDocument(playerGamefield).toJson(QJsonDocument::Compact);
}

bool Gamefield::isGameActive()
{
    int activePlayers = 0;
    for (Player *player :qAsConst(m_players))
    {
        if(player->getCards()->length() > 0 && ++activePlayers > 1)
        {
            return true;
        }
    }
    return false;
}
