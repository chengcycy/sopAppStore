import QtQuick 2.0
import com.syberos.basewidgets 2.0
import "../component"
CSwipeTab {
    property var  listModel
    property var  classId
    Image{
        id:ico
        visible: listView.contentHeight<=0
        source: "qrc:/res/images/store.png"
        anchors.centerIn: parent
        anchors.verticalCenterOffset: -200
        z:listView.z+1
    }
    Text{
        id:tips

        font.pixelSize: 30
        color: '#7b7b7b'

        text:'暂未发布此类型应用'
        visible: ico.visible
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: ico.bottom
        anchors.topMargin: 30
    }

    ListView{
        id:listView
        model:listModel

        anchors.fill: parent
        delegate:Rectangle{
            id:appsDelegete

            function  appStatus(){
                if(appInstall === 1){
                    return '已安装';
                }else if(appInstall === 2){
                    return '安装';
                }else if(appInstall === 3){
                    return '更新';
                }else{
                    return progress+'%';
                }
            }

            width:parent.width
            visible: classId === classify
            height: visible ? 150:0
            color: 'transparent'


            MouseArea{
                anchors.fill: parent
                onPressed: appsDelegete.color = '#cdcdcd'
                onCanceled:appsDelegete.color = 'transparent'
                onReleased:appsDelegete.color = 'transparent'
            }

            RectHeadComponent{
                id:appico

                iconSource: icon
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                anchors.leftMargin: 30
            }
            Text{
                id:appName

                font.pixelSize: 28
                text:name
                anchors.left: appico.right
                anchors.leftMargin: 10
                anchors.top: appico.top
            }
            Text{
                id:appVer

                font.pixelSize: 28
                color: '#7b7b7b'

                text:'版本号:'+version
                anchors.left: appico.right
                anchors.leftMargin: 10
                anchors.bottom: appico.bottom
            }
            Rectangle{
                id:appBtn
                width:124
                height: 64
                border.color: appInstall !== 1?"#0000ff":"#000000"
                border.width: 1
                radius: 10
                color: appInstall !== 1?"#0000ff":"white"

                anchors.verticalCenter: parent.verticalCenter
                anchors.right: parent.right
                anchors.rightMargin: 30

                /*
                1.　已安装
                2.　未安装
                3.　需更新
                4.　正在安装
                */
                Text{
                    id:statusT
                    text:appsDelegete.appStatus()
                    font.pixelSize: 28
                    color: appInstall !== 1?"white":"#000000"
                    anchors.centerIn: parent
                }
                MouseArea{
                    anchors.fill: parent
                    onClicked: {
                        //install
                        if(appInstall ===2 || appInstall ===3){
                            if(type === 2){//h5
                                listModel.setProperty(index,'appInstall',1);
                                appClient.queryAppStore(JSON.stringify({ type: "6", id:id,classify:classify}));
                            }else{
                                if(appInstall === 2){
                                    var sysApps = JSON.parse(mainApp.getSystemAppList());
                                    var sopId = packageName.split('-')[0];
                                    if(sysApps.hasOwnProperty(sopId)){
                                        listModel.setProperty(index,'appInstall',1);
                                        appClient.queryAppStore(JSON.stringify({ type: "6", id:id,classify:classify}));
                                        return;
                                    }
                                }

                                var caches = appClient.downloadingApps;
                                if(caches !==""){
                                    caches = JSON.parse(caches);
                                    gToast.requestToast('"'+caches.name+'"应用正在下载,请稍后',"","");
                                }else{
                                    appClient.downloadingApps = JSON.stringify({name:name,id:id,packageName:packageName,classify:classify});
                                    listModel.setProperty(index,'appInstall',4);
                                    appClient.downloadApp(packageName,downloadUrl);
                                }

                            }
                        }
                    }
                }
            }
            CLine{
                anchors.top: parent.bottom
            }
        }
    }
}
