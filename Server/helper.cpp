#include "helper.h"
#include "clientaction.h"
#include <QJsonObject>
#include <QJsonDocument>

#define DISPLAY_ERROR QString::number(static_cast<int>(ClientAction::DisplayError))

Helper::Helper(QObject *parent)
    : QObject{parent}
{}

void Helper::sendError(QWebSocket *client, QString message)
{
    sendClientAction(client, ClientAction::DisplayError, QJsonObject{{"message", message}});
}

void Helper::sendClientAction(QWebSocket *client, ClientAction action, QJsonObject payload)
{
    QJsonObject message{
        {"action", static_cast<int>(action)},
        {"payload", payload}
    };

    client->sendTextMessage(QJsonDocument(message).toJson(QJsonDocument::Compact));
}

void Helper::sendClientAction(QList<QWebSocket *> clients, ClientAction action, QJsonObject payload)
{
    QJsonObject message{
        {"action", static_cast<int>(action)},
        {"payload", payload}
    };

    for (QWebSocket * client : clients)
    {
        client->sendTextMessage(QJsonDocument(message).toJson(QJsonDocument::Compact));
    }
}
