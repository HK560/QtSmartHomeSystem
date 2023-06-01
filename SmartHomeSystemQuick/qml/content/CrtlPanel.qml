import QtQuick 2.15
import QtQuick.Controls 2.15
import "CreateObjects.js" as DevicePanelCreator
Item {
    id: item1
    width: 1024
    height: 500
    onVisibleChanged: {
        showAnim.stop()
        showAnim.start()}
    PropertyAnimation {
        id:showAnim
        target: item1
        properties:"opacity"
        from:0
        to:1
        duration : 500
    }
    SwipeView {
        id: swipeView
        anchors.fill: parent
        anchors.rightMargin: 10
        orientation: Qt.Vertical
        anchors.leftMargin: 10
        anchors.bottomMargin: 10
        anchors.topMargin: 10
        spacing: 10


        Item{
            id: item2
            MbuttonBlue {
                id: mbuttonBlue
                text: "刷新"
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                anchors.topMargin: 200
                anchors.rightMargin: 200
                anchors.leftMargin: 200
                anchors.bottomMargin: 200
                onClicked: {
//                    qmlCtrl.sendUdpDcNow()

                    if(!isCtrlEnabled())
                        return
                    rectangle.visible = true
                    DevicePanelCreator.destoryAllDeviceCardObjects();
                    DevicePanelCreator.createAllDevices(swipeView);
                    qmlCtrl.updateDeviceCtrlDataList();
                    qmlCtrl.updateChatGptDeviceCtrlCommand();
                    swipeView.moveItem(swipeView.currentIndex,swipeView.count - 1);
                    swipeView.setCurrentIndex(0);
                    rectangle.visible = false
                }
            }
        }


    }
    PageIndicator {
        id: indicator
        height: 20
        anchors.verticalCenter: parent.verticalCenter
        anchors.right: parent.right
        anchors.rightMargin: 0

        count: swipeView.count
        currentIndex: swipeView.currentIndex

        z: 0
        rotation: -270
        hoverEnabled: true
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

    Component.onCompleted:{
        //        console.log("try creating object");

        ////        for(var i = 0; i< 3;i++){
        ////             FuncCtrlCreator.createFuncCtrlObjects("t2t", 1,0.5);
        ////        }


        //            console.log("try creating object");
        //            DevicePanelCreator.createAllDevices(swipeView);

    }

    Rectangle {
        visible: false
        id: rectangle
        color: "#632c2c2c"
        anchors.fill: parent
        onVisibleChanged: {
            showAnim2.stop()
            showAnim2.start()}
        PropertyAnimation {
            id:showAnim2
            target: rectangle
            properties:"opacity"
            from:0
            to:1
            duration : 500
        }
        LoadingIndicator{
            x: 437
            y: 175
            width: 150
            height: 150
            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter

        }

        MouseArea {
            id: mouseArea
            anchors.fill: parent
        }
    }
}
