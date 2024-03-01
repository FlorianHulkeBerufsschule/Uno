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
    void initGamefield();
    void updatePlayersGamefields();
    Player *getPlayer(QWebSocket *client);
    QString getPlayerGamefield(Player *player);

    QList<UnoCardBase*> m_drawStack;
    UnoCardBase* m_lastPlayedCard;
    QList<Player *> m_players;
    int m_currentPlayerId;
    int m_countToDraw;
    bool m_stackOrDraw;
    bool m_isClockwise;
    bool m_debug;

signals:
};

#endif // GAMEFIELD_H
