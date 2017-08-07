import QtQuick 2.0
import com.syberos.basewidgets 2.0
import QtQml.Models 2.1

import "../component"
import "../Helper.js" as Helper
Rectangle{
    id:noticeMain

    color:"#f7f3f7"
    property var  userObj: JSON.parse(appClient.curUserInfo)
    property bool needRefreshData: false
    //////////////////////////////////////////////////////////////////

    function handleOfflineMsg(){
        var msgs = JSON.parse(appClient.getOfflineMsg());
        console.log('//////////////////////////////////////');
        for(var i=0 ;i<msgs.length;++i){
            handleRecMsg(msgs[i]);
        }
    }
    function handleRecMsg(msgObj){
        var appMsg = JSON.parse(msgObj.message);
        var app = findAppInforByAppName(appMsg.appName);
        if(app !== null){
            var newUrl = app.type===1?app.activityName:app.homeUrl;
            newUrl = newUrl.replace("{{idCard}}",app.key);

            var noticeData = {
                msgId:msgObj.msgId,
                targetId:msgObj.targetId,
                showUnread:msgObj.showUnread,
                id:app.id,
                key:app.key,
                img: app.icon,
                name: app.name,
                msg: appMsg.msg,
                time: formatTime(appMsg.time),
                notice:  msgObj.showUnread ? appMsg.unReadCount+'':"0",
                                             url: newUrl,
                                             statistics: '{"type":"8","appType":"'+app.type+'","appID":"'+app.id+'","orgID":'+userObj.orgID+',"unitID":'+userObj.unitId+',"orgCode":'+userObj.orgCode+'}'
            };

            var index = -1;
            for(var i=0;i<noticeModel.count;++i){
                console.log('id:'+noticeModel.get(i).id+',app:'+app.id+',nm:'+app.name)
                if(noticeModel.get(i).id === app.id){
                    index = i;
                    break;
                }
            }
            if(index === -1){
                noticeModel.append(noticeData);
                if(msgObj.showUnread){
                    mainClient.msgCount += parseInt( noticeData.notice);
                }
            }else{
                console.log('msg:'+appMsg.msg+',tm:'+appMsg.time+',index:'+index)
                noticeModel.setProperty(index,'msg',appMsg.msg);
                noticeModel.setProperty(index,'time',formatTime(appMsg.time));

                if(msgObj.showUnread){
                    mainClient.msgCount += parseInt(noticeData.notice);
                    mainClient.msgCount -= parseInt( noticeModel.get(index).notice);
                }
                noticeModel.setProperty(index,'notice',noticeData.notice);
            }
        }
    }
    function findAppInforByAppName(appName){

        console.log('find ========================:'+appName)
        var myApps = JSON.parse(appClient.myApps).appInfos;
        for(var i=0;i<myApps.length;++i){
            var apps = myApps[i].appInfoList;
            for(var j=0;j<apps.length;++j){
                if(apps[j].name === appName){

                    return apps[j];
                }
            }
        }
        return null;
    }

    Connections{
        target: mainApp
        onRefreshData:{
            if(needRefreshData){
                if((userObj.unitId+'') === "1"){
                    getXTBG();
                }else{
                    getGWGL();
                }
                getMail();
            }
            needRefreshData = false;
        }
    }
    Connections{
        target: appClient
        onCallback:{
            var obj = JSON.parse(json);
            if(obj.fName === 'noticeLastMsg'){
                handleRecMsg(obj.data);
            }
        }
    }

    function isSysApp(id){
        var ids = [100000,100001,100002,100003,100004];
        for(var i=0;i<ids.length;++i){
            if(id===ids[i]){
                return true;
            }
        }
        return false;
    }
    function initSysApp(){
        noticeModel.clear();
        if((userObj.unitId+'') === "1"){
            var XXFB = { // 信息发布
                id:100000,
                key:'',
                img: 'qrc:/res/images/XXFB.png',
                name: '协同办公',
                msg: "",
                time: '',
                notice: '',
                url: 'http://10.152.36.26:8080/page_m/dblist.jsp?userName=' +userObj.enname + '&PID=' + userObj.usbkeyidentification + '&webService=',
                statistics: '{"type":"8","appType":"2","appID":"100000","orgID":'+userObj.orgID+',"unitID":'+userObj.unitId+',"orgCode":'+userObj.orgCode+'}'
            }
            noticeModel.insert(0,XXFB);
            getXTBG();
        }else{
            var noticeData = { // 公文管理
                id:100001,
                key:'',
                img: 'qrc:/res/images/GWGL.png',
                name: '公文管理',
                msg: '暂无待处理公文',
                time: '',
                notice: "0",
                url: 'casicoa:showOA?pid='+userObj.usbkeyidentification+'&sessionID=54545333' ,
                statistics: '{"type":"8","appType":"1","appID":"100001","orgID":'+userObj.orgID+',"unitID":'+userObj.unitId+',"orgCode":'+userObj.orgCode+'}'
            };
            noticeModel.insert(0,noticeData);
            getGWGL();
        }
        var AQYJ = { // 安全邮件
            id:100004,
            key:'',
            img: 'qrc:/res/images/YJ.png',
            name: '安全邮件',
            msg: '暂无待处理邮件',
            time: '',
            notice: '0',
            url: 'http://10.152.36.20/secmail/loginapp.do?type=cid&type2=Unread&PID='+userObj.usbkeyidentification,
            statistics: '{"type":"8","appType":"2","appID":"100004","orgID":'+userObj.orgID+',"unitID":'+userObj.unitId+',"orgCode":'+userObj.orgCode+'}'
        }
        noticeModel.insert(1,AQYJ);
        getMail();
    }

    function getGWGL(){
        var url = 'http://10.152.36.33:8080/CasicOA/std/entity/page_data.tsp?objectName=WfActivity!portal&objectEvent=Query&$bizId=my_all_without_doc_mobile&isMobile=y&PID='+userObj.usbkeyidentification
        Helper.requestHttps(url,function(res){
            console.log('getGWGL:'+res);
            var data =JSON.parse(res);
            if (data.pageData.length > 0) {
                var date = Date.parse(data.pageData[0].startTime.replace(/-/gi, "/"))
                var number = data.pageData.length
                mainClient.msgCount +=number;
//                if (number > 99) number = '99+'
                noticeModel.setProperty(0,'msg',data.pageData[0]["wfInstance.description"]);
                noticeModel.setProperty(0,'time',formatTime(date));
                noticeModel.setProperty(0,'notice',number+'');
            }else{
                noticeModel.setProperty(0,'notice','0');
            }
        });
    }

    function getXTBG(){
        var url = 'http://10.152.36.26:8080/CASIC/interfaces/304DaiBanInterface.jsp?userName=' + userObj.enname + '&PID=' + userObj.usbkeyidentification + '&webService=';
        Helper.requestHttps(url,function(res){
            console.log('getXTBG:'+res);

            var number = parseInt(cutString(res, "wdNum>", "<"))
            mainClient.msgCount +=number;
//            if (number > 99) number = '99+'
            var date = Date.parse(cutString(res, "SentTime>", "<").replace(/-/gi, "/"))
            noticeModel.setProperty(0,'msg',cutString(res, "Title>", "<"));
            noticeModel.setProperty(0,'time',formatTime(date));
            noticeModel.setProperty(0,'notice',number+'');
        })
    }

    function getMail(){
        var url = 'http://10.152.36.31/secmail/GetAppUnreadFileService?id_card='+userObj.usbkeyidentification+'&username=secmail&password=welcome'
        Helper.requestHttps(url,function(res){
            console.log('getMail:'+res);
            var data = JSON.parse(res);
            if (data.length > 0) {
                var date = Date.parse(data[0].send_date.replace(/-/gi, "/"))
                var number = parseInt(data[0].count)
                mainClient.msgCount +=number;
//                if (number > 99) number = '99+'
                noticeModel.setProperty(1,'msg',data[0].subject);
                noticeModel.setProperty(1,'time',formatTime(date));
                noticeModel.setProperty(1,'notice',number+'');
            }else{
                noticeModel.setProperty(1,'notice','0');
            }
        })
    }

    function formatTime(nS) {
        var result;
        if (nS < 10000000000) nS = nS * 1000
        var diffValue = new Date().getTime() - nS;
        if (diffValue < 0) {
            return "时间戳错误";
        }
        var monthC = parseInt(diffValue / 2592000000);
        var weekC = parseInt(diffValue / (7 * 86400000));
        var dayC = parseInt(diffValue / 86400000);
        var hourC = parseInt(diffValue / 3600000);
        var minC = parseInt(diffValue / 60000);
        if (monthC >= 1) {
            result = monthC + "月前";
        } else if (weekC >= 1) {
            result = weekC + "周前";
        } else if (dayC >= 1) {
            result = dayC + "天前";
        } else if (hourC >= 1) {
            result = hourC + "小时前";
        } else if (minC >= 1) {
            result = minC + "分钟前";
        } else {
            result = "刚刚";
        }
        return result;
    }
    function cutString(original, before, after, index) {
        index = index || 0;
        if (typeof index === "number") {
            const P = original.indexOf(before, index);
            if (P > -1) {
                if (after) {
                    const f = original.indexOf(after, P + 1);
                    return (f > -1) ? original.slice(P + before.toString().length, f) :
                                      console.error("owo [在文本中找不到 参数三 " + after + "]");
                }
                else {
                    return original.slice(P + before.toString().length);
                }
            }
            else {
                console.error("owo [在文本中找不到 参数一 " + before + "]");
            }
        }
        else {
            console.error("owo [sizeTransition:" + index + "不是一个整数!]");
        }
    }

    Component.onCompleted: {
        initSysApp();
        handleOfflineMsg();
    }

    TitleBar {
        id: titleBar
        tips: qsTr("通知")
        ico:"qrc:/res/images/search.png"
        showRightIco: false
        anchors.top: parent.top
    }
    ListModel{
        id:noticeModel
    }

    ListView {
        id: noticeLst

        anchors.top: titleBar.bottom
        anchors.topMargin: 2
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        property var selectedItem: null

        clip: true
        function unsetSelectedItem()
        {
            if (selectedItem) {
                selectedItem.toInitState();
                selectedItem = null;
            }
        }
        function setSelectedItem(item) {
            if (selectedItem !== item) {
                unsetSelectedItem();
                selectedItem = item;
            }
        }

        displaced: Transition {
            NumberAnimation { properties: "x,y"; easing.type: Easing.OutQuad }
        }

        Behavior on contentY {
            NumberAnimation { duration: 200 }
        }
        model: DelegateModel {
            id: visualModel
            model: noticeModel
            delegate: Item {
                id: rootItem

                width: parent.width
                height: 130
                property int visualIndex: DelegateModel.itemsIndex
                SlideDelegate {
                    id: delegateRoot
                    anchors.fill: parent

                    onPositionChanged: {
                        if(!delegateRoot.pressed){
                            background.color=noticeMain.color;
                        }
                    }
                    onPressed: background.color="#CDCDCD"
                    onReleased: background.color=noticeMain.color
                    onCanceled: background.color=noticeMain.color
                    onClicked: {
                        if(isSysApp(id)){
                            var app = { "scheme": url }
                            appClient.opensopApp(JSON.stringify(app));
                            appClient.queryAppStore(statistics);
                        }else{
                            mainClient.openAppUrl = url;

                            var data = {appID: key + ""};
                            appClient.getLoginAuthCode(JSON.stringify(data));
                            var msg = {msgId:msgId,targetId:targetId};
                            appClient.setMessageRead(JSON.stringify(msg));
                        }
                        appClient.queryAppStore(statistics);
                        if(isSysApp(id)){
                            needRefreshData = true;
                            var pos = index==0?1:0;
                            var countMsg = parseInt(noticeModel.get(pos).notice);
                            mainClient.msgCount -=countMsg;
                            if(mainClient.msgCount<0){
                                mainClient.msgCount = 0;
                            }
                        }
                        var count = parseInt(notice);
                        mainClient.msgCount -= count;
                        if(mainClient.msgCount<0){
                            mainClient.msgCount = 0;
                        }
                        noticeModel.setProperty(index,'notice','0');
                    }

                    onSlideFinished: {
                        noticeLst.setSelectedItem(delegateRoot);
                    }

                    _rightMenuItem: isSysApp(id)?null :rigthMenu

                    property Item rigthMenu: Item {
                        width: 130
                        height: delegateRoot.height

                        Rectangle {
                            anchors.fill: parent

                            color: "red"
                            Text{
                                anchors.centerIn: parent
                                text:qsTr("删除")
                                font.pixelSize: 34
                                color:"white"
                            }
                        }

                        MouseArea {
                            anchors.fill: parent
                            onClicked: {
                                var count = parseInt(notice);
                                mainClient.msgCount -= count;
                                if(mainClient.msgCount<0){
                                    mainClient.msgCount = 0;
                                }
                                noticeModel.remove(index);
                            }
                        }
                    }

                    property Item contentItem: Rectangle {
                        id: cellItem

                        parent:delegateRoot.slideItem

                        anchors.fill: delegateRoot.slideItem
                        anchors.margins: 1


                        Rectangle {
                            width: cellItem.width
                            height: cellItem.height

                            Rectangle {
                                id : mousePressBackgroud
                                anchors.fill: parent
                                visible: false
                                color: noticeMain.color
                            }
                            Rectangle {
                                id : background

                                anchors.fill: parent
                                color:noticeMain.color

                                RectHeadComponent{
                                    id: headPortraitImage

                                    anchors.left: parent.left
                                    anchors.leftMargin: 19
                                    anchors.verticalCenter: parent.verticalCenter
                                    iconSource: img

                                }
                                Rectangle{
                                    id:unreadcount

                                    anchors.top: headPortraitImage.top
                                    anchors.right: headPortraitImage.right
                                    anchors.topMargin: -width/2
                                    anchors.rightMargin: -width/2

                                    width:notice=='99+'?42:38
                                    height: width
                                    radius: width/2
                                    visible: notice !== '0'
                                    color:"red"
                                    Text{
                                        font.pixelSize: 20
                                        anchors.centerIn: parent
                                        color:"white"
                                        text:notice
                                    }
                                }

                                Text {
                                    id: nameText

                                    anchors.left: headPortraitImage.right
                                    anchors.leftMargin:30
                                    anchors.right: timeText.left
                                    anchors.rightMargin: 20
                                    anchors.top: parent.top
                                    anchors.topMargin: 25

                                    font.pixelSize: 30
                                    height: 33
                                    clip: true
                                    color: "#000000"
                                    verticalAlignment: Text.AlignVCenter
                                    elide: Text.ElideRight
                                    text: name
                                }
                                Text{
                                    id:tipText
                                    anchors.left: headPortraitImage.right
                                    anchors.leftMargin: 30
                                    anchors.bottom: parent.bottom
                                    anchors.bottomMargin: 10
                                    anchors.top: nameText.bottom
                                    anchors.topMargin: 10
                                    color: "red"

                                    font.pixelSize: 26
                                    visible: false
                                    text:""
                                }

                                CLabel{
                                    id: contentText

                                    anchors.left: !tipText.visible?headPortraitImage.right:tipText.right
                                    anchors.leftMargin: !tipText.visible?30:10
                                    anchors.bottom: parent.bottom
                                    anchors.bottomMargin: 10
                                    anchors.top: nameText.bottom
                                    anchors.topMargin: 10

                                    font.pixelSize: 24
                                    clip: true
                                    width:460
                                    elide: Text.ElideRight
                                    color: "#A5A5A5"
                                    text: msg
                                }

                                Text {
                                    id: timeText

                                    anchors.right: parent.right
                                    anchors.rightMargin: noticeLst.editing ? 100 : 22
                                    anchors.top: nameText.top
                                    height: nameText.height
                                    verticalAlignment: Text.AlignVCenter

                                    font.pixelSize: 22
                                    color: "#B8B8B8"

                                    text:time
                                }
                            }
                        }

                        CLine {
                            width: parent.width
                            anchors.left: parent.left
                            anchors.leftMargin: 19
                            color:"#dedfdc"
                            anchors.right: parent.right
                            anchors.bottom: parent.bottom
                            z: parent.z+2
                        }
                        DropArea {
                            id: dropArea
                            anchors { fill: parent; margins: 15 }

                            onEntered: visualModel.items.move(drag.source.visualIndex, rootItem.visualIndex)
                        }
                    }
                }
            }
        }
        CScrollDecorator{
            flickableItem: noticeLst
        }
    }
}
