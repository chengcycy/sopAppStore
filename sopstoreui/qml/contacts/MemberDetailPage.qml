import QtQuick 2.0
import com.syberos.basewidgets 2.0
import "../component"

CPage {
    id: memberDetailPage

    property string userName
    property string department
    property string position
    property string telNum
    property string moblieNum

    statusBarHoldEnabled: false
    onStatusChanged: {
        if (status === CPageStatus.WillShow) {
            memberDetailPage.statusBarHoldItemColor = "black"

            memberDetailPage.statusBarHoldEnabled = true
            gScreenInfo.setStatusBar(memberDetailPage.statusBarHoldEnabled)
            memberDetailPage.statusBarHoldItemColor = "#edf0f0"
            gScreenInfo.setStatusBarStyle("black")
        }
    }

    contentAreaItem: Item {
        anchors.fill :parent

        Rectangle {
            id: background
            anchors.fill: parent
            color: '#eef3ee'
        }

        TitleBar {
            id: titleBar
            tips: qsTr("详细资料")
            showLeftIco: true
            showRightIco: false
            anchors.top: parent.top
            onClicked: {
                if (pos === 1) {
                    pageStack.pop()
                }
            }
        }

        Rectangle {
            id: generalArea
            width: parent.width
            height: 172
            anchors.top: titleBar.bottom
            anchors.topMargin: 23
            color: '#ffffff'

            CDoodHeaderImage {
                id: avatar
                width: 120
                height: 120
                anchors.left: parent.left
                anchors.leftMargin: 31
                anchors.verticalCenter: parent.verticalCenter
                iconSource: "qrc:/res/images/user.png"
            }

            Text {
                id: nameText
                anchors.left: avatar.right
                anchors.leftMargin: 40
                anchors.top: avatar.top
                anchors.topMargin: 15
                text: memberDetailPage.userName
                font.pixelSize: 40
            }

            Text {
                id: departmentText
                anchors.left: avatar.right
                anchors.leftMargin: 40
                anchors.bottom: avatar.bottom
                anchors.bottomMargin: 10
                text: memberDetailPage.department
                font.pixelSize: 20
                color: '#b5b2b5'
            }

            CLine {
                anchors.top: parent.top
                color: '#eeebee'
            }

            CLine {
                anchors.bottom:  parent.bottom
                color: '#eeebee'
            }
        }
    }
}
