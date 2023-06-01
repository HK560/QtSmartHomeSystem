import QtQuick 2.15
import QtQuick.Controls 2.15
import "CreateObjects.js" as DevicePanelCreator
import QtQuick.Timeline 1.0
Item {
    id:ittm
    width: 1024
    height: 500
    onVisibleChanged: {
        showAnim.stop()
        showAnim.start()}
        PropertyAnimation {
        id:showAnim
        target: ittm
         properties:"opacity"
         from:0
         to:1
         duration : 500
    }
    Flickable {
        id: flickable
        anchors.fill: parent
        anchors.rightMargin: 0
        anchors.bottomMargin: 0
        anchors.leftMargin: 0
        anchors.topMargin: 0
        contentHeight: 0
        contentWidth: 20

        Grid {
            id: grid
            x: 30
            y: 30
            anchors.fill: parent
            anchors.leftMargin: 30
            anchors.bottomMargin: 30
            anchors.topMargin: 30
        }

        Rectangle {
            id: rectangle
            x: 405
            y: 45
            width: 214
            height: 237
            color: "#6da5ff"
            radius: 30

            MLabel2 {
                id: nowTemplb
                y: 0
                width: 193
                height: 123
                anchors.horizontalCenter: parent.horizontalCenter
                labelText: "27"
                labelFontpointSize: 60

            }

            MLabel2 {
                id:tempRangelb
                width: 152
                height: 32
                anchors.top: nowTemplb.bottom
                anchors.topMargin: -10
                anchors.horizontalCenter: parent.horizontalCenter
                labelFontpointSize: 20
                labelText: "8~27"
            }

            MLabel2 {
                id: locationlb
                x: 8
                y: 192
                width: 93
                height: 64
                anchors.bottom: parent.bottom
                labelFontpointSize: 15
                anchors.bottomMargin: -7
                labelText: "guanzoushi"
            }

            MLabel2 {
                id: unitlb
                x: 131
                y: 21

                width: 86
                height: 45
                anchors.left: nowTemplb.right
                anchors.top: nowTemplb.bottom
                anchors.topMargin: -105
                anchors.leftMargin: -77
                labelText: "°C"
            }

            Item {
                id: row
                y: 151
                width: 199
                height: 42
                anchors.horizontalCenterOffset: 0
                anchors.horizontalCenter: parent.horizontalCenter

                MLabel2 {
                    id: winglb
                    width: 107
                    height: 46
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: parent.left
                    anchors.leftMargin: 0
                    labelFontpointSize: 15
                    labelText: "dongfeng"
                }

                MLabel2 {
                    id: weatherlb
                    x: 123
                    width: 100
                    height: 81
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.right: parent.right
                    anchors.rightMargin: 0
                    labelFontpointSize: 20
                    labelText: "qing"
                }
            }

            MouseArea {
                id: mouseArea
                anchors.fill: parent
                onClicked: {
                    weatherInfoDetail.visible = true
                }
            }
        }

        Rectangle {
            id: rvRectangle
            x: 280
            y: 300
            width: 460

            height: 120
            color: "#7caaf4"
            radius: 30

            SwipeView {
                id: rvSwipeView
                anchors.fill: parent
                interactive: true
                opacity:1
                clip: true
                Timer {
                        interval: 3000  // 5秒
                        running: true
                        repeat: true
                        onTriggered: {
                            var currentIdx = rvSwipeView.currentIndex
                                        var nextIdx = (currentIdx + 1) % rvSwipeView.count

                                        // 将当前项目的透明度逐渐变为0，然后切换到下一个项目并将其透明度逐渐变为1
//                                        rvSwipeView.opacity = 0
                            rvSwipeView.currentIndex = nextIdx
//                                        rvSwipeView.opacity = 1
                                        }
                }
//                wrap: true
//                DeviceRvPanel{
//                    rvValue: "1"

//                }
//                DeviceRvPanel{
//                    rvValue: "2"
//                }
//                DeviceRvPanel{
//                    rvValue: "3"
//                }
                Behavior on opacity {
                                NumberAnimation {
                                    duration: 100  // 0.5秒
                                }
                }
            }

            MLabel2 {
                id: mLabel2
                visible: false
                anchors.fill: parent
                labelText: "暂无来自被控设备的信息"
            }

        }
    }

    WeatherInfoDetail{
        id :weatherInfoDetail
        visible: false

    }

    Connections{
        target: qmlCtrl;
        function onWeatherInfoChanged(){
            console.log("qml get weatherinfo");
            nowTemplb.labelText =  qmlCtrl.getWeatherNowInfo(2);
            tempRangelb.labelText =  qmlCtrl.getWeatherInfo(2,0);
            locationlb.labelText = qmlCtrl.getWeatherNowInfo(1);
            winglb.labelText = qmlCtrl.getWeatherInfo(4,0);
            weatherlb.labelText = qmlCtrl.getWeatherInfo(3,0);
        }
    }

    Timeline {
        id: timeline
        animations: [
            TimelineAnimation {
                id: timelineAnimation
                duration: 1000
                running: true
                loops: 1
                to: 1000
                from: 0
            }
        ]
        startFrame: 0
        enabled: true
        endFrame: 1000
    }

    Component.onCompleted:{

        console.log("qml get weatherinfo");
        nowTemplb.labelText =  qmlCtrl.getWeatherNowInfo(2);
        tempRangelb.labelText =  qmlCtrl.getWeatherInfo(2,0);
        locationlb.labelText = qmlCtrl.getWeatherNowInfo(1);
        winglb.labelText = qmlCtrl.getWeatherInfo(4,0);
        weatherlb.labelText = qmlCtrl.getWeatherInfo(3,0);

        DevicePanelCreator.destoryAllRvDevicePanel();
        DevicePanelCreator.createALLRvDevicePanel(rvSwipeView);
        if(rvSwipeView.count==0){
            mLabel2.visible = true
        }else{
            mLabel2.visible = false
        }
        updateStatusTimer.start();

    }
    Timer {
        id:updateStatusTimer
            interval: qmlCtrl.udpSendCycleTime *1000 // 5秒
//            running: true
            repeat: true
            onTriggered: {
                console.log("update status");
                DevicePanelCreator.destoryAllRvDevicePanel();
                DevicePanelCreator.createALLRvDevicePanel(rvSwipeView);
                if(rvSwipeView.count==0){
                    mLabel2.visible = true
                }else{
                    mLabel2.visible = false
                }
            }
    }

}
