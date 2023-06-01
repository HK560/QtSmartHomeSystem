

/*
This is a UI file (.ui.qml) that is intended to be edited in Qt Design Studio only.
It is supposed to be strictly declarative and only uses a subset of QML. If you edit
this file manually, you might introduce QML code that is not supported by Qt Design Studio.
Check out https://doc.qt.io/qtcreator/creator-quick-ui-forms.html for details on .ui.qml files.
*/
import QtQuick 2.15
import QtQuick.Controls 2.15
import QtGraphicalEffects 1.12

Rectangle {

    color: "#00ffffff"
    border.color: "#00ffffff"
    border.width: 0
    property alias labelHorizontalAlignment: label.horizontalAlignment
    antialiasing: true
    property alias labelFontbold: label.font.bold
    property alias labelFontweight: label.font.weight
    property alias labelFontpointSize: label.font.pointSize
    property alias labelColor: label.color
    property alias labelText: label.text
    property alias wrapMode: label.wrapMode
    width: 100
    height: 50

    Label {
        id: label
        color: "#ffffff"

        text: qsTr("label")
        anchors.fill: parent
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        textFormat: Text.PlainText
        font.family: "Microsoft YaHei"
        font.italic: false
        font.underline: false
        font.capitalization: Font.MixedCase
        font.hintingPreference: Font.PreferDefaultHinting
        font.pointSize: 20
        //        layer.enabled: true
        //        layer.effect: DropShadow {
        //            verticalOffset: 2
        //            color: "#80000000"
        //            radius: 1
        //            samples: 3
        //        }
        Behavior on color {
                    ColorAnimation {
                        id:colorTofalse
                        duration: 200
                    }}
    }
}
