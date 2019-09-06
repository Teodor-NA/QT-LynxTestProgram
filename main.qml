import QtQuick 2.7
import QtQuick.Window 2.2
import backend 1.1
import QtQuick.Controls 1.6


Window
{
    visible: true
    width: 640
    height: 480
    title: qsTr("Lynx Test App")

    BackEnd
    {
        id: backEnd
        onClearPortList:
        {
            portListModel.clear()
            portListModel.append({ text: qsTr("Select port") })
        }
        onAddPort: portListModel.append({ text: portName })
    }

    Column
    {
        spacing: 10
        padding: 20
        width: 200

        Row
        {
            width: parent.width
            spacing: 10

            TextField
            {
                width: parent.width/2
                id: textField
                placeholderText: qsTr("Input number")
                validator: IntValidator { top: 2147483647; bottom: 0 }
                onAccepted:
                {
                    backEnd.transmitInterval = text
                    label.text = text;
                    text = qsTr("");
                }
            }

            Label
            {
                width: parent.width/2
                id: label
                text: qsTr("Not set")
            }

            Column
            {
                spacing: 10

                Row
                {
                    spacing: 5

                    Slider
                    {
                        id: blueSlider

                        width: 200
                        minimumValue: 0
                        maximumValue: 255

                        onValueChanged:
                        {
                            backEnd.blueLight = value
                        }
                    }

                    Label
                    {
                        id: blueLabel
                        text: Math.floor(blueSlider.value)
                    }
                }
                Row
                {
                    spacing: 5

                    Slider
                    {
                        id: orangeSlider

                        width: 200
                        minimumValue: 0
                        maximumValue: 255

                        onValueChanged:
                        {
                            backEnd.orangeLight = value
                        }
                    }

                    Label
                    {
                        id: orangeLabel
                        text: Math.floor(orangeSlider.value)
                    }
                }
            }
        }



        Button
        {
            width: parent.width
            id: button
            text: qsTr("Send all")
            onClicked: backEnd.sendData()
        }

        Row
        {
            spacing: 5

            ComboBox
            {
                width: 200
                id: portComboBox
                // currentIndex: -1
                model:
                    ListModel
                    {
                        id: portListModel
                        ListElement{text: qsTr("Select port")}
                    }

                onActivated:
                {
                    // console.log("Activated")
                    if (currentIndex > 0)
                    {
                        backEnd.portSelected(portComboBox.currentIndex - 1)
                        connectButton.enabled = true
                    }
                    else
                        connectButton.enabled = false
                }

                onPressedChanged:
                {
                    if (pressed)
                    {
                        backEnd.refreshPortList()
                        if (portListModel.count < 2)
                            connectButton.enabled = false
                        // console.log("Pressed")
                    }
                }
            }

            Button
            {
                width: 100
                id: connectButton
                enabled: false
                text: qsTr("Connect")
                onClicked:
                {
                    backEnd.connectButtonClicked()
                    if (backEnd.uartConnected())
                    {
                        text = qsTr("Disconnect")
                        portComboBox.enabled = false
                    }
                    else
                    {
                        text = qsTr("Connect")
                        portComboBox.enabled = true
                    }
                }
            }
        }
    }


}
