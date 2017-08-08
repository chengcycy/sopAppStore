import QtQuick 2.0

Rectangle {
    id: searchResultTip
    width: parent.width
    height: 60
    color: '#f7f7f7'
    Text {
        id: tipText
        anchors.left: parent.left
        anchors.leftMargin: 20
        anchors.verticalCenter: parent.verticalCenter
        text: '公搜索到了' + listModel.count + '条结果'
        color: '#c5cac5'
        font.pixelSize: 30
    }
    Image{
        id: closeButton
        anchors.right: parent.right
        anchors.rightMargin: 12
        anchors.verticalCenter: parent.verticalCenter
        source: 'qrc:/res/images/close.png'
        sourceSize.height: 34
        MouseArea {
            id: closeButtonMouseArea
            anchors.fill: parent
            onClicked: searchResultTip.visible = false
        }
    }
}
