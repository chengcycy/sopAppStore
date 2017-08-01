import QtQuick 2.0
import com.syberos.basewidgets 2.0
import "../component"

Rectangle{
    color:"#efeef4"
    TitleBar{
        id:tBar
        tips: qsTr("应用")
        ico:"qrc:/res/images/store_n.png"
        anchors.top: parent.top

    }
}
