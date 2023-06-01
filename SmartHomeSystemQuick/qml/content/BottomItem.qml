import QtQuick 2.15
import QtQuick.Controls 2.15

Item {
    id: item1
    width: 150
    height: 50
    property alias mLabelLabelFontpointSize: mLabel.labelFontpointSize
    property alias mLabelLabelText: mLabel.labelText
    property alias selectedVisible: selected.visible

    MLabel {
        id: mLabel
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left
        anchors.horizontalCenter: parent.horizontalCenter
    }

//    Image {
//        id: selected
//        x: 0
//        y: 41
//        height: 9
//        visible: true
//        anchors.left: parent.left
//        anchors.right: parent.right
//        anchors.bottom: parent.bottom
//        source: "assets/selected.png"
//        fillMode: Image.PreserveAspectFit
//    }

    Image {
        id: selected
        y: 11
        anchors.verticalCenter: parent.verticalCenter
        source: "assets/pressed-bg-up.png"
        anchors.verticalCenterOffset: 22
        anchors.horizontalCenter: parent.horizontalCenter
        fillMode: Image.PreserveAspectFit
    }
}
