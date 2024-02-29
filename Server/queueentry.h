#ifndef QUEUEENTRY_H
#define QUEUEENTRY_H

#include "qwebsocket.h"
#include <QObject>

class QueueEntry : public QObject
{
    Q_OBJECT
public:
    explicit QueueEntry(QWebSocket *client, QString name, QObject *parent = nullptr);
    QWebSocket *getClient();
    QString getName() const;
    void setName(QString name);

private:
    QWebSocket *m_client;
    QString m_name;
};

#endif // QUEUEENTRY_H
