#ifndef MYTCPSERVER_H
#define MYTCPSERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>


class MYTcpServer : public QObject
{
    Q_OBJECT
public:
    explicit MYTcpServer(int port, QObject *parent = nullptr);
    bool isServerStarted() const;

    void sendToAll(QString message);

signals:
    void newClientConnected();
    void clientDisconnect();
    void dataReceived(QString data);

private slots:

    void on_client_connecting();
    void on_client_disconnect();
    void on_client_data_ready();

private:
    QTcpServer *_server;
    QList<QTcpSocket *> _socketsLists;
    bool _isServerStarted;

};

#endif // MYTCPSERVER_H
