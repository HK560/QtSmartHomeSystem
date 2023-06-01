import QtQuick 2.15
import QtQuick.Controls 2.15

Item {
    id: item1
    width: 1024
    height: 500
    visible: true
//    property alias unbannedListVieww: unbannedListView
    property int nowIndex
//    property int audioListIndex
    property int choosenUserIndex: 0
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
    Rectangle {
        id: rectangle
        width: 312
        color: "#ececec"
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.leftMargin: 0
        anchors.bottomMargin: 0
        anchors.topMargin: 0

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
                id: listModel
                ListElement {
                    settingName: "关于"
//                                        settingName: "当前用户设置"
                }

                ListElement {
                    settingName: "通用设置"
                }

                ListElement {
                    settingName: "权限设置"
                }

                ListElement {
                    settingName: "网络设置"
                }
                ListElement{
                    settingName:"API接口设置"
                }
                ListElement {
                    settingName: "音频设置"
                }
                ListElement {
                    settingName: "系统"
                }
            }
            delegate: listDelegate
            highlight:Rectangle {
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
        Component {
            id: listDelegate
            Item {
                id: wrapper
                width: listView.width
                height: 50

                // 实现了鼠标点选高亮的效果
                MouseArea {
                    anchors.fill: parent;
                    onClicked: {
                        wrapper.ListView.view.currentIndex = index;
                        nowIndex = index;
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


                    Rectangle {
                        id:nameRectangle
                        width: parent.width/2
                        anchors.left: parent.left
                        anchors.leftMargin: 10
                        MLabel2 {
                            labelText: settingName
                            labelHorizontalAlignment: Text.AlignLeft
                            anchors.fill: parent ; anchors.leftMargin: 20;
                            labelColor: index === listView.currentIndex ? "white" : "#40a7e3"

                        }
                        // Text {
                        //     id: wifinameid
                        //     text: wifiname
                        //     anchors.fill: parent
                        //     horizontalAlignment: Text.AlignHCenter
                        //     verticalAlignment: Text.AlignVCenter
                        // }
                    }
                    //                    Rectangle {
                    //                        id:wifilevelRectangle

                    //                        anchors.left: wifinameRectangle.right
                    //                        anchors.right: parent.right
                    //                        anchors.rightMargin: -10
                    //                        anchors.leftMargin: 0
                    //                        MLabel2 {
                    //                            id: wifilevelid
                    //                            labelText: wifilevel
                    //                            anchors.fill: parent
                    //                            labelHorizontalAlignment: Text.AlignHCenter

                    //                        }
                    //                    }

                }
            }
        }
    }

//UserSetting{
//    id:userSetting
//    visible: nowIndex == 0 ? true : false


//}


GeneralSetting{
    id:generalSetting
            visible: nowIndex == 1 ? true : false
}


RoleSetting{
id:roleSetting
        visible: nowIndex == 2 ? true : false
}

NetworkSetting{
    id:networkSetting
            visible: nowIndex == 3 ? true : false

}

AudioSetting{
id:audioSetting
        visible: nowIndex == 5 ? true : false
}

SysSetting{
    id:sysSetting
    visible: nowIndex == 6 ? true : false
}

ApiSetting{
    id:apiSettting
    visible: nowIndex == 4 ? true : false}

        Rectangle {
            visible: nowIndex == 0 ? true : false
            id: rectangle1
            y: 0
            height: 500
            color: "#ffffff"
            anchors.left: rectangle.right
            anchors.right: parent.right
            anchors.leftMargin: 0
            anchors.rightMargin: 0

            MLabel {
                id: mLabel
                x: 356
                y: 189
                labelText: "智慧家庭系统"
            }

            MLabelBlack {
                id: mLabelBlack
                x: 356
                y: 239
                labelText: "版本: 0.1"
            }
        }

}
