import QtQuick 2.0
import com.syberos.basewidgets 2.0
import "../component"

CPage {
    id: appsStore

    property var  appSwipeTabviewModel

    onStatusChanged: {
        if (status === CPageStatus.WillShow) {
            appsStore.statusBarHoldItemColor = "black"

            appsStore.statusBarHoldEnabled = true
            gScreenInfo.setStatusBar(appsStore.statusBarHoldEnabled)
            appsStore.statusBarHoldItemColor = "#edf0f0"
            gScreenInfo.setStatusBarStyle("black")
        } else if (status === CPageStatus.WillHide) {

        }
    }
    contentAreaItem:Rectangle{
        id:store

        color:"#f7f3f7"
        TitleBar{
            id:tBar
            tips: qsTr("应用商店")
            ico:"qrc:/res/images/store_n.png"
            showRightIco: false
            showLeftIco:true
            anchors.top: parent.top
            onClicked: {
                pageStack.pop();
            }
        }

        CSwipeTabView{
            id:appSwipeTabview

            tabVisible: true
            width: parent.width
            tabBar: AppStoreTabStyle{
                tabView: appSwipeTabview
                lineColor: "#f7f7f7"
                tabSpacing:10
                titleColor: '#0000ff'
                titleHighlightColor: 'white'
                titlePixelSize: 28

            }
            anchors.top: tBar.bottom
            anchors.topMargin: 2
            anchors.bottom: parent.bottom
            function addPage(jsonObj,model){
                var component = Qt.createComponent(Qt.resolvedUrl("./AppStoreTab.qml"));
                if (component.status === Component.Ready) {
                    var obj  = component.createObject(appSwipeTabview);
                    obj.title = jsonObj.classifyName;
                    obj.classId = jsonObj.classifyID;
                    obj.listModel = model;
                }
            }
        }
        Component.onCompleted: {
            appClient.queryAppStore(JSON.stringify({ type: "4" }));
        }

        Connections{
            target: appClient
            onCallback:{
                var obj = JSON.parse(json)
                if(obj.fName === 'classifyBeans'){
                    var cls = obj.data.classifyBeans;
                    for(var i=0;i<cls.length;++i){
                        console.log('add page==========================')
                        appSwipeTabview.addPage(cls[i],appSwipeTabviewModel);
                    }
                }else if(obj.fName === 'addApp'){
                    appClient.queryAppStore(JSON.stringify({type: "1"}));
                }
            }
        }
    }
}
