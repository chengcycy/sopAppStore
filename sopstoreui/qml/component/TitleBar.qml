import QtQuick 2.0
import com.syberos.basewidgets 2.0

Rectangle{
    id:titileBar

    property alias tips: title.text
    property alias ico : icoImg.source
    property bool  showRightIco: true
    property bool  showLoad: false
    signal clicked(int pos)

    color:"#f7f7f7"
    height: 90
    width:parent.width

    Text{
        id:title
        font.pixelSize: 36

        anchors.centerIn: parent
    }
    Image{
        id:icoImg

        sourceSize: Qt.size(40,40)
        visible: showRightIco

        anchors.verticalCenter: parent.verticalCenter
        anchors.right: parent.right
        anchors.rightMargin: 30
        MouseArea{
            anchors.fill: parent
            onClicked: {
                emit: titileBar.clicked(0);
            }
        }
    }
    AnimatedImage{
        id:load
        visible: showLoad
        source: "qrc:/res/images/loading.gif"
        anchors.verticalCenter: parent.verticalCenter
        anchors.right: parent.right
        anchors.rightMargin: 30
    }

    Image{
        id:icoImgLeft

        sourceSize: Qt.size(40,40)
        source: "qrc:/res/images/arrow_left.png"
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left
        anchors.leftMargin: 30
        MouseArea{
            anchors.fill: parent
            onClicked: {
                emit: titileBar.clicked(1);
            }
        }
    }
    CLine{
        anchors.top: parent.bottom
        color:"#dedfe6"
    }
}
