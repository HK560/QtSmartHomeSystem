import QtQuick 2.15
import QtQuick.Controls 2.15

Item {
    width: 1024
    height: 500
    property bool recording: false
        property string filePath: "audio.wav" // 音频文件保存路径
    Timer {
            id: timer
            interval: 5000 // 10秒后自动松开按钮
            onTriggered: {
                button.released(Qt.LeftButton)
            }
        }
    MLabelBlack {
        id: mLabelRecognizedResult
        x: 305
        y: 273
    }

    Image {
        id: mic
        x: 678
        y: 173
        width: 200
        height: 200
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

    MbuttonBlue {
        id: mbuttonBlue
        x: 500
        y: 351
        text: "开始录制"
        onClicked: {
                if (mbuttonBlue.text === "开始录制") {
                    qmlCtrl.startRecordAudio()
                    mbuttonBlue.text = "停止录制";
                } else {
                    qmlCtrl.stopRecordAudio()
                    mbuttonBlue.text = "开始录制";
                }
    }

    }
    Connections{
        target: qmlCtrl
        function onAudioRecognizerResultGet(resultText){
            mLabelRecognizedResult.labelText = resultText
        }

    }
}
