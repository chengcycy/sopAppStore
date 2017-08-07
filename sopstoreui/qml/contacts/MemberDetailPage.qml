import QtQuick 2.0
import com.syberos.basewidgets 2.0
import "../component"

CPage {
    id: memberDetailPage

    property alias userName: nameText.text
    property alias department: departmentText.text
    property alias position: positionInfo.contentText
    property alias telNum: telNumInfo.contentText
    property alias moblieNum: mobileNumInfo.contentText

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
                anchors.topMargin: 18
                font.pixelSize: 37
            }

            Text {
                id: departmentText
                anchors.left: avatar.right
                anchors.leftMargin: 40
                anchors.bottom: avatar.bottom
                anchors.bottomMargin: 12
                font.pixelSize: 25
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

        UserInfoItem {
            id: positionInfo
            anchors.top: generalArea.bottom
            anchors.topMargin: 40
            titleText: '职位'
        }

        UserInfoItem {
            id: telNumInfo
            anchors.top: positionInfo.bottom
            anchors.topMargin: -1
            titleText: '固定电话'
            Image {
                id: telIcon
                anchors.left: parent.left
                anchors.leftMargin: 474
                anchors.verticalCenter: parent.verticalCenter
                source: 'qrc:/res/images/telphone.png'
                sourceSize.height: 40
                MouseArea {
                    anchors.fill: parent
                    onClicked: {}
                }
            }
        }

        UserInfoItem {
            id: mobileNumInfo
            anchors.top: telNumInfo.bottom
            anchors.topMargin: -1
            titleText: '手机号码'

            Image {
                id: mobileIcon
                anchors.left: parent.left
                anchors.leftMargin: 474
                anchors.verticalCenter: parent.verticalCenter
                source: 'qrc:/res/images/phnoe.png'
                sourceSize.height: 40
                MouseArea {
                    anchors.fill: parent
                    onClicked: {}
                }
            }
            Image {
                id: msgIcon
                anchors.left: mobileIcon.right
                anchors.leftMargin: 30
                anchors.verticalCenter: parent.verticalCenter
                source: 'qrc:/res/images/msg.png'
                sourceSize.height: 40
                MouseArea {
                    anchors.fill: parent
                    onClicked: {}
                }
            }
            Image {
                id: mailIcon
                anchors.left: msgIcon.right
                anchors.leftMargin: 30
                anchors.verticalCenter: parent.verticalCenter
                source: 'qrc:/res/images/mail.png'
                sourceSize.height: 40
                MouseArea {
                    anchors.fill: parent
                    onClicked: {}
                }
            }
        }
    }
}
