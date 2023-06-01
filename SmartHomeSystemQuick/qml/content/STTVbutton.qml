import QtQuick 2.15
import QtQuick.Controls 2.15

Item {
    id: item1
    width: 50
    height: 50
    visible: qmlCtrl.baiduApiEnable
    property int flag
    property bool recording: false
    Image {
        id: mic
        x: 17
        y: 0
        anchors.fill: parent


            transformOrigin: Item.Center
            scale: 1
            source: "images/icon/mic.png"
            fillMode: Image.PreserveAspectFit

            MouseArea {
                id: button
                anchors.fill: parent

                onPressed: {
                    if (!recording) {
                        //                           startRecording(filePath)
                        qmlCtrl.sttFlag = flag
                        qmlCtrl.startRecordAudio()
                        recording = true
                        console.log("start Record")
                        timer.start()
                    }
                    scaleAnimation.to = 0.8 // 缩小80%
                    scaleAnimation.duration = 100
                    scaleAnimation.target = mic// 设置动画时长为200毫秒
                    scaleAnimation.start()
                }
                onReleased: {
                    if (recording) {
                        //                            stopRecording()
//                        qmlCtrl.sttFlag =
                        qmlCtrl.stopRecordAudio()
                        recording = false
                        console.log("stop Record")
                        timer.stop()
                    }
                    scaleAnimation.to = 1 // 恢复原本大小
                    scaleAnimation.duration = 100
                    scaleAnimation.target = mic// 设置动画时长为200毫秒
                    scaleAnimation.start()
                }
                PropertyAnimation  {
                    id: scaleAnimation
                    target: mic
                    property: "scale"
                }
            }
        }
    Connections{
        target: qmlCtrl
        function onAudioRecognizerResultGet(resultText){
            console.log("now stt flag is",qmlCtrl.sttFlag,"get stt result",resultText)

            if(qmlCtrl.sttFlag == flag){
                getResult(resultText)
            }
        }

    }
    Timer {
        id: timer
        interval: 5000 // 10秒后自动松开按钮
        onTriggered: {
            button.released(Qt.LeftButton)
        }
    }
    signal getResult(string message)
}
