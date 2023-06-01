import QtQuick 2.15
import QtQuick.Controls 2.15

Rectangle {
    id: rectangle2
    width: 200
    color: "#318fc9"
    radius: 30
    border.color: "#ffffff"
    border.width: 3

    property alias wind: windlb.labelText
    property alias weather: weatherlb.labelText
    property alias tempRange: tempRangelb.labelText
    property alias week: weeklb.labelText
    property alias date: datelb.labelText

    MLabel2 {
        id: datelb
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.rightMargin: 0
        anchors.leftMargin: 0
        anchors.topMargin: 15
        labelText: "2-27"
    }

    MLabel2 {
        id: weeklb
        anchors.left: parent.left
        anchors.right: parent.right

        anchors.top: datelb.bottom
        anchors.rightMargin: 0
        anchors.leftMargin: 0
        anchors.topMargin: 0
        labelText: "星期一"
    }

    MLabel2 {
        id: tempRangelb
        anchors.left: parent.left
        anchors.right: parent.right


        anchors.top: weeklb.bottom
        anchors.rightMargin: 0
        anchors.leftMargin: 0
        anchors.topMargin: 0
        labelText: "8~27"
    }

    MLabel2 {
        id: weatherlb
        height: 50
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: tempRangelb.bottom
        anchors.rightMargin: 8
        anchors.leftMargin: 0
        anchors.topMargin: 0
        labelText: "qing"
    }

    MLabel2 {
        id: windlb
        width: 200
        height: 50

        anchors.top: weatherlb.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.topMargin: 0
        labelText: "dongfeng"
    }
}
