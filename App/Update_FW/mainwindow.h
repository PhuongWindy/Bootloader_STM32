#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QTextEdit>
#include <QDebug>
#include <QString>

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

private slots:
    void on_bttFile_clicked();

private:
    Ui::MainWindow *ui;
    QTextEdit *plTextFile;
    QTextEdit *plTextCode;
};
#endif // MAINWINDOW_H
