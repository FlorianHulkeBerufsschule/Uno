#include "client.h"
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

void Client::StartGame()
{
    m_webSocket.sendTextMessage(START_GAME);

}

void Client::Login(const QString name)
{

    // Todo: The following must be executed by the frontend, not on init
    const QString name = "Name";
    //const QString name = "Name";
    const QString payload = QJsonDocument(QJsonObject{{"name", name}}).toJson(QJsonDocument::Compact);

    m_webSocket.sendTextMessage(JOIN_QUEUE + ";" + payload);
    m_webSocket.sendTextMessage(START_GAME);
}

void Client::onTextMessageReceived(QString message)
{
    if (m_debug)
        qDebug() << "Message received:" << message;
    // m_webSocket.close();
}
