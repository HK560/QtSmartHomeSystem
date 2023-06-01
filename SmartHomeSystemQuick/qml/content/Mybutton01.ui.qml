

/*
This is a UI file (.ui.qml) that is intended to be edited in Qt Design Studio only.
It is supposed to be strictly declarative and only uses a subset of QML. If you edit
this file manually, you might introduce QML code that is not supported by Qt Design Studio.
Check out https://doc.qt.io/qtcreator/creator-quick-ui-forms.html for details on .ui.qml files.
*/
import QtQuick 2.15
import QtQuick.Controls 2.15

Button {
    id: control
    width: 200
    height: 100

    implicitWidth: Math.max(
                       buttonBackground ? buttonBackground.implicitWidth : 0,
                       textItem.implicitWidth + leftPadding + rightPadding)
    implicitHeight: Math.max(
                        buttonBackground ? buttonBackground.implicitHeight : 0,
                        textItem.implicitHeight + topPadding + bottomPadding)
    leftPadding: 4
    rightPadding: 4

    text: "Button"
    icon.color: "#ffffff"
    focusPolicy: Qt.StrongFocus
    highlighted: true
    flat: true
    display: AbstractButton.TextOnly
    autoRepeat: false
    checked: true

    background: buttonBackground
    Rectangle {
        id: buttonBackground
        width: 200
        color: "#a4f7b9"
        implicitWidth: 100
        implicitHeight: 40
        opacity: enabled ? 1 : 0.3
        radius: 30
        border.color: "#76ef5a"
        border.width: 4
        antialiasing: false
    }

    contentItem: textItem
    Text {
        id: textItem
        opacity: 1
        text: control.text
        anchors.fill: parent

        color: "#047eff"
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        font.family: "Arial"
        font.pointSize: 21
    }

    states: [
        State {
            name: "normal"
            when: !control.down

            PropertyChanges {
                target: buttonBackground
                color: "#00000000"
                border.color: "#047eff"
            }

            PropertyChanges {
                target: textItem
                color: "#047eff"
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
                color: "#047eff"
                border.color: "#00000000"
            }
        }
    ]
}
