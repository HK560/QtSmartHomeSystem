

/*
This is a UI file (.ui.qml) that is intended to be edited in Qt Design Studio only.
It is supposed to be strictly declarative and only uses a subset of QML. If you edit
this file manually, you might introduce QML code that is not supported by Qt Design Studio.
Check out https://doc.qt.io/qtcreator/creator-quick-ui-forms.html for details on .ui.qml files.
*/
import QtQuick 2.15
import QtQuick.Controls 2.15

import QtQuick.Timeline 1.0
import QtGraphicalEffects 1.12

Rectangle {
    id: rectangle1
    width: 1024
    height: 600
    color: "#00ffffff"
    border.color: "#00ffffff"
    property alias toLoginANIM: toLoginANIM
    property bool isFinished: false
    property bool isLogin: false
    Rectangle {
        id: rectangle
        x: 44
        y: 109
        width: 359
        height: 385
        color: "#ffffff"
        radius: 31

        layer.enabled: true

        layer.effect: DropShadow {
            radius: 8
            samples: 17
            horizontalOffset: 0
            verticalOffset: 2
            spread: 0
        }
        MLabel {
            id: mLabel
            y: 25
            width: 113
            height: 50
            anchors.top: parent.top
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.topMargin: 0
            labelText: "用户登录"
        }

        MLineEdit1 {
            id: username
            x: 21
            width: 305
            height: 50
            anchors.top: mLabel.bottom
            anchors.topMargin: 20
            textInputText: "hk560"
        }

        MLineEdit1 {
            id: password
            textInputText: "1dsfsad"
            x: 21
            y: 146
            width: 305
            height: 50
            anchors.top: username.bottom
            anchors.topMargin: 20
        }

        Item {
            id: item1
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: password.bottom
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 19
            anchors.topMargin: 116
            anchors.rightMargin: 0
            anchors.leftMargin: 0

            MbuttonBlue {
                id: loginBtn
                width: 150
                text: "登录"
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.bottomMargin: 0
                anchors.topMargin: 0
                Connections {
                    target: loginBtn
                    function onClicked() {
                        loginBtn.text = "登录中..."
                        if (qmlCtrl.loginUser(username.textInputText,
                                              password.textInputText)) {
                            loginFailedLabel.visible = false
                            rectangle1.state = "logined"
                        } else {
                            loginFailedLabel.visible = true
                        }
                    }
                }

                MouseArea {
                    id: mouseArea
                    anchors.fill: parent
                    propagateComposedEvents: true

                    onPressed: mouse.accepted = false;
                    onReleased: mouse.accepted = false;
                    onClicked: mouse.accepted = false;
                    onEntered: {}
                    onExited: {}

                }
            }

            MbuttonBlue {
                id: faceLoginBtn
                x: 193
                width: 150
                visible: false
                text: "LoginWithFace"
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 0
                anchors.topMargin: 0
                Connections {
                    target: loginBtn
                    function onClicked() {
                        loginBtn.text = "fucked"
                    }
                }
            }
        }

        MLabel {
            id: loginFailedLabel
            x: 120
            y: 220
            width: 113
            height: 50
            anchors.top: parent.top
            anchors.topMargin: 0
            labelText: "登录失败"
            anchors.horizontalCenter: parent.horizontalCenter
        }
    }

    MLabel {
        id: loginSuccessLabel
        width: 113
        height: 50
        anchors.top: parent.top
        anchors.horizontalCenterOffset: 331
        anchors.topMargin: 232
        labelFontpointSize: 35
        labelColor: "#d5d5d5"
        labelText: "登录成功"
    }

    Timeline {
        id: timeline
        animations: [
            TimelineAnimation {
                id: toLoginANIM
                //                onFinished: rectangle1.state = "logined"
                running: false
                loops: 1
                duration: 1000
                to: 300
                from: 0
            }
        ]
        endFrame: 1000
        enabled: true
        startFrame: 0

        KeyframeGroup {
            target: rectangle
            property: "x"
            Keyframe {
                value: -376
                frame: 300
            }
        }

        KeyframeGroup {
            target: rectangle
            property: "y"
            Keyframe {
                value: 109
                frame: 300
            }
        }

        KeyframeGroup {
            target: rectangle
            property: "opacity"
            Keyframe {
                value: 1
                frame: 0
            }

            Keyframe {
                value: 0
                frame: 300
            }
        }

        KeyframeGroup {
            target: rectangle
            property: "width"
            Keyframe {
                value: 353
                frame: 0
            }
        }

        KeyframeGroup {
            target: loginFailedLabel
            property: "anchors.topMargin"
            Keyframe {
                value: 226
                frame: 0
            }
        }

        KeyframeGroup {
            target: loginFailedLabel
            property: "anchors.horizontalCenterOffset"
            Keyframe {
                value: 0
                frame: 0
            }
        }

        KeyframeGroup {
            target: loginFailedLabel
            property: "visible"
            Keyframe {
                value: false
                frame: 0
            }
        }

        KeyframeGroup {
            target: loginSuccessLabel
            property: "anchors.topMargin"
            Keyframe {
                value: 252
                frame: 0
            }

            Keyframe {
                value: 252
                frame: 300
            }
        }

        KeyframeGroup {
            target: loginSuccessLabel
            property: "anchors.horizontalCenterOffset"
            Keyframe {
                value: 331
                frame: 0
            }
        }

        KeyframeGroup {
            target: loginSuccessLabel
            property: "visible"
            Keyframe {
                value: true
                frame: 0
            }

            Keyframe {
                value: true
                frame: 300
            }
        }

        KeyframeGroup {
            target: loginSuccessLabel
            property: "opacity"
            Keyframe {
                value: 1
                frame: 300
            }

            Keyframe {
                value: 0
                frame: 0
            }
        }

        KeyframeGroup {
            target: loginSuccessLabel
            property: "x"
            Keyframe {
                value: 808
                frame: 0
            }

            Keyframe {
                value: 456
                frame: 300
            }
        }



        KeyframeGroup {
            target: busyIndicator
            property: "opacity"
            Keyframe {
                value: 1
                frame: 0
            }

            Keyframe {
                value: 0
                frame: 150
            }
        }

        KeyframeGroup {
            target: rectangle1
            property: "isFinished"
            Keyframe {
                value: false
                frame: 0
            }

            Keyframe {
                value: true
                frame: 300
            }
        }
    }

    LoadingIndicator{
        id:busyIndicator
        width: 200
        height: 200
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenterOffset: 170

        anchors.horizontalCenter: parent.horizontalCenter
    }

    states: [
        State {
            name: "logined"
            when: rectangle1.isLogin
            PropertyChanges {
                target: timeline
                currentFrame: 0
                enabled: true
            }
            PropertyChanges {
                target: timeline
                enabled: true
            }

            PropertyChanges {
                target: toLoginANIM
                running: true
            }
//            PropertyChanges {
//                target: timeline
//                currentFrame: 300
//            }
        }
    ]
}
