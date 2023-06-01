import QtQuick 2.15
import QtQuick.Controls 2.15

import QtQuick 2.0
import QtQuick.Controls 2.4
import QtQuick 2.11

ComboBox {
    id: combobox;
    height: 50
    font.pointSize: fontSize;
    font.family: "Microsoft YaHei"
    model: ["Option 1", "Option 2", "Option 3"]
    signal currentDataChanged(var text);

    property real combHeight: 30;       //复选框高度
    property real combWidth: 140;       //复选框宽度
    property real combRadius: 2;
    property real popupHeight: 400;     //下拉框高度
    property real indHeight: 8;         //下拉按钮高度
    property real indWidth: 12;         //下拉按钮宽度
    property string disColor: "#333";
    property real fontSize: 10;
    property real textLeftPadding: width * 0.2;
    property real beforeIndex: 0;
    property real itemHeight: 40
    width: 180

    delegate: ItemDelegate {
        width: combobox.width
        text: modelData
//        font.weight: Font.Normal
        font.family: "Microsoft YaHei"
        font.weight: combobox.currentIndex === index ? Font.DemiBold : Font.Normal
        highlighted: combobox.highlightedIndex == index
    }

    //下拉点击三角形
    indicator: Canvas {
        x: combobox.width - width - combobox.rightPadding
        y: combobox.topPadding + (combobox.availableHeight - height) / 2
        width: indWidth
        height: indHeight

        Connections {
            target: combobox
            function onPressedChanged(){combobox.indicator.requestPaint()}
        }

        onPaint: {
            var context = getContext( "2d" );
            context.reset();
            context.moveTo(0, 0);
            context.lineTo(width, 0);
            context.lineTo(width / 2, height);
            context.closePath();
            context.fillStyle = combobox.pressed ? "#40a7e3": "#333";
            context.fill();
        }
    }

    //显示的文字
    contentItem: Text {
        text: combobox.displayText
        font: combobox.font
        color: combobox.pressed ? "#40a7e3": "#333";
        leftPadding: textLeftPadding;
        horizontalAlignment: Text.AlignLeft
        verticalAlignment: Text.AlignVCenter
        anchors.horizontalCenter: parent.horizontalCenter
        elide: Text.ElideRight
        anchors.verticalCenter: parent.verticalCenter
    }

    background: Rectangle {
        color: "#00ffffff"
        implicitWidth: parent.width;
        implicitHeight: parent.height;
//        border.color: combobox.pressed ? "#40a7e3" : disColor;
//        border.width: combobox.visualFocus ? 2 : 1
        radius: combRadius
    }

    popup: Popup {
        y: combobox.height - 1
        width: combobox.width
        implicitHeight: contentItem.implicitHeight
        padding: 1

        contentItem: ListView {
            clip: true
            implicitHeight: combobox.model.length * 40 < popupHeight ? combobox.model.length * 40 : popupHeight;
            model: combobox.popup.visible ? combobox.delegateModel : null
            currentIndex: combobox.highlightedIndex
            ScrollIndicator.vertical: ScrollIndicator { }
        }
    }

    onCurrentIndexChanged: {
        if(combobox.model && parseFloat(currentIndex) !== parseFloat(beforeIndex)) {
            beforeIndex = currentIndex;
            displayText = combobox.model[currentIndex];
            currentDataChanged(displayText);
        }
    }

    Rectangle {
        id: rectangle
        color: "#00ffffff"
        radius: 25
        border.color: "#40a7e3"
        border.width: 3
        anchors.fill: parent
    }
}
