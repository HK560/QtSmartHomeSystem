

/*
This is a UI file (.ui.qml) that is intended to be edited in Qt Design Studio only.
It is supposed to be strictly declarative and only uses a subset of QML. If you edit
this file manually, you might introduce QML code that is not supported by Qt Design Studio.
Check out https://doc.qt.io/qtcreator/creator-quick-ui-forms.html for details on .ui.qml files.
*/
import QtQuick 2.15
import QtQuick.Controls 2.15

Rectangle {

    color: "#00ffffff"
    border.color: "#00000000"
    property alias labelFontbold: label.font.bold
    property alias labelFontweight: label.font.weight
    property alias labelFontpointSize: label.font.pointSize
    property alias labelColor: label.color
    property alias labelText: label.text

    Label {
        id: label
        color: "#40a7e3"
        text: qsTr("Label")
        anchors.fill: parent
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        font.family: "Microsoft YaHei"
        font.italic: false
        font.underline: false
        font.capitalization: Font.MixedCase
        font.hintingPreference: Font.PreferDefaultHinting
        font.pointSize: 20
    }
}
