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

    //DRAW CARD COLOR
    QGraphicsScene *s = new QGraphicsScene(this);
    s->setBackgroundBrush(QColor(0, 0, 0, 255));
    QGraphicsTextItem *t = s->addText("UNO");
    t->setDefaultTextColor(QColor(255, 255, 255));
    t->setPos(0, 0);
    t->setZValue(1);
    QFont font = t->font();
    font.setPointSize(20);
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
    QGraphicsTextItem *textItem = scene->addText(getCardText(m_lastPlayedCard));
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
    ui->labelGegner1->setText("");
    ui->labelGegner2->setText("");
    ui->labelGegner3->setText("");
    int currentEnemyIndex = m_playerId - 1;
    for (int itteration = 1; itteration <= 3; itteration++)
    {
        if(currentEnemyIndex >= 3)
        {
            currentEnemyIndex = 0;
        }
        QGraphicsScene *scene = new QGraphicsScene(this);
        QGraphicsTextItem *textItem = nullptr;
        if(itteration <= m_enemies.count())
        {
            scene->setBackgroundBrush(QColor(0, 0, 0));
            textItem = scene->addText("UNO");
            textItem->setDefaultTextColor(QColor(255, 255, 255));
        }
        else
        {
            scene->setBackgroundBrush(QColor(255, 255, 255));
            textItem = scene->addText("");
            textItem->setDefaultTextColor(QColor(0, 0, 0));
        }
        textItem->setPos(0, 0);
        textItem->setZValue(1);
        QFont font = textItem->font();
        font.setPointSize(20);
        textItem->setFont(font);

        switch(itteration)
        {
        case 1:
            ui->Gegner1->setScene(scene);
            ui->labelGegner1->setText(m_enemies.at(currentEnemyIndex)->getName() + ": " + QString::number(m_enemies.at(currentEnemyIndex)->getCardCount()));
            break;
        case 2:
            ui->Gegner2->setScene(scene);
            if(itteration <= m_enemies.count())
                ui->labelGegner2->setText(m_enemies.at(currentEnemyIndex)->getName() + ": " + QString::number(m_enemies.at(currentEnemyIndex)->getCardCount()));
            break;
        case 3:
            ui->Gegner3->setScene(scene);
            if(itteration <= m_enemies.count())
                ui->labelGegner3->setText(m_enemies.at(currentEnemyIndex)->getName() + ": " + QString::number(m_enemies.at(currentEnemyIndex)->getCardCount()));
            break;
        }
        currentEnemyIndex++;
    }
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

QString GameView::getCardText(UnoCardBase *card)
{
    if(UnoCard *unoCard = dynamic_cast<UnoCard*>(card))
    {
        return QString::number( unoCard->getValue());
    }

    if(UnoSpecialCard *specialCard = dynamic_cast<UnoSpecialCard*>(card))
    {
        auto type = specialCard->getType();
        switch (type)
        {
        case UnoSpecialCard::DrawFour:
            return "+4";
        case UnoSpecialCard::DrawTwo:
            return "+2";
        case UnoSpecialCard::Skip:
            return "⌀";
        case UnoSpecialCard::Reverse:
            return "↻";
        case UnoSpecialCard::Wildcard:
            return "⁛";
        default:
            return nullptr;
        }
    }
    return nullptr;
}
