import QtQuick 2.15
import QtQuick.Controls 2.15
import QtGraphicalEffects 1.0

Item {
    id: loadingIndicator
    width: 500
    height: 500


    BusyIndicator {
        anchors.fill: parent
        running: true

           contentItem: Item {
               Rectangle {
                   id: rect
                   width: parent.width
                   height: parent.height
                   color: Qt.rgba(0, 0, 0, 0)
                   radius: width / 2
                   border.width: width / 6
                   visible: false
               }

               ConicalGradient {
                   width: rect.width
                   height: rect.height
                   gradient: Gradient {
                       GradientStop { position: 0.0; color: "#ffffff" }
                       GradientStop { position: 1.0; color: "#2ccafb" }
                   }
                   source: rect

                   Rectangle {
                       anchors.top: parent.top
                       anchors.horizontalCenter: parent.horizontalCenter
                       width: rect.border.width
                       height: width
                       radius: width / 2
                       color: "#2ccafb"
                   }

                   RotationAnimation on rotation {
                       from: 0
                       to: 360
                       duration: 1000
                       loops: Animation.Infinite
                   }
               }
           }
        }
}
