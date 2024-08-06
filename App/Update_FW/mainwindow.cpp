#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    plTextFile = new QTextEdit(this);
    plTextCode = new QTextEdit(this);
    connect(ui->bttFile, &QPushButton::clicked, this, &MainWindow::on_bttFile_clicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_bttFile_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), QCoreApplication::applicationDirPath(), tr("Hex Files (*.hex);;All Files (*)"));
    if (!fileName.isEmpty()) {
        ui->plTextFile->setPlainText(fileName);
        qDebug() << "FileName: " << fileName;
        QFile file(fileName);
        QString line;
        ui->plTextCode->clear();
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream in(&file);
            while (!in.atEnd()) {
                line = in.readLine();
                ui->plTextCode->setPlainText(ui->plTextCode->toPlainText()+line+"\n");
                qDebug() << "line : " << line;
            }
        }
    }
}

