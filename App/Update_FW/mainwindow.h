#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QTextEdit>
#include <QDebug>
#include <QString>
#include <QMessageBox>
#include <QByteArray>
#include <QPlainTextEdit>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QIODevice>
#include <QTimer>
#include <QPalette>

#include <QTcpSocket>
#include "crc16.h"
#include "tcp.h"
#include "udp.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    enum color {
        red,
        green
    };

    enum Protocol {
        UART,
        TCP,
        UDP
    };
    QByteArray fileData;
    uint16_t CRC;

private slots:

    void BttFile_clicked();

    void BttUart_clicked();

    void BttTcp_clicked();

    void BttUdp_clicked();

    void BttFlash_clicked();


private:
    Ui::MainWindow *ui;
    QPlainTextEdit *pTdirection;
    QSerialPort  *comPort;
    tcp *Tcpserver;
    udp *Udpserver;

    void loadPort();
    void setupPortUpdater();
    void setColorButton(uint8_t button, uint8_t Color);
    void uartSendData();
    void tcpSendDada();
    void udpSendData();

};
#endif // MAINWINDOW_H
