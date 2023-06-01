import QtQuick 2.15
import QtQuick.Controls 2.15
import QtGraphicalEffects 1.12
Item {
    id:itemm
    width: 1024
    height: 600
    property alias mouseArea: mouseArea



    Image {
        id: pic
        anchors.fill: parent
        source: "file:///"+ appDir + "/images/" + qmlCtrl.imageName
//        source: "file:///I:/Desktop/00004-979915500.png"
        fillMode: Image.PreserveAspectCrop



    }

    Connections {
        target: qmlCtrl;
        function onImageNameChanged(imageName){
            console.log("lockScreen image have changed")
            pic.source = "file:///"+ appDir + "/images/" + imageName
        }
    }

    Timer {
        id:timer
        interval: 1000; running: true; repeat: true

        onTriggered: {
            mLabel2.labelText = Qt.formatDateTime(new Date(), "hh:mm");
            mLabel3.labelText = Qt.formatDateTime(new Date(), "MM月dd日 dddd");

        } // 星期 www.it165.net 年份 月份 号 大月份
    }

    Rectangle {
        id: rectangle
        x: 729
        y: 442
        width: 295
        height: 140
        color: "#00252525"
        radius: 30
        border.width: 0

        MLabel2 {
            id: mLabel2
            y: 448
            width: 278
            height: 68
            anchors.verticalCenter: parent.verticalCenter
            anchors.verticalCenterOffset: -18
            anchors.horizontalCenter: parent.horizontalCenter
            labelFontpointSize: 58
            labelText: "12:00"
        }
        MLabel2 {
            id: mLabel3
            width: 203
            height: 25
            anchors.top: mLabel2.bottom
            anchors.topMargin: 0
            anchors.horizontalCenter: parent.horizontalCenter
            labelFontpointSize: 15

            labelText: "2月24日 星期一"
        }
    }

    MouseArea {
        id: mouseArea
        anchors.fill: parent
    }
    states: [
        State {
            name: "State1"
        }
    ]

    Component.onCompleted: {
//        var dir = Qt.resolvedUrl(".")
        console.log("Current directory: " + appDir)
        timer.start();
        mLabel2.labelText = Qt.formatDateTime(new Date(), "hh:mm");
        mLabel3.labelText = Qt.formatDateTime(new Date(), "MM月dd日 dddd");
    }



}
