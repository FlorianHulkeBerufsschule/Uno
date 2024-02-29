#ifndef SERVER_H
#define SERVER_H

#include "gamefield.h"
#include "queueentry.h"
#include <QObject>
#include <QList>

QT_FORWARD_DECLARE_CLASS(QWebSocketServer)
QT_FORWARD_DECLARE_CLASS(QWebSocket)

class Server : public QObject
{
    Q_OBJECT
public:
    explicit Server(quint16 port, bool debug = false, QObject *parent = nullptr);
    ~Server();

Q_SIGNALS:
    void closed();

private Q_SLOTS:
    void onNewConnection();
    void processTextMessage(QString message);
    void socketDisconnected();

private:
    // ServerActions
    void joinQueue(QWebSocket *client, QJsonObject name);
    void startGame();

    // ClientActions
    void updateQueue();

    QWebSocketServer *m_pWebSocketServer;
    QList<QWebSocket *> m_clients;
    QList<QueueEntry *> m_queue;
    Gamefield *m_gamefield;
    bool m_debug;

};

#endif // SERVER_H
