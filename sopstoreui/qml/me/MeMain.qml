import QtQuick 2.0
import com.syberos.basewidgets 2.0
import "../component"
Rectangle{
    id:meMain

    property var  userObj: JSON.parse(appClient.curUserInfo)
    property var  sysApps :JSON.parse(mainApp.getSystemAppList());
    property var  usrExtendObj: JSON.parse(appClient.profile)
    color:"#f7f3f7"
    TitleBar {
        id: titleBar
        tips: qsTr("我")
        ico:"qrc:/res/images/search.png"
        showRightIco: false
        anchors.top: parent.top
    }

    Text{
        id:tips
        text:'个人信息'
        font.pixelSize: 30
        color: "#545454"

        anchors.left: parent.left
        anchors.leftMargin: 30
        anchors.top: titleBar.bottom
        anchors.topMargin: 30
    }

    SetButton{
        id:head
        icoSource: 'qrc:/res/images/user.png'
        leftText: userObj.enname
        rigthText: usrExtendObj.gender === 1?'男':'女'
        canEdible: true
        icoSize:88
        height: 122
        isLast: true
        anchors.top: tips.bottom
        anchors.topMargin: 20
        onClicked: {
            listdialog.currentIndex = usrExtendObj.gender === 1?0:1;
            listdialog.select(listdialog.currentIndex,true);
            listdialog.show();
        }
    }

    Text{
        id:tips1
        text:'操作'
        font.pixelSize: 30
        color: "#545454"

        anchors.left: parent.left
        anchors.leftMargin: 30
        anchors.top: head.bottom
        anchors.topMargin: 30
    }
    SetButton{
        id:set

        icoSource: 'qrc:/res/images/set.png'
        leftText:'修改密码'
        canEdible: true
        anchors.top: tips1.bottom
        anchors.topMargin: 20
        onClicked: {
            pageStack.push(Qt.resolvedUrl('./ChangePasswd.qml'))
        }

    }
    SetButton{
        id:phone

        icoSource: 'qrc:/res/images/phnoe.png'
        leftText:'手机号码'
        rigthText: usrExtendObj.phone
        canEdible: true
        anchors.top: set.bottom
        onClicked: {
            inputDialog.setText('');
            inputDialog.type = 1;
            inputDialog.placeholderText = '请输入新的手机号'
            inputDialog.show();
        }
    }
    SetButton{
        id:telPhone

        icoSource: 'qrc:/res/images/telphone.png'
        leftText:'固定电话'
        rigthText: usrExtendObj.telPhone
        canEdible: true
        anchors.top: phone.bottom
        onClicked: {
            inputDialog.setText('');
            inputDialog.type = 2;
            inputDialog.placeholderText = '请输入新的固定电话'
            inputDialog.show();
        }
    }
    SetButton{
        id:ver
        icoSource: 'qrc:/res/images/info.png'
        leftText:'当前版本'
        anchors.top: telPhone.bottom
        canEdible: true
        isLast:true
        rigthText: sysApps['com.vrv.sopstore'].ver

    }
    Rectangle{
        id:btnLoginout

        border.width: 1
        border.color: "#cfcece"
        radius: 10
        color:"white"
        anchors.top:ver.bottom
        anchors.topMargin: 60
        anchors.left: parent.left
        anchors.leftMargin: 19
        anchors.right: parent.right
        anchors.rightMargin:19
        height: 100

        Text{
            text:qsTr("退出登录")
            font.pixelSize: 30
            color:"black"
            anchors.centerIn: parent
        }

        MouseArea{
            anchors.fill: parent
            onPressed: btnLoginout.color = "#cdcdcd"
            onReleased: btnLoginout.color = "white"
            onClicked: {
                loadingPage.show();
                appClient.loginout();
            }
        }
    }

    CIndicatorDialog {
        id:loadingPage
        messageText: '正在退出．．．'
    }
    CInputDialog{
        id:inputDialog

        titleText:'设置联系方式'
        inputMethodHints:Qt.ImhDialableCharactersOnly
        validator:RegExpValidator{regExp:/^[0-9]*$/}
        property int type: 1

        onAccepted: {
            if(inputDialog.text()!==''){
                var data;
                if(type == 1){
                    data = {type:2,phone:inputDialog.text(),telPhone:telPhone.rigthText};
                }else{
                    data = {type:2,phone:phone.rigthText,telPhone:inputDialog.text()};
                }
                console.log('2222222222222222222222:'+JSON.stringify(data))
                appClient.updateAccount(JSON.stringify(data));
            }
        }
    }
    ListDialog{
        id:listdialog

        property  int  currentIndex: 0
        titleText: qsTr("设置性别")
        onNotifySelectedItems:{
            listdialog.currentIndex = curIndex;
            var data = {type:3,gander:curIndex+1};
            console.log('1111111111111111111:'+JSON.stringify(data))
            appClient.updateAccount(JSON.stringify(data));
        }
        Component.onCompleted: {
            model = [qsTr("男"),qsTr("女")]
        }
    }

    Connections{
        target: appClient
        onCallback:{
            var obj = JSON.parse(json);
            if(obj.fName === 'loginout'){
                loadingPage.hide();
                pageStack.clear();
                pageStack.push(Qt.resolvedUrl('./Login.qml'));
            }
        }
    }
}
