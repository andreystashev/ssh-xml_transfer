#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <libssh/libssh.h>
#include <QPlainTextEdit>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:


private slots:

    void on_readTempPi_clicked();

    void on_readSppzPi_clicked();

    void on_compareButton_clicked();

    void on_giveFiles_clicked();

    void on_changeBoardPathButton_clicked();

    void on_changeSPPZPathButton_clicked();

    void on_getFileButton_clicked();

private:
    void readPi(QByteArray, QPlainTextEdit *console);
    void readTempPi();
    void readSppzPi();
    void getFile(QString fileName);
    void changeFile(QString fileName);
    Ui::MainWindow *ui;

    QPlainTextEdit *consoleBoard = new QPlainTextEdit();
    QPlainTextEdit *consoleSppz = new QPlainTextEdit();
    QString tempFolder = "/our/file/location";
    QString SppzFolder = "/our/file/location/files";
};
#endif // MAINWINDOW_H
