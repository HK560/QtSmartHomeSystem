import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Timeline 1.0

Rectangle {
    id: rectangle

    height: 50
    opacity: 0
    color: "#725f5f5f"
    radius: 25
    border.color: "#00000000"
    border.width: 0
    property alias showUpANIM: showUpANIM
    property alias labelText: mLabel2.labelText
    width: 200
    MLabel2{
        id: mLabel2
        anchors.fill: parent
        labelFontpointSize: 15
    }

    Timeline {
        id: timeline
        animations: [
            TimelineAnimation {
                id: showUpANIM
                duration: 1000
                loops: 1
                running: false
                to: 1000
                from: 0
            }
        ]
        startFrame: 0
        enabled: true
        endFrame: 1000

        KeyframeGroup {
            target: rectangle
            property: "opacity"
            Keyframe {
                value: 0
                frame: 0
            }

            Keyframe {
                value: 1
                frame: 200
            }

            Keyframe {
                value: 1
                frame: 800
            }

            Keyframe {
                value: 0
                frame: 1000
            }

            Keyframe {
                value: 0.175
                frame: 35
            }
        }
    }
}
