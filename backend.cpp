#include "backend.h"

BackEnd::BackEnd(QObject *parent) :
    QObject(parent),
    _lynx(0x25),
    _uart(_lynx),
    _lightControl(_lynx, 0x15)
{
   //  _uart.open(4, 115200);

    connect(_uart.portPointer(), SIGNAL(readyRead()), this, SLOT(readData()));
}

void BackEnd::sendData()
{
    qDebug() << "";
    qDebug() << "--------------- Sending ---------------";
    qDebug() << "Blue light: " << _lightControl.blueLight;
    qDebug() << "Orange light: " << _lightControl.orangeLight;
    qDebug() << "---------------------------------------";

    _uart.send(_lightControl.lynxId());
}

void BackEnd::readData()
{
    _receiveInfo = _uart.update();
//
//    const LynxByteArray & temp = _uart.readBuffer();
//
//    qDebug() << temp.count();

//    QString tempStr = "";
//
//    for (int i = 0; i < temp.count(); i++)
//    {
//        tempStr += QString::number(temp.at(i));
//        if(i != temp.count())
//            tempStr += " ";
//    }
//
//    qDebug() << tempStr;

    // _receiveID = _lynx.lynxID();
    // qDebug() << "Device ID: " << _receiveID.deviceId;
    // qDebug() << "Struct ID: " << _receiveID.structId;
    // qDebug() << "Length: " << _receiveID.length;
    // qDebug() << "Index: " << _receiveID.index;
    // qDebug() << "State: " << _receiveID.state;

    if(_receiveInfo.state != eNoChange)
    {
        qDebug() << "";
        qDebug() << "------------- Received ----------------";
        qDebug() << QString::asprintf("Device ID: 0x%x", _receiveInfo.deviceId);
        qDebug() << QString::asprintf("Struct ID: 0x%x", _lynx.structId(_receiveInfo.lynxId));
        qDebug() << "Struct Index: " << _receiveInfo.lynxId.structIndex;
        qDebug() << "Variable Index: " << _receiveInfo.lynxId.variableIndex;
        qDebug() << "Length: " << _receiveInfo.dataLength;
        qDebug() << "State: " << lynsStateTextList[_receiveInfo.state];
        qDebug() << "---------------------------------------";

        if(_receiveInfo.state == eNewDataReceived)
        {
            qDebug() << "Blue light: " << _lightControl.blueLight;
            qDebug() << "Orange light: " << _lightControl.orangeLight;
            qDebug() << "Time: " << _lightControl.time;
            qDebug() << "Transmit interval" << _lightControl.transmitInterval;
            qDebug() << "---------------------------------------";
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
