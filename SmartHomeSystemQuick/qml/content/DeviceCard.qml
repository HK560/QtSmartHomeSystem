import QtQuick 2.15
import QtQuick.Controls 2.15
import "CreateObjects.js" as FuncCtrlCreator
Item {
    id: item1
    width: 1024
    height: 500
    property alias lockDevice: lockMask.visible
    property alias deviceIdName: deviceIdname.labelText
    property alias deviceName: mLabel.labelText
    property int deviceIndex

    Rectangle {
        id: rectangle
        color: "#ffffff"
        radius: 30
        anchors.fill: parent

        MLabel {
            id: mLabel
            width: 119
            height: 37
            anchors.left: parent.left
            anchors.top: parent.top
            anchors.leftMargin: 64
            labelText: "DeviceName"
            anchors.topMargin: 16
        }

        Image {
            id: pressedbgdown
            y: 190
            anchors.bottom: parent.bottom
            source: "assets/pressed-bg-down.png"
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottomMargin: 5
            fillMode: Image.PreserveAspectFit
        }

        Image {
            id: settings_gear_icon
            x: 413
            y: 16
            width: 48
            height: 37
            anchors.right: parent.right
            source: "images/icon/settings_gear_icon.png"
            anchors.rightMargin: 39
            fillMode: Image.PreserveAspectFit

            MouseArea {
                id: mouseArea
                anchors.fill: parent
            onClicked:  {
                settingMenu.visible=true

            }
            }
        }

        SwipeView {
            id: swipeView
            anchors.fill: parent
            anchors.bottomMargin: 20
            anchors.leftMargin: 20
            anchors.rightMargin: 20
            anchors.topMargin: 66
            spacing: 10
//            FuncCtrlPanel{
//                visible: true
////                anchors.fill: parent
//            }
//            FuncCtrlPanel{
//                visible: true
////                anchors.fill: parent
//            }


        }

        PageIndicator {
                id: indicator
                height: 20

                count: swipeView.count
                currentIndex: swipeView.currentIndex

                anchors.bottom: parent.bottom
                anchors.bottomMargin: 0
                anchors.horizontalCenter: parent.horizontalCenter
        }

        MLabelBlack {
            id: deviceIdname
            anchors.verticalCenter: mLabel.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter
            labelText: "idname"
            anchors.verticalCenterOffset: 0
            labelFontpointSize: 15

        }

        Image {
            id: refresh_cw_icon
            x: 886
            width: 32
            height: 37
            anchors.verticalCenter: settings_gear_icon.verticalCenter
            anchors.right: settings_gear_icon.left
            source: "images/icon/refresh_cw_icon.png"
            anchors.rightMargin: 15
            fillMode: Image.PreserveAspectFit

            MouseArea {
                id: mouseArea2
                anchors.fill: parent
                onClicked:{
                    FuncCtrlCreator.destoryAllDeviceFuncObjects();
                    FuncCtrlCreator.createAllFunc(swipeView,deviceIndex);
                }
            }
        }

        Rectangle {
            id: lockMask
            visible: true
            color: "#a6222222"
            radius: 30
            anchors.fill: parent

            MLabel2 {
                id: mLabel2
                anchors.fill: parent
                labelText: "此用户禁止使用该设备"
            }

            MouseArea {
                id: mouseArea3
                anchors.fill: parent
            }
        }
    }

    Rectangle {
        id: settingMenu
        visible: false
        color: "#7c383838"
        anchors.fill: parent

        MouseArea {
            id: mouseArea1
            anchors.fill: parent
            onClicked: {
            settingMenu.visible=false}
        }

        Rectangle {
            id: rectangle2
            width: 200
            height: 205
            color: "#ffffff"
            radius: 30
            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter

            MbuttonBlue {
                id: saveBtn
                x: 25
                text: "保存配置 "
                anchors.top: parent.top
                anchors.topMargin: 20
                onClicked:{
                    if(qmlCtrl.getCtrlEnabled()){
                    qmlCtrl.setCtrlNow(true);
                    qmlCtrl.saveDeviceSetting(deviceIndex);
                    qmlCtrl.setCtrlNow(false);
                    }

                }
            }

//            MbuttonBlue {
//                id: ignoredBtn
//                x: 25
//                y: 257
//                text: "隐藏"
//                anchors.bottom: parent.bottom
//                anchors.bottomMargin: 30
//                onClicked: {
//                qmlCtrl.setDeviceEnable(deviceIndex,false);
//                }
//            }

            MbuttonBlue {
                id: setNameBtn
                x: 25
                text: "设置备注名"
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 20
                onClicked: {
                    tempTextInput.visible = true
                }
            }
        }

    }


    TempTextInput{
        id:tempTextInput
        visible: false
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter

        mbuttonBlue.onClicked: {
            console.log(tempTextInput.inputText);
            deviceName = tempTextInput.inputText
            qmlCtrl.setDeviceName(deviceIndex,deviceName)
            mMessagebox.labelText = "设置备注名:"+mLabel.labelText
            mMessagebox.showUpANIM.start()
            //qmlctrl func
        }


    }

    MMessagebox {
        id: mMessagebox
        y: 450
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 29
        anchors.horizontalCenter: parent.horizontalCenter
    }

    Component.onCompleted:{
        console.log("try creating object");

//        for(var i = 0; i< 3;i++){
//             FuncCtrlCreator.createFuncCtrlObjects("t2t", 1,0.5);
//        }
        // qmlCtrl.readDeviceSetting(deviceIndex);
        FuncCtrlCreator.createAllFunc(swipeView,deviceIndex);
    }





}


