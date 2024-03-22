#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include <QWidget>
#include "client.h"
#include "enemie.h"
#include "unocardbase.h"
#include <QGraphicsItem>
#include <unocard.h>
#include <unospecialcard.h>

namespace Ui {
class GameView;
}

class GameView : public QWidget
{
    Q_OBJECT

public:
    explicit GameView(Client *client, QWidget *parent = nullptr);
    ~GameView();

private:
    void updateView(QJsonObject &payload);
    void updateLastPlayedCard();
    void updateCards();
    void updateEnemies();
    QColor unoCardColor2QColor(UnoCardColor color);
    QString getCardText(UnoCardBase *card);
    QList<UnoCardBase *> m_cards;
    QList<Enemie *> m_enemies;
    int m_currentPlayerId;
    bool m_isClockwise;
    UnoCardBase *m_lastPlayedCard;
    int m_playerId;
    bool m_stackOrDraw;

    Ui::GameView *ui;
    Client *m_client;
};

#endif // GAMEVIEW_H
