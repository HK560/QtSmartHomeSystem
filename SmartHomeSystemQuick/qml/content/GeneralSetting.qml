import QtQuick 2.15
import QtQuick.Controls 2.15

Rectangle {
    id: generalSetting
    x: -1
    y: -1
//                    visible: true
    visible: nowIndex == 1 ? true : false
    color: "#ffffff"
    anchors.left: rectangle.right
    anchors.right: parent.right
    anchors.top: parent.top
    anchors.bottom: parent.bottom
    anchors.bottomMargin: 0
    anchors.leftMargin: 0
    anchors.topMargin: 0
    anchors.rightMargin: 0
    onVisibleChanged: {
        showAnim.stop()
        showAnim.start()}
        PropertyAnimation {
        id:showAnim
        target: generalSetting
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
            id:rectangle2
            x: 0
            y: 0
            width: 712
            height: 600
            color: "#00070303"
            Column {
                anchors.fill: parent
                Item {
                    id: item1
                    height: 100
                    anchors.left: parent.left
                    anchors.right: parent.right
                    anchors.leftMargin: 0
                    anchors.rightMargin: 0
                    MLabelBlack {
                        id:labelUdp
                        x: 126
                        width: 135
                        height: 65
                        anchors.verticalCenter: parent.verticalCenter
                        labelText: "UDP广播周期"
                        anchors.verticalCenterOffset: 1
                    }
                    MSpinBox {
                        id: udpSendCycleTime
                        width: 150
                        height: 50
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.left: labelUdp.right
                        anchors.leftMargin: 160
                        value: qmlCtrl.udpSendCycleTime
                    }
                }

                Item {
                    id: item2
                    height: 100
                    anchors.left: parent.left
                    anchors.right: parent.right
                    anchors.leftMargin: 0
                    anchors.rightMargin: 0
                    MLabelBlack {
                        id:lockScreenLabel
                        x: 126
                        width: 135
                        height: 65
                        anchors.verticalCenter: parent.verticalCenter
                        labelText: "无操作锁屏时间(s)"
                        anchors.verticalCenterOffset: 1
                    }

                    MSpinBox {
                        id: screenLockTimeout
                        width: 150
                        height: 50
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.left: lockScreenLabel.right
                        anchors.leftMargin: 160
                        value: qmlCtrl.lockScreenTimeout
                    }
                }
                Item {
                    id: item4
                    height: 100
                    anchors.left: parent.left
                    anchors.right: parent.right
                    anchors.leftMargin: 0
                    anchors.rightMargin: 0



                    ListModel {
                        id: piccModel
                        ListElement {
                            fileName:"shit"
                        }
                    }

                    MLabelBlack {
                        id: mLabelBlack1
                        width: 169
                        height: 50
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.left: parent.left
                        anchors.leftMargin: 100
                        labelText: "锁屏壁纸"
                    }

                    MComboxBox {
                        id: combo
                        width: 200
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.left: mLabelBlack1.right
                        anchors.leftMargin: 120
                        currentIndex: qmlCtrl.getImageIndexfromName()
                        model:qmlCtrl.getImagesList()
                        //                                        model:piccModel
                        //                                        placeholderText: "Select an image file..."
                    }



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
            qmlCtrl.udpSendCycleTime = udpSendCycleTime.value;
            qmlCtrl.lockScreenTimeout = screenLockTimeout.value;
            qmlCtrl.setImageNameFromIndex(combo.currentIndex);
        }
    }
}
