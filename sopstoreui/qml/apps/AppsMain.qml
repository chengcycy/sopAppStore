import QtQuick 2.0
import com.syberos.basewidgets 2.0
import "../component"

Rectangle{
    id:appsMain

    property string classicJson

    color:"#f7f3f7"
    TitleBar{
        id:tBar
        tips: qsTr("应用")
        ico:"qrc:/res/images/store_n.png"
        anchors.top: parent.top
        onClicked: {
            if(pos === 0){
                var page = pageStack.push(Qt.resolvedUrl("./AppsStore.qml"));
                page.appSwipeTabviewModel = appSwipeTabviewModel;
                page.classicJson = classicJson;
                tBar.showRedPoint = false;
            }
        }
    }
    /////////////////AppsStore/////////////////////
    ListModel{
        id:appSwipeTabviewModel
    }
    function updateAllsApps(appId,propertyName,value){
        for(var i=0;i<appSwipeTabviewModel.count;++i){
            console.log('===============================:'+appSwipeTabviewModel.get(i).id+',appId:'+appId)
            if(appSwipeTabviewModel.get(i).id ===appId){
                appSwipeTabviewModel.setProperty(i,propertyName,value);
                break;
            }
        }
    }

    /////////////////轮播图/////////////////////
    SlidesshowArea
    {
        id:slides
        width:parent.width
        height: 360
        anchors.top: tBar.bottom
    }
    SlidesshowIndicator {
    }

    //////////////////////应用列表///////////////////////
    MyAppsListArea{
        id:myApps
        width: parent.width

        anchors.top: slides.bottom
        anchors.bottom: parent.bottom
    }
    //////////////////////////////////////////////////

    Component.onCompleted: {
        slidesshow();
    }

    /*
    1.　已安装
    2.　未安装
    3.　需更新
    4.　正在安装
    */
    function appInstallStatus(app){

        var sysApps = JSON.parse(mainApp.getSystemAppList());
        var myApps = (JSON.parse(appClient.myApps)).appInfos;
        var findApped = false;
        for(var i=0;i<myApps.length;++i){
            if(myApps[i].appClassify.classifyID === app.classify){
                var items = myApps[i].appInfoList;
                for(var j=0;j<items.length;++j){
                    //                        console.log('id:'+app.id+',id2:'+items[j].id)
                    if(items[j].id === app.id){
                        findApped = true;
                        break;
                    }
                }
                if(findApped){
                    break;
                }
            }
        }
        if(!findApped){
            return 2;
        }else if(app.type === 1){//sop
            var sopId = app.packageName.split('-')[0];
            console.log('hhhhhhhhhhhhhhhh:'+sopId+',hasPro:'+sysApps.hasOwnProperty(sopId))
            if(sysApps.hasOwnProperty(sopId)){
                console.log('ver11:'+sysApps.valueOf(sopId)+',app:'+app.version);
                var newVersion = app.version.replace('V','');
                newVersion = app.version.replace('v','');
                if(sysApps.valueOf(sopId).ver < newVersion){
                    tBar.showRedPoint = true;
                    return 3;
                }else
                {
                    return 1;
                }
            }else{
                return 2;
            }
        }else{
            return 1;
        }
    }

    function slidesshow(){
        slides.visible = false;
        tBar.showLoad = true;
        tBar.showRightIco = false;
        var obj = {type: "5"}
        appClient.slidesshow(JSON.stringify(obj));
    }
    function getMyAppList(){
        var obj = {type: "1"}
        appClient.queryAppStore(JSON.stringify(obj));
    }
    ///////////////////////////////////////////////////////////
    function handleSlidesshow(obj){
        slides.tabModel.clear();
        for(var i=0;i<obj.data.length;++i){
            slides.addPage(JSON.stringify(obj.data[i]));
        }
        getMyAppList();
    }
    function handleMyApps(obj){
        myApps.myAppsModel.clear();
        var hasWorkApp = false;
        var hasChatApp = false;

        for(var i=0;i<obj.length;++i){
            var item = obj[i];
            var arr=[];
            if(item.appClassify.classifyName === '办公应用'){
                arr = initOfficeApps(item.appInfoList);
                hasWorkApp = true;
            }else if(item.appClassify.classifyName === '通讯应用'){
                arr = initChatApps(item.appInfoList);
                hasChatApp = true;
            }else {
                arr = item.appInfoList;
            }
            item.appInfos = JSON.stringify(arr);
            myApps.myAppsModel.append(item);
        }

        if(!hasWorkApp){
            var classic = {appClassify:{classifyName:'办公应用'},appInfos:JSON.stringify(initOfficeApps(null))};
            myApps.myAppsModel.insert(0,classic);
            hasWorkApp = true;
        }

        if(!hasChatApp){
            classic = {appClassify:{classifyName:'通讯应用'},appInfos:JSON.stringify(initChatApps(null))};
            var pos = hasWorkApp?1:0;
            myApps.myAppsModel.insert(pos,classic);
        }

        appClient.queryAppStore(JSON.stringify({ type: "2" }));
    }

    Connections{
        target: appClient
        onCallback:{
            var obj = JSON.parse(json)
            if(obj.fName === 'slidesshow'){
                handleSlidesshow(obj);
            }else if(obj.fName === 'appInfos'){
                handleMyApps(obj.data.appInfos);
            }else if(obj.fName === 'appStores'){
                handleGetAllApss(obj);

            }if(obj.fName === 'classifyBeans'){
                appsMain.classicJson = json;
                tBar.showLoad = false;
                tBar.showRightIco = true;
            }else if(obj.fName === 'addApp'){
                appClient.queryAppStore(JSON.stringify({type: "1"}));
            }else if(obj.fName === 'progress'){
                var app = JSON.parse(appClient.downloadingApps);
                appsMain.updateAllsApps(app.id,'progress',obj.data.progress+'');
            }else if(obj.fName === 'downloadApp'){
                var curApp = JSON.parse(appClient.downloadingApps);
                if(obj.data.code){
                    appClient.installSopApp(curApp.packageName);
                    appsMain.updateAllsApps(curApp.id,'progress','');
                    appsMain.updateAllsApps(curApp.id,'appInstall',1);
                    appClient.queryAppStore(JSON.stringify({ type: "6", id:curApp.id,classify:curApp.classify}));
                }else{
                    appsMain.updateAllsApps(curApp.id,'progress','');
                    appsMain.updateAllsApps(curApp.id,'appInstall',2);
                    gToast.requestToast('安装包下载失败，请重新安装！',"","");
                }
                appClient.downloadingApps = '';
            }
        }
    }
    function handleGetAllApss(obj){

        if(tBar.showLoad){
            slides.visible = true;
            slides.startTimer();

            var apps = obj.data.appStore.appInfoList;
            if(apps.length>0){
                appSwipeTabviewModel.clear();
            }

            for(var j=0;j<apps.length;++j){
                var item = apps[j];
                var status = appInstallStatus(apps[j]);
                item.appInstall = status;
                item.progress = "";
                appSwipeTabviewModel.append(item);
            }
            //classic
            appClient.queryAppStore(JSON.stringify({ type: "4" }));
        }
    }

    function initChatApps(arr){
        var apps=[];
        var userInfor = JSON.parse(appClient.curUserInfo);
        var tgyy = { id: 100002, type: 1, name: "天工圆圆", icon: 'qrc:/res/images/TGYY.png', activityName: 'linkdood:showlinkdood?id='+userInfor.usbkeyidentification};
        apps[0] = tgyy;

        for(var i = 0;(arr!==null) && i<arr.length;++i){
            apps[apps.length] = arr[i];
        }
        return apps;
    }

    function initOfficeApps(arr){
        var apps=[];
        var userInfor = JSON.parse(appClient.curUserInfo);
        console.log('dddddddddddddddddddddddd:'+appClient.curUserInfo)

        var gwgl = { id: 100001, type: 1, name: "公文管理", icon: 'qrc:/res/images/GWGL.png', activityName: 'casicoa:showOA?pid='+userInfor.usbkeyidentification+'&sessionID=54545333' };
        var sfml = { id: 100004, type: 2, name: "安全邮件", icon: 'qrc:/res/images/YJ.png', homeUrl: 'http://10.152.36.31/secmail/loginapp.do?type=cid&PID='+userInfor.usbkeyidentification};
        var xifb = { id: 100003, type: 2, name: "信息发布", icon: 'qrc:/res/images/XXFB.png', homeUrl: 'http://info.casic.cs/jeecms2/index/mobile/'};

        var url = 'http://10.152.36.26:8080/portal/menu.jsp?userName='+userInfor.usbkeyname+'&PID='+userInfor.usbkeyidentification;//+'&webService=&SessionID='
        var xtbg = { id: 100000, type: 2, name: "协同办公", icon: 'qrc:/res/images/TGYY.png', homeUrl: url };

        if(userInfor.unitId === '1'){
            apps[apps.length] = xtbg;
        }else{
            apps[apps.length] = gwgl;
        }
        apps[apps.length] = sfml;
        apps[apps.length] =  xifb;

        for(var i = 0;(arr!==null) && i<arr.length;++i){
            apps[apps.length] = arr[i];
        }
        return apps;
    }
}
