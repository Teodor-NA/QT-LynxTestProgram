#include "backend.h"

BackEnd::BackEnd(QObject *parent) :
    QObject(parent),
    _lynx(0x25, "Device 1"),
    _uart(_lynx),
    _lightControl_2(_lynx, 0x30),
    _lightControl(_lynx, 0x15)
{
   //  _uart.open(4, 115200);

    _selectedDevice = -1;
    _selectedStruct = -1;

    connect(_uart.portPointer(), SIGNAL(readyRead()), this, SLOT(readData()));
}

void BackEnd::scan()
{
    qDebug() << "\n------------ Sending Scan -------------\n";
    _uart.scan();
    // this->clearDevices();
    // this->addDevice("desc");
}

void BackEnd::readData()
{
    _receiveInfo = _uart.update();

    if(_receiveInfo.state != LynxLib::eNoChange)
    {
        qDebug() << "";
        qDebug() << "------------- Received ----------------";
        qDebug() << QString::asprintf("Device ID: 0x%x", _receiveInfo.deviceId);
        qDebug() << QString::asprintf("Struct ID: 0x%x", _lynx.structId(_receiveInfo.lynxId));
        qDebug() << "Struct Index: " << _receiveInfo.lynxId.structIndex;
        qDebug() << "Variable Index: " << _receiveInfo.lynxId.variableIndex;
        qDebug() << "Length: " << _receiveInfo.dataLength;
        qDebug() << "State: " << LynxLib::lynxStateTextList[_receiveInfo.state];
        qDebug() << "---------------------------------------";

        if(_receiveInfo.state == LynxLib::eNewDataReceived)
        {
            qDebug() << "Blue light: " << _lightControl.blueLight;
            qDebug() << "Orange light: " << _lightControl.orangeLight;
            qDebug() << "Time: " << _lightControl.time;
            qDebug() << "Transmit interval: " << _lightControl.transmitInterval;
            qDebug() << "Remote state: " << LynxString(_lightControl.state);
            qDebug() << "---------------------------------------";
        }
        else if (_receiveInfo.state == LynxLib::eNewDeviceInfoReceived)
        {
            _deviceInfoList.append(_uart.lynxDeviceInfo());
            this->addDevice(QString(_deviceInfoList.last().description) + QString::asprintf(" - Id: 0x%x", _deviceInfoList.last().deviceId));
        }
    }
}

void BackEnd::refreshPortList()
{
    this->clearPortList();
    _portList = QSerialPortInfo::availablePorts();

    QString tempName;
    for (int i = 0; i < _portList.count(); i++)
    {
        tempName = _portList.at(i).portName();
        tempName += " - ";
        tempName += _portList.at(i).description();

        if (!_portList.at(i).isNull())
            this->addPort(tempName);
    }
}

void BackEnd::portSelected(int index)
{
    qDebug() << "Port selsected";
    qDebug() << "Index: " << index;
    if ((index < 0) || (index >= _portList.count()))
        return;

    _selectedPort = _portList.at(index);
}

void BackEnd::connectButtonClicked()
{
    // qDebug() << "Button clicked";
    if (_uart.opened())
    {
        qDebug() << "Closing port";
        _uart.close();
    }
    else
    {
        qDebug() << "Attempting to open";
        qDebug() << _selectedPort.portName();
        qDebug() << _selectedPort.description();
        if (_uart.open(_selectedPort, _baudrate))
            qDebug() << "Opened successfully";
        else
            qDebug() << "Open failed";
    }

}

void BackEnd::selectDevice(int index)
{
    qDebug() << "deviceIndex:" << index;

    _selectedDevice = index - 1;

    if ((_selectedDevice >= _deviceInfoList.count()) || (_selectedDevice < 0))
    {
        this->addDeviceInfo("No selection", "No selection", "No selection", "No selection");
        this->clearStructList();
        // this->addStruct("No selection");
        // this->addStructInfo("No selection", "No selection", "No selection");
        // this->clearVariableList();
        // this->addVarable("No selection", "No selection", "No selection");
    }
    else
    {
        this->addDeviceInfo(
                    QString(_deviceInfoList.at(index - 1).description),
                    "0x" + QString::number(_deviceInfoList.at(index - 1).deviceId, 16),
                    QString(_deviceInfoList.at(index - 1).lynxVersion),
                    QString::number(_deviceInfoList.at(index - 1).structCount)
                    );

        this->clearStructList();
        // this->addStruct("No selection");
        for (int i = 0; i < _deviceInfoList.at(index - 1).structs.count(); i++)
        {
            this->addStruct(
                        QString(_deviceInfoList.at(index - 1).structs.at(i).description) +
                        QString::asprintf(" - 0x%x", _deviceInfoList.at(index - 1).structs.at(i).structId)
                        );
        }
    }
}

void BackEnd::selectStruct(int index)
{
    qDebug() << "structIndex:" << index;

    _selectedStruct = index - 1;

    if ((_selectedDevice >= _deviceInfoList.count()) || (_selectedDevice < 0))
    {
        this->addStructInfo("No selection", "No selection", "No selection");
        this->clearVariableList();
        this->addVarable("No selection", "No selection", "No selection");
    }
    else if ((_selectedStruct >= _deviceInfoList.at(_selectedDevice).structs.count()) || (_selectedStruct < 0))
    {
        this->addStructInfo("No selection", "No selection", "No selection");
        this->clearVariableList();
        this->addVarable("No selection", "No selection", "No selection");
    }
    else
    {
        qDebug() << "var count:" << _deviceInfoList.at(_selectedDevice).structs.at(_selectedStruct).variableCount;
        this->addStructInfo(
                    QString(_deviceInfoList.at(_selectedDevice).structs.at(_selectedStruct).description),
                    QString::asprintf("0x%x", _deviceInfoList.at(_selectedDevice).structs.at(_selectedStruct).structId),
                    QString::number(_deviceInfoList.at(_selectedDevice).structs.at(_selectedStruct).variableCount)
        );

        this->clearVariableList();

        for (int i = 0; i < _deviceInfoList.at(_selectedDevice).structs.at(_selectedStruct).variables.count(); i++)
        {
            this->addVarable(
                        QString(_deviceInfoList.at(_selectedDevice).structs.at(_selectedStruct).variables.at(i).description),
                        QString::number(_deviceInfoList.at(_selectedDevice).structs.at(_selectedStruct).variables.at(i).index),
                        QString(LynxLib::lynxTypeTextList[_deviceInfoList.at(_selectedDevice).structs.at(_selectedStruct).variables.at(i).dataType])
            );
        }
    }

}
