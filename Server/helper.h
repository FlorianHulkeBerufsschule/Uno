#ifndef HELPER_H
#define HELPER_H

#include "clientaction.h"
#include <QObject>
#include <QWebSocket>

class Helper : public QObject
{
    Q_OBJECT
public:
    explicit Helper(QObject *parent = nullptr);
    static void sendError(QWebSocket *client, QString message);
    static void sendClientAction(QWebSocket *client, ClientAction action, QJsonObject payload);
    static void sendClientAction(QList<QWebSocket *> clients, ClientAction action, QJsonObject payload);

signals:
};

#endif // HELPER_H
