#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QByteArray>
#include <QFile>
#include <QDebug>
#include <QXmlStreamReader>
#include <QProcess>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->scrollArea_Board->setWidget(consoleBoard);
    ui->scrollArea_Sppz->setWidget(consoleSppz);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::getFile(QString fileName){
    QProcess process;
    QString command = "scp root@192.168.1.1:/root/"+fileName+" "+tempFolder;
    //QString command = "sshpass -p 'root' scp root@192.168.1.1:/root/sshtest.xml /our/home/folder";
    process.start(command);
    consoleBoard->appendPlainText(command);

    if (!process.waitForFinished()) {

        consoleBoard->appendPlainText("Failed to execute SCP command.");
        qWarning("Failed to execute SCP command.");
    }
    QByteArray output = process.readAllStandardOutput();
    QByteArray outputError = process.readAllStandardError();

    consoleBoard->appendPlainText(output);
    consoleBoard->appendPlainText(outputError);
}

void MainWindow::changeFile(QString fileName){
    QProcess process;

    QString command = "scp "+tempFolder+"/"+fileName+" root@192.168.1.1:/root";//server ip and password
    //QString command = "sshpass -p 'root' scp root@192.168.1.1:/root/sshtest.xml /our/home/folder";
    process.start(command);
    qDebug()<<command;

    if (!process.waitForFinished()) {
        consoleBoard->clear();
        consoleBoard->appendPlainText("Failed to execute SCP command.");
        qWarning("Failed to execute SCP command.");
    }
    QByteArray output = process.readAllStandardOutput();
    QByteArray outputError = process.readAllStandardError();
    consoleBoard->clear();
    consoleBoard->appendPlainText(output);
    consoleBoard->appendPlainText(outputError);

}


void MainWindow::on_giveFiles_clicked()
{

    changeFile("sshtest.txt");
    ui->compareLabel->setText("Files update");
    ui->compareLabel->setStyleSheet("background-color:green; font-size:14px; font:bold; color:black");
}


void MainWindow::readPi(QByteArray fileData, QPlainTextEdit *console)
{
    console->clear();
    QXmlStreamReader xml(fileData);
    while (!xml.atEnd())
    {
        xml.readNext();
        QString stringAttributes;
        if(xml.attributes().hasAttribute("ClassTag"))
            stringAttributes.append(" Тег класса - "+xml.attributes().value("ClassTag").toString()+"; ");
        if(xml.attributes().hasAttribute("id"))
            stringAttributes.append(" Идентификатор - "+xml.attributes().value("id").toString()+"; ");
        if(xml.attributes().hasAttribute("filename"))
            stringAttributes.append(" Имя файла - "+xml.attributes().value("filename").toString()+"; ");
        if(xml.attributes().hasAttribute("RUS"))
            stringAttributes.append(" "+xml.attributes().value("RUS").toString()+": ");
        if(xml.attributes().hasAttribute("CharGroupId"))
            stringAttributes.append(" Идентификатор - "+xml.attributes().value("CharGroupId").toString()+"; ");
        if(xml.attributes().hasAttribute("Value"))
            stringAttributes.append(" "+xml.attributes().value("Value").toString()+"; ");
        if(stringAttributes.size()>0)
            //qDebug()<<"stringAttributes"<< stringAttributes;
            console->appendPlainText(stringAttributes);
    }


}

void MainWindow::readTempPi(){
    getFile("pi.xml");
    QFile file(tempFolder+"/sshtest.xml");
    file.open(QIODevice::ReadOnly);
    QByteArray array = file.readAll();
    file.close();
    readPi(array,consoleBoard);
}
void MainWindow::readSppzPi(){
    QFile file(SppzFolder+"/sshtest.xml");
    file.open(QIODevice::ReadOnly);
    QByteArray array = file.readAll();
    file.close();
    readPi(array,consoleSppz);
}

void MainWindow::on_readTempPi_clicked()
{
    readTempPi();
}

void MainWindow::on_readSppzPi_clicked()
{
    readSppzPi();
}
void MainWindow::on_compareButton_clicked()
{
    QFile fileTemp(tempFolder+"/sshtest.xml");
    fileTemp.open(QIODevice::ReadOnly);
    QByteArray arrayTemp = fileTemp.readAll();
    fileTemp.close();

    QFile fileSppz(SppzFolder+"/sshtest.xml");
    fileSppz.open(QIODevice::ReadOnly);
    QByteArray arraySppz = fileSppz.readAll();
    fileSppz.close();

    if(arrayTemp==arraySppz){
        ui->compareLabel->setText("Files equals");
        ui->compareLabel->setStyleSheet("background-color:green; font-size:14px; font:bold; color:black");
        }
    else{
        ui->compareLabel->setText("Files differs");
        ui->compareLabel->setStyleSheet("background-color:red; font-size:14px; font:bold; color:white");
    }
}


void MainWindow::on_changeBoardPathButton_clicked()
{

    tempFolder=ui->boardPath->toPlainText();

}


void MainWindow::on_changeSPPZPathButton_clicked()
{
    SppzFolder=ui->sppzPath->toPlainText();
}


void MainWindow::on_getFileButton_clicked()
{
    getFile(ui->fileName->toPlainText());

}

