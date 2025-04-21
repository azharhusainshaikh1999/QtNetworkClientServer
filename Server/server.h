#ifndef SERVER_H
#define SERVER_H

#include <QMainWindow>
#include "myTcpServer.h"
#include <QStyle>

QT_BEGIN_NAMESPACE
namespace Ui { class Server; }
QT_END_NAMESPACE

class Server : public QMainWindow
{
    Q_OBJECT

public:
    Server(QWidget *parent = nullptr);
    ~Server();

private slots:
    void on_btn_StartServer_clicked();
    void on_new_client_connected();
    void on_btn_Send_clicked();
    void clientDisconnected();
    void clientDataReceived(QString message);

private:
    Ui::Server *ui;
    MYTcpServer *_server;
};
#endif // SERVER_H
