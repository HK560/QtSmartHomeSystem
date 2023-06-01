import QtQuick 2.15
import QtQuick.Controls 2.15

Rectangle {
    id: sysSetting
    x: -11
    y: -11
    visible: nowIndex == 5 ? true : false
    color: "#ffffff"
    anchors.left: rectangle.right
    anchors.right: parent.right
    anchors.top: parent.top
    anchors.bottom: parent.bottom
    anchors.topMargin: 0
    onVisibleChanged: {
        showAnim.stop()
        showAnim.start()}
        PropertyAnimation {
        id:showAnim
        target: sysSetting
         properties:"opacity"
         from:0
         to:1
         duration : 500
    }
    Flickable {
        anchors.fill: parent
        contentWidth: parent.width
        contentHeight: rectangle2.height
        Rectangle {
            x: 0
            y: 0
            width: 712
            height: 853
            color: "#00070303"
            Item {
                id: item5
                height: 100
                anchors.left: parent.left
                anchors.right: parent.right
                MLabelBlack {
                    id:reloginlabel
                    width: 135
                    height: 65
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: parent.left
                    anchors.leftMargin: 65
                    labelText: "系统控制"
                    anchors.verticalCenterOffset: 1
                }

                MbuttonBlue {
                    id: mbuttonBlue1
                    text: "重新登录"
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: reloginlabel.right
                    anchors.leftMargin: 50
                    onClicked: {
                        qmlCtrl.sendReloginSingle()
                    }
                }

                MbuttonBlue {
                    id: mbuttonBlue2
                    y: -3
                    text: "退出程序"
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: mbuttonBlue1.right
                    anchors.leftMargin: 20
                    onClicked: {
                        qmlCtrl.sendExitProgramSingle()
                    }
                }

                anchors.rightMargin: 0
                anchors.leftMargin: 0
            }


        }
        interactive: true
        ScrollBar.vertical: ScrollBar {
            width: 10
            anchors.right: parent.right
            policy: ScrollBar.AlwaysOn
            anchors.rightMargin: 0
        }
    }

    MbuttonBlue {
        x: 281
        y: 442
        text: "应用"
        onClicked: {
            qmlCtrl.setAudioDevice(audioListIndex)
            mLabelAudioDevice.labelText = qmlCtrl.getAudioDeviceName()
        }
    }


    anchors.rightMargin: 0
    anchors.leftMargin: 0
    anchors.bottomMargin: 0
}
