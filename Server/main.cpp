#include <QCoreApplication>
#include "server.h"
#include "gamefield.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Server server;
    Gamefield gamefield;

    return a.exec();
}
