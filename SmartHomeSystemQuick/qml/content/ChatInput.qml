import QtQuick 2.15
import QtQuick.Controls 2.15

Item {
    id: chatInput
    width: parent.width
    height: 50
    property alias inputFieldText: mLineEdit1.textInputText

//    Rectangle {
//        color: "#ffffff"
//        width: parent.width
//        height: parent.height
//        border.width: 1
//        border.color: "#cccccc"
//        radius: 5
//        anchors.centerIn: parent
//    }
    property bool recording: false
        property string filePath: "audio.wav" // 音频文件保存路径
    Timer {
            id: timer
            interval: 30000 // 10秒后自动松开按钮
            onTriggered: {
                console.log("out of length limit")
                button.released(Qt.LeftButton)
            }
        }

    TextField {
        id: inputField
        width: parent.width - 80
        height: parent.height
        visible: false
        anchors.left: parent.left
        anchors.leftMargin: 10
        anchors.verticalCenter: parent.verticalCenter
        font.pixelSize: 16
        hoverEnabled: true
        placeholderText: "Type your message here..."
        onAccepted: {
            submit()
        }
    }


    MLineEdit1 {
        id: mLineEdit1
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: sttbtn.right
        anchors.right: refresh_cw_icon.left
        textInputText: ""
        anchors.rightMargin: 10
        anchors.leftMargin: 10
        //        textInputWrapMode:Text.WordWrap

//        MbuttonBlue {
//            id: clearBtn
//            x: 42
//            y: 5
//            width: 120
//            height: 40
//            visible: false
//            text: "清除会话"
//            anchors.verticalCenter: parent.verticalCenter
//            anchors.right: sendBtn.left
//            anchors.rightMargin: 10
//        }
        //        placeholderText: "Type your message here..."
    }


    STTVbutton{
        id:sttbtn
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.topMargin: 0
        anchors.bottomMargin: 0
        anchors.leftMargin: 0
        flag:0

    }

    Connections{
        target: sttbtn
        function onGetResult(message){
            mLineEdit1.textInputText= message
        }
    }

//    Image {
//        id: mic
//        y: 0
//        width: 50


//        height: 50
//        anchors.verticalCenter: parent.verticalCenter
//        anchors.left: parent.left
//        transformOrigin: Item.Center
//        scale: 1
//        source: "images/icon/mic.png"
//        anchors.leftMargin: 10
//        fillMode: Image.PreserveAspectFit

//        MouseArea {
//            id: button
//            anchors.fill: parent

//            onPressed: {
//                if (!recording) {
//                    //                           startRecording(filePath)
//                    qmlCtrl.startRecordAudio()
//                    recording = true
//                    console.log("start Record")
//                    timer.start()
//                }
//                scaleAnimation.to = 0.8 // 缩小80%
//                scaleAnimation.duration = 100
//                scaleAnimation.target = mic// 设置动画时长为200毫秒
//                scaleAnimation.start()
//            }
//            onReleased: {
//                if (recording) {
//                    //                            stopRecording()
//                    qmlCtrl.stopRecordAudio()
//                    recording = false
//                    console.log("stop Record")
//                    timer.stop()
//                }
//                scaleAnimation.to = 1 // 恢复原本大小
//                scaleAnimation.duration = 100
//                scaleAnimation.target = mic// 设置动画时长为200毫秒
//                scaleAnimation.start()
//            }
//            PropertyAnimation  {
//                id: scaleAnimation
//                target: mic
//                property: "scale"
//            }
//        }
//    }
//    Connections{
//        target: qmlCtrl
//        function onAudioRecognizerResultGet(resultText){
//            inputFieldText = resultText
//        }

//    }

    MbuttonBlue {
        id: sendBtn
        x: 190
        y: 7
        width: 100

        height: 45


        text: "发送"
        anchors.verticalCenter: parent.verticalCenter
        anchors.right: parent.right
        anchors.rightMargin: 10
        onClicked: {
            submit()
        }
    }



    Image {
        id: refresh_cw_icon
        x: 246
        anchors.verticalCenter: parent.verticalCenter
        anchors.right: sendBtn.left
        source: "images/icon/refresh_cw_icon.png"
        anchors.rightMargin: 10
        fillMode: Image.PreserveAspectFit

        MouseArea {
            id: mouseArea
            anchors.fill: parent
            onClicked: {
                refresh()
            }
        }
    }


    Connections{
        target: qmlCtrl
        function onRefreshChatGptHistory(){
//            console.log("")
           refresh()
        }
    }


    signal refresh()
    signal submit()
}
