import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.1


import QtGraphicalEffects 1.12
import QtQuick.Timeline 1.0
WifiConnectForm {
    id:wifiConnectForm
    width: 1024
    height: 600
    visible: true
    property alias toConnectedANIM: toConnectedANIM
    property variant background
    onVisibleChanged: {
        if(wifiConnectForm.visible == true){

            console.log("doing addwifimodel");
            wifiListModel.clear();
            var max = qmlCtrl.getWifiListSize();
            for(var i = 0; i<max;i++){
                addWifiModel(qmlCtrl.getWifiName(i),qmlCtrl.getWifiLevel(i));
            }
        }
        if (qmlCtrl.wifiStatus == true){
            wifiConnectForm.state = "connected";
        }
    }
    MMessagebox{
        id:messageboxInfo
        width: 200
        height: 38
        anchors.top: parent.top
        anchors.topMargin: 20
        anchors.horizontalCenterOffset: 0
        anchors.horizontalCenter: parent.horizontalCenter
    }

    Rectangle {
        id: rectangle
        x: 562
        y: 64
        width: 440
        height: 472
        color: "#32000000"
        radius: 30
        border.width: 0

//        FastBlur {
//            anchors.fill: parent
//            source: rectangle
//            focus: false
//            activeFocusOnTab: false
//            antialiasing: false
//            clip: true
//            transparentBorder: true
//            cached: false
//            radius: 32
//        }

        ListView {
            id: listView
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: parent.top
            // anchors.bottom: parent.bottom

            anchors.fill: parent
            anchors.rightMargin: 20
            anchors.leftMargin: 20
            // anchors.bottomMargin: 20
            anchors.topMargin: 20

            model: ListModel {
                id: wifiListModel
                ListElement {
                    wifiname: "Grey"
                    wifilevel: "1"
                }

                ListElement {
                    wifiname: "Red"
                    wifilevel: "2"
                }

                ListElement {
                    wifiname: "Blue"
                    wifilevel: "3"
                }

                ListElement {
                    wifiname: "Green"
                    wifilevel: "4"
                }
            }
            delegate: wifiDelegate
            highlight:Rectangle{
                id: highlight
                color: "#40a7e3"
                radius: 30
                border.width: 0

                ColorAnimation {
                    id: colorAnimation
                    target:highlight
                    from:"#00ffffff"
                    to: "#40a7e3"
                }
            }
            focus: true;
        }


        MbuttonBlue{
            id: wifireloadBtn
            text: "刷新"

            anchors.bottom: parent.bottom
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottomMargin: 20
            onClicked: {
                console.log("doing addwifimodel");
                wifiListModel.clear();
                var max = qmlCtrl.getWifiListSize();
                for(var i = 0; i<max;i++){
                    addWifiModel(qmlCtrl.getWifiName(i),qmlCtrl.getWifiLevel(i));
                }
            }
        }
    }



    Component {
        id: wifiDelegate
        Item {
            id: wrapper
            width: listView.width
            height: 50

            // 实现了鼠标点选高亮的效果
            MouseArea {
                anchors.fill: parent;
                onClicked: {
                    wrapper.ListView.view.currentIndex = index;
                    lineEditWifiName.textInputText = getWifiModelName(index);
                    lineEditWifiPwd.textInput.clear();

                }
            }

            // 内嵌三个Text对象，水平布局
            Row {
                id: row
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.rightMargin: 0
                anchors.verticalCenter: parent.verticalCenter
                spacing: 10


                Rectangle{
                    id:wifinameRectangle
                    width: parent.width/2
                    anchors.left: parent.left
                    anchors.leftMargin: 10
                    MLabel2{    labelText:wifiname
                        labelHorizontalAlignment: Text.AlignLeft
                        anchors.fill: parent}
                    // Text{
                    //     id: wifinameid
                    //     text: wifiname
                    //     anchors.fill: parent
                    //     horizontalAlignment: Text.AlignHCenter
                    //     verticalAlignment: Text.AlignVCenter
                    // }
                }
                Rectangle{
                    id:wifilevelRectangle

                    anchors.left: wifinameRectangle.right
                    anchors.right: parent.right
                    anchors.rightMargin: -10
                    anchors.leftMargin: 0
                    MLabel2{
                        id: wifilevelid
                        labelText: wifilevel
                        anchors.fill: parent
                        labelHorizontalAlignment: Text.AlignHCenter

                    }
                }

            }
        }
    }


    MLabel{
        id:connectSucees;
        opacity: 0
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
        labelText: "已连接到网络"
    }

    Rectangle {
        id: rectangle1
        x: 56
        y: 146
        width: 418
        height: 309
        color: "#ffffff"
        radius: 30

        layer.enabled: true

        layer.effect: DropShadow{
            radius: 8
            samples: 10
            horizontalOffset: 0
            verticalOffset: 0
            spread: 0
        }

        MLabel {
            id: connectWifiLabel
            y: 37
            width: 48
            height: 35
            anchors.horizontalCenter: parent.horizontalCenter
            labelText: "连接到WIFI"

        }
        MLineEdit1{
            id: lineEditWifiName
            width:250
            height:40

            anchors.top: connectWifiLabel.bottom
            textInputText: "SSID"
            anchors.topMargin: 30
            anchors.horizontalCenter: parent.horizontalCenter
//            textInput.onTextEdited: {
//                if (textInput.text == "SSID"){
//                    textInput.clear();
//                }

//            }
        }

        MLineEdit1{
            id: lineEditWifiPwd

            width:250
            height:40

            anchors.top: lineEditWifiName.bottom
            textInputText: "PASSWORD"
            anchors.topMargin: 20
            anchors.horizontalCenter: parent.horizontalCenter


        }
        MLabelBlack{
            id: connectStateLabel
            labelText : ""

            anchors.top: lineEditWifiPwd.bottom
            labelFontpointSize: 15
            anchors.topMargin: 20
            anchors.horizontalCenter: parent.horizontalCenter

//            PropertyAnimation {
//                id: connectFailedANIM
//                properties: labelText
//                target: connectStateLabel
//                from :"需要连接网络"
//                to :"连接失败"
//            }

//            PropertyAnimation {
//                id: connectingANIM
//                properties: labelText
//                target: connectStateLabel
//                from :"需要连接网络"
//                to :"连接中"
//            }

        }
        MbuttonBlue{
            id: connectBtn
            text: "连接"
            anchors.top: connectStateLabel.bottom
            anchors.topMargin: 20
            anchors.horizontalCenter: parent.horizontalCenter
            onClicked: {
                console.log("qml trying to run connect wifi");
                if(lineEditWifiPwd.textInputText.length < 8){
                    messageboxInfo.labelText = "密码格式不正确";
                    messageboxInfo.showUpANIM.start();
                    return;
                }
                qmlCtrl.connectWifi(lineEditWifiName.textInputText, lineEditWifiPwd.textInputText);
                messageboxInfo.labelText = "连接中";
                messageboxInfo.showUpANIM.start();
                //#ifdef Q_OS_WIN32
//                connectStateLabel.labelText = "已连接";
//                    messageboxInfo.labelText = "已连接到网络";
//                    messageboxInfo.showUpANIM.start();
//                    toConnectedANIM.start();
                //#endif
            }
        }


    }

    Connections{
        target: qmlCtrl;
        function onWifiStatusChanged(status){
            console.log("qml get wifistatus");
            if(status == true){
            connectStateLabel.labelText = "已连接";
                messageboxInfo.labelText = "已连接到网络";
                messageboxInfo.showUpANIM.start();
                toConnectedANIM.start();
            }else{
                connectStateLabel.labelText = "未连接"
            }
        }
    }

    Timeline {
        id: timeline
        animations: [
            TimelineAnimation {
                id: toConnectedANIM
                onFinished: wifiConnectForm.state = "connected"
                duration: 2000
                loops: 1
                running: false
                to: 200
                from: 0
            }
        ]
        startFrame: 0
        enabled: false
        endFrame: 200

        KeyframeGroup {
            target: rectangle
            property: "opacity"
            Keyframe {
                value: 1
                frame: 0
            }

            Keyframe {
                value: 0
                frame: 200
            }
        }

        KeyframeGroup {
            target: rectangle1
            property: "opacity"
            Keyframe {
                value: 1
                frame: 0
            }

            Keyframe {
                value: 0
                frame: 200
            }
        }

        KeyframeGroup {
            target: connectSucees
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

        KeyframeGroup {
            target: rectangle1
            property: "x"
            Keyframe {
                value: 56
                frame: 0
            }

            Keyframe {
                value: -230
                frame: 200
            }
        }

        KeyframeGroup {
            target: rectangle1
            property: "y"
            Keyframe {
                value: 146
                frame: 200
            }
        }

        KeyframeGroup {
            target: rectangle
            property: "x"
            Keyframe {
                value: 562
                frame: 0
            }

            Keyframe {
                value: 795
                frame: 200
            }
        }

        KeyframeGroup {
            target: rectangle
            property: "y"
            Keyframe {
                value: 64
                frame: 200
            }
        }

    }
    states: [
        State {
            id: wifiConnectState
            name: "connected"

            PropertyChanges {
                target: timeline
                enabled: true
            }

            PropertyChanges {
                target: toConnectedANIM
                running: true
            }

            PropertyChanges {
                target: rectangle
                opacity: 0
            }

            PropertyChanges {
                target: rectangle1
                x: -168
                opacity: 0
            }

            PropertyChanges {
                target: connectSucees
                opacity: 1
            }

        }
    ]


    function setWifiModel(index, wifiName, wifiLevel){
        var item = wifiListModel.get(index);
        item.wifiname = wifiName;
        item.wifilevel = wifiLevel;
        console.log("setting wifimodel",index,wifiName,wifiLevel);
    }

    function getWifiModelName(index){
        var item = wifiListModel.get(index);
        return item.wifiname;
    }

    function addWifiModel(wifiName,wifiLevel){
        console.log("add wifi:",wifiName,wifiLevel);
        wifiListModel.append({wifiname:wifiName, wifilevel:wifiLevel})
    }


}



