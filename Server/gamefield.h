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
    explicit Gamefield(QList<QueueEntry *> queue, QObject *parent = nullptr);
private:
    void initDrawStack();
    void initPlayers(QList<QueueEntry *> clients);

    QList<UnoCardBase*> m_drawStack;
    UnoCardBase* m_lastPlayedCard;
    QList<Player *> m_players;
    bool m_isClockwise = true;

signals:
};

#endif // GAMEFIELD_H
