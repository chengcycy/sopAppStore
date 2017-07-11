import QtQuick 2.3
import com.syberos.basewidgets 2.0
import com.app.sopApp 1.0

CPage {
    statusBarHoldEnabled: true
    statusBarHoldItemColor: "white"
    orientationPolicy:CPageOrientation.Automatic
    clip: true

    SopAppClient{
        id:sopApp
    }
    Connections{
        target: sopApp
        onOpenApp:{
            var res = JSON.parse(param);
            mainApp.openApp(res.scheme);
        }
        onVoiceCall:{
            var res = JSON.parse(param);
            mainApp.voiceCall(res.call);
        }
    }

    contentAreaItem: Flickable{
        anchors.fill: parent
        Column{
            anchors.fill: parent
            spacing: 16
            CButton{
                anchors.horizontalCenter: parent.horizontalCenter
                height: 60
                text:"login"
                onClicked: {
                    var json = {"usbkeyidentification":"123455","password":"123456"};
                    sopApp.login(JSON.stringify(json));
                }
            }
            CButton{
                anchors.horizontalCenter: parent.horizontalCenter
                height: 60
                text:"preLogin"
                onClicked: {
                    var json = {"userName":"刘霞"};
                    sopApp.preLogin(JSON.stringify(json));
                }
            }
            CButton{
                anchors.horizontalCenter: parent.horizontalCenter
                height: 60
                text:"loginout"
                onClicked: {
                    sopApp.loginout();
                }
            }
            CButton{
                anchors.horizontalCenter: parent.horizontalCenter
                height: 60
                text:"slidesshow"
                onClicked: {
                    var json = {"type":"5"};
                    sopApp.slidesshow(JSON.stringify(json));
                }
            }
            CButton{
                anchors.horizontalCenter: parent.horizontalCenter
                height: 60
                text:"queryAppStore"
                onClicked: {
                    var json = {"type":"6"};
                    sopApp.queryAppStore(JSON.stringify(json));
                }
            }
            CButton{
                anchors.horizontalCenter: parent.horizontalCenter
                height: 60
                text:"queryEnOS"
                onClicked: {
                    var json = {"type":"6"};
                    sopApp.queryEnOS(JSON.stringify(json));
                }
            }
        }
    }

}
