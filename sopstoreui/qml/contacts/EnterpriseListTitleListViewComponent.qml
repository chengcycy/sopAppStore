import QtQuick 2.0
import com.syberos.basewidgets 2.0
Rectangle{
    id: titleListView_root
    property alias model: orgTitleListView.model
    signal clickOrg()
    color: "transparent"
    //anchors.fill: parent
    ListView{
        id: orgTitleListView
        anchors.top: line.bottom
        anchors.left: parent.left
        width: parent.width
        height: parent.height
        orientation:ListView.Horizontal
        spacing: 0
        snapMode: ListView.SnapOneItem
        Rectangle{
            anchors.fill: parent
            color: "#eeefee"
            z: parent.z -1
        }

        delegate: Rectangle{
            width: name.contentWidth + arrow.width + 10
            height: 62
            anchors.top: parent.top
            anchors.topMargin: 0
            color: "transparent"
            Text {
                id: name
                anchors.verticalCenter: parent.verticalCenter
                anchors.horizontalCenter: parent.horizontalCenter
                text: orgName
                font.pixelSize: 26
                color:"#2982ff"
            }
            Image{
                id: arrow
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: name.right
                anchors.leftMargin: 5
                sourceSize.height: 26
                source: 'qrc:/res/images/arrow.png'
            }
            MouseArea{
                anchors.fill: parent
                onClicked: {
                    orgTitleListView.model.remove(index + 1, orgTitleListView.model.count - index - 1);

                    emit: clickOrg();

                    var EnOS = {enterId: 454, orgId: orgID, type: operType};
                    appClient.queryEnOS(JSON.stringify(EnOS));
                }
            }
        }
    }
    CLine {
        id: line
        width: parent.width
        color:"#dedfe6"
        anchors.top: parent.top
        z: parent.z+2
        visible: /*enterpriseManager.isOrg?true:false*/true
    }

}
