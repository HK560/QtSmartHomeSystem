

/*
This is a UI file (.ui.qml) that is intended to be edited in Qt Design Studio only.
It is supposed to be strictly declarative and only uses a subset of QML. If you edit
this file manually, you might introduce QML code that is not supported by Qt Design Studio.
Check out https://doc.qt.io/qtcreator/creator-quick-ui-forms.html for details on .ui.qml files.
*/
import QtQuick 2.15
import QtQuick.Controls 2.15

SpinBox {
    id: control
    value: 10
    editable: true

    contentItem: textInput
    Rectangle {
        id: rectangle
        color: "#00ffffff"
        radius: 20
        border.color: "#40a7e3"
        border.width: 3
        anchors.fill: parent
    }

    up.indicator: upIndicator

    Rectangle {
        id: backgroundRect
        color: "#00000000"
//        implicitWidth: 140
        border.color: "#40a7e3"
        border.width: 0
    }

    Rectangle {
        id: upIndicator
        x: control.mirrored ? 0 : parent.width - width
        height: parent.height
        color: "#00000000"
        radius: 20
        border.color: "#0040a7e3"
        border.width: 3
        implicitWidth: 40
        implicitHeight: 40

        Text {
            id: text1
            text: "+"
            font.family: "Microsoft YaHei"
            font.pixelSize: control.font.pixelSize * 2
            color: "#047eff"
            anchors.fill: parent
            fontSizeMode: Text.Fit
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }
    }

    down.indicator: downIndicator

    Rectangle {
        id: downIndicator
        x: control.mirrored ? parent.width - width : 0
        height: parent.height
        color: "#00000000"
        radius: 20
        border.color: "#0040a7e3"
        border.width: 3
        implicitWidth: 40
        implicitHeight: 40

        Text {
            id: text2
            text: "-"
            font.family: "Microsoft YaHei"
            font.pixelSize: control.font.pixelSize * 2
            color: "#047eff"
            anchors.fill: parent
            fontSizeMode: Text.Fit
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }
    }

    background: backgroundRect

    Rectangle {
        id: rectangle1
        y: -6
        width: 200
        color: "#00ffffff"
        radius: 20
        border.color: "#2acfff"
        border.width: 0
        anchors.left: downIndicator.right
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.leftMargin: 0
        anchors.bottomMargin: 0
        anchors.topMargin: 0
        anchors.horizontalCenter: parent.horizontalCenter

        TextInput {
            id: textInput
            x: 46
            y: 6
            z: 2
            text: control.value
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            font.family: "Microsoft YaHei"
            font.italic: false
            font.underline: false
            font.capitalization: Font.MixedCase
            font.hintingPreference: Font.PreferDefaultHinting
            font.pointSize: 20
            color: "#047eff"
            selectionColor: "#047eff"
            selectedTextColor: "#ffffff"
            horizontalAlignment: Qt.AlignHCenter
            verticalAlignment: Qt.AlignVCenter
            anchors.bottomMargin: 0
            anchors.topMargin: 0
            anchors.horizontalCenter: parent.horizontalCenter

            readOnly: !control.editable
            validator: control.validator
            inputMethodHints: Qt.ImhFormattedNumbersOnly
        }
    }

    states: [
        State {
            name: "normal"
            when: !control.down.pressed && !control.up.pressed
                  && control.enabled

            PropertyChanges {
                target: upIndicator
                border.color: "#00047eff"
            }

            PropertyChanges {
                target: downIndicator
                border.color: "#00047eff"
            }

            PropertyChanges {
                target: backgroundRect
                border.color: "#047eff"
            }

            PropertyChanges {
                target: textInput
                color: "#047eff"
                selectionColor: "#ffffff"
            }

            PropertyChanges {
                target: text1
                color: "#047eff"
            }

            PropertyChanges {
                target: text2
                color: "#047eff"
            }
        },
        State {
            name: "upPressed"
            when: control.up.pressed

            PropertyChanges {
                target: text1
                color: "#ffffff"
            }

            PropertyChanges {
                target: upIndicator
                color: "#047eff"
                radius: 20
                border.color: "#047eff"
            }

            PropertyChanges {
                target: textInput
                color: "#047eff"
                selectionColor: "#ffffff"
            }

            PropertyChanges {
                target: downIndicator
                border.color: "#00047eff"
            }

            PropertyChanges {
                target: text2
                color: "#047eff"
            }

            PropertyChanges {
                target: backgroundRect
                border.color: "#047eff"
            }

            PropertyChanges {
                target: rectangle
                radius: 20
            }
        },
        State {
            name: "downPressed"
            when: control.down.pressed

            PropertyChanges {
                target: text2
                color: "#ffffff"
            }

            PropertyChanges {
                target: downIndicator
                color: "#047eff"
                radius: 20
                border.color: "#047eff"
            }

            PropertyChanges {
                target: textInput
                color: "#047eff"
                selectionColor: "#ffffff"
            }

            PropertyChanges {
                target: upIndicator
                border.color: "#00047eff"
            }

            PropertyChanges {
                target: text1
                color: "#047eff"
            }

            PropertyChanges {
                target: backgroundRect
                border.color: "#047eff"
            }

            PropertyChanges {
                target: rectangle1
                border.color: "#002acfff"
            }
        },
        State {
            name: "disabled"
            when: !control.enabled

            PropertyChanges {
                target: downIndicator
                border.color: "#b3047eff"
            }

            PropertyChanges {
                target: upIndicator
                border.color: "#b3047eff"
            }

            PropertyChanges {
                target: textInput
                color: "#b3047eff"
            }

            PropertyChanges {
                target: text1
                color: "#b3047eff"
            }

            PropertyChanges {
                target: text2
                color: "#b3047eff"
            }

            PropertyChanges {
                target: backgroundRect
                border.color: "#b3047eff"
            }
        }
    ]
}
