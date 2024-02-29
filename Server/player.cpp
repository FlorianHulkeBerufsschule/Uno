#include "player.h"

Player::Player(QWebSocket *client, QObject *parent)
    : QObject{parent}, m_client(client)
{}

QWebSocket *Player::getClient() const
{
    return m_client;
}

QList<UnoCardBase *> *Player::getCards()
{
    return &m_cards;
}
