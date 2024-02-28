#include "server.h"
#include "QtWebSockets/qwebsocketserver.h"
#include "QtWebSockets/qwebsocket.h"
#include "serveraction.h"
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>

Server::Server(quint16 port, bool debug, QObject *parent)
    : QObject{parent},
    m_pWebSocketServer(new QWebSocketServer(QStringLiteral("Echo Server"), QWebSocketServer::NonSecureMode, this)),
    m_debug(debug)
{
    if (m_pWebSocketServer->listen(QHostAddress::Any, port)) {
        if (m_debug)
            qDebug() << "Echoserver listening on port" << port;
        connect(m_pWebSocketServer, &QWebSocketServer::newConnection,
                this, &Server::onNewConnection);
        connect(m_pWebSocketServer, &QWebSocketServer::closed, this, &Server::closed);
    }
}

Server::~Server()
{
    m_pWebSocketServer->close();
    qDeleteAll(m_clients.begin(), m_clients.end());
}

void Server::onNewConnection()
{
    QWebSocket *pSocket = m_pWebSocketServer->nextPendingConnection();

    connect(pSocket, &QWebSocket::textMessageReceived, this, &Server::processTextMessage);
    connect(pSocket, &QWebSocket::disconnected, this, &Server::socketDisconnected);

    m_clients << pSocket;
}

void Server::processTextMessage(QString message)
{
    const QStringList params = message.split(';');
    const ServerAction action = static_cast<ServerAction>(params[0].toInt());
    const QString payloadStr = params.length() == 2 ? params[1] : "";
    const QJsonObject payload = QJsonDocument::fromJson(payloadStr.toUtf8()).object();

    switch (action) {
    case ServerAction::StartGame:
        startGame();
        break;
    }

    // const UnoCard *card = new UnoCard(1, "black", 7);
    // const QString jsonStr = card->toJsonStr();
    // const UnoCard *parsed = UnoCard::fromJsonStr(jsonStr);
    // qDebug() << "Parsed card:" << parsed->toJsonStr();

    // QWebSocket *pClient = qobject_cast<QWebSocket *>(sender());
    // if (m_debug)
    //     qDebug() << "Message received:" << message;
    //     qDebug() << "Sending JSON:" << jsonStr;
    // if (pClient) {
    //     pClient->sendTextMessage(jsonStr);
    // }
}

void Server::socketDisconnected()
{
    QWebSocket *pClient = qobject_cast<QWebSocket *>(sender());
    if (m_debug)
        qDebug() << "socketDisconnected:" << pClient;
    if (pClient) {
        m_clients.removeAll(pClient);
        pClient->deleteLater();
    }
}

void Server::startGame()
{
    this->m_gamefield = new Gamefield(m_clients);
}
