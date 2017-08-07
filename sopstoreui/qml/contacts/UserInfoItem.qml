import QtQuick 2.0
import com.syberos.basewidgets 2.0

Rectangle {
    id: userInfoItem

    property string titleText: ''
    property string contentText: ''

    width: parent.width
    height: 86

    Text {
        id: title
        anchors.left: parent.left
        anchors.leftMargin: 33
        anchors.verticalCenter: parent.verticalCenter
        text: titleText
        font.pixelSize: 30
    }

    Text {
        id: content
        anchors.left: parent.left
        anchors.leftMargin: 191
        anchors.verticalCenter: parent.verticalCenter
        text: contentText === '' ? '未设置' : contentText
        font.pixelSize: 30
    }

    CLine {
        anchors.top: parent.top
        color: '#eeebee'
    }

    CLine {
        anchors.bottom:  parent.bottom
        color: '#eeebee'
    }
}
