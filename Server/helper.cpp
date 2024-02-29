#include "helper.h"
#include "clientaction.h"
#include <QJsonObject>
#include <QJsonDocument>

#define DISPLAY_ERROR QString::number(static_cast<int>(ClientAction::DisplayError))

Helper::Helper(QObject *parent)
    : QObject{parent}
{}

void Helper::displayError(QWebSocket *client, QString message)
{
    const QString error = QJsonDocument(QJsonObject{{"message", message}}).toJson(QJsonDocument::Compact);
    client->sendTextMessage(DISPLAY_ERROR + ";" + error);
}
