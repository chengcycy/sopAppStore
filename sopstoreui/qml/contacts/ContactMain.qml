import QtQuick 2.0
import com.syberos.basewidgets 2.0
import "../component"

Rectangle {
    color: "#f7f3f7"

    TitleBar {
        id: titleBar
        tips: qsTr("通讯录")
        ico:"qrc:/res/images/search.png"
        anchors.top: parent.top
    }
}
