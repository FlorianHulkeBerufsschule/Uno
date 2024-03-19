#ifndef CLIENT_H
#define CLIENT_H

#include "serveraction.h"
#include <QObject>
#include <QtWebSockets/QWebSocket>

class Client : public QObject
{
    Q_OBJECT
public:
    explicit Client(const QUrl &url, bool debug = false, QObject *parent = nullptr);
    void startGame();
    void login(QString name);
    void switchWindow(bool a);

Q_SIGNALS:
    void closed();

private Q_SLOTS:
    void onConnected();
    void onTextMessageReceived(QString message);

private:
    void sendServerAction(ServerAction action, QJsonObject payload);
    QWebSocket m_webSocket;
    QUrl m_url;
    bool m_debug;
};

#endif // CLIENT_H
