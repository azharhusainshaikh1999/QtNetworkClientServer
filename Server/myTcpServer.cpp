#include "myTcpServer.h"

MYTcpServer::MYTcpServer(int port, QObject *parent) : QObject(parent)
{
    _server = new QTcpServer(this);

    connect(_server, &QTcpServer::newConnection, this, &MYTcpServer::on_client_connecting);

    _isServerStarted = _server->listen(QHostAddress::Any, port);
    if(!_isServerStarted)
    {
        qDebug()<<"Server Could Not Start";
    }
    else
    {
        qDebug()<<"Server Started";
    }

}

void MYTcpServer::on_client_connecting()
{
    qDebug()<<" A Client Connected to Client";
    auto socket = _server->nextPendingConnection();
    connect(socket, &QTcpSocket::disconnected, this, &MYTcpServer::on_client_disconnect);
    connect(socket,&QTcpSocket::readyRead, this, &MYTcpServer::on_client_data_ready);
    _socketsLists.append(socket);
    socket->write("Welcome to the Server");
    emit newClientConnected();
}

void MYTcpServer::on_client_disconnect()
{
    emit clientDisconnect();
}

void MYTcpServer::on_client_data_ready()
{
    auto socket = qobject_cast<QTcpSocket *>(sender());
    auto data = QString(socket->readAll());
    emit dataReceived(data);
}

bool MYTcpServer::isServerStarted() const
{
    return _isServerStarted;
}

void MYTcpServer::sendToAll(QString message)
{
    foreach(auto socket , _socketsLists){
        socket->write(message.toUtf8());
    }
}
