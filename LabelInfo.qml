import QtQuick 2.12
import QtQuick.Controls 2.12

Row
{
    id: row1
    property string first: "Not set"
    property string second: "Not set"

    Label
    {
        width: 160
        text: qsTr(row1.first + ": ")
        font.bold: true
        font.pixelSize: 15
    }

    Label
    {
        width: 200
        text: row1.second
        font.pixelSize: 15
    }
}
