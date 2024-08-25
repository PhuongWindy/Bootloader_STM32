#ifndef ETHERNET_H
#define ETHERNET_H

#include <QObject>
#include <QTcpSocket>
#include <QTcpServer>

class Ethernet : public QObject
{
    Q_OBJECT
public:
    explicit Ethernet(QObject *parent = nullptr);

signals:

public:
    virtual bool deviceConnect(QString ip, int port) = 0;
    virtual void deviceDisconnect() = 0;
    virtual bool sendData(const QByteArray &data) = 0;
    virtual bool receiveData(char* data, qint64 maxLen) = 0;
};

#endif // ETHERNET_H
