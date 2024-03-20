#include "gameview.h"
#include "qjsonarray.h"
#include "qjsondocument.h"
#include "qjsonobject.h"
#include "ui_gameview.h"

GameView::GameView(Client *client, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::GameView)
    , m_client(client)
{
    ui->setupUi(this);
    connect(m_client, &Client::updateGameView, this, &GameView::updateView);
}

GameView::~GameView()
{
    delete ui;
}

void GameView::updateView(QJsonObject &payload)
{
    if(payload.contains("cards") && payload["cards"].isArray())
    {
        QJsonArray cards = payload["cards"].toArray();
        for (int i = 0; i < cards.count(); i++)
            m_cards.append(UnoCardBase::fromJsonObj(cards.at(i).toObject()));
    }
    else throw "Updated GameView doesn't contain 'cards'";

    if(payload.contains("enemies") && payload["enemies"].isArray())
    {
        QJsonArray enemies = payload["enemies"].toArray();
        for(int i = 0; i < enemies.count(); i++)
            m_enemies.append(Enemie::fromJsonObj(enemies.at(i).toObject()));
    }
    else throw "Updated GameView doesn't contain 'enemies'";

    if(payload.contains("currentPlayerId") && payload["currentPlayerId"].isDouble())
        m_currentPlayerId = payload["currentPlayerId"].toInt();
    else throw "Updated GameView doesn't contain 'currentPlayerId'";

    if(payload.contains("isClockwise") && payload["isClockwise"].isBool())
        m_isClockwise = payload["isClockwise"].toBool();
    else throw "Updated GameView doesn't contain 'isClockwise'";

    if(payload.contains("lastPlayedCard") && payload["lastPlayedCard"].isObject())
        m_lastPlayedCard = UnoCardBase::fromJsonObj(payload["lastPlayedCard"].toObject());
    else throw "Updated GameView doesn't contain 'lastPlayedCard'";

    if(payload.contains("playerId") && payload["playerId"].isDouble())
        m_playerId = payload["playerId"].toInt();
    else throw "Updated GameView doesn't contain 'playerId'";

    if(payload.contains("stackOrDraw") && payload["stackOrDraw"].isBool())
        m_stackOrDraw = payload["stackOrDraw"].toBool();
    else throw "Updated GameView doesn't contain 'stackOrDraw'";
}
