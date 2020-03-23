#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSerialPortInfo>
#include <QDebug>
#include <QMessageBox>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    const auto infos = QSerialPortInfo::availablePorts();

    serial.setBaudRate(QSerialPort::Baud9600);
    serial.setStopBits(QSerialPort::OneStop);
    serial.parityChanged(QSerialPort::NoParity);
    serial.setFlowControl(QSerialPort::NoFlowControl);

    for (const QSerialPortInfo &info : infos)
        ui->comboBoxSerial->addItem(info.portName());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::send()
{
#pragma pack(push,1)
    struct {
        bool light  :1;
        quint8      :3;
        quint8 key  :4;
        quint8 lr;
        quint8 fb;
    } message;
#pragma pack(pop)

    int lr = ui->horizontalSliderControl->value();
    int fb = ui->verticalSliderMove->value();

    message.lr = static_cast<quint8>((((lr>>31)&0x1)<<7) | (abs(lr)&0x7F));
    message.fb = static_cast<quint8>((((fb>>31)&0x1)<<7) | (abs(fb)&0x7F));
    message.light = ui->checkBoxLight->isChecked();
    message.key = 0xA;

    serial.write(reinterpret_cast<char*>(&message), sizeof (message));

    QByteArray data;
    data.append(reinterpret_cast<char*>(&message), sizeof (message));
    ui->labelOutput->setText(data.toHex());

}

void MainWindow::on_horizontalSliderControl_sliderMoved(int position)
{
    send();
}

void MainWindow::on_verticalSliderMove_sliderMoved(int position)
{
    send();
}

void MainWindow::on_pushButtonConnect_clicked(bool checked)
{
    if (checked) {
        serial.setPortName(ui->comboBoxSerial->currentText());
        if (!serial.open(QIODevice::ReadWrite)) {
            QMessageBox::warning(this, "Error", "Device not connect.");
            static_cast<QPushButton*>(sender())->setChecked(false);
        }
    }
    else {
        if (serial.isOpen())
            serial.close();
    }
}

void MainWindow::on_checkBoxLight_clicked()
{
    send();
}
