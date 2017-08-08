import QtQuick 2.0
import com.syberos.basewidgets 2.0

Rectangle {
    id: searchEditArea
    property alias text: searchEdit.text
    signal buttonClick()
    width: parent.width
    height: 64
    color: '#f7f7f7'

    Rectangle {
        id: searchEditBackground
        width: 612
        height: 52
        anchors.left: parent.left
        anchors.leftMargin: 10
        anchors.verticalCenter: parent.verticalCenter
        radius: 8
        color: '#d6dbd6'
        CLineEdit {
            id: searchEdit
            anchors.fill: parent
            placeholderText: '输入人名关键字'
            placeholderTextItem.color: '#adaaad'
        }
    }

    Text {
        id: searchButton
        anchors.left: searchEditBackground.right
        anchors.leftMargin: 18
        anchors.right: parent.right
        anchors.rightMargin: 10
        anchors.verticalCenter: parent.verticalCenter
        text: '搜索'
        color: '#adaaad'
        font.pixelSize: 26
        MouseArea {
            id: searchButtonMouseArea
            anchors.fill: parent
            onClicked: {
                emit: buttonClick()
            }
        }
    }

    CLine {
        height: 2
        anchors.top: parent.top
        color: '#dedfe6'
    }
    CLine {
        height: 2
        anchors.bottom: parent.bottom
        color: '#dedfe6'
    }
}
