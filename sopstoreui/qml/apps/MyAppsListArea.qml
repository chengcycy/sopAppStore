import QtQuick 2.0
import com.syberos.basewidgets 2.0
import "../component"
Item{
    id:myApps
    property  alias  myAppsModel:myAppsLst.model
    property  string openAppUrl:''


    function isSysApp(id){
        var ids = [100000,100001,100002,100003,100004];
        for(var i=0;i<ids.length;++i){
            if(id===ids[i]){
                return true;
            }
        }
        return false;
    }

    ListModel{
        id:myAppsLstModel
    }
    ListView{
        id:myAppsLst

        model:myAppsLstModel
        anchors.fill: parent
        clip: true
        delegate: Item {
            id:appDelegete
            width: parent.width
            height: childrenRect.height

            property var appsClassic:appClassify
            onAppsClassicChanged: {
                var appInfoList = JSON.parse(appInfos);
                for(var i=0;i<appInfoList.length;++i){
                    var item = appInfoList[i];
                    myAppsgridModel.append(item);
                }
            }
            function rmItem(){
                myAppsLstModel.remove(index,1);
            }

            Rectangle{
                id: classic
                height: 60
                width: parent.width
                color: "#ffffff"
                border.width: 1
                border.color: "#e6e3e6"

                anchors.top: parent.top
                Text{
                    text:appClassify.classifyName
                    font.pixelSize: 32
                    color:"#7b7b7b"

                    anchors.left: parent.left
                    anchors.leftMargin: 30
                    anchors.verticalCenter: parent.verticalCenter
                }
            }
            ListModel{
                id:myAppsgridModel
            }
            GridView{
                id: grid

                function row(){
                    var r = grid.count%4;
                    if(r==0){
                        return 160*grid.count/4;
                    }else{
                        return 160*(grid.count/4+1);
                    }
                }

                anchors.top: classic.bottom
                anchors.left: parent.left

                width: parent.width
                height:  row()
                model:myAppsgridModel

                cellWidth: grid.width/4
                cellHeight: cellWidth -10
                clip: true
                interactive: false
                delegate: Rectangle{
                    id:appsDele

                    width: grid.cellWidth
                    height: grid.cellHeight
                    color:'transparent'

                    RectHeadComponent{
                        id:appIco

                        iconSource: icon
                        //                        sourceSize: Qt.size(88,88)

                        anchors.horizontalCenter: parent.horizontalCenter
                        anchors.top: parent.top
                        anchors.topMargin: 10
                        MouseArea{
                            anchors.fill: parent
                            onPressed:appsDele.color = '#d6d6d6'
                            onCanceled:appsDele.color = 'transparent'
                            onReleased:appsDele.color = 'transparent'
                            onPressAndHold: {
                                if(isSysApp(id)){
                                    gToast.requestToast("系统应用不能删除！","","");
                                    return;
                                }
                                rmIco.visible = true;
                            }
                            onClicked: {
                                if(rmIco.visible){
                                    rmIco.visible = false;
                                }else{

                                    if(type === 1){
                                        var sysApps = JSON.parse(mainApp.getSystemAppList());
                                        if(id !== 100001){
                                            var sopId = (id === 100002)?'com.vrv.linkDood':packageName.split('-')[0];
                                            if(!sysApps.hasOwnProperty(sopId)){
                                                gToast.requestToast('系统未安装"'+name+'"应用，请在应用商店安装后再使用！',"","");
                                                return;
                                            }
                                        }
                                    }

                                    if(isSysApp(id)){
                                        console.log('111111111111111111111111111111111111111111')
                                        var newUrl = type===1?activityName:homeUrl;
                                        var app = { "scheme": newUrl }
                                        appClient.opensopApp(JSON.stringify(app));
                                    }else{

                                        newUrl = type===1?activityName:homeUrl;
                                        newUrl = newUrl.replace("{{idCard}}",key);
                                        if(type === 2){
                                            var appUrl = { "scheme": newUrl }
                                            appClient.opensopApp(JSON.stringify(appUrl));
                                        }else{
                                            mainClient.openAppUrl = newUrl+'&appsecret='+secret;

                                            var data = {appID: key + ""};
                                            appClient.getLoginAuthCode(JSON.stringify(data));
                                        }
                                    }
                                    var userInfor = JSON.parse(appClient.curUserInfo);
                                    var statisticalData = JSON.stringify({ type: "8", appType: type+'', appID: id + "", orgID: userInfor.orgID, unitID: userInfor.unitId, orgCode: userInfor.orgCode })
                                    appClient.queryAppStore(statisticalData);
                                }
                            }
                        }
                    }
                    Image{
                        id:rmIco
                        visible: false
                        height: 60
                        width: height
                        source: "qrc:/res/images/rm_app.png"

                        anchors.top:appIco.top
                        anchors.topMargin: -20
                        anchors.left: appIco.right
                        anchors.leftMargin: -30
                        MouseArea{
                            anchors.fill: parent
                            onClicked: {
                                appClient.queryAppStore(JSON.stringify({ type: "7", id:id}));
                                appsMain.updateAllsApps(id,'appInstall',2);

                                myAppsgridModel.remove(index,1);
                                if(grid.count<=0){
                                    appDelegete.rmItem();
                                }
                            }
                        }
                    }

                    Text{
                        id:appName

                        font.pixelSize: 32
                        text:name

                        anchors.horizontalCenter: parent.horizontalCenter
                        anchors.top: appIco.bottom
                        anchors.topMargin: 10
                    }
                }
            }

        }
    }
}
