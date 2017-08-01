import QtQuick 2.0
import com.syberos.basewidgets 2.0
import "./component"
import "./apps"
import "./contacts"
import "./me"
import "./notice"

CPage {
    id: mainClient

    onStatusChanged: {
        if (status === CPageStatus.WillShow) {
            mainClient.statusBarHoldItemColor = "black"

            mainClient.statusBarHoldEnabled = true
            gScreenInfo.setStatusBar(mainClient.statusBarHoldEnabled)
            mainClient.statusBarHoldItemColor = "#edf0f0"
            gScreenInfo.setStatusBarStyle("black")
            console.log('dddddddddddddddddddddddddddddddddddddddddddddd')
        } else if (status === CPageStatus.WillHide) {

        }
    }


    contentAreaItem: Item {
        CTabView {
            id:tabView
            tabPosition : Qt.BottomEdge

            anchors.top:parent.top
            anchors.bottom: parent.bottom

            width:parent.width
            tabBar: Row {
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 10
                height: 98
                Repeater {
                    delegate: TabviewStyle{
                        tabview: tabView
                        id: tabviewStyle
                        width: tabView.width / tabView.tabModel.count
                        onMsgTabClick: {
                        }
                    }
                    model: tabView.tabModel
                }
            }

            onCurrentIndexChanged: {
                if(currentIndex == 2){
                    var EnOS = {enterID: 454, OrgID: '2920082168215965', type: 4}
                    appClient.queryEnOS(JSON.stringify(EnOS))
                }
            }

            CTab {
                id:sessionListTab
                property url imgSource: "qrc:/res/images/tab_notice.png"
                property url imgActiveSource: imgSource
                property bool newMessage:true

                title: os.i18n.ctr(qsTr("通知"))
                NoticeMain{
                    anchors.fill: parent
                }
            }

            CTab {
                id:contactRootTab
                property url imgSource: "qrc:/res/images/tab_apps.png"
                property url imgActiveSource: imgSource
                property bool newMessage: false

                title: os.i18n.ctr(qsTr("我的应用"))
                AppsMain{
                    anchors.fill: parent
                }

            }

            CTab {
                id:contactStoreTab
                property url imgSource: "qrc:/res/images/tab_contact.png"
                property url imgActiveSource: imgSource
                property bool newMessage: false

                title: os.i18n.ctr(qsTr("通讯录"))
                ContactMain{
                    anchors.fill: parent
                }

            }

            CTab {
                id:userListTab
                property url imgSource: "qrc:/res/images/tab_me.png"
                property url imgActiveSource: imgSource
                property bool newMessage: false

                title: os.i18n.ctr(qsTr("我"))
                MeMain{
                    anchors.fill: parent
                }
            }
        }
    }
}
