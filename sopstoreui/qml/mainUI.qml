import QtQuick 2.0
import com.syberos.basewidgets 2.0
import com.app.sopApp 1.0

import "./me"
CPageStackWindow {

    keyHandle: false
    onBackKey: {
        if(pageStack.depth>1){
            pageStack.pop();
        }else{
            hide();
        }
    }

    SopAppClient{
        id:appClient

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
        onLoginoutUI:{
            mainApp.closeBrowser();
        }
        onCallback:{
            console.log('=================json:'+json)

            var obj = JSON.parse(json);
            if(obj.fName === 'preLogin'){
                showUserLstPage(JSON.stringify(obj.data));
            }else if(obj.fName === 'login'){
                showMainClientPage(json);
            }
            loadingPage.hide();
        }
    }
    Connections{
        target: mainApp
        onRefreshData:{
            var json = {"refreshData":true};
            appClient.onRefreshData(JSON.stringify(json));
        }
        onSystemApps:{
            appClient.onGetSystemApps(json);
        }
    }

    initialPage:Login{
        id: startPage

        property string passwd: ''
        property string userInfo:''

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
        onLoginClicked:{
            var json = {"userName":userName}
            startPage.passwd = passwd;
            loadingPage.toolTip = qsTr("正在请求登录")
            loadingPage.show();
            appClient.preLogin(JSON.stringify(json));
        }
    }
    CIndicatorDialog {
        id:loadingPage
        property string toolTip: ""
        messageText: os.i18n.ctr(toolTip)
    }
    /////////////////////////////////////////////////////////////////
    function showUserLstPage(data){
        var arr = JSON.parse(data);
        if(arr.length === 0){
            gToast.requestToast('登录失败',"","");
        }else if(arr.length === 1){
            startPage.userInfo = JSON.stringify(arr[0]);
            login();
        }else{
            var page = pageStack.push(Qt.resolvedUrl('./me/LoginUserSelectList.qml'));
            page.setModelData(data);
            page.callback.connect(function(data){
                startPage.userInfo = data;
                login();
            });
        }
    }
    function login(){
        var obj = JSON.parse(startPage.userInfo);
        var data = {usbkeyidentification:obj.usbkeyidentification,password:startPage.passwd}

        loadingPage.toolTip = qsTr("正在登录．．．")
        loadingPage.show();
        appClient.login(JSON.stringify(data));
    }

    function showMainClientPage(data){
        var obj = JSON.parse(data);
        if(obj.data.code === 0){
            pageStack.clear();
            var page = pageStack.push(Qt.resolvedUrl('./MainClient.qml'));
        }else{
            gToast.requestToast('登录失败:'+obj.data.code,"","");
        }
    }
}
