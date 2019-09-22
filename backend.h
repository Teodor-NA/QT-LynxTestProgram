#ifndef BACKEND_H
#define BACKEND_H

#include <QObject>
#include <QtDebug>
#include "lynxstructure.h"
#include "lynxuartqt.h"
#include "lightcontrol.h"
// #include "teststruct.h"

class BackEnd : public QObject
{
    Q_OBJECT

//    Q_PROPERTY(int blueLight READ blueLight WRITE setBlueLight NOTIFY blueLightChanged)
//    Q_PROPERTY(int orangeLight READ orangeLight WRITE setOrangeLight NOTIFY orangeLightChanged)
//    Q_PROPERTY(unsigned int transmitInterval READ transmitInterval WRITE setTransmitInterval NOTIFY transmitIntervalChanged)

    LynxManager _lynx;
    LynxUartQt _uart;

    LightControl _lightControl_2;
    LightControl _lightControl;

    LynxInfo _receiveInfo;

    QList<QSerialPortInfo> _portList;
    QSerialPortInfo _selectedPort;

    unsigned long _baudrate = 115200;

    LynxList<LynxDeviceInfo> _deviceInfoList;

    int _selectedDevice;
    int _selectedStruct;

public:
    explicit BackEnd(QObject *parent = nullptr);
    ~BackEnd() { _uart.close(); }

//    int blueLight() const { return _lightControl.blueLight; }
//    int orangeLight() const { return _lightControl.orangeLight; }
//    unsigned int transmitInterval() const { return _lightControl.transmitInterval; }

//    void setBlueLight(int input)
//    {
//        if (input == _lightControl.blueLight)
//            return;
//        _lightControl.blueLight = uint8_t(input);
//        _uart.send(_lightControl.blueLight.lynxId());

//        qDebug() << "";
//        qDebug() << "--------------- Sending ---------------";
//        qDebug() << "Blue light: " << _lightControl.blueLight;
//        qDebug() << "---------------------------------------";


//        emit blueLightChanged();
//    }

//    void setOrangeLight(int input)
//    {
//        if (input == _lightControl.orangeLight)
//            return;

//        _lightControl.orangeLight = uint8_t(input);
//        _uart.send(_lightControl.orangeLight.lynxId());

//        qDebug() << "";
//        qDebug() << "--------------- Sending ---------------";
//        qDebug() << "Orange light: " << _lightControl.orangeLight;
//        qDebug() << "---------------------------------------";

//        emit orangeLightChanged();
//    }

//    void setTransmitInterval(unsigned int input)
//    {
//        if (input == _lightControl.transmitInterval)
//            return;

//        _lightControl.transmitInterval = input;
//        _uart.send(_lightControl.transmitInterval.lynxId());

//        qDebug() << "";
//        qDebug() << "--------------- Sending ---------------";
//        qDebug() << "Transmit interval: " << _lightControl.transmitInterval;
//        qDebug() << "---------------------------------------";

//        emit transmitIntervalChanged();
//    }

signals:
    void clearPortList();
    void addPort(const QString & portName);
//    void blueLightChanged();
//    void orangeLightChanged();
//    void transmitIntervalChanged();
    void clearDevices();
    void addDevice(const QString & device);
    void addDeviceInfo(const QString & description, const QString & id, const QString & version, const QString & count);
    void clearStructList();
    void addStruct(const QString & structInfo);
    void addStructInfo(const QString & description, const QString & id, const QString & count);
    void clearVariableList();
    void addVarable(const QString & description, const QString & index, const QString & type);

public slots:
    void scan();
    void readData();
    void refreshPortList();
    void portSelected(int index);
    void connectButtonClicked();
    bool uartConnected() { return _uart.opened(); }
    void selectDevice(int index);
    void selectStruct(int index);
};

#endif // BACKEND_H
