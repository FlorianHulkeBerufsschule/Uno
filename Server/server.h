#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>


#define MAXCLIENT 2

class Server : public QObject
{
    Q_OBJECT
public:
    explicit Server(QObject *parent = nullptr);
    ~Server();

public slots:
    void acceptConnection();
    void startRead();

private:
    QTcpServer *server;
    QTcpSocket *socket;

signals:

};

#endif // SERVER_H
