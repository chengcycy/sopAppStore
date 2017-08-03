import QtQuick 2.0
import com.syberos.basewidgets 2.0
import "./me"
CPageStackWindow {

//    keyHandle: false
    onBackKey: {
        if(pageStack.depth>1){
            pageStack.pop();
        }else{
            hide();
        }
    }

    Connections{
        target: appClient

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
        onSystemApps:{
            appClient.onGetSystemApps(json);
        }
    }

    initialPage:CPage{
        anchors.fill: parent
        color: "#F7F7FA"
        orientationLock: CPageOrientation.LockPortrait

        onStateChanged: {
            if (status == CPageStatus.WillShow) {
                gScreenInfo.setWindowProperty("STATUSBAR_VISIBLE",true)
                gScreenInfo.setWindowProperty("STATUSBAR_STYLE","transBlack")
            } else if (status == CPageStatus.Show) {

            }
        }
    }
    Component.onCompleted: {
        pageStack.replace(Qt.resolvedUrl('./me/Login.qml'));
    }
}
