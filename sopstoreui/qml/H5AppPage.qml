import QtQuick 2.3
import com.syberos.basewidgets 2.0
import QtWebKit 3.0
import QtWebKit.experimental 1.0
import QtWebChannel 1.0

import com.app.sopApp 1.0

CPage {
    property alias  webViewPage: webView

    statusBarHoldEnabled: true
    statusBarHoldItemColor: "black"
    orientationPolicy:CPageOrientation.Automatic
    clip: true

    contentAreaItem: Flickable{
        id:root
        anchors.fill: parent
        width:parent.width
        height: parent.height
        clip:true

        Image {
            id: resultImg
            source: "qrc:/res/wellcomepage.png"

            anchors.centerIn: parent
            width:parent.width
            height: parent.height
            z:parent.z - 1
        }

        SopAppClient{
            id:content

            WebChannel.id: "content"
            onOpenApp:{
                var res = JSON.parse(param);
                mainApp.openApp(res.scheme);
            }
            onVoiceCall:{
                var call = "contact://showdialpage?"+param;
                globalApp.openUrl(call);
            }
            onInstallApp:{
                mainApp.install(appPath);
            }
            onUninstallApp:{
                mainApp.uninstall(sopId);
            }
            onGetSystemApps:{
                mainApp.getSystemAppList();
            }
        }
        Connections{
            target: mainApp
            onRefreshData:{
                var json = {"refreshData":true};
                content.onRefreshData(JSON.stringify(json));
            }
            onSystemApps:{
                content.onGetSystemApps(json);
            }
        }

        WebView {
            id: webView



            //      url:'http://172.25.76.6:8080'
            //   url:'http://172.16.16.57:8080'

            z:parent.z + 9999
            url:mainApp.appUrl
            width:parent.width
            height: parent.height
            clip: true
            //interactive:false
            experimental.userAgent:"Mozilla/5.0 (Linux; Android 4.4.2; GT-I9505 Build/JDQ39) AppleWebKit/537.36 (KHTML, like Gecko) Version/1.5 Chrome/28.0.1500.94 Mobile Safari/537.36"
            experimental.minimumScale: false
            experimental.webChannel.registeredObjects : [content]
            visible: false

            //anchors.fill: parent
            onNavigationRequested:{
            }
            onLoadingChanged: {
                switch (loadRequest.status)
                {
                case WebView.LoadSucceededStatus:
                    console.log('loading2:'+webView.url)
                    if(!webView.visible){
                        webView.visible = true;
                        resultImg.visible = false;
                    }
                    break;

                case WebView.LoadFailedStatus:
                    console.log('loading3:'+webView.url)
                    break;
                }
            }
        }
    }

}
