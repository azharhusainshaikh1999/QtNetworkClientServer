#ifndef DEVICECONTROLLER_H
#define DEVICECONTROLLER_H

#include <QObject>
#include <QTcpSocket>

class DeviceController : public QObject
{
    Q_OBJECT
public:
    explicit DeviceController(QObject *parent = nullptr);

    void connectToDevice(QString ip, int port);

    bool isConnected();

    void disconnect();

    void send(QString message);

signals:
    void connected();
    void disconnected();
    void stateChanged(QAbstractSocket::SocketState);
    void errorOccurred(QAbstractSocket::SocketError);
    void dataReadyRead(QByteArray data);

private slots:
    void socket_readyRead();
private:

    QTcpSocket _socket;
    QString _ip;
    int _port;
};

#endif // DEVICECONTROLLER_H
