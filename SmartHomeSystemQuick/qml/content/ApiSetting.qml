import QtQuick 2.15
import QtQuick.Controls 2.15

Rectangle {
    id: apiSetting
    x: 0
    y: 0
    visible: true
    //        visible: nowIndex == 3 ? true : false
    color: "#ffffff"
    border.color: "#ffffff"
    anchors.left: rectangle.right
    anchors.right: parent.right
    anchors.top: parent.top
    anchors.bottom: parent.bottom
    anchors.rightMargin: 0
    anchors.leftMargin: 0
    anchors.bottomMargin: 0
    anchors.topMargin: 0
    onVisibleChanged: {
        showAnim.stop()
        showAnim.start()}
        PropertyAnimation {
        id:showAnim
        target: apiSetting
         properties:"opacity"
         from:0
         to:1
         duration : 500
    }
    Flickable {
        anchors.fill: parent
        contentHeight: rectangle2.height
        contentWidth: parent.width
        ScrollBar.vertical: ScrollBar {
            width: 10
            anchors.right: parent.right
            anchors.rightMargin: 0
            policy: ScrollBar.AlwaysOn
        }
        Rectangle {
            id:rectangle2
            x: 0
            y: 0
            width: 712
            height: 900
            color: "#00070303"
            Column {
                anchors.fill: parent
                anchors.left: parent.left
                anchors.leftMargin: 20
                Item {
                    height: 100
                    anchors.left: parent.left
                    anchors.right: parent.right
                    anchors.rightMargin: 0
                    anchors.leftMargin: 0
                    MLabelBlack {
                        x: 126
                        width: 135
                        height: 65
                        anchors.verticalCenter: parent.verticalCenter
                        labelText: "启用AI助理"
                        anchors.verticalCenterOffset: 1
                    }

                    PowerSwitch {
                        id:aienableSW
                        x: 420
                        y: 25
                        width: 99
                        height: 58
                        checked: qmlCtrl.assistantEnable
                        onCheckedChanged: {
                            if(checked == false){
                            chatGPTenableSW.checked = checked
                            }
                        }
                    }
                }
                Item {
                    height: 100
                    anchors.left: parent.left
                    anchors.right: parent.right
                    anchors.rightMargin: 0
                    anchors.leftMargin: 0
                    MLabelBlack {
                        x: 126
                        width: 135
                        height: 65
                        anchors.verticalCenter: parent.verticalCenter
                        labelText: "启用Baidu TTS&STT Api"
                        anchors.verticalCenterOffset: 1
                    }

                    PowerSwitch {
                        id:baiduApienableSW
                        x: 420
                        y: 25
                        width: 99
                        height: 58
                        checked: qmlCtrl.baiduApiEnable
//                        onCheckedChanged: {
//                            if(checked == false){
//                            chatGPTenableSW.checked = checked
//                            }
//                        }
                    }
                }
                Item {
                    id: item8
                    height: 100
                    anchors.left: parent.left
                    anchors.right: parent.right
                    anchors.rightMargin: 0
                    anchors.leftMargin: 0
                    MLabelBlack {
                        id:labelTTS
                        width: 135
                        height: 65
                        anchors.horizontalCenter: parent.horizontalCenter
                        labelText: "百度 TTS&STT API Key"
                    }

                    MLineEdit1 {
                        id:baiduApiKeyEdit
                        x: 420
                        anchors.left: parent.left
                        anchors.right: parent.right
                        anchors.top: labelTTS.bottom
                        anchors.rightMargin: 20
                        anchors.leftMargin: 20
                        anchors.topMargin: 0
                        textInputText: qmlCtrl.baiduApiKey
                        readOnly: !baiduApienableSW.checked
                        textInput.validator: RegExpValidator {
                            regExp: /^[a-zA-Z0-9]*$/
                        }
                    }
                }

                Item {
                    id: item7
                    height: 100
                    anchors.left: parent.left
                    anchors.right: parent.right
                    anchors.rightMargin: 0
                    anchors.leftMargin: 0
                    MLabelBlack {
                        id:labeltts2
                        width: 135
                        height: 65
                        anchors.horizontalCenter: parent.horizontalCenter
                        labelText: "百度 TTS&STT API Secret Key"
                    }

                    MLineEdit1 {
                        id:baiduApiSecretEdit
                        x: 420
                        anchors.left: parent.left
                        anchors.right: parent.right
                        anchors.top: labeltts2.bottom
                        anchors.rightMargin: 20
                        anchors.leftMargin: 20
                        anchors.topMargin: 0
                        textInputText: qmlCtrl.baiduApiSecret
                        readOnly: !baiduApienableSW.checked
                        textInput.validator: RegExpValidator {
                            regExp: /^[a-zA-Z0-9]*$/
                        }
                    }
                }

                Item {
                    height: 100
                    anchors.left: parent.left
                    anchors.right: parent.right
                    anchors.rightMargin: 0
                    anchors.leftMargin: 0
                    MLabelBlack {
                        x: 126
                        width: 135
                        height: 65
                        anchors.verticalCenter: parent.verticalCenter
                        labelText: "启用OpenAI语言模型助理"
                        anchors.verticalCenterOffset: 1
                    }

                    PowerSwitch {
                        id:chatGPTenableSW
                        x: 420
                        y: 25
                        width: 99
                        height: 58
                        checked: qmlCtrl.chatGPTEnable
                        checkable: aienableSW.checked
                    }
                }

                Item {
                    id: item1
//                        id: item8
                    height: 100
                    anchors.left: parent.left
                    anchors.right: parent.right
                    anchors.rightMargin: 0
                    anchors.leftMargin: 0
                    MLabelBlack {
                        id:openApilabel
                        width: 135
                        height: 65
                        anchors.horizontalCenter: parent.horizontalCenter
                        labelText: "OpenAI API key"
                    }

                    MLineEdit1 {
                        id: openaiKeyEdit
                        x: 420
                        anchors.left: parent.left
                        anchors.right: parent.right
                        anchors.top: openApilabel.bottom
                        anchors.rightMargin: 20
                        anchors.leftMargin: 20
                        anchors.topMargin: 0
                        textInputText: qmlCtrl.openAiApiKey
                        readOnly: !chatGPTenableSW.checked
                        textInput.validator: RegExpValidator {
                            regExp: /^sk-[a-zA-Z0-9]+$/


                        }

//                        MouseArea {
//                            id: mouseArea
//                            anchors.fill: parent

//                            onClicked: {
//                            tempTextInput.obj = commandEdit
//                            tempTextInput.visible = true
//                            tempTextInput.mLineEdit.
//                            }
//                        }
                    }


                }
                Item {
                    id: item6
                    height: 100
                    anchors.left: parent.left
                    anchors.right: parent.right
                    anchors.rightMargin: 0


                    MLineEdit1 {
                        id: commandEdit
                        height: 50
                        anchors.left: parent.left
                        anchors.right: parent.right
                        anchors.top: chatgptCommandLabel.bottom
                        anchors.rightMargin: 20
                        anchors.leftMargin: 20
                        anchors.topMargin: 0
                        textInputText: qmlCtrl.chatgptCommandSetting
                        readOnly: !chatGPTenableSW.checked
                        STTVbutton{
                            id:sstVbuttonCommand
                            anchors.right: parent.right
                            anchors.top: parent.top
                            anchors.bottom: parent.bottom
                            anchors.bottomMargin: 10
                            anchors.topMargin: 10
                            anchors.rightMargin: 0
                            flag:1
                        }
                        MouseArea {
                            id: mouseArea
                            anchors.fill: parent

                            onClicked: {
                            tempTextInput.obj = commandEdit
                                tempTextInput.visible = true
                            }
                        }

                        Connections{
                            target: sstVbuttonCommand
                            function onGetResult(message){
                                commandEdit.textInputText= message
                            }
                        }


                    }

                    MLabelBlack {
                        id:chatgptCommandLabel
                        width: 200
                        height: 50
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.horizontalCenter: parent.horizontalCenter
                        labelText: "ChatGPT前置命令"

                    }


                    anchors.leftMargin: 0
                }
            }
        }
        interactive: true
    }

    MbuttonBlue {
        x: 281
        y: 442
        text: "应用"
        onClicked: {
                qmlCtrl.assistantEnable = aienableSW.checked
                qmlCtrl.baiduApiEnable = baiduApienableSW.checked
                qmlCtrl.baiduApiKey = baiduApiKeyEdit.textInputText
                qmlCtrl.baiduApiSecret = baiduApiSecretEdit.textInputText
                qmlCtrl.chatGPTEnable = chatGPTenableSW.checked
                qmlCtrl.openAiApiKey = openaiKeyEdit.textInputText
                qmlCtrl.chatgptCommandSetting = commandEdit.textInputText
                qmlCtrl.updateApiSettings()
                qmlCtrl.sendReloginSingle()
        }
    }

    TempTextInput {
        id: tempTextInput
        visible: false
        anchors.fill: parent
    }
}
