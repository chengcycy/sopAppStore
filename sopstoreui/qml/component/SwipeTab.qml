import QtQuick 2.0
import com.syberos.basewidgets 2.0
CSwipeTab {
    property alias  imageSource: page.source
    property string url :""

    Rectangle{
        id:back
        color: "#dcdcdc"
        anchors.fill: parent
    }

    Image {
        id:page
        asynchronous: true
        z:back.z+1
        anchors.fill: parent
        MouseArea{
            anchors.fill: parent
            onClicked: {
                var data = {scheme:url}
                appClient.opensopApp(JSON.stringify(data));
            }
        }
    }
    Text{
        id:txt
        text:title
        font.pixelSize: 36
        color: 'white'
        z:page.z+1

        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.leftMargin: 30
        anchors.bottomMargin: 10
    }
}
