import QtQuick 2.15
import QtQuick.Controls 2.15

Rectangle {
    id: audioSetting
    x: -11
    y: -11
//                visible: true
    visible: nowIndex == 4 ? true : false
    color: "#ffffff"
    anchors.left: rectangle.right
    anchors.right: parent.right
    anchors.top: parent.top
    anchors.bottom: parent.bottom
    anchors.bottomMargin: 0
    anchors.rightMargin: 0
     property int audioListIndex
    onVisibleChanged: {
        showAnim.stop()
        showAnim.start()}
        PropertyAnimation {
        id:showAnim
        target: audioSetting
         properties:"opacity"
         from:0
         to:1
         duration : 500
    }
    Flickable {
        anchors.fill: parent
        ScrollBar.vertical: ScrollBar {
            width: 10
            anchors.right: parent.right
            anchors.rightMargin: 0
            policy: ScrollBar.AlwaysOn
        }
        Rectangle {
            id: rectangle3
            x: 0
            y: 0
            width: 712
            height: 853
            color: "#00070303"


            //                    property QStringList myStringList: ["Item 1", "Item 2", "Item 3"]

            Rectangle {
                id: rectangle1
                height: 300

                color: "#00363636"
                radius: 30
                border.color: "#40a7e3"
                border.width: 2
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.top: itemAudioDevice.bottom
                anchors.topMargin: 10
                anchors.rightMargin: 10
                anchors.leftMargin: 10

                ListView {
                    id: devicelistView
                    x: 10
                    clip:true
                    anchors.left: parent.left
                    anchors.right: parent.right
                    anchors.top: parent.top
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 20
                    anchors.rightMargin: 20
                    anchors.leftMargin: 20
                    anchors.topMargin: 20
                    model: qmlCtrl.getAudioDeviceList()
                    delegate: audioDeviceDelegate
                    focus: true;
                    currentIndex: -1
                }
            }

            Item {
                id:itemAudioDevice
                x: 10
                y: 0
                height: 100


                anchors.left: parent.left
                anchors.right: parent.right
                anchors.rightMargin: 0
                MLabelBlack {
                    id: labelAudio
                    width: 135
                    height: 50

                    anchors.horizontalCenter: parent.horizontalCenter
                    labelText: "当前音频输入设备"
                }

                MLabel {
                    id: mLabelAudioDevice
                    anchors.top: labelAudio.bottom
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.topMargin: 20
                    labelText: qmlCtrl.getAudioDeviceName()
                }


                anchors.leftMargin: 0
            }

        }
        contentWidth: parent.width
        contentHeight: rectangle2.height
        interactive: true
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

    Component {
        id: audioDeviceDelegate
        Item {
            id: wrapperAudio
            width: devicelistView.width
            height: 50
            MouseArea {
                anchors.fill: parent;
                onClicked: {
                    wrapperAudio.ListView.view.currentIndex = index;
                    //                        qmlCtrl.setAudioDevice(index)
                    audioListIndex = index
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
                    id:deviceeRectangle
                    width: parent.width/2
                    anchors.left: parent.left
                    anchors.leftMargin: 10
                    MLabel2 {
                        labelText: modelData
                        labelHorizontalAlignment: Text.AlignLeft
                        anchors.fill: parent ; anchors.leftMargin: 20;labelColor: index === devicelistView.currentIndex ? "#40a7e3" : "#979797"}
                }
            }
        }
    }
    anchors.leftMargin: 0
    anchors.topMargin: 0
}
