#include "queueentry.h"

QueueEntry::QueueEntry(QWebSocket *client, QString name, QObject *parent)
    : QObject{parent}, m_client(client), m_name(name)
{}

QWebSocket * QueueEntry::getClient()
{
    return m_client;
}

QString QueueEntry::getName() const
{
    return m_name;
}

void QueueEntry::setName(QString name)
{
    m_name = name;
}
