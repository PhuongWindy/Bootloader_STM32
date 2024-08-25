#ifndef TCP_H
#define TCP_H

#include "ethernet.h"
class tcp : public Ethernet
{
public:
    explicit tcp(QObject *parent = nullptr);
    bool deviceConnect(QString ip, int port) override;
    void deviceDisconnect() override;
    bool sendData(const QByteArray &data) override;
    bool receiveData(char* data, qint64 maxLen) override;
    bool handleUnConnection(QAbstractSocket::SocketState state);
    bool IsClientConnection;
private slots:
    void handleNewConnection();
    void checkSocketState();
private:
    QTcpSocket *tcpSocket;
    QTcpServer *tcpServer;
    void Checksocket();
};

#endif // TCP_H
