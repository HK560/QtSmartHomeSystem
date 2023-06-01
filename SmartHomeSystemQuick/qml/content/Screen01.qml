

/*
This is a UI file (.ui.qml) that is intended to be edited in Qt Design Studio only.
It is supposed to be strictly declarative and only uses a subset of QML. If you edit
this file manually, you might introduce QML code that is not supported by Qt Design Studio.
Check out https://doc.qt.io/qtcreator/creator-quick-ui-forms.html for details on .ui.qml files.
*/
import QtQuick 2.15
import QtQuick.Controls 2.15
import UntitledProject 1.0
import QtQuick.Timeline 1.0

import QtQuick.Window 2.9


Rectangle {
    id: rectangle
    width: Constants.width
    height: 600
    color: "#00c2c2c2"
    border.color: "#ffffff"
    property alias _114: _114


            state: "tofirst"

            Rectangle {
                id: rectangle2
                color: "#ffffff"
                anchors.fill: parent
            }
            Image {
                id: _104454718_p0
                visible: false
                anchors.fill: parent
                source: "images/104454718_p0.jpg"
                fillMode: Image.PreserveAspectCrop
            }

            Image {
                id: _114
                x: 0
                y: 0
                width: 1024
                height: 600
                visible: false
                anchors.verticalCenter: parent.verticalCenter
                source: "images/114.jpg"
                anchors.horizontalCenterOffset: 0
                anchors.rightMargin: 0
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenterOffset: 0
                sourceSize.height: 600
                sourceSize.width: 1024
                fillMode: Image.Stretch
            }

            Rectangle {
                id: welcome
                width: 1024
                height: 600
                opacity: 0
                color: "#00ffffff"

                Button {
                    id: button
                    x: 793
                    y: 560
                    visible: false
                    text: qsTr("Press me")
                    icon.source: ""
                    highlighted: true
                    clip: false
                    flat: true
                    display: AbstractButton.TextOnly
                    focusPolicy: Qt.ClickFocus
                    checkable: true

                    Connections {
                        target: button
                        function onClicked()
                        {
                            animation.start()
                        }
                    }
                }

                MLabel {
                    id: label
                    width: 287
                    height: 204
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.horizontalCenterOffset: 1
                    anchors.horizontalCenter: parent.horizontalCenter
                    labelFontpointSize: 40
                    labelText: "智慧家庭管理系统"
//                    color: "#77f5f7"

                }



                Rectangle {
                    id: rectangle1
                    y: 347
                    width: 402
                    height: 200
                    visible: true
                    color: "#00ffffff"
                    anchors.horizontalCenter: parent.horizontalCenter

                    MLabelBlack {
                        anchors.verticalCenter: parent.verticalCenter
                        labelText: "欢迎使用智慧家庭管理系统"
                        anchors.horizontalCenter: parent.horizontalCenter


                    }
                }
            }



            Connections {
                target: mouseAreaLogin
                function onClicked()
                {
                    rectangle.state = "tologin"
                }
            }

//            Connections {
//                id: connectionsTologin
//                target: userLoginForm.toLoginANIM
//                enabled: false
//                function onFinished()
//                {
//                    console.log("bool is", userLoginForm.isFinished)
//                    if (userLoginForm.isFinished == true)
//                    {
//                        if (qmlCtrl.wifiStatus == true)
//                        {
//                            rectangle.state = "towifitomainmenu"
//                        } else {
//                        rectangle.state = "towificonnect"
//                    }
//                }
//            }
//        }




        Connections {
            id: connectionsToWificonnect
            target: wifiConnect.toConnectedANIM
            enabled: false
            function onFinished()
            {
                console.log("wificonnect finished")
                console.log("wifiStatus  is", qmlCtrl.wifiStatus)
                if (qmlCtrl.wifiStatus == true)
                {

                    rectangle.state = "tomainmenu"
                }
            }
        }



        Connections {
            id: connectionsToLoginSuccess
            target:qmlCtrl
            function onSecondInitFinished()
            {
                if (qmlCtrl.wifiStatus == true)
                {
                    rectangle.state = "towifitomainmenu"
                } else {
                rectangle.state = "towificonnect"

            }
            mainmenu.source ="Mainmenu.qml"
        }
    }



    Connections {
        id: connectionReLogin
        target:qmlCtrl
        function onReLoginSingle()
        {
            mainmenu.source =""
            userLoginForm.source=""
            userLoginForm.source ="UserLoginForm.qml"
            state = "toRelogin"
        }
    }




    Loader {
        id: userLoginForm
        x: 0
        y: 0
        visible: false
        source:"UserLoginForm.qml"
        MouseArea {
            id: mouseAreaLogin
            width: 1024
            height: 600
            visible: false
        }
    }


    Loader {
        id: mainmenu
        opacity: 1
        visible: false
    }


    WifiConnect {
        id: wifiConnect
        opacity: 0
        visible: false
        background: _114
    }


    states: [
        State {
            name: "tofirst"
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
                target: tofirstANIM
                running: true
            }
            PropertyChanges {
                target: timeline
                currentFrame: 200
                enabled: true
            }
        },
        State {
            name: "tologin"
            PropertyChanges {
                target: timeline
                currentFrame: 200
                enabled: true
            }
            PropertyChanges {
                target: timeline
                enabled: true
            }

            PropertyChanges {
                target: firstToLoginANIM
                running: true
            }
        },
        State {
            name: "toRelogin"
            PropertyChanges {
                target: timeline
                currentFrame: 400
                enabled: true
            }
            PropertyChanges {
                target: timeline
                enabled: true
            }

//            PropertyChanges {
//                target: firstToLoginANIM
//                running: true
//            }
        },
        State {
            name: "towificonnect"
            PropertyChanges {
                target: timeline
                currentFrame: 400
                enabled: true
            }
            PropertyChanges {
                target: timeline
                enabled: true
            }

            PropertyChanges {
                target: firstToLoginANIM
            }

            PropertyChanges {
                target: loginTowifiConnectANIM
                running: true
            }

            PropertyChanges {
                target: mainmenu
                x: 0
                y: 0
                width: 1920
                height: 1035
            }
        },
        State {
            name: "tomainmenu"
            PropertyChanges {
                target: timeline
                currentFrame: 500
                enabled: true
            }
            PropertyChanges {
                target: timeline
                enabled: true
            }

            PropertyChanges {
                target: wifiConnectToMainmenu
                running: true
            }
        },
        State {
            name: "towifitomainmenu"
            PropertyChanges {
                target: timeline
                currentFrame: 400
                enabled: true
            }
            PropertyChanges {
                target: timeline
                enabled: true
            }

            PropertyChanges {
                target: loginToMainmenu
                running: true
            }
        }
    ]

    Timeline {
        id: timeline
        animations: [
            TimelineAnimation {
                id: tofirstANIM
                loops: 1
                duration: 1500
                running: false
                to: 200
                from: 0
            },
            TimelineAnimation {
                id: firstToLoginANIM
                onFinished: rectangle.state = "tologin"
                duration: 1000
                running: false
                loops: 1
                to: 400
                from: 199
            },
            TimelineAnimation {
                id: loginTowifiConnectANIM
                loops: 1
                duration: 1000
                running: false
                to: 500
                from: 400
            },
            TimelineAnimation {
                id: wifiConnectToMainmenu
                duration: 1000
                loops: 1
                running: false
                to: 600
                from: 500
            },
            TimelineAnimation {
                id: loginToMainmenu
                duration: 1000
                loops: 1
                running: false
                to: 600
                from: 400
            }
        ]
        startFrame: 0
        enabled: true
        endFrame: 1000

        KeyframeGroup {
            target: rectangle1
            property: "x"
            Keyframe {
                value: 412
                frame: 200
            }

            Keyframe {
                value: 412
                frame: 41
            }
        }

        KeyframeGroup {
            target: rectangle1
            property: "y"
            Keyframe {
                value: 347
                frame: 200
            }

            Keyframe {
                value: 605
                frame: 41
            }
        }

        KeyframeGroup {
            target: rectangle1
            property: "opacity"
            Keyframe {
                value: 0
                frame: 41
            }

            Keyframe {
                value: 1
                frame: 200
            }
        }

        KeyframeGroup {
            target: label
            property: "x"
            Keyframe {
                value: 449
                frame: 200
            }
        }

        KeyframeGroup {
            target: label
            property: "y"
            Keyframe {
                value: 21
                frame: 200
            }
        }

        KeyframeGroup {
            target: label
            property: "opacity"
            Keyframe {
                value: 0
                frame: 0
            }

            Keyframe {
                value: 1
                frame: 200
            }
        }


//        KeyframeGroup {
//            target: loginBtn
//            property: "y"
//            Keyframe {
//                value: 644
//                frame: 0
//            }
//        }

        KeyframeGroup {
            target: welcome
            property: "opacity"
            Keyframe {
                value: 0
                frame: 400
            }

            Keyframe {
                value: 1
                frame: 200
            }
        }

        KeyframeGroup {
            target: welcome
            property: "visible"
            Keyframe {
                value: true
                frame: 200
            }

            Keyframe {
                value: false
                frame: 400
            }
        }

        KeyframeGroup {
            target: userLoginForm
            property: "visible"
            Keyframe {
                value: true
                frame: 200
            }

            Keyframe {
                frame: 500
                value: false
            }
        }

        KeyframeGroup {
            target: userLoginForm
            property: "opacity"
            Keyframe {
                value: 0
                frame: 200
            }

            Keyframe {
                value: 1
                frame: 400
            }

            Keyframe {
                frame: 500
                value: 0
            }
        }

        KeyframeGroup {
            target: mouseAreaLogin
            property: "visible"
            Keyframe {
                value: true
                frame: 200
            }

            Keyframe {
                value: false
                frame: 220
            }
        }

//        KeyframeGroup {
//            target: connectionsTologin
//            property: "enabled"
//            Keyframe {
//                value: false
//                frame: 200
//            }

//            Keyframe {
//                value: true
//                frame: 300
//            }
//        }

        KeyframeGroup {
            target: wifiConnect
            property: "visible"
            Keyframe {
                frame: 400
                value: true
            }

            Keyframe {
                frame: 0
                value: false
            }

            Keyframe {
                value: true
                frame: 500
            }

            Keyframe {
                value: false
                frame: 600
            }
        }

        KeyframeGroup {
            target: wifiConnect
            property: "opacity"
            Keyframe {
                frame: 400
                value: 0
            }

            Keyframe {
                frame: 500
                value: 1
            }
            Keyframe {
                frame: 600
                value: 0
            }
        }

        KeyframeGroup {
            target: mainmenu
            property: "visible"
            Keyframe {
                value: true
                frame: 500
            }
        }

        KeyframeGroup {
            target: mainmenu
            property: "opacity"
            Keyframe {
                value: 0
                frame: 500
            }

            Keyframe {
                value: 1
                frame: 600
            }
        }

        KeyframeGroup {
            target: connectionsToWificonnect
            property: "enabled"
            Keyframe {
                value: true
                frame: 500
            }
        }
    }


}



/*##^##
Designer {
    D{i:0}D{i:1}D{i:3;invisible:true}D{i:7}D{i:8}D{i:4}D{i:11}D{i:15}D{i:14}D{i:16}D{i:17}
}
##^##*/
