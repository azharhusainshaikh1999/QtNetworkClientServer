#include "deviceController.h"

DeviceController::DeviceController(QObject *parent) : QObject(parent)
{
    connect(&_socket, &QTcpSocket::connected, this, &DeviceController::connected);
    connect(&_socket, &QTcpSocket::disconnected, this, &DeviceController::disconnected);
    connect(&_socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(errorOccurred(QAbstractSocket::SocketError)));
    connect(&_socket, &QTcpSocket::stateChanged, this, &DeviceController::stateChanged);
    connect(&_socket, &QTcpSocket::readyRead, this, &DeviceController::socket_readyRead);
}

void DeviceController::connectToDevice(QString ip, int port)
{
    if(_socket.isOpen())
    {
        if(ip == _ip && port == _port)
        {
            return;
        }
        _socket.close();
    }

    _ip = ip;
    _port = port;
    qDebug()<<"IP : "<<_ip<<"\nport : "<<_port;
    _socket.connectToHost(ip, port);
}

bool DeviceController::isConnected()
{
    return _socket.state() == QAbstractSocket::ConnectedState;
}

void DeviceController::disconnect()
{
    _socket.close();
}

void DeviceController::send(QString message)
{
    _socket.write(message.toUtf8());
}

void DeviceController::socket_readyRead()
{
    auto data = _socket.readAll();
    emit dataReadyRead(data);
}
