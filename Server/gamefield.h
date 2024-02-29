#ifndef GAMEFIELD_H
#define GAMEFIELD_H

#include <QObject>
#include <QList>
#include "queueentry.h"
#include "unocardbase.h"
#include "player.h"

class Gamefield : public QObject
{
    Q_OBJECT
public:
    explicit Gamefield(QList<QueueEntry *> queue, bool debug = false, QObject *parent = nullptr);
    void drawRandomCard(QWebSocket *client);
    void drawRandomCard(QWebSocket *client, int countToDraw);
private:
    void initDrawStack();
    void initPlayers(QList<QueueEntry *> clients);
    void initPlayerCards();
    Player *getPlayer(QWebSocket *client);

    QList<UnoCardBase*> m_drawStack;
    UnoCardBase* m_lastPlayedCard;
    QList<Player *> m_players;
    bool m_isClockwise = true;
    bool m_debug;
    int m_countToDraw;

signals:
};

#endif // GAMEFIELD_H
