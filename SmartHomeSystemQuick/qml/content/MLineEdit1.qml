

/*
This is a UI file (.ui.qml) that is intended to be edited in Qt Design Studio only.
It is supposed to be strictly declarative and only uses a subset of QML. If you edit
this file manually, you might introduce QML code that is not supported by Qt Design Studio.
Check out https://doc.qt.io/qtcreator/creator-quick-ui-forms.html for details on .ui.qml files.
*/
import QtQuick 2.15
import QtQuick.Controls 2.15
import QtGraphicalEffects 1.15
Rectangle {
    id: rectangle
    width: 200
    height: 50
    color: "#ffffff"
    radius: 25
    border.color: "#40a7e3"
    border.width: 3
    property alias textInputWrapMode: textInput.wrapMode
    property bool readOnly: false
    property alias textInput: textInput
    property alias textInputText: textInput.text
    TextInput {
        id: textInput
        color: "#737373"
        text: qsTr("文本")
        clip: true
        anchors.fill: parent
        font.pixelSize: 20
        verticalAlignment: Text.AlignVCenter
        wrapMode: Text.NoWrap
        anchors.rightMargin: 10
        anchors.leftMargin: 10
        readOnly: readOnly
        font.family: "Microsoft YaHei"
        renderType: Text.QtRendering
        selectByMouse: true
//        maximumLength: 40
        rightPadding: 0
        leftPadding: 12
        cursorPosition: 0

        //        validator: RegExpValidator { regExp: /^([a-zA-Z0-9]{4,8})$/ }
    }
    Rectangle {
        id: lineeditbottom
        color: "#00000000"
        radius: 25
        border.color: "#40a7e3"
        border.width: 3
        anchors.fill: parent
    }

    Rectangle {
        //        visible: readOnly
        id: lineedittop
//        color: "#78368ebc"
                color: readOnly ? "#78368ebc" : "#00000000"

        Behavior on color {
            ColorAnimation {
                id: colorTofalse
                duration: 200
            }
        }
        radius: 25
        border.color: "#40a7e3"
        border.width: 3
        anchors.fill: parent

        MouseArea {
            visible: readOnly
            id: mouseArea
            anchors.fill: parent
        }
    }
    layer.enabled: false

    layer.effect: DropShadow{
        color: "#bf4c4c4c"
        radius: 8
        samples: 20
        horizontalOffset: 1
        verticalOffset: 1
        spread: 0
    }
}
