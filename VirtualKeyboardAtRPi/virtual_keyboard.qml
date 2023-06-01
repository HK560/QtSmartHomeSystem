import QtQuick 2.6
import QtQuick.VirtualKeyboard 2.2
import QtQuick.VirtualKeyboard.Settings 2.2

Item {

    InputPanel {
        id: vkb
        visible: true //active
        y: Qt.inputMethod.visible ? parent.height - vkb.height : parent.height
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        Component.onCompleted: {
            VirtualKeyboardSettings.locale = "en_GB";
            VirtualKeyboardSettings.activeLocales = ["en_GB", "zh_CN"];
        }
    }

}
