#include "mainwindow.h"
#include "client.h"
#include "startwindow.h"

#include <QApplication>
#include <QtCore/QCommandLineParser>
#include <QtCore/QCommandLineOption>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.showMaximized();

    QCommandLineParser parser;
    parser.setApplicationDescription("QtWebSockets example: echoclient");
    parser.addHelpOption();

    QCommandLineOption dbgOption(QStringList() << "d" << "debug",
                                 QCoreApplication::translate("main", "Debug output [default: off]."));
    parser.addOption(dbgOption);
    parser.process(a);
    bool debug = parser.isSet(dbgOption);

    Client client(QUrl(QStringLiteral("ws://localhost:8888")), debug);
    QObject::connect(&client, &Client::closed, &a, &QCoreApplication::quit);

    w.setClient(&client);

    return a.exec();
}
