import QtQuick 2.0
import com.syberos.basewidgets 2.0
import QtQml.Models 2.1

import "../component"
import "../Helper.js" as Helper
Rectangle{
    id:noticeMain

    color:"#f7f3f7"
    property var  userObj: JSON.parse(appClient.curUserInfo)

    //////////////////////////////////////////////////////////////////
    function getGWGL(){
        var url = 'http://10.152.36.33:8080/CasicOA/std/entity/page_data.tsp?objectName=WfActivity!portal&objectEvent=Query&$bizId=my_all_without_doc_mobile&isMobile=y&PID='+userObj.usbkeyidentification
        Helper.requestHttps(url,function(res){
            console.log('getGWGL:'+res);

            //            const noticeData = {
            //                   img: $XXFB,
            //                   name: '协同办公',
            //                   text: '这里是邮件的题目',
            //                   time: '2066年6月6日',
            //                   notice: '99+',
            //                   url: 'owo.help'
            //                 }
            var noticeData = { // 公文管理
                img: '',
                name: '公文管理',
                text: '暂无待处理公文',
                time: '',
                notice: "0",
                url: '#',
              };
            var data =JSON.parse(res);
            if (data.pageData.length > 0) {
                var date = Date.parse(data.pageData[0].startTime.replace(/-/gi, "/"))
                noticeData.text = data.pageData[0]["wfInstance.description"]
                var number = data.pageData.length
                if (number > 99) number = '99+'
                noticeData.time = formatTime(date)
                noticeData.notice = number
            }
            console.log('sss:'+JSON.stringify(noticeData))
        });
    }

    function getXTBG(){
        var url = 'http://10.152.36.26:8080/CASIC/interfaces/304DaiBanInterface.jsp?userName=' + userObj.enname + '&PID=' + userObj.usbkeyidentification + '&webService=';
        Helper.requestHttps(url,function(res){
            console.log('getXTBG:'+res);
        })
    }

    function getMail(){
        var url = 'http://10.152.36.31/secmail/GetAppUnreadFileService?id_card='+userObj.usbkeyidentification+'&username=secmail&password=welcome'
        Helper.requestHttps(url,function(res){
            console.log('getMail:'+res);
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
    Component.onCompleted: {
        getGWGL();
        getXTBG();
        getMail();
    }

    TitleBar {
        id: titleBar
        tips: qsTr("通知")
        ico:"qrc:/res/images/search.png"
        showRightIco: false
        anchors.top: parent.top
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
            model: sessionListManager
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
                            background.color="#f2f2f2";
                        }
                    }
                    onPressed: background.color="#CDCDCD"
                    onReleased: background.color="#f2f2f2"
                    onCanceled: background.color="#f2f2f2"
                    onClicked: {
                    }

                    onSlideFinished: {
                        noticeLst.setSelectedItem(delegateRoot);
                    }

                    _rightMenuItem: Item {
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
                                color: "#f2f2f2"
                            }
                            Rectangle {
                                id : background

                                anchors.fill: parent
                                color:"#f2f2f2"

                                RectHeadComponent{
                                    id: headPortraitImage

                                    anchors.left: parent.left
                                    anchors.leftMargin: 19
                                    anchors.verticalCenter: parent.verticalCenter
                                    iconSource: ""

                                }
                                Rectangle{
                                    id:unreadcount

                                    anchors.top: headPortraitImage.top
                                    anchors.right: headPortraitImage.right
                                    anchors.topMargin: -6

                                    width:38
                                    height: 38
                                    radius: 19
                                    //                                    visible: setUnread()
                                    color:"red"
                                    Text{
                                        font.pixelSize: 24
                                        anchors.centerIn: parent
                                        color:"white"
                                        text:""
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
                                    //                                    text: model.modelData.name
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
                                    text: "con()"
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

                                    text:""
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
