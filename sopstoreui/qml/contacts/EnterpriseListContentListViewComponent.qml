import QtQuick 2.0
import com.syberos.basewidgets 2.0
import "../component"

Rectangle{
    id: contentListView_root
    property alias model: orgListView.model
    signal clickOrg(var id, string name)
    //anchors.fill: parent
    color:"transparent"

    ListView {
        id: orgListView
        anchors.fill: parent
        clip: true
        delegate:Item {
            id:contactListDelegate
            visible: true//(''+model.modelData.id) !== mainApp.currentID
            width: parent.width
            height: false/*((''+model.modelData.id) === mainApp.currentID)*/ ? 0 : 124
            MouseArea {
                anchors.fill: parent

                onPressed: {
                    if(mousePressBackgroud.visible){
                        background.color = "#f7f3f7"
                        mousePressBackgroud.visible = false
                    }else{
                        background.color = "#dcdcdc"
                        mousePressBackgroud.visible = true
                    }
                }

                onReleased: {
                    background.color = "#f7f3f7"
                    mousePressBackgroud.visible = false
                    if(isDepart){
                        var EnOS = {enterId: 454, orgId: itemID, type: 4};
                        emit: clickOrg(itemID, name);
                        appClient.queryEnOS(JSON.stringify(EnOS));

                        EnOS.type = 3;
                        appClient.queryEnOS(JSON.stringify(EnOS));
                    }
                    else{
                        background.color = "#f7f3f7"
                        mousePressBackgroud.visible = false
                        var parameter = {userName: name, department: orgName, position: position,
                                         telNum: telNum, mobileNum: mobileNum}
                        pageStack.push(Qt.resolvedUrl('MemberDetailPage.qml'), parameter);
                    }
                }

                onCanceled: {
                    background.color = "#f7f3f7"
                    mousePressBackgroud.visible = false
                }
            }

            Rectangle {
                width: contactListDelegate.width
                height: contactListDelegate.height
                color:"#f7f3f7"


                Rectangle {
                    id : mousePressBackgroud
                    anchors.fill: parent
                    visible: false
                    color: "#dcdcdc"
                }

                Rectangle {
                    id : background
                    anchors.fill: parent
                    color:"#f7f3f7"

                    CDoodHeaderImage{
                        id: portraitImage
                        anchors.left: parent.left
                        anchors.leftMargin: 17
                        anchors.verticalCenter: parent.verticalCenter
                        iconSource: isDepart ? "qrc:/res/images/Organization.png"
                                             : "qrc:/res/images/user.png"
                    }

                    Text {
                        id: nameText
                        anchors.left: portraitImage.right
                        anchors.leftMargin: 17
                        anchors.rightMargin: 20
                        anchors.right: subOrgCountAreaBg.left
                        anchors.verticalCenter: parent.verticalCenter
                        font.pixelSize: 30
                        height: 50
                        clip: true
                        color: "#000000"
                        verticalAlignment: Text.AlignVCenter
                        elide: Text.ElideRight
                        text: name
                    }

                    Rectangle {
                        id: subOrgCountAreaBg
                        visible: isDepart
                        width: 60
                        anchors.right: subMemberCountBg.left
                        anchors.rightMargin: 33
                        anchors.verticalCenter: parent.verticalCenter
                        Rectangle {
                            id: subOrgCountArea
                            width: subOrgIcon.sourceSize.width + subOrgCountText.contentWidth
                            anchors.horizontalCenter: parent.horizontalCenter
                            Image {
                                id: subOrgIcon
                                anchors.left: parent.left
                                anchors.verticalCenter: parent.verticalCenter
                                source: "qrc:/res/images/org.png"
                                sourceSize.height: 30
                            }
                            Text {
                                id: subOrgCountText
                                anchors.left: subOrgIcon.right
                                anchors.leftMargin: 5
                                anchors.verticalCenter: parent.verticalCenter
                                text: subOrgCount
                                font.pixelSize: 30
                            }
                        }
                    }

                    Rectangle {
                        id: subMemberCountBg
                        visible: isDepart
                        width: 60
                        anchors.right: parent.right
                        anchors.rightMargin: 51
                        anchors.verticalCenter: parent.verticalCenter
                        Rectangle {
                            id: subMemberCountArea
                            width: subMemberIcon.sourceSize.width + subMemberCountText.contentWidth
                            anchors.horizontalCenter: parent.horizontalCenter
                            Image {
                                id: subMemberIcon
                                anchors.left: parent.left
                                anchors.verticalCenter: parent.verticalCenter
                                source: "qrc:/res/images/server.png"
                                sourceSize.height: 30
                            }
                            Text {
                                id: subMemberCountText
                                anchors.left: subMemberIcon.right
                                anchors.leftMargin: 5
                                anchors.verticalCenter: parent.verticalCenter
                                text: subMemberCount
                                font.pixelSize: 30
                            }
                        }
                    }

                    CLine {
                        anchors.left: parent.left
                        anchors.bottom: parent.bottom
                        color:"#e6ebe6"
                        z: parent.z+2
                    }
                }
            }
        }
    }
}
