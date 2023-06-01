import QtQuick 2.15
import QtQuick.Controls 2.15

Rectangle {
    id: networkSetting
    x: 1024
    y: 0
    visible: nowIndex == 3 ? true : false
    color: "#ffffff"
    anchors.left: rectangle.right
    anchors.right: parent.right
    anchors.top: parent.top
    anchors.bottom: parent.bottom
    anchors.bottomMargin: 0
    onVisibleChanged: {
        showAnim.stop()
        showAnim.start()}
        PropertyAnimation {
        id:showAnim
        target: networkSetting
         properties:"opacity"
         from:0
         to:1
         duration : 500
    }
    Flickable {
        anchors.fill: parent
        interactive: true
        contentWidth: parent.width
        ScrollBar.vertical: ScrollBar {
            width: 10
            anchors.right: parent.right
            anchors.rightMargin: 0
            policy: ScrollBar.AlwaysOn
        }
        contentHeight: rectangle2.height
        Rectangle {
            x: 0
            y: 0
            width: 712
            height: 853
            color: "#00070303"
            Column {
                anchors.fill: parent
                Item {
                    height: 100
                    anchors.left: parent.left
                    anchors.right: parent.right
                    MLabelBlack {
                        x: 126
                        width: 135
                        height: 65
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.verticalCenterOffset: 1
                        labelText: "使用代理"
                    }

                    PowerSwitch {
                        id: usingProxySw
                        x: 420
                        y: 25
                        width: 99
                        height: 58
                        checked: qmlCtrl.enableProxy
                    }
                    anchors.leftMargin: 0
                    anchors.rightMargin: 0
                }

                Item {
                    height: 100
                    anchors.left: parent.left
                    anchors.right: parent.right
                    MLabelBlack {
                        x: 126
                        width: 135
                        height: 65
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.verticalCenterOffset: 1
                        labelText: "代理服务器地址(IPv4)"
                    }

                    MLineEdit1 {
                        id: proxyServerAddr
                        textInputText: qmlCtrl.proxyServerAddr
                        readOnly:!usingProxySw.checked
                        x: 420
                        y: 25
                        textInput.validator: RegExpValidator { regExp: /^((25[0-5]|2[0-4]\d|[01]?\d\d?)\.){3}(25[0-5]|2[0-4]\d|[01]?\d\d?)$/ }
                    }
                    anchors.leftMargin: 0
                    anchors.rightMargin: 0
                }
                Item {
                    height: 100
                    anchors.left: parent.left
                    anchors.right: parent.right
                    MLabelBlack {
                        x: 126
                        width: 135
                        height: 65
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.verticalCenterOffset: 1
                        labelText: "代理服务器端口"

                    }

                    MLineEdit1 {
                        id: proxyServerPort
                        textInputText: qmlCtrl.proxyServerPort
                        readOnly:!usingProxySw.checked
                        textInput.validator: RegExpValidator { regExp: /^([1-9]|[1-9]\d {1, 3}|[1-5]\d {4}|6[0-4]\d {3}|65[0-4]\d {2}|655[0-2]\d|6553[0-5])$/ }
                        x: 420
                        y: 25
                    }
                    anchors.leftMargin: 0
                    anchors.rightMargin: 0
                }
            }
        }
    }

    MbuttonBlue {
        x: 281
        y: 442
        text: "应用"
        onClicked: {
            qmlCtrl.enableProxy = usingProxySw.checked
            qmlCtrl.proxyServerAddr = proxyServerAddr.textInputText
            qmlCtrl.proxyServerPort = proxyServerPort.textInputText
            qmlCtrl.updateProxySetting()
        }

    }
    anchors.topMargin: 0
    anchors.leftMargin: 0
    anchors.rightMargin: 0
    Connections {
        target: qmlCtrl;
        function onProxyVaildChanged(status)
        {
            console.log("qml get proxyStatus");
            if (status == true)
            {
            }else {
                // connectStateLabel.labelText = "代理连接失败"
                usingProxySw.checked = false
            }
        }
    }

}
