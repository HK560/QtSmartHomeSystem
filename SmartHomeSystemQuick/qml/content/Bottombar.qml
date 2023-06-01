import QtQuick 2.15
import QtQuick.Controls 2.15

Rectangle {
    width: 1024
    height: 50
    color: "#ffffff"
    property int nowindex


    ListView {
        id: listView
        anchors.fill: parent
        orientation: ListView.Horizontal
        flickableDirection: Flickable.HorizontalFlick
//        spacing: 100
        model: ListModel {
            ListElement {
                name: "主界面"
                colorCode: "设备"
            }

            ListElement {
                name: "设备列表"
                colorCode: "red"
            }

            ListElement {
                name: "AI助手"
                colorCode: "blue"
            }

            ListElement {
                name: "设置菜单"
                colorCode: "blue"
            }

        }
        delegate: bottomDelegate
        highlight:Item{
            Rectangle{
            id: highlight
            color: "#3e1799e4"
            radius: 20
            border.width: 0
            anchors.fill: parent
            anchors.rightMargin: 50
            anchors.leftMargin: 50

            ColorAnimation {
                id: colorAnimation
                target:highlight
                from:"#00ffffff"
                to: "#40a7e3"
            }
        }
        }
        focus: true;
    }
    Component {
        id: bottomDelegate
        Item {
            id: wrapper
            width: 256
            height: 50

            // 实现了鼠标点选高亮的效果
            MouseArea {
                anchors.fill: parent;
                onClicked: {
                    wrapper.ListView.view.currentIndex = index;
//                    lineEditWifiName.textInputText = getWifiModelName(index);
//                    lineEditWifiPwd.textInput.clear();
                    nowindex = index;
                    console.info(nowindex);
                }
            }

            // 内嵌三个Text对象，水平布局
            Item {

                        width: 80
                        height: 40
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.horizontalCenter: parent.horizontalCenter
                        BottomItem{
                            anchors.fill: parent
                            mLabelLabelText: name

                         }
                    }
        }
    }

}
