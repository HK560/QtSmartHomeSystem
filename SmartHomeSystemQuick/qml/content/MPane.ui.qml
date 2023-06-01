import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15
import UntitledProject 1.0

Pane {
    id: pane
    width: Constants.width
    height: Constants.height

    SwipeView {
        id: swipeView
        x: 124
        y: 68
        width: 451
        height: 415
        anchors.verticalCenter: parent.verticalCenter
        anchors.fill: parent
        anchors.horizontalCenter: parent.horizontalCenter
        currentIndex: 2

        Label {
            id: firstPage
            text: "firstPage"
        }
        Label {
            id: secondPage
            text: "secondPage"
        }
        Label {
            id: thirdPage
            text: "thirdPage"
        }
    }
}
