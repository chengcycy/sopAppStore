import QtQuick 2.0
import com.syberos.basewidgets 2.0
import "../component"
Rectangle{
    id:meMain

    color:"#f7f3f7"
    TitleBar {
        id: titleBar
        tips: qsTr("我")
        ico:"qrc:/res/images/search.png"
        showRightIco: false
        anchors.top: parent.top
    }

    CButton {
        id: loginOutButton

        anchors.bottom: parent.bottom
        anchors.bottomMargin: 120
        anchors.horizontalCenter: parent.horizontalCenter
        height:108
        width:parent.width - 80

        opacity:  pressed ? 1.0:0.7
        text:os.i18n.ctr(qsTr("退出登录"))
        textColor:  "white"
        pixelSize: 43

        backgroundComponent: Rectangle {
            anchors.fill: parent
            color:"#313563"
            radius: 16
            border.width: 3
            border.color: "#313563"
        }
        onClicked:
        {
            loadingPage.show();
            appClient.loginout();
        }
    }


    CIndicatorDialog {
        id:loadingPage
        messageText: '正在退出．．．'
    }

    Connections{
        target: appClient
        onCallback:{
            var obj = JSON.parse(json);
            if(obj.fName === 'loginout'){
                loadingPage.hide();
                pageStack.clear();
                pageStack.push(Qt.resolvedUrl('./Login.qml'));
            }
        }
    }
}
