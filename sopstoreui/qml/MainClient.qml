import QtQuick 2.0
import com.syberos.basewidgets 2.0
import "./component"
import "./apps"
import "./contacts"
import "./me"
import "./notice"

CPage {
    id: mainClient

    property string openAppUrl
    property int    msgCount:0
    property string baseUrl: 'http://ieop.casic.cs:8080/adp/mobileV2/formpostH5.ht?sid='+mainApp.sid+'&systemId='
    onStatusChanged: {
        if (status === CPageStatus.WillShow) {
            mainClient.statusBarHoldItemColor = "black"

            mainClient.statusBarHoldEnabled = true
            gScreenInfo.setStatusBar(mainClient.statusBarHoldEnabled)
            mainClient.statusBarHoldItemColor = "#edf0f0"
            gScreenInfo.setStatusBarStyle("black")
        } else if (status === CPageStatus.WillHide) {

        }
    }

    Connections{
        target: appClient
        onCallback:{
            var obj = JSON.parse(json)
            if(obj.fName === 'getLoginAuthCode'){
                var authCode = obj.data.authCode;
                var app = { "scheme": openAppUrl+'&authcode='+ authCode};
                console.log('===============================openApp:'+JSON.stringify(app))
                appClient.opensopApp(JSON.stringify(app));
            }
        }
    }

    contentAreaItem: Item {
        anchors.fill: parent
        NewTabView{
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
//                if(currentIndex == 2){
//                    var obj = JSON.parse(appClient.curUserInfo)
//                    var EnOS = {enterId: 454, orgId: obj.unitId, type: 4}
//                    appClient.queryEnOS(JSON.stringify(EnOS))
//                }
            }

            CTab {
                id:sessionListTab
                opacity: 1.0
                property url imgSource: "qrc:/res/images/tab_notice.png"
                property url imgActiveSource: imgSource
                property bool newMessage:msgCount>0

                title: os.i18n.ctr(qsTr("通知"))
                NoticeMain{
                    anchors.fill: parent
                }
            }

            CTab {
                id:contactRootTab
                opacity: 1.0
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
                opacity: 1.0
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
                opacity: 1.0
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
