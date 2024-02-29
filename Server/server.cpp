#include "server.h"
#include "QtWebSockets/qwebsocketserver.h"
#include "QtWebSockets/qwebsocket.h"
#include "clientaction.h"
#include "serveraction.h"
#include "helper.h"
#include <QDebug>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

#define DISPLAY_ERROR QString::number(static_cast<int>(ClientAction::DisplayError))
#define UPDATE_QUEUE QString::number(static_cast<int>(ClientAction::UpdateQueue))
#define PLAY_CARD QString::number(static_cast<int>(ClientAction::PlayCard))
#define DRAW_CARD QString::number(static_cast<int>(ClientAction::DrawCard))

Server::Server(quint16 port, bool debug, QObject *parent)
    : QObject{parent},
    m_pWebSocketServer(new QWebSocketServer(QStringLiteral("Uno Server"), QWebSocketServer::NonSecureMode, this)),
    m_debug(debug)
{
    if (m_pWebSocketServer->listen(QHostAddress::Any, port)) {
        if (m_debug)
            qDebug() << "Unoserver listening on port" << port;
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
    if (m_debug)
        qDebug() << "Message received:" << message;

    QWebSocket *client = qobject_cast<QWebSocket *>(sender());
    const QStringList params = message.split(';');
    const ServerAction action = static_cast<ServerAction>(params[0].toInt());

    // Payload initialisieren
    QJsonObject payload;
    if (params.size() >= 2) {
        payload = QJsonDocument::fromJson(params[1].toUtf8()).object();
    }

    switch (action) {
    case ServerAction::JoinQueue:
        joinQueue(client, payload);
        break;
    case ServerAction::StartGame:
        startGame(client);
        break;
    case ServerAction::PlayCard:
        break;
    case ServerAction::DrawCard:
        m_gamefield->drawRandomCard(client);
        break;
    default:
        Helper::displayError(client, "Parsed invalid ServerAction: " + QString::number(static_cast<int>(action)));
        return;
    }
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

void Server::joinQueue(QWebSocket *client, QJsonObject payload)
{
    QString name;
    if (payload.contains("name") && payload["name"].isString())
        name = payload["name"].toString();
    else throw "Player joining queue has no name provided";

    bool alreadyInQueue = false;
    for (QueueEntry *entry : qAsConst(m_queue))
    {
        if(entry->getClient() == client)
        {
            //Found dublicate
            entry->setName(name);
            alreadyInQueue = true;
            break;
        }
    }

    if (!alreadyInQueue)
    {
        if(m_queue.length() < 4)
        {
            m_queue.append(new QueueEntry(client, name));
        }
        else
        {
            Helper::displayError(client, "Queue is already full");
        }
    }

    updateQueue();
}

void Server::startGame(QWebSocket *client)
{
    if(m_queue.size() < 2)
        return Helper::displayError(client, "Not enough players!");

    this->m_gamefield = new Gamefield(m_queue, m_debug);
    m_queue.clear();
}

void Server::updateQueue()
{
    QJsonArray queueArr;
    for (const QueueEntry *entry : qAsConst(m_queue))
    {
        queueArr.append(entry->getName());
    }
    const QString queue = QJsonDocument(queueArr).toJson((QJsonDocument::Compact));

    for(QWebSocket *client : qAsConst(m_clients))
    {
        client->sendTextMessage(UPDATE_QUEUE + ";" + queue);
    }
}
