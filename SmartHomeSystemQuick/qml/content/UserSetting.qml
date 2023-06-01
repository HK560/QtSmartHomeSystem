import QtQuick 2.15
import QtQuick.Controls 2.15

Rectangle {
    id: userSetting
    visible: nowIndex == 0 ? true : false
    color: "#ffffff"
    border.color: "#ffffff"
    anchors.left: rectangle.right
    anchors.right: parent.right
    anchors.top: parent.top
    anchors.bottom: parent.bottom
    anchors.topMargin: 0
    anchors.bottomMargin: 0
    anchors.rightMargin: 0
    anchors.leftMargin: 0

    onVisibleChanged: {
        showAnim.stop()
        showAnim.start()}
        PropertyAnimation {
        id:showAnim
        target: userSetting
         properties:"opacity"
         from:0
         to:1
         duration : 500
    }
    Flickable {
        id: flickable
        interactive:true
        anchors.fill: parent

        contentWidth: parent.width
        contentHeight: rectangle2.height
        Rectangle {
            id: rectangle2
            x: 0
            y: 0
            width: 712
            height: 600

            color: "#00070303"

            Column {
                id: column
                anchors.fill: parent

                Item {
                    id: item2
                    height: 100
                    anchors.left: parent.left
                    anchors.right: parent.right
                    anchors.rightMargin: 0
                    anchors.leftMargin: 0

                    MLabelBlack {
                        id: mLabelBlack
                        x: 126
                        width: 135
                        height: 65
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.verticalCenterOffset: 1
                        labelText: "用户名"
                    }

                    MLineEdit1 {
                        id: userNameEdit
                        x: 420
                        y: 25
                        textInputText: ""
                    }
                }

                Item {
                    id: item3
                    height: 100
                    anchors.left: parent.left
                    anchors.right: parent.right
                    anchors.leftMargin: 0
                    MLabelBlack {
                        x: 126
                        width: 135
                        height: 65
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.verticalCenterOffset: 1
                        labelText: "密码"
                    }

                    MLineEdit1 {
                        id: userPasswordEdit

                        x: 420
                        y: 25
                        textInputText: ""
                    }
                    anchors.rightMargin: 0
                }
            }
        }
        ScrollBar.vertical: ScrollBar {
            width: 10
            anchors.right: parent.right
            anchors.rightMargin: 0 // adjust the anchor as suggested by derM
            policy: ScrollBar.AlwaysOn
        }
    }

    MbuttonBlue {
        id: mbuttonBlue
        x: 281
        y: 442
        text: "应用"
        onClicked: {
            qmlCtrl.updateNowUserName(userNameEdit.textInputText);
            qmlCtrl.updateNowUserPwd(userPasswordEdit.textInputText);

        }
    }


}
