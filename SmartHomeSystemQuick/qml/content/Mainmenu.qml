import QtQuick 2.15
import QtQuick.Controls 2.15

Rectangle {
    id: rectangle1
    width: 1024
    height: 600
    color: "#ffffff"
    border.color: "#ffffff"
    property int menuIndex: bottombar.nowindex


    Rectangle {
        id: panel
        color: "#00ffffff"
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: bottombar.bottom
        anchors.bottom: bottombar.top
        anchors.rightMargin: 0
        anchors.leftMargin: 0
        anchors.bottomMargin: 0
        anchors.topMargin: 0

        CrtlPanel{
            visible: menuIndex === 1 ? true: false
        }

        StatusPanel{
            visible: menuIndex === 0 ? true: false
        }

        SettingPanel{
             visible: menuIndex === 3 ? true: false
        }

        ChatPannel{
            visible: menuIndex === 2 ? true: false
        }
    }
    Topbar {
        id: topbar
        height: 50
        x: 0
        y: 550
    }

    Bottombar {
        id: bottombar


    }

    MMessagebox{
        id:mmessagebox
        y: 445
        anchors.horizontalCenter: parent.horizontalCenter

    }

    Connections{
        target: qmlCtrl;
        function onProxyVaildChanged(status){
            console.log("qml get proxyStatus");
            if(status == true){
                mmessagebox.labelText = "代理连接成功";
                mmessagebox.showUpANIM.start();
            }else{
                mmessagebox.labelText = "代理连接失败"
                mmessagebox.showUpANIM.start();
            }
        }
    }

    Connections{
        target: qmlCtrl;
        function onSendMessageSingle(message){
            console.log("qml get message");

                mmessagebox.labelText = message;
                mmessagebox.showUpANIM.start();

        }
    }
}
