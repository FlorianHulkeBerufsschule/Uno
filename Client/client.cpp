#include "client.h"
#include "qhostaddress.h"

Client::Client(QObject *parent)
    : QObject{parent}
{

    socket=new QTcpSocket;
    connect( socket, SIGNAL( connected() ), this, SLOT( startTransfer() ) );
    connect(socket, SIGNAL(readyRead()), this, SLOT(startRead()));
}

Client::~Client(){
    socket->close();
    socket->deleteLater();
}

void Client::start( QString address, quint16 port )
{
    QHostAddress addr( address );
    socket->connectToHost( addr, port );
}

void Client::startTransfer(){
    QString str("GET \r\n \r\n");
    QByteArray ba = str.toLocal8Bit();
    const char *c_str = ba.data();

    socket->write( c_str, str.length()+1 );
}


void Client::startRead(){

    char buffer[1024] = {0};
    QTcpSocket *sender = (QTcpSocket* ) QObject::sender();
    sender->read(buffer, sender->bytesAvailable());

    //Empfangenen String zum Debuggen ausgeben
    qDebug() << buffer;

    //Empfangenen String auswerten
    //ToDo
}
