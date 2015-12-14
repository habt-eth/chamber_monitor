#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QtSerialPort/QSerialPort>
#include <QByteArray>


namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Dialog
     *
     * @param parent
     */
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();


//signals:

//    void update_temperature(QString);
//    void update_humidity(QString);

private slots:
    /**
     * @brief readSerial
     * This function read data from the port
     */
    void readSerial();

    /**
     * this function updates the temperature
     * values received from the
     * control box
    */
    void updateTemperature(QString);
    void updateHumidity(QString);

private:
    Ui::Dialog *ui;

    QSerialPort *rpi;

    QByteArray serialData;


};

#endif // DIALOG_H
