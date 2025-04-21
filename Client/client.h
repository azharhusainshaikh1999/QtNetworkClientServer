#ifndef CLIENT_H
#define CLIENT_H

#include <QMainWindow>
#include <QHostAddress>
#include <QStyle>
#include "deviceController.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Client; }
QT_END_NAMESPACE

class Client : public QMainWindow
{
    Q_OBJECT

public:
    Client(QWidget *parent = nullptr);
    ~Client();

private slots:
    void on_ln_IP_Adress_textChanged(const QString &arg1);

    void on_btn_Connect_clicked();

    void device_connected();
    void device_disconnected();
    void device_stateChanged(QAbstractSocket::SocketState);
    void device_errorOccurred(QAbstractSocket::SocketError);
    void device_dataReadyRead(QByteArray data);

    void on_btn_Clear_clicked();

    void on_pushButton_clicked();

private:
    Ui::Client *ui;
    DeviceController _controller;

    void setDeviceController();
};
#endif // CLIENT_H
