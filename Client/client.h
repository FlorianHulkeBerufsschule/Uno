#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>

class Client : public QObject
{
    Q_OBJECT
public:
    explicit Client(QObject *parent = nullptr);
    ~Client();
public slots:
private:

signals:
};

#endif // CLIENT_H
