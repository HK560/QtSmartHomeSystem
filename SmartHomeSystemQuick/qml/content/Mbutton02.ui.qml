

/*
This is a UI file (.ui.qml) that is intended to be edited in Qt Design Studio only.
It is supposed to be strictly declarative and only uses a subset of QML. If you edit
this file manually, you might introduce QML code that is not supported by Qt Design Studio.
Check out https://doc.qt.io/qtcreator/creator-quick-ui-forms.html for details on .ui.qml files.
*/
import QtQuick 2.15
import QtQuick.Controls 2.15
import QtGraphicalEffects 1.12
Button {
    id: control
    width: 500
    height: 100

    implicitWidth: Math.max(
                       buttonBackground ? buttonBackground.implicitWidth : 0,
                       textItem.implicitWidth + leftPadding + rightPadding)
    implicitHeight: Math.max(
                        buttonBackground ? buttonBackground.implicitHeight : 0,
                        textItem.implicitHeight + topPadding + bottomPadding)
    leftPadding: 4
    rightPadding: 4

    text: "My Button"
    hoverEnabled: false

    background: buttonBackground

    Rectangle {
        id: buttonBackground
        color: "#9cffffff"
        implicitWidth: 100
        implicitHeight: 40
        opacity: enabled ? 1 : 0.3
        radius: 50
        border.color: "#921cf7d2"
        border.width: 5

        
    layer.enabled: true
    
    layer.effect: DropShadow{
        radius: 8
        samples: 17
        horizontalOffset: 0
        verticalOffset: 2
        spread: 0
    }

    }

    contentItem: textItem
    Text {
        id: textItem
        text: control.text

        opacity: enabled ? 1.0 : 0.3
        color: "#ffffff"
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        font.pointSize: 22
        font.family: "Microsoft YaHei"
    }

    ColorAnimation {
        id: colorAnimation
        target: buttonBackground
        running: false
    }

    states: [
        State {
            name: "normal"
            when: !control.down

            PropertyChanges {
                target: buttonBackground
                color: "#8008bcf7"
                border.color: "#921cf7d2"
            }

            PropertyChanges {
                target: textItem
                color: "#ffffff"
            }
        },
        State {
            name: "down"
            when: control.down
            PropertyChanges {
                target: textItem
                color: "#ffffff"
            }

            PropertyChanges {
                target: buttonBackground
                color: "#bd04dbff"
                border.color: "#9b00ffd4"
                layer.enabled: false
            }
        }
    ]
    transitions: [
        Transition {
            from: "normal"
            to: "down"

            ColorAnimation {
                duration: 200
            }
        },
        Transition {
            from: "down"
            to: "normal"
            ColorAnimation {
                duration: 200
            }
        }
    ]
}
