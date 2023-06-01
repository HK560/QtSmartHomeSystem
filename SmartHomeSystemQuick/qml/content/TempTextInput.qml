import QtQuick 2.15
import QtQuick.Controls 2.15

Rectangle {
    id: rectangle1
    width: 1024
    height: 500
    color: "#d4191919"
    property alias inputText: mLineEdit1.textInputText
    property alias mLineEdit: mLineEdit1
    property alias mbuttonBlue: mbuttonBlue

    property MLineEdit1 obj

    MouseArea {
        id: mouseArea
        anchors.fill: parent
        onClicked: {
            rectangle1.visible = false
        }
    }

    Rectangle {
        id: rectangle
        x: 179
        y: 5
        width: 638
        height: 79
        color: "#ffffff"
        radius: 30
        anchors.horizontalCenterOffset: 0
        anchors.horizontalCenter: parent.horizontalCenter

        MLineEdit1 {
            id: mLineEdit1
            x: 48
            y: 20
            width: 448
            height: 40
            focus: true
            textInputText: ""

            MouseArea {
                id: mouseArea1
                x: 406
                y: 5
                width: 30
                height: 30
                anchors.verticalCenter: parent.verticalCenter
                anchors.right: parent.right
                anchors.rightMargin: 12


                Image {
                    id: close
                    y: 8
                    anchors.verticalCenter: parent.verticalCenter
                    source: "assets/close.png"
                    anchors.horizontalCenter: parent.horizontalCenter
                    fillMode: Image.PreserveAspectFit
                }
                onClicked: {
                mLineEdit1.textInputText = ""

                }
            }

        }

        MbuttonBlue {
            id: mbuttonBlue
            x: 516
            width: 107
            height: 40
            text: "确定"
            anchors.verticalCenter: mLineEdit1.verticalCenter
            anchors.top: mLineEdit1.bottom
            anchors.topMargin: -40

            onClicked: {
                obj.textInputText = mLineEdit1.textInputText
                rectangle1.visible = false
            }
        }

        STTVbutton{
            id:sttbtn
            width: 42
            height: 40
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.left
            anchors.leftMargin: 4
            flag:3

        }

        Connections{
            target: sttbtn
            function onGetResult(message){
                mLineEdit1.textInputText= message
            }
        }

    }
}
