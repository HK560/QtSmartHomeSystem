// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0

import QtQuick 2.15
import QtQuick.Window 2.15
import UntitledProject 1.0
import QtQuick.Timeline 1.0

Window {
    id:root
    width: 1024
    height: 600

    //    visibility:Window.FullScreen
    //    flags: Qt.FramelessWindowHint
    Scale {
        xScale: 0.5
        yScale: 0.5
    }
    visible: true
    title: "UntitledProject"
    property bool sclocked: true

        StateGroup {
            id: stateGroup
            states: [
                State {
                    name: "State1"

                    PropertyChanges {
                        target: lockScreen
                        y: -600
                    }
                }
            ]
        }



        Timeline {
            id: timeline
            animations: [
                TimelineAnimation {
                    id: unlockScreenAnim
                    loops: 1
                    duration: 1000
                    running: false
                    to: 150
                    from: 0
                },
                TimelineAnimation {
                    id: lockScreenAnim
                    loops: 1
                    duration: 1000
                    running: false
                    to: 0
                    from: 150
                }
            ]
            endFrame: 1000
            startFrame: 0
            enabled: true

            KeyframeGroup {
                target: mainScreen
                property: "opacity"
                Keyframe {
                    frame: 0
                    value: 0
                }

                Keyframe {
                    frame: 150
                    value: 1
                }
            }
        }




        Timer {
            id: timeoutTimer
            //        interval: 1000 * 60 * 5 // 5 minutes
            interval: 1000 * qmlCtrl.lockScreenTimeout // 5 minutes
            repeat: true
            //        running: !locked
            onTriggered: {
                // Set the state to "timeout"
                //            root.state = "timeout"
                if (sclocked == false)
                {
                    lockScreenAnim.start();
                    sclocked = true;
                    running = false
                }

            }
        }




        Item {
            id: item1
            y: 0

            width: 1024
            height: 600
            opacity: 1
            visible: true

            //        Flickable {
            //            visible: true
            //            anchors.fill: parent
            //            interactive: true
            //            contentHeight: LockScreen.height
            //            contentWidth: LockScreen.height
            //            flickableDirection: Flickable.VerticalFlick
            LockScreen {
                //                id: lockScreen
                //                mouseArea.onClicked: {
                //                    unlockScreenAnim.start();
                //                }
            }
            //        }




            Component.onCompleted: {
                console.log("compilted");
                timeoutTimer.start();
            }


        }
        Screen01 {
            id: mainScreen
            width: 1024
            height: 600
            opacity: 1


        }
        MouseArea {

            id: mouseArea
            visible: true
            anchors.fill: parent
            propagateComposedEvents: true
            //        drag.active: true
            //        drag.target: parent
            //        drag.axis: Drag.XAndYAxis
            //        drag.minimumX: 0
            //        drag.maximumX: 0
            //        drag.minimumY: -300
            //        drag.maximumY: 0

            onPressed: {
                timeoutTimer.stop();
                timeoutTimer.start();
                mouse.accepted=false;
                if (sclocked == true)
                {
                    unlockScreenAnim.start();
                    sclocked = false;
                    timeoutTimer.start()
                }

                //            console.log( mouseArea.propagateComposedEvents);
            }
            onReleased: mouse.accepted = false;
            onClicked: mouse.accepted = false;
            onEntered: {}
            onExited: {}
            //        onReleased: {
            //            if(item1.y < -200 && sclocked == true){    //触发
            //                mouse.accepted=false;
            //                console.log("shit");
            //                console.log(sclocked);
            //                unlockScreenAnim.start();
            ////                mouseArea.propagateComposedEvents = true;
            //                sclocked = false;
            //                timeoutTimer.start()
            //            }
            //        }
            Component.onCompleted: {
                console.log("screenlocktimeout:", qmlCtrl.lockScreenTimeout)
            }
        }
        Component.onCompleted: {
            if(qmlCtrl.runInLinux()){
                root.visibility = Window.FullScreen
                root.flags=Qt.FramelessWindowHint
            }
        }

        Connections{
            target:qmlCtrl
            function onExitProgramSingle(){
                console.log("close qml");
                close();
            }
        }
    }
