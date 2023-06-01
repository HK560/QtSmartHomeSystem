import QtQuick 2.15
import QtQuick.Controls 2.15

Item {
    id: item1
    width: 1024
    height: 500
    onVisibleChanged: {
        showAnim.stop()
        showAnim.start()}
        PropertyAnimation {
        id:showAnim
        target: item1
         properties:"opacity"
         from:0
         to:1
         duration : 500
    }
    Rectangle {
        id: chatArea
        anchors.fill: parent
        color: "#f5f5f5"

        ListView {
            id: chatList
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: parent.top
            anchors.bottom: chatInput.top
            anchors.bottomMargin: 0
            anchors.rightMargin: 20
            anchors.leftMargin: 20
            model: chatModel
            clip: true
            delegate: ChatBubble {
                author: model.author
                message: model.message
                alignment: model.align
                wwidth: parent.width
                clip:true
                }
                ScrollBar.vertical: ScrollBar {
                    width: 10
                    anchors.right: parent.right
                    anchors.rightMargin: 0
                    policy: ScrollBar.AsNeeded
                }
            }

        ChatInput {
            id: chatInput
            anchors {
                left: parent.left
                right: parent.right
                bottom: parent.bottom
            }
            onSubmit: {
                if (chatInput.inputFieldText != "")
                {
                    if (qmlCtrl.chatGptSendMessage(chatInput.inputFieldText))
                    {
                        chatModel.append({
                        author: "User A",
                        message: chatInput.inputFieldText,
                        align: Qt.AlignRight
                    })
                }

                chatInput.inputFieldText = ""
                chatList.positionViewAtEnd()

            }
        }
            onRefresh:{
                console.log("clear chatgpt history");
                qmlCtrl.chatGptClearHistory();
                chatModel.clear();
                
        }
    }
}

ListModel {
    id: chatModel
    //           ListElement
    //               {
    //                   author: "User A"
    //                   message: "sicksicksicksicksicksicksicksicksicksicksicksicksicksicksicksicksicksicksicksicksicksicksicksicksicksicksicksicksicksicksicksicksicksicksicksicksicksicksicksicksicksicksicksicksicksicksicksicksicksicksicksicksicksicksicksicksicksicksicksicksicksicksicksicksicksicksicksicksicksick"
    //                   align: Qt.AlignRight
    //               }
    //           ListElement
    //               {
    //                   author: "User A"
    //                   message: "sicksicksicksicksicksicksicksicksicksicksicksicksicksick"
    //                   align: Qt.AlignLeft
    //               }
}
Connections {
    target: qmlCtrl
    function onChatGptNewResponse(response)
    {
        chatModel.append({
        author: "User B",
        message: response,
        align: Qt.AlignLeft})
        chatList.positionViewAtEnd()
    }
}
LoadingIndicator{
    width: 100
    height: 100
    visible: qmlCtrl.loadingRequestStatue

    anchors.verticalCenter: parent.verticalCenter
    anchors.horizontalCenter: parent.horizontalCenter
//    Connections{
//        target: qmlCtrl
//        onloadingRequestStatueChanged(status){
            
//        }
//    }
}


}






