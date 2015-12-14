#include "dialog.h"
#include "ui_dialog.h"
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/qserialportglobal.h>
#include <QSerialPortInfo>
#include <string>
#include <QDebug>
#include <QMessageBox>

QSerialPort *rpi;

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    ui->tempLcdNumber->display("-------");
    ui->humidLcdNumber->display("-------");
    rpi = new QSerialPort(this);

  // we set the port properties


        rpi->setPortName("ttyUSB0");
        //rpi->setPortName("ttyS0");

        rpi->setBaudRate(QSerialPort::Baud9600);
        rpi->setDataBits(QSerialPort::Data8);
        rpi->setFlowControl(QSerialPort::NoFlowControl);
        rpi->setParity(QSerialPort::NoParity);
        rpi->setStopBits(QSerialPort::OneStop);

        bool open = rpi->open(QSerialPort::ReadOnly);
        //rpi->write("ACK");
        connect(rpi, SIGNAL(readyRead()), this, SLOT(readSerial()));
//         connect(this, SIGNAL(update_temperature(QString)), this, SLOT(updateTemperature(QString)));
//          connect(this, SIGNAL(update_humidity(QString)), this, SLOT(updateHumidity(QString)));

         qDebug() << "Ready to receive from control box: " << open << endl; // we write on the console

}

Dialog::~Dialog()
{
    rpi->close();
    delete ui;
}



void Dialog::readSerial()
{

    QStringList buffer_split;

        serialData.append(rpi->readAll());

        if(serialData.endsWith(0x0D)){
            QString newData(serialData);

            qDebug() << newData;

            //buffer_split = newData.split(' ');
            //buffer_split[0].left(3).endsWith('A', Qt::CaseInsensitive)
            if(newData.at(2) == 'A'){
                 buffer_split = newData.split(' ');
                QString temperature = buffer_split[0].mid(4,9);
                QString humidity = buffer_split[2].left(4);
                qDebug() <<"temperature:"<<temperature;
                updateTemperature(temperature);
                updateHumidity(humidity);
                serialData.clear();

            }
        }

}

void Dialog::updateTemperature(QString temp_reading)
{
    //  update the value displayed on the lcdNumber
    ui->tempLcdNumber->display(temp_reading);
    qDebug() <<"temp reading:"<<temp_reading;
}

void Dialog::updateHumidity(QString humi_reading)
{
    //  update the value displayed on the lcdNumber
    ui->humidLcdNumber->display(humi_reading);
}


