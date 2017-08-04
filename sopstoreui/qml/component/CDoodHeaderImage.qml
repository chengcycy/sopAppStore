import QtQuick 2.0
import com.syberos.basewidgets 2.0
import QtGraphicalEffects 1.0

Item {
    id: root

    property alias bkRect: roundImage
    property url iconSource: ""
    property string name: "storeapp"
    property string type: ""
    property int radius: 8
    height: 90
    width: 90
    function setIcon(type,source){
        root.type = type;
        if(source !== ""){
            var tmp = source + "";
            tmp = tmp.substring(0, 3);
            if(tmp === "qrc"){
                return source;
            }else{
                roundImage.visible = true;
                return "file://"+source;
            }
        }
        else if(type === "1")
            return "qrc:/res/images/user.png";
        else
            return "qrc:/res/images/user.png";
    }

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
                    src.source = setIcon(root.type,"");
                } else if (src.status === Image.Ready) {
                    roundImage.visible = true
                }
            }
        }
    }
}
