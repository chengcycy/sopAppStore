import QtQuick 2.0
import com.syberos.basewidgets 2.0
CPage {
    id: loginUserLst

    signal callback(string data)

    function setModelData(data){
        var objs = JSON.parse(data);
        usrLstModel.clear();
        for(var i = 0; i<objs.length;++i){
            var item = objs[i];
            usrLstModel.append(item)
        }
    }

    statusBarHoldEnabled: false
    onStatusChanged: {
        if (status === CPageStatus.WillShow) {
            gScreenInfo.setStatusBar(true)
            gScreenInfo.setStatusBarStyle("transwhite")
        }
    }
    contentAreaItem: Item {
        anchors.fill :parent
        Flickable{
            id: filckableInput
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            contentHeight: parent.height

            Connections {
                target: gInputContext
                onSoftwareInputPanelVisibleChanged: {
                    if(gInputContext.softwareInputPanelVisible) {
                        filckableInput.contentHeight = filckableInput.parent.height + 200
                    } else {
                        filckableInput.contentHeight = filckableInput.parent.height
                    }
                }
            }

            Image {
                id: logoImage
                source: "qrc:/res/images/logo.png"

                anchors.top: parent.top
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.topMargin: 114
                smooth: true
            }
            Text{
                id:title
                text:qsTr("智慧企业运行平台")
                font.pixelSize: 36

                anchors.top: logoImage.bottom
                anchors.topMargin: 10
                anchors.horizontalCenter: parent.horizontalCenter
            }
            Rectangle {
                id: listBackGround

                width: parent.width - 80
                border.color: "#094a84"
                border.width: 1
                color: "#fefefe"
                radius: 2

                anchors.top: title.bottom
                anchors.topMargin: 30
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 200
                Rectangle{
                    id:tips
                    color:"#cdcdcd"
                    width: parent.width -2
                    height: 80

                    anchors.top: parent.top
                    anchors.horizontalCenter: parent.horizontalCenter
                    Text{
                        text:'共查找到'+usrLst.count+'个组织'
                        font.pixelSize: 30
                        color:"blue"
                        verticalAlignment:Text.AlignVCenter

                        anchors.left: parent.left
                        anchors.leftMargin: 30
                        anchors.verticalCenter: parent.verticalCenter
                    }
                }
                ListView{
                    id:usrLst

                    width:parent.width
                    model: usrLstModel
                    clip: true
                    anchors.top: tips.bottom
                    anchors.bottom: parent.bottom
                    delegate: MouseArea{
                        width:parent.width
                        height: 80
                        //                        anchors.fill: parent

                        Rectangle{
                            id:backRect

                            anchors.fill: parent
                            anchors.margins: 1

                            color:"white"
                            z:parent.z-1
                        }
                        onReleased:backRect.color='white'
                        onPressed:backRect.color='cdcdcd'
                        onCanceled: backRect.color='white'
                        onClicked: {
                            emit:callback(JSON.stringify(usrLstModel.get(index)));
                            backRect.color='white';
                        }
                        Text{
                            text:unitName
                            font.pixelSize: 30
                            verticalAlignment:Text.AlignVCenter

                            anchors.centerIn: parent
                        }
                        CLine{
                            color: listBackGround.border.color
                            anchors.top:parent.bottom
                        }
                    }

                }
                ListModel{
                    id:usrLstModel
                }
            }
        }
    }
}
