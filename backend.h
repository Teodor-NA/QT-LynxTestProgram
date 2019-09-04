#ifndef BACKEND_H
#define BACKEND_H

#include <QObject>
#include <QtDebug>
#include "LynxStructure.h"
#include "lynxuartqt.h"
#include "lightcontrol.h"
// #include "teststruct.h"

class BackEnd : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int blueLight READ blueLight WRITE setBlueLight NOTIFY blueLightChanged)
    Q_PROPERTY(int orangeLight READ orangeLight WRITE setOrangeLight NOTIFY orangeLightChanged)
    // Q_PROPERTY(bool uartConnected READ )

    LynxManager _lynx;
    LynxUartQt _uart;

    LightControl _lightControl;

    LynxInfo _receiveInfo;

    QList<QSerialPortInfo> _portList;
    QSerialPortInfo _selectedPort;

    unsigned long _baudrate = 115200;

public:
    explicit BackEnd(QObject *parent = nullptr);
    ~BackEnd() { _uart.close(); }

    int blueLight() const { return _lightControl.blueLight; }
    int orangeLight() const { return _lightControl.orangeLight; }

    void setBlueLight(int input)
    {
        if (input == _lightControl.blueLight)
            return;
        _lightControl.blueLight = uint8_t(input);
        _uart.send(_lightControl.blueLight.lynxId());

        qDebug() << "";
        qDebug() << "--------------- Sending ---------------";
        qDebug() << "Blue light: " << _lightControl.blueLight;
        qDebug() << "---------------------------------------";


        emit blueLightChanged();
    }

    void setOrangeLight(int input)
    {
        if (input == _lightControl.orangeLight)
            return;

        _lightControl.orangeLight = uint8_t(input);
        _uart.send(_lightControl.orangeLight.lynxId());

        qDebug() << "";
        qDebug() << "--------------- Sending ---------------";
        qDebug() << "Orange light: " << _lightControl.orangeLight;
        qDebug() << "---------------------------------------";

        emit orangeLightChanged();
    }

signals:
    void clearPortList();
    void addPort(const QString & portName);
    void blueLightChanged();
    void orangeLightChanged();

public slots:
    void sendData();
    void readData();
    void refreshPortList();
    void portSelected(int index);
    void connectButtonClicked();
    bool uartConnected() { return _uart.opened(); }
};

#endif // BACKEND_H