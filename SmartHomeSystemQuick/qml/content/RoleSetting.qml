import QtQuick 2.15
import QtQuick.Controls 2.15

Rectangle {
    id: roleSetting
    x: -5
    y: -5
    //                    visible: true
    visible: nowIndex == 2 ? true : false
    property alias unbannedListVieww: unbannedListView
    color: "#ffffff"
    anchors.left: rectangle.right
    anchors.right: parent.right
    anchors.top: parent.top
    anchors.bottom: parent.bottom
    anchors.leftMargin: 0
    anchors.bottomMargin: 0
    anchors.topMargin: 0
    anchors.rightMargin: 0
        property int choosenUserIndex: 0
    onVisibleChanged: {
        showAnim.stop()
        showAnim.start()}
        PropertyAnimation {
        id:showAnim
        target: roleSetting
         properties:"opacity"
         from:0
         to:1
         duration : 500
    }
    Flickable {
        anchors.fill: parent
        contentWidth: parent.width
        interactive: true
        contentHeight: rectangle2.height
        Rectangle {
            id:roleSetting2
            x: 0
            y: 0
            width: 712
            height: 853
            color: "#00070303"
            property int choosenUserIndex

            MLabelBlack {
                id: mLabelBlack3
                width: 100
                height: 20
                anchors.top: parent.top
                labelText: "选择用户进行设置"
                anchors.topMargin: 20
                anchors.horizontalCenter: parent.horizontalCenter
            }

            Rectangle {
                id: rectangleList1
                y: 98
                width: 206
                height: 300
                color: "#36ffffff"
                radius: 30
                border.color: "#68c5e1"
                border.width: 3
                anchors.top: mLabelBlack3.bottom
                anchors.horizontalCenterOffset: -239
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.topMargin: 70
                ListView {
                    id: userlistView
                    height: 297
                    clip: true
                    anchors.left: parent.left
                    anchors.right: parent.right
                    //                            anchors.top: itemAudioDevice.bottom
                    anchors.rightMargin: 20
                    anchors.leftMargin: 20
                    anchors.topMargin: 20
                    //                            model: ["shit", "fk"]
                    model:qmlCtrl.getUserNameList()
                    delegate: userDelegate
                    focus: true;
                }

                MLabelBlack {
                    id: mLabelBlack
                    anchors.top: parent.top
                    labelText: "用户列表"
                    labelColor: "#40a7e3"
                    anchors.topMargin: -15
                    anchors.horizontalCenter: parent.horizontalCenter
                }

            }

            Rectangle {
                id: rectangleList2
                x: -1
                y: 97
                width: 206
                height: 300
                color: "#36ffffff"
                radius: 30
                border.color: "#68c5e1"
                border.width: 3
                anchors.top: mLabelBlack3.bottom
                anchors.topMargin: 70
                anchors.horizontalCenter: parent.horizontalCenter
                ListView {
                    id :bannedListView
                    height: 297
                    anchors.left: parent.left
                    anchors.right: parent.right
                    //                                anchors.top: itemAudioDevice.bottom
                    anchors.topMargin: 20
                    anchors.rightMargin: 20
                    clip: true
                    delegate: bannedDelegate
                    model: qmlCtrl.getUserBannedDeviceList(choosenUserIndex)
                    anchors.leftMargin: 20
                    focus: true
                }
                MLabelBlack {
                    id: mLabelBlack1
                    anchors.top: parent.top
                    labelText: "已禁用设备"
                    labelColor: "#40a7e3"
                    anchors.topMargin: -15
                    anchors.horizontalCenter: parent.horizontalCenter
                }

                anchors.horizontalCenterOffset: 0
            }

            Rectangle {
                id: rectangleList3
                x: -5
                y: 93
                width: 206
                height: 300
                color: "#36ffffff"
                radius: 30
                border.color: "#68c5e1"
                border.width: 3
                anchors.top: mLabelBlack3.bottom
                anchors.topMargin: 70
                anchors.horizontalCenter: parent.horizontalCenter
                ListView {
                    id:unbannedListView
                    height: 297
                    anchors.left: parent.left
                    anchors.right: parent.right
                    //                                anchors.top: itemAudioDevice.bottom
                    anchors.topMargin: 20
                    anchors.rightMargin: 20
                    clip: true
                    delegate: unbannedDelegate
                    model: qmlCtrl.getUserUnbannedDeviceList(choosenUserIndex)
                    anchors.leftMargin: 20
                    focus: true
                }
                MLabelBlack {
                    id: mLabelBlack4
                    anchors.top: parent.top
                    labelText: "未禁用设备"
                    labelColor: "#40a7e3"
                    anchors.topMargin: -15
                    anchors.horizontalCenter: parent.horizontalCenter
                }

                anchors.horizontalCenterOffset: 232
            }

        }




        Component {
            id: userDelegate
            Item {
                id: wrapperUser
                width: userlistView.width
                height: 50
                MouseArea {
                    anchors.fill: parent;
                    onClicked: {
                        console.log("nowuserindex%d",index)
                        wrapperUser.ListView.view.currentIndex = index;
                        //                        qmlCtrl.setAudioDevice(index)
                        choosenUserIndex = index
                        bannedListView.model = qmlCtrl.getUserBannedDeviceList(choosenUserIndex)
                        unbannedListView.model = qmlCtrl.getUserUnbannedDeviceList(choosenUserIndex)

                        //                                        console.log(userlistView.model.at(index).modelData)
                    }
                }
                Row {
                    id: row
                    anchors.left: parent.left
                    anchors.right: parent.right
                    anchors.rightMargin: 0
                    anchors.verticalCenter: parent.verticalCenter
                    spacing: 10
                    Rectangle {
                        id:userRectangle
                        width: parent.width/2
                        anchors.left: parent.left
                        anchors.leftMargin: 10
                        MLabel2 {
                            labelText: modelData
                            labelHorizontalAlignment: Text.AlignLeft
                            anchors.fill: parent ; anchors.leftMargin: 20;labelColor: index === userlistView.currentIndex ? "#40a7e3" : "#979797"}
                    }
                }
            }
        }

        Component {
            id: bannedDelegate
            Item {
                id: wrapperUser1
                width: bannedListView.width
                height: 50
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        wrapperUser1.ListView.view.currentIndex = index;
                        qmlCtrl.removeBannedDevice(choosenUserIndex, index);
                        unbannedListVieww.model = qmlCtrl.getUserUnbannedDeviceList(choosenUserIndex)
                        bannedListView.model = qmlCtrl.getUserBannedDeviceList(choosenUserIndex);
                        //                                                roleSetting2.rectangleList3.unbannedListView.model = qmlCtrl.getUserUnbannedDeviceList(choosenUserIndex)

                    }
                }

                Row {
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: parent.left
                    anchors.right: parent.right
                    spacing: 10
                    Rectangle {
                        width: parent.width/2
                        anchors.left: parent.left
                        MLabel2 {
                            anchors.fill: parent
                            labelText: modelData
                            labelColor: index === userlistView.currentIndex ? "#40a7e3" : "#979797"
                            anchors.leftMargin: 20
                            labelHorizontalAlignment: Text.AlignLeft
                        }
                        anchors.leftMargin: 10
                    }
                    anchors.rightMargin: 0
                }
            }
        }

        Component {
            id:unbannedDelegate
            Item {
                id:wrapperUser2
                width: unbannedListView.width
                height: 50
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        wrapperUser2.ListView.view.currentIndex = index;
                        //                        qmlCtrl.setAudioDevice(index)
//                        audioListIndex = index
                        qmlCtrl.addBannedDevice(choosenUserIndex, index)
                        bannedListView.model = qmlCtrl.getUserBannedDeviceList(choosenUserIndex)
                        unbannedListView.model = qmlCtrl.getUserUnbannedDeviceList(choosenUserIndex)

                    }
                }

                Row {
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: parent.left
                    anchors.right: parent.right
                    spacing: 10
                    Rectangle {
                        width: parent.width/2
                        anchors.left: parent.left
                        MLabel2 {
                            anchors.fill: parent
                            labelText: modelData
                            labelColor: index === userlistView.currentIndex ? "#40a7e3" : "#979797"
                            anchors.leftMargin: 20
                            labelHorizontalAlignment: Text.AlignLeft
                        }
                        anchors.leftMargin: 10
                    }
                    anchors.rightMargin: 0
                }
            }
        }
        ScrollBar.vertical: ScrollBar {
            width: 10
            anchors.right: parent.right
            anchors.rightMargin: 0
            policy: ScrollBar.AlwaysOn
        }
    }

    MbuttonBlue {
        x: 281
        y: 442
        text: "应用"
        onClicked: {
            qmlCtrl.updateBannedDeviceToDB()
        }
    }

    Rectangle {
        id: banNormalUser
                                        visible: false
//        visible: ! qmlCtrl.getNowUserRoleIsAdmin()

        color: "#ffffff"
        anchors.fill: parent

        MLabelBlack {
            id: mLabelBlack2
            width: 134
            height: 66
            visible: true
            anchors.verticalCenter: parent.verticalCenter
            labelText: "非管理员，无法操作"
            anchors.horizontalCenter: parent.horizontalCenter
        }

        MouseArea {
            id: mouseArea
            anchors.fill: parent
        }
    }
}
