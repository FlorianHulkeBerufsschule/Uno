#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QTcpSocket>

class Client : public QObject
{
    Q_OBJECT
public:
    explicit Client(QObject *parent = nullptr);
    ~Client();
    void start( QString address, quint16 port );
public slots:
    void startTransfer();
    void startRead();
private:
    QTcpSocket *socket;

signals:
};

#endif // CLIENT_H
