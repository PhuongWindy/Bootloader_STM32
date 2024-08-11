#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)

{
    ui->setupUi(this);
    comPort = nullptr;
    pTdirection = new QPlainTextEdit(this);
    loadPort();
    setupPortUpdater();
    setColorButtonUart(red);
    connect(ui->BttFile, &QPushButton::clicked, this, &MainWindow::BttFile_clicked);
    connect(ui->BttUart, &QPushButton::clicked, this, &MainWindow::BttUart_clicked);
    connect(ui->BttFlash, &QPushButton::clicked, this, &MainWindow::BttFlash_clicked);
}

MainWindow::~MainWindow()
{
    delete ui;
    if (comPort != nullptr) {
        comPort->close();
        delete comPort;
        setColorButtonUart(red);
    }
}

void MainWindow::BttFile_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open File","D:/Study/Pet_Project/Bootloader_STM32/Firmware/STM32F103RCT6/MDK-ARM/STM32F103RCT6"," Files (*.bin);;All Files (*)");
    if (!fileName.isEmpty()) {
        ui->pTdirection->setPlainText(fileName);
        qDebug() << "FileName: " << fileName;
        QFile file(fileName);
        if (!file.open(QFile::ReadOnly)) {
            qDebug() << "File is not open permission";
            QMessageBox::warning(this, "Warning", "file is not open");
        } else {
            fileData = file.readAll();
            QString hexData;
            for (char byte : fileData) {
                // Chuyển byte thành chuỗi hex và thêm tiền tố "0x"
                hexData += QString("%1 ").arg(static_cast<unsigned char>(byte), 2, 16, QChar('0')).toLower();
            }
            ui->pTdisplay->setPlainText(hexData);
        }
    } else {
        qDebug() << "File is empty" ;
    }
}


void MainWindow::BttUart_clicked()
{
    if(ui->cBxproto->currentIndex() == 0) {
        if (comPort != nullptr) {
            setColorButtonUart(red);
            comPort->close();
            delete comPort;
            comPort = nullptr;
            ui->progressBar->setValue(0);
        } else {
            comPort = new QSerialPort(this);
            comPort->setPortName(ui->cBUart->currentText());
            uint16_t baudrate = ui->cBBaud->currentText().toLong();
            comPort->setBaudRate(baudrate);
            comPort->setParity(QSerialPort::NoParity);
            comPort->setDataBits(QSerialPort::Data8);
            comPort->setStopBits(QSerialPort::OneStop);
            if (comPort->open(QIODevice::ReadWrite)) {
                // QMessageBox::information(this, "Open Port", "Port open successfull");
                setColorButtonUart(green);
            } else {
                QMessageBox::critical(this, "Port Error", "Unable to open specific port!");
            }
        }
    } else {
        QMessageBox::critical(this, "Protocol Error", "Unable use Protocol. Please choose UART protocol to use this function!");
    }
}


void MainWindow::BttTcp_clicked()
{

}

void MainWindow::BttUdp_clicked()
{

}

void MainWindow::loadPort()
{
    QStringList currentPorts;
    for (int i = 0; i < ui->cBUart->count(); ++i) {
        currentPorts << ui->cBUart->itemText(i);
    }

    // Duyệt qua các cổng hiện có và xóa những cổng đã không còn khả dụng
    foreach (auto &portName, currentPorts) {
        bool found = false;
        foreach (auto &port, QSerialPortInfo::availablePorts()) {
            if (port.portName() == portName) {
                found = true;
                break;
            }
        }
        if (!found) {
            int index = ui->cBUart->findText(portName);
            if (index != -1) {
                ui->cBUart->removeItem(index);
            }
        }
    }

    // Thêm những cổng mới chưa có trong QComboBox
    foreach (auto &port, QSerialPortInfo::availablePorts()) {
        if (ui->cBUart->findText(port.portName()) == -1) {
            ui->cBUart->addItem(port.portName());
        }
    }
}

void MainWindow::setupPortUpdater()
{
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::loadPort);
    timer->start(1000);  // Kiểm tra và cập nhật danh sách cổng mỗi giây
}

void MainWindow::setColorButtonUart(uint8_t Color)
{
    QPalette pal = ui->BttUart->palette();
    if (Color == red) {
         pal.setColor(QPalette::Button, QColor(Qt::red));
    } else if (Color == green) {
            pal.setColor(QPalette::Button, QColor(Qt::green));
    }
    ui->BttUart->setAutoFillBackground(true);
    ui->BttUart->setPalette(pal);
    ui->BttUart->update();
}

void MainWindow::uartSendData()
{
    size_t fileSize = fileData.size();
    size_t bytesSent = 0;
    const int chunkSize = 1024; // Kích thước khối dữ liệu (tùy chỉnh theo buffer UART)

    while (bytesSent < fileSize) {
        QByteArray chunk = fileData.mid(bytesSent, chunkSize);
        comPort->write(chunk);
        bytesSent += chunk.size();

        uint8_t percen = (bytesSent * 100) / fileSize;
        ui->progressBar->setValue(percen);
    }
}

void MainWindow::tcpSendDada()
{

}

void MainWindow::udpSendData()
{

}

void MainWindow::BttFlash_clicked()
{
    switch (ui->cBxproto->currentIndex()) {
    case UART:
        if (comPort == nullptr) {
            qDebug() << "COM port isn't initialize!";
            QMessageBox::critical(this, "COM PORT error", "Port is not initialize!");
        } else {
            if (!comPort->isOpen()) {
                QMessageBox::critical(this, "Transfer data", "Port is not open!");
            } else {
                uartSendData();
            }
        }
        break;
    case TCP:
        tcpSendDada();
        break;
    case UDP:
        udpSendData();
        break;
    default:
        break;
    }
}

