import QtQuick 2.0
import com.syberos.basewidgets 2.0
import "../component"

Rectangle{
    color:"#f7f3f7"

    TitleBar{
        id:tBar
        tips: qsTr("应用")
        ico:"qrc:/res/images/store_n.png"
        anchors.top: parent.top
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
        getMyAppList();
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
        for(var i=0;i<obj.data.length;++i){
            slides.addPage(JSON.stringify(obj.data[i]));
        }
        tBar.showLoad = false;
        tBar.showRightIco = true;
        slides.visible = true;
        slides.startTimer();
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
    }

    Connections{
        target: appClient
        onCallback:{
            var obj = JSON.parse(json)
            if(obj.fName === 'slidesshow'){
                handleSlidesshow(obj);
            }else if(obj.fName === 'appInfos'){
                handleMyApps(obj.data.appInfos);
            }
        }
    }

    function initChatApps(arr){
        var apps=[];
        var userInfor = JSON.parse(appClient.curUserInfo);
        var tgyy = { id: 100002, type: 1, name: "天工圆圆", icon: 'qrc:/res/images/TGYY.png', activityName: 'linkdood:showlinkdood?pid='+userInfor.usbkeyidentification, sysApp: true };
        apps[0] = tgyy;

        for(var i = 0;(arr!==null) && i<arr.length;++i){
            apps[apps.length] = arr[i];
        }
        return apps;
    }

    function initOfficeApps(arr){
        var apps=[];
        var userInfor = JSON.parse(appClient.curUserInfo);

        var gwgl = { id: 100001, type: 1, name: "公文管理", icon: 'qrc:/res/images/GWGL.png', activityName: 'casicoa:showOA?pid='+userInfor.usbkeyidentification+'&sessionID=54545333', sysApp: true };
        var sfml = { id: 100004, type: 2, name: "安全邮件", icon: 'qrc:/res/images/YJ.png', homeUrl: 'http://10.152.36.31/secmail/loginapp.do?type=cid&PID='+userInfor.usbkeyidentification, sysApp: true };
        var xifb = { id: 100003, type: 2, name: "信息发布", icon: 'qrc:/res/images/XXFB.png', homeUrl: 'http://info.casic.cs/jeecms2/index/mobile/', sysApp: true };

        var url = 'http://10.152.36.26:8080/portal/menu.jsp?userName='+userInfor.usbkeyname+'&PID='+userInfor.usbkeyidentification+'&webService=&SessionID=';
        var xtbg = { id: 100000, type: 2, name: "协同办公", icon: 'qrc:/res/images/TGYY.png', homeUrl: url, sysApp: true };

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
