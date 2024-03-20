#include "client.h"
#include "clientaction.h"
#include "qjsondocument.h"
#include "qjsonobject.h"
#include "serveraction.h"
#include <QDebug>

#define JOIN_QUEUE QString::number(static_cast<int>(ServerAction::JoinQueue))
#define START_GAME QString::number(static_cast<int>(ServerAction::StartGame))

Client::Client(const QUrl &url, bool debug, QObject *parent)
    : QObject{parent},
    m_url(url),
    m_debug(debug)
{
    if (m_debug)
        qDebug() << "WebSocket server:" << url;
    connect(&m_webSocket, &QWebSocket::connected, this, &Client::onConnected);
    connect(&m_webSocket, &QWebSocket::disconnected, this, &Client::closed);
    m_webSocket.open(QUrl(url));
}

void Client::onConnected()
{
    if (m_debug)
        qDebug() << "WebSocket connected";
    connect(&m_webSocket, &QWebSocket::textMessageReceived, this, &Client::onTextMessageReceived);
}

void Client::onTextMessageReceived(QString messageStr)
{
    if (m_debug)
        qDebug() << "Message received:" << messageStr;

    QJsonObject message = QJsonDocument::fromJson(messageStr.toUtf8()).object();

    ClientAction action;
    if(message.contains("action") && message["action"].isDouble())
        action = static_cast<ClientAction>(message["action"].toInt());
    else
        return throw "Either nor or invalid ClientAction";

    QJsonObject payload;
    if(message.contains("payload") && message["payload"].isObject())
        payload = message["payload"].toObject();

    switch (action) {
    case ClientAction::DisplayError:
        break;
    case ClientAction::StartGame:
        emit showGameView();
        break;
    case ClientAction::UpdateQueue:
        break;
    case ClientAction::UpdateGamefield:
        break;
    default:
        throw "Recieved invalid ClientAction";
        return;
    }
}

void Client::sendServerAction(ServerAction action, QJsonObject payload)
{
    QJsonObject message
    {
        {"action", static_cast<int>(action)},
        {"payload", payload},
    };
    m_webSocket.sendTextMessage(QJsonDocument(message).toJson(QJsonDocument::Compact));
}

void Client::startGame()
{
    sendServerAction(ServerAction::StartGame, QJsonObject{});
}

void Client::login(QString name)
{
    sendServerAction(ServerAction::JoinQueue, QJsonObject{{"name", name}});
}

