import QtQuick 2.0
import com.syberos.basewidgets 2.0
CSwipeTab {
    title: "tab"
    property alias  imageSource: page.source
    property string url :""
    Image {
        id:page
        asynchronous: true
        anchors.fill: parent
        MouseArea{
            anchors.fill: parent
            onClicked: {
                var data = {scheme:url}
                appClient.opensopApp(JSON.stringify(data));
            }
        }
    }
}
