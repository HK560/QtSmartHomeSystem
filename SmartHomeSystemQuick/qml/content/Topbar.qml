import QtQuick 2.15
import QtQuick.Controls 2.15

Rectangle {
    id: rectangle
    width: 1024
    height: 55
    color: "#ffffff"

    MLabelBlack {
        id: mLabelBlack
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left
        labelFontpointSize: 15
        anchors.leftMargin: 115
        labelText: currentDateTime()

    }

    Timer{
        id: timer
        interval: 1 //间隔(单位毫秒):1000毫秒=1秒
        repeat: true //重复
        onTriggered:{
            mLabelBlack.labelText = currentDateTime();
        }
    }

    Rectangle {
        id: rectangle1
        width: 50

        height: parent .height
        color: "#ffffff"
        anchors.right: parent.right
        anchors.rightMargin: 0

        Image {
            id: strong_wifi_icon
            visible: false
            anchors.fill: parent
            source: "images/icon/strong_wifi_icon.png"
            fillMode: Image.PreserveAspectFit
        }

        Image {
            id: mid_wifi_icon
            visible: false
            anchors.fill: parent
            source: "images/icon/mid_wifi_icon.png"
            fillMode: Image.PreserveAspectFit
        }

        Image {
            id: disconnect_wifi_icon
            visible: false
            anchors.fill: parent
            source: "images/icon/disconnect_wifi_icon.png"
            fillMode: Image.PreserveAspectFit
        }

        Image {
            id: searching_icon
            visible: false
            anchors.fill: parent
            source: "images/icon/searching_icon.png"
            fillMode: Image.PreserveAspectFit
        }
    }

    Rectangle {
        id: rectangle2
        width: 50


        color: "#ffffff"
        anchors.right: rectangle1.left
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10
        anchors.topMargin: 10
        anchors.rightMargin: 0

        Image {
            id: searching_icon1
            anchors.fill: parent
            source: "images/icon/searching_icon.png"
            fillMode: Image.PreserveAspectFit

            SequentialAnimation {
                id: blinkAnimation

                PropertyAnimation {
                    target: searching_icon1
                    property: "opacity"
                    to: 0
                    duration: 500

                }
                PropertyAnimation {
                    target: searching_icon1
                    property: "opacity"
                    to: 1
                    duration: 500

                }
            }
        }

        MouseArea {
            id: mouseArea
            anchors.fill: parent
             onClicked:{
                qmlCtrl.sendUdpDcNow()
            }
        }
    }

    Connections{
        target:qmlCtrl
        function onFoundDevice(name){
        blinkAnimation.start()
        }

    }

    MLabel {
        id: mLabel
        anchors.verticalCenter: parent.verticalCenter
        labelFontpointSize: 25
        labelText: "智慧家庭系统"
        anchors.horizontalCenter: parent.horizontalCenter
    }

       function currentDateTime(){
           return Qt.formatDateTime(new Date(), "MM月dd日 hh时mm分");
       }

}
