#include "enemie.h"
#include "qjsonobject.h"

Enemie::Enemie(int cardCount, int id, QString name, QObject *parent)
    : QObject{parent}
    , m_cardCount(cardCount)
    , m_id(id)
    , m_name(name)
{}

Enemie *Enemie::fromJsonObj(QJsonObject json)
{
    int cardCount;
    int id;
    QString name;

    if(json.contains("cardCount") && json["cardCount"].isDouble())
        cardCount = json["cardCount"].toInt();
    else throw "Enemie's JSON doesn't contain 'cardCount'";

    if(json.contains("id") && json["id"].isDouble())
        id = json["cardCount"].toInt();
    else throw "Enemie's JSON doesn't contain 'id'";

    if(json.contains("name") && json["name"].isString())
        name = json["name"].toString();
    else throw "Enemie's JSON doesn't contain 'name'";

    return new Enemie(cardCount, id, name);
}

int Enemie::getCardCount()
{
    return m_cardCount;
}

int Enemie::getId()
{
    return m_id;
}

QString Enemie::getName()
{
    return m_name;
}
