#include "player.h"

Player::Player(QWebSocket *client, QObject *parent)
    : QObject{parent}, m_client(client)
{}
