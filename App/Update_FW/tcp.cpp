#include "tcp.h"
#include <QTimer>

tcp::tcp(QObject *parent)
{
    tcpServer = new QTcpServer;
    tcpSocket = nullptr;
    IsClientConnection = true;
    Checksocket();
}

bool tcp:: deviceConnect(QString ip, int port)
{
    bool result = false;
    if (tcpServer->isListening()) {
        tcpServer->close();
        return result;
    }
    IsClientConnection = true;
    QAbstractSocket::connect(tcpServer, &QTcpServer::newConnection, this, &tcp::handleNewConnection, Qt::UniqueConnection);

    if(!tcpServer->listen(QHostAddress::Any, port)) {
        qDebug() << "Sever could not start!";
        return result;
    } else {
        qDebug() << "Sever started!";
        result = true;
        return result;
    }
}

void tcp:: deviceDisconnect()
{
    if (tcpSocket) {
        tcpSocket->close();
        tcpSocket = nullptr;
    }
    if (tcpServer) {
        tcpServer->close();
    }
    qDebug() << "Server stopped!";
}

bool tcp::sendData(const QByteArray &data)
{
    bool result = false;
    qint64 dataWrite = tcpSocket->write(data);
    if (dataWrite == data.size()) {
        result = true;
    }
    return result;
}

bool tcp::receiveData(char* data, qint64 maxLen)
{
    bool result = false;
    qint64 dataWrite = tcpSocket->read(data, maxLen);
    if (dataWrite != -1) {
        result = true;
    }
    return result;
}

void tcp::handleNewConnection()
{
    if (tcpSocket) {
        qDebug() << "Already connected to a client. Rejecting new connection!";
        QTcpSocket *newClientSocket = tcpServer->nextPendingConnection();
        newClientSocket->disconnectFromHost();
        newClientSocket->deleteLater();
        return;
    }
    qDebug() << "Connected client!";
    tcpSocket = tcpServer->nextPendingConnection();
}
void tcp::Checksocket() {
    QTimer *timerCheck = new QTimer(this);
    connect(timerCheck, &QTimer::timeout, this, &tcp::checkSocketState);
    timerCheck->start(1000);  // Kiểm tra và cập nhật danh sách cổng mỗi giây
}
void tcp::checkSocketState() {
    if (tcpSocket && tcpSocket != nullptr && IsClientConnection == true) {
        IsClientConnection = handleUnConnection(tcpSocket->state());
    }
}

bool tcp::handleUnConnection(QAbstractSocket::SocketState state)
{
    if (state == QAbstractSocket::UnconnectedState) {
        if (tcpSocket) {
            tcpSocket->close();
            tcpSocket = nullptr;
        }
        if (tcpServer) {
            tcpServer->close();
        }
        qDebug() << "Client Disconnect!";
        return false;
    } else {
        return true;
    }
}
