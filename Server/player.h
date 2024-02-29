#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QWebSocket>
#include "unocardbase.h"

class Player : public QObject
{
    Q_OBJECT
public:
    explicit Player(QWebSocket *client, QObject *parent = nullptr);
    QWebSocket *getClient() const;
    QList<UnoCardBase *> *getCards();

private:
    QWebSocket *m_client;
    QList<UnoCardBase *> m_cards;
};

#endif // PLAYER_H
