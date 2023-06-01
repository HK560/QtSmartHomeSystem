import QtQuick 2.15
import QtQuick.Controls 2.15

Item {
    id :root
    width: 500
    height: 300
    property alias funcEnableForAI: swforAI.checked
    property alias mbuttonValueBlue: mbuttonValueBlue
    property alias funcName: mLabelBlack.labelText
    property bool enable
    property int type: 1
    property string desc
    property int deviceIndex

    property int funcIndex
    property bool valueBool: false
    property double valueInt:0
    property string valueStr :"NULL"
    Rectangle {
        id: rectangle
        color: "#00ffffff"
        radius: 20
        border.color: "#484848"
        border.width: 5
        anchors.fill: parent

        MLabelBlack {
            id: mLabelBlack
            width: 182
            height: 47
            anchors.top: parent.top
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.topMargin: 5
            labelFontpointSize: 20
            labelText: "funcName"
        }

        Item {
            id: switchItem
            visible: root.type === 0
            //            visible:true
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: mLabelBlack.bottom
            anchors.bottom: parent.bottom
            anchors.leftMargin: 5
            anchors.bottomMargin: 5
            anchors.topMargin: 0

            PowerSwitch {
                width:93
                height:56
                id: enabledSwitch
                y: 0
                enabled: true

                visible: true
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.horizontalCenter
                anchors.leftMargin: 89
                anchors.horizontalCenterOffset: 135
                anchors.verticalCenterOffset: -45
                anchors.horizontalCenter: parent.horizontalCenter

                checked: valueBool

                //             Connections {
                //                 target: enabledSwitch

                //                     function onEnabledChanged() {
                //                     enabledSwitch.checked = (root.room.status !== Room.Off)
                //                 }

                //                     function onCheckedChanged() {
                // //                        root.room.power = enabledSwitch.checked
                //                 }
                //             }
            }

            MbuttonBlue {
                id: mbuttonSwitchBlue
                width: 118
                height: 40
                text: "应用"
                anchors.verticalCenter: parent.verticalCenter
                anchors.horizontalCenterOffset: 0
                anchors.verticalCenterOffset: 33
                anchors.horizontalCenter: enabledSwitch.horizontalCenter
                onClicked: {
                                        if(isCtrlEnabled()){
                                            qmlCtrl.setCtrlNow(true);
                    qmlCtrl.setDeviceFuncEnabledForAiByIndex(deviceIndex,funcIndex,funcEnableForAI);
                    qmlCtrl.setDeviceFuncValueByIndex(deviceIndex,funcIndex,funcName,enabledSwitch.checked ? "1":"0");
                qmlCtrl.setCtrlNow(false);
                                        }}
            }

            MLabelBlack {
                id: mLabelBlack3
                height: 151
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                anchors.right: parent.horizontalCenter
                anchors.leftMargin: 35
                anchors.rightMargin: 8
                labelText: desc
                labelWrapMode: 1
                labelColor: "#3f3f3f"
            }
        }

        Item {
            id: valueItem
            visible: root.type === 1
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: mLabelBlack.bottom
            anchors.bottom: parent.bottom
            anchors.leftMargin: 5
            anchors.bottomMargin: 5
            anchors.topMargin: 0

            MbuttonBlue {
                id: mbuttonValueBlue
                x: 310
                width: 118
                height: 46
                text: "应用"
                anchors.top: mLabelBlack1.bottom
                anchors.topMargin: 7
                anchors.horizontalCenterOffset: -1
                anchors.horizontalCenter: mLabelBlack1.horizontalCenter
                onClicked: {
//mmsInfo.showUpANIM.start();
                    if(isCtrlEnabled()){
                        qmlCtrl.setCtrlNow(true);
                        qmlCtrl.setDeviceFuncEnabledForAiByIndex(deviceIndex,funcIndex,funcEnableForAI);
                        qmlCtrl.setDeviceFuncValueByIndex(deviceIndex,funcIndex,funcName,Math.floor(dial.value*100).toString());
qmlCtrl.setCtrlNow(false);
                    }
                }
            }

            Dial {
                id: dial
                y: -11
                width: 184
                anchors.left: parent.left
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                value: root.valueInt/100
                anchors.bottomMargin: 10
                anchors.topMargin: 10
                anchors.leftMargin: 50

            }

            MLabelBlack {
                id: mLabelBlack1
                anchors.left: dial.right
                anchors.right: parent.right
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                labelWrapMode: 1
                anchors.topMargin: 41
                anchors.bottomMargin: 105
                anchors.rightMargin: 30
                anchors.leftMargin: 40
                labelText: desc
                labelColor: "#3f3f3f"
            }
        }

        Item {
            id: strItem
            visible: root.type === 2
            //            visible:true
            anchors.fill: parent
            anchors.leftMargin: 5

            MLineEdit1 {
                id: mLineEdit1
                height: 50
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.horizontalCenter
                anchors.right: parent.right
                anchors.leftMargin: 20
                anchors.rightMargin: 60
                textInputText: valueStr
                anchors.verticalCenterOffset: 0

                MouseArea {
                    id: mouseArea
                    anchors.fill: parent
                    onClicked: {
                        tmpInput.obj = mLineEdit1
                    tmpInput.visible =true
                    }
                }

            }


            MbuttonBlue {
                id: mbuttonBlue
                anchors.top: mLineEdit1.bottom
                anchors.horizontalCenterOffset: 0
                text: "应用"
                anchors.horizontalCenter: mLineEdit1.horizontalCenter
                anchors.topMargin: 30
                onClicked: {
                                        if(isCtrlEnabled()){
                                            qmlCtrl.setCtrlNow(true);
                    qmlCtrl.setDeviceFuncEnabledForAiByIndex(deviceIndex,funcIndex,funcEnableForAI);
                    qmlCtrl.setDeviceFuncValueByIndex(deviceIndex,funcIndex,funcName,mLineEdit1.textInputText);
                qmlCtrl.setCtrlNow(false);
                                        }}
            }

            MLabelBlack {
                id: mLabelBlack2
                anchors.left: parent.left
                anchors.right: mLineEdit1.left
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 59
                anchors.topMargin: 81
                anchors.rightMargin: 50
                labelText: desc
                anchors.leftMargin: 40
                labelWrapMode: 1
                labelColor: "#3f3f3f"
            }
        }

        PowerSwitch{
            id:swforAI
            x: 380
            y: -2
            width: 100
            height: 56
            anchors.right: parent.right
            anchors.rightMargin: 20

        }



    }
    TempTextInput{
        id:tmpInput
        visible: false
        anchors.fill: parent
        obj:mLineEdit1
    }
    MMessagebox{
        id:mmsInfo
        anchors.verticalCenter: parent.verticalCenter
        labelText: "正在同步信息，请稍后重试"
        width:300
        anchors.horizontalCenter: parent.horizontalCenter
        implicitWidth :textMetrics.width(labelText) + 2 * horizontalPadding
//        implicitHeight : textMetrics.height + 2 * verticalPadding



    }

    function isCtrlEnabled(){
       if(!qmlCtrl.getCtrlEnabled()){
           mmsInfo.showUpANIM.start();
        return false;
       }
       return true;
    }
}






