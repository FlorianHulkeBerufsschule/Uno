#include "mainwindow.h"
#include "client.h"
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

    w.generateClient(QUrl(QStringLiteral("ws://localhost:8888")), debug);

    return a.exec();
}
