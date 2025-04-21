#include "client.h"
#include "ui_client.h"
#include <QDebug>
#include <QMetaEnum>

Client::Client(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Client)
{
    ui->setupUi(this);
    setDeviceController();
}

Client::~Client()
{
    delete ui;
}


void Client::on_ln_IP_Adress_textChanged(const QString &arg1)
{
    QString state = "0";

    if(arg1 == "...")
    {
        state = "";
    }
    else
    {
        QHostAddress address(arg1);
        if(QAbstractSocket::IPv4Protocol == address.protocol())
        {
            state = "1";
        }
        ui->ln_IP_Adress->setProperty("state", state);
        style()->polish(ui->ln_IP_Adress);
    }
}


void Client::on_btn_Connect_clicked()
{
    if(_controller.isConnected())
    {
        _controller.disconnect();
    }
    else
    {
        auto ip = ui->ln_IP_Adress->text();
        auto port = ui->spb_Port->value();

        _controller.connectToDevice(ip, port);
    }

}

void Client::device_connected()
{
    ui->lst_Console->addItem("Connected to Server");
    ui->btn_Connect->setText("Disconnect");
    ui->grp_SendDataBox->setEnabled(true);
}

void Client::device_disconnected()
{
    ui->lst_Console->addItem("Disconnected From Server");
    ui->btn_Connect->setText("Connect");
    ui->grp_SendDataBox->setEnabled(false);
}

void Client::device_stateChanged(QAbstractSocket::SocketState state)
{
    QMetaEnum metaEnum = QMetaEnum::fromType<QAbstractSocket::SocketState>();
    ui->lst_Console->addItem(metaEnum.valueToKey(state));
}

void Client::device_errorOccurred(QAbstractSocket::SocketError error)
{
    QMetaEnum metaEnum = QMetaEnum::fromType<QAbstractSocket::SocketError>();
    ui->lst_Console->addItem(metaEnum.valueToKey(error));
}

void Client::device_dataReadyRead(QByteArray data)
{
    ui->lst_Console->addItem(data);
}

void Client::setDeviceController()
{
    connect(&_controller, &DeviceController::connected, this, &Client::device_connected);
    connect(&_controller, &DeviceController::disconnected, this, &Client::device_disconnected);
    connect(&_controller, &DeviceController::errorOccurred, this, &Client::device_errorOccurred);
    connect(&_controller, &DeviceController::stateChanged, this, &Client::device_stateChanged);
    connect(&_controller, &DeviceController::dataReadyRead, this, &Client::device_dataReadyRead);
}


void Client::on_btn_Clear_clicked()
{
    ui->lst_Console->clear();
}


void Client::on_pushButton_clicked()
{
    QString message = ui->ln_Message->text().trimmed();
    _controller.send(message);
}

