#include "player.h"

Player::Player(QWebSocket *client, int id, QString name, QObject *parent)
    : QObject{parent}, m_client(client), m_id(id), m_name(name)
{}

QWebSocket *Player::getClient() const
{
    return m_client;
}

int Player::getId()
{
    return m_id;
}

QString Player::getName()
{
    return m_name;
}

QList<UnoCardBase *> *Player::getCards()
{
    return &m_cards;
}
