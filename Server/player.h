#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QWebSocket>
#include "unocardbase.h"

class Player : public QObject
{
    Q_OBJECT
public:
    explicit Player(QWebSocket *client, int id, QString name, QObject *parent = nullptr);
    QWebSocket *getClient() const;
    int getId();
    QString getName();
    QList<UnoCardBase *> *getCards();

private:
    QWebSocket *m_client;
    int m_id;
    QString m_name;
    QList<UnoCardBase *> m_cards;
};

#endif // PLAYER_H
