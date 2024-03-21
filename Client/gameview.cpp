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




    //LAST CARD PLAYED COLOR
    QGraphicsScene *scene = new QGraphicsScene(this);
    scene->setBackgroundBrush(QColor(255, 0, 0, 255));
    QGraphicsTextItem *textItem = scene->addText("+2");
    textItem->setDefaultTextColor(QColor(255, 255, 255));
    textItem->setPos(0, 0);
    textItem->setZValue(1);
    QFont font = textItem->font();
    font.setPointSize(30);
    textItem->setFont(font);
    ui->LastPlayed->setScene(scene);

    //DRAW CARD COLOR
    QGraphicsScene *s = new QGraphicsScene(this);
    s->setBackgroundBrush(QColor(0, 255, 0, 255));
    QGraphicsTextItem *t = s->addText("+2");
    t->setDefaultTextColor(QColor(255, 255, 255));
    t->setPos(0, 0);
    t->setZValue(1);
    font.setPointSize(30);
    t->setFont(font);
    ui->drawCards->setScene(s);
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

    updateLastPlayedCard();
    updateCards();
    updateEnemies();
}

void GameView::updateLastPlayedCard()
{
    //LAST CARD PLAYED COLOR
    QGraphicsScene *scene = new QGraphicsScene(this);
    scene->setBackgroundBrush(unoCardColor2QColor(m_lastPlayedCard->getColor()));
    QGraphicsTextItem *textItem = scene->addText("+2");
    textItem->setDefaultTextColor(QColor(255, 255, 255));
    textItem->setPos(0, 0);
    textItem->setZValue(1);
    QFont font = textItem->font();
    font.setPointSize(30);
    textItem->setFont(font);
    ui->LastPlayed->setScene(scene);
}

void GameView::updateCards()
{
    // TODO
}

void GameView::updateEnemies()
{
    // TODO
}

QColor GameView::unoCardColor2QColor(UnoCardColor color)
{
    switch(color)
    {
    case UnoCardColor::Red:
        return QColor(255,0,0);
    case UnoCardColor::Yellow:
        return QColor(255, 255, 0);
    case UnoCardColor::Green:
        return QColor(0, 255, 0);
    case UnoCardColor::Blue:
        return QColor(0, 0, 255);
    case UnoCardColor::Black:
        return QColor(0, 0, 0);
        break;
    default:
        throw "Invalid color";
    }
}
