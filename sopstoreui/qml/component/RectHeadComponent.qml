import QtQuick 2.0
import com.syberos.basewidgets 2.0
import QtGraphicalEffects 1.0

Item {
    id: root
    property int radius: 10
    property string iconSource
    height: 88
    width: height

    Item{
        id: roundImage
        anchors.fill: parent
        OpacityMask {
            id: bd
            anchors.fill: parent
            source: src.status === Image.Ready ? src : null
            maskSource:  Rectangle{
                width:root.width
                height:root.height
                radius: root.radius
                visible: false
            }
        }

        Image {
            id: src
            anchors.fill: parent
            visible: false

            sourceSize: Qt.size(src.width,src.height)
            asynchronous: true
            cache: true
            source:iconSource

            onStatusChanged: {
                if (src.status === Image.Error || src.status === Image.Null) {
                    roundImage.visible = false
                } else if (src.status === Image.Ready) {
                    roundImage.visible = true
                }
            }
        }
    }
}
