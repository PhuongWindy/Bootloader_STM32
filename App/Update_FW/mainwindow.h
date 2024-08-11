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
    uint8_t CRC[2];

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

    void loadPort();
    void setupPortUpdater();
    void setColorButtonUart(uint8_t Color);
    void uartSendData();
    void tcpSendDada();
    void udpSendData();
    uint16_t calculateCRC16(uint8_t *data);
};
#endif // MAINWINDOW_H
