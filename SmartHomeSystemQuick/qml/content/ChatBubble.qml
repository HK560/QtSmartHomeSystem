import QtQuick 2.15
import QtQuick.Controls 2.15
import QtGraphicalEffects 1.0
Item {
    id: item1
    property string author
    property string message
    property int alignment


    width:   rectangle.width + 30
    height: 80+rectangle.height
    property alias wwidth: item1.width
    anchors.margins:10

    Rectangle  {
id: avatar
            color: "#00000000"
            width: 50
            height: 50
//            radius: width/2
            anchors {
                top: parent.top
                right: alignment == Qt.AlignRight ? parent.right : undefined
                left: alignment == Qt.AlignLeft ? parent.left : undefined
                topMargin: 10
                rightMargin: alignment == Qt.AlignRight ? 10 : undefined
                leftMargin: alignment == Qt.AlignLeft ? 10 : undefined        }
        clip:true
    Image {
        id: _image
        visible: false
        anchors.fill: parent
        source: alignment == Qt.AlignRight ? "images/user_icon.png" : "images/ChatGPT_logo.png"
        fillMode: Image.PreserveAspectFit
    }


    Rectangle {
        id: _mask
//        color: "black"
        anchors.fill: parent
        radius: width/2
        visible: true
        antialiasing: true
        smooth: true
    }
    OpacityMask {
        id:mask_image
        anchors.fill: _image
        source: _image
        maskSource: _mask
        visible: true
        antialiasing: true
    }

}
    Rectangle {
        id: rectangle

        width: Math.min((showText.implicitWidth )   ,
                                   item1.wwidth /2)
        height: showText.implicitHeight
//        width: (20 +showText2.implicitWidth ) < item1.wwidth/2 ? (20 + showText2.implicitWidth ) : item1.wwidth/2
//        height: parent.height -40
        color: "#7596fd"
        radius: 25
        smooth: false
        anchors{
        top: avatar.bottom
        right: alignment == Qt.AlignRight ? parent.right : undefined
        left: alignment == Qt.AlignLeft ? parent.left : undefined
        topMargin: 10
        rightMargin: alignment == Qt.AlignRight ? 10 : undefined
        leftMargin: alignment == Qt.AlignLeft ? 10 : undefined

        }

        Text {
            id:showText
//            visible: /*false*/
//            height: 40
            padding: 14
            text: message
            anchors.fill: parent
//            verticalAlignment: TextInput.AlignVCenter
//                horizontalAlignment: TextInput.AlignHCenter
//            anchors.verticalCenter: parent.verticalCenter
//            anchors.left: parent.left
//            anchors.right: parent.right
            wrapMode: Text.Wrap
//             maximumLineCount: 2
//            anchors.rightMargin: 0
            font.pixelSize: 20
//            color: "#333333"
            font.family: "Microsoft YaHei"
            font.italic: false
            font.underline: false
            font.capitalization: Font.MixedCase
            font.hintingPreference: Font.PreferDefaultHinting
            color: "#ffffff"
        }
// //
        MLabel2 {
            id: mLabel2
            visible: false
            anchors.margins: 10
            anchors.fill: parent
            labelText: message
            labelFontpointSize: 20
            wrapMode: Text.Wrap
            labelHorizontalAlignment: 1

        }



    }



}
