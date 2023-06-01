import QtQuick 2.15
import QtQuick.Controls 2.15

Item {
    id: item1
    width: 460
    height: 120
    property alias rvName: rvNameLabel.labelText
    property alias rvValue: rvValueLabel.labelText
    property alias rvDesc: rvDescLabel.labelText
    property alias rvDeviceName: rvDeviceNameLabel.labelText
    MLabel2 {
        id: rvNameLabel
        x: 29
        y: 8
        labelText: "RvNAme"
        labelHorizontalAlignment:Text.AlignLeft
    }

    MLabel2 {
        id: rvValueLabel
        x: 338
        y: 32
        labelText: "VALUE"
    }

    MLabel2 {
        id: rvDescLabel
        y: 46
        anchors.left: rvNameLabel.left
        anchors.leftMargin: 0
        labelFontpointSize: 15
        labelText: "descdescdescdesc"
        labelHorizontalAlignment:   Text.AlignLeft
    }
    MLabel2{
        id: rvDeviceNameLabel
        y: 79
        anchors.bottom: parent.bottom
        anchors.horizontalCenterOffset: 0
        labelText: "devName"
        labelFontpointSize: 10
        anchors.bottomMargin: -9
        anchors.horizontalCenter: parent.horizontalCenter

    }
}
