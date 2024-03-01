#ifndef HELPER_H
#define HELPER_H

#include <QObject>
#include <QWebSocket>

class Helper : public QObject
{
    Q_OBJECT
public:
    explicit Helper(QObject *parent = nullptr);
    static void displayError(QWebSocket *client, QString message);

signals:
};

#endif // HELPER_H
