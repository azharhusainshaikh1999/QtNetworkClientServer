#include "server.h"
#include "ui_server.h"

Server::Server(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Server)
{
    ui->setupUi(this);
    _server = nullptr;
}

Server::~Server()
{
    delete ui;
}


void Server::on_btn_StartServer_clicked()
{
    if(_server == nullptr)
    {
        auto port = ui->spb_Port->value();
        _server = new MYTcpServer(port);
        connect(_server, &MYTcpServer::newClientConnected, this, &Server::on_new_client_connected );
        connect(_server, &MYTcpServer::dataReceived, this, &Server::clientDataReceived);
        connect(_server, &MYTcpServer::clientDisconnect, this, &Server::clientDisconnected);
    }
    auto state = (_server->isServerStarted())?"1":"0";
    ui->lbl_ConnectionStatus->setProperty("state",state);
    style()->polish(ui->lbl_ConnectionStatus);
}

void Server::on_new_client_connected()
{
    ui->lst_Console->addItem("New Client Connected");
}


void Server::on_btn_Send_clicked()
{
    QString message = ui->ln_Message->text().trimmed();
    _server->sendToAll(message);
}

void Server::clientDisconnected()
{
    ui->lst_Console->addItem("Client Disconnected");
}

void Server::clientDataReceived(QString message)
{
    ui->lst_Console->addItem(message);
}

