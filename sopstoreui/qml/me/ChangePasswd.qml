import QtQuick 2.0
import com.syberos.basewidgets 2.0
import "../component"
CPage {
    id: activateaccountPage

    property string  server
    property string  name
    property string  password
    onStatusChanged: {
        if (status === CPageStatus.WillShow) {
            activateaccountPage.statusBarHoldEnabled = true
            gScreenInfo.setStatusBar(activateaccountPage.statusBarHoldEnabled)
            activateaccountPage.statusBarHoldItemColor = "#edf0f0"
            gScreenInfo.setStatusBarStyle("black")
        }
    }

    Connections{
        target: appClient
        onCallback:{
            var obj = JSON.parse(json);
            console.log('===================changedPwd=============================')
            if(obj.fName === 'changedPwd'){
                loadingDialog.hide();
                switch (obj.data.code) {
                case 543:gToast.requestToast('当前密码不正确'); break;
                case 542: gToast.requestToast('新密码不合法'); break;
                case 541: gToast.requestToast('用户不存在'); break;
                case 1304: gToast.requestToast( '修改失败'); break;
                case 0: gToast.requestToast('修改成功');
                    mainApp.usrPasswd = passWordEdit.text;
                    appClient.loginout();
                    break;
                default:gToast.requestToast('遇到错误:'+obj.data.code);
                }
            }
        }
    }

    contentAreaItem: Item {

        anchors.fill :parent
        Rectangle {
            id: loginBackground
            anchors.fill: parent
            color: "#f7f3f7"
        }

        Flickable{
            id: filckableInput
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            contentHeight: parent.height

            Connections {
                target: gInputContext
                onSoftwareInputPanelVisibleChanged: {
                    if(gInputContext.softwareInputPanelVisible) {
                        filckableInput.contentHeight = filckableInput.parent.height + 200
                    } else {
                        filckableInput.contentHeight = filckableInput.parent.height
                    }
                }
            }

            TitleBar{
                id:titleBackground
                tips:'修改密码'
                showLeftIco: true
                anchors.top: parent.top
                anchors.left: parent.left
                onClicked: {
                    pageStack.pop();
                }
            }

            Rectangle {
                id: inputBackGround

                anchors.top: titleBackground.bottom
                height: 303
                anchors.topMargin: 16
                anchors.left: parent.left
                anchors.right:parent.right
                anchors.leftMargin: 16
                anchors.rightMargin:16
                border.color: "#777777"
                border.width: 1
                radius:10
                color: "#f7f3f7"
            }
            Text{
                id:srvTip

                anchors{
                    left:inputBackGround.left
                    leftMargin: 25
                    verticalCenter: srvLineEdit.verticalCenter
                }
                width:100
                text:qsTr("旧密码")
                font.pixelSize: 30
            }

            CLineEdit {
                id: srvLineEdit
                anchors.top: inputBackGround.top
                anchors.left: srvTip.right
                anchors.right:inputBackGround.right
                anchors.rightMargin: 80
                anchors.leftMargin: 50
                echoMode: TextInput.Password
                height: 101
                passwordLabelEnabled: false
                textLeftMargin: 50
                clip: true

                textColor:"#787777"
                font.pixelSize: 30
                placeholderText:os.i18n.ctr(qsTr("请输入旧密码"))

                inputMethodHints: Qt.ImhPreferLatin
                onTextChanged: {
                    passWordEdit.text = "";
                    userLineEdit.text = "";
                    if(activateaccountPage.state !== "hidden") {
                        activateaccountPage.state = "hidden"
                    }
                }
                onKeyPressed: {
                    if (key === Qt.Key_Return)
                    {
                        userLineEdit.forceActiveFocus()
                    }
                }
            }
            CButton{
                id: seePassword1;
                anchors.top: inputBackGround.top
                anchors.right: inputBackGround.right
                anchors.rightMargin: 20
                iconSource: srvLineEdit.echoMode === TextInput.Normal ? "qrc:/res/images/echo_normal.png" : "qrc:/res/images/echo_pwd.png"
                backgroundEnabled: false
                width: 40
                height: 101
                onReleased: {
                    if(containsMouse){
                        srvLineEdit.echoMode = srvLineEdit.echoMode === TextInput.Normal ? TextInput.Password : TextInput.Normal;
                    }
                }
            }
            CLine {
                width: inputBackGround.width
                anchors.top: srvLineEdit.bottom
                anchors.left:inputBackGround.left
                z: parent.z+2
            }
            Text{
                id:userTip

                anchors{
                    left:inputBackGround.left
                    leftMargin: 25
                    verticalCenter: userLineEdit.verticalCenter
                }
                width:100
                text:qsTr("新密码")
                font.pixelSize: 30
            }

            CLineEdit {
                id: userLineEdit
                anchors.top: srvLineEdit.bottom
                anchors.left: userTip.right
                anchors.right:inputBackGround.right
                anchors.rightMargin: 80
                anchors.leftMargin: 50

                height: 101
                passwordLabelEnabled: false
                echoMode: TextInput.Password
                textLeftMargin: 50
                clip: true

                font.pixelSize: 30
                placeholderText:os.i18n.ctr(qsTr("请输入新密码"))

                inputMethodHints: Qt.ImhPreferLatin/*|Qt.ImhPreferNumbers*/

                onTextChanged: {
                    passWordEdit.text = ""

                    if(activateaccountPage.state !== "hidden") {
                        activateaccountPage.state = "hidden"
                    }
                }
                onKeyPressed: {
                    if (key === Qt.Key_Return)
                    {
                        passWordEdit.forceActiveFocus()
                    }
                }
            }
            CButton{
                id: seePassword2;
                anchors.top: seePassword1.bottom
                anchors.right: inputBackGround.right
                anchors.rightMargin: 20
                iconSource: userLineEdit.echoMode === TextInput.Normal ? "qrc:/res/images/echo_normal.png" : "qrc:/res/images/echo_pwd.png"
                backgroundEnabled: false
                width: 40
                height: 101
                onReleased: {
                    if(containsMouse){
                        userLineEdit.echoMode = userLineEdit.echoMode === TextInput.Normal ? TextInput.Password : TextInput.Normal;
                    }
                }
            }
            CLine {
                width: inputBackGround.width
                anchors.top: userLineEdit.bottom
                anchors.left:inputBackGround.left
                z: parent.z+2
            }

            Text{
                id:srvPwd

                anchors{
                    left:inputBackGround.left
                    leftMargin: 25
                    verticalCenter: passWordEdit.verticalCenter
                }
                width: 100
                text:qsTr("确认新密码")
                font.pixelSize: 30
            }

            CLineEdit {
                id: passWordEdit
                anchors.top: userLineEdit.bottom
                anchors.left: srvPwd.right
                anchors.right:inputBackGround.right
                anchors.rightMargin: 80
                anchors.leftMargin: 50

                height: 101
                passwordLabelEnabled: false
                echoMode: TextInput.Password
                textLeftMargin: 50
                clip: true

                textColor:"#787777"
                font.pixelSize: 30
                placeholderText:os.i18n.ctr(qsTr("请输入新密码"))
                inputMethodHints: Qt.ImhPreferLatin
            }
            CButton{
                id: seePassword3;
                anchors.top: seePassword2.bottom
                anchors.right: inputBackGround.right
                anchors.rightMargin: 20
                iconSource: passWordEdit.echoMode === TextInput.Normal ? "qrc:/res/images/echo_normal.png" : "qrc:/res/images/echo_pwd.png"
                backgroundEnabled: false
                width: 40
                height: 101
                onReleased: {
                    if(containsMouse){
                        passWordEdit.echoMode = passWordEdit.echoMode === TextInput.Normal ? TextInput.Password : TextInput.Normal;
                    }
                }
            }

            Rectangle{
                id:loginButton

                border.width: 1
                border.color: "#cfcece"
                radius: 10
                color:"white"
                anchors.top:seePassword3.bottom
                anchors.topMargin: 60
                anchors.left: parent.left
                anchors.leftMargin: 19
                anchors.right: parent.right
                anchors.rightMargin:19
                height: 100

                Text{
                    text:qsTr("修改密码")
                    font.pixelSize: 30
                    color:"black"
                    anchors.centerIn: parent
                }

                MouseArea{
                    anchors.fill: parent
                    onPressed: loginButton.color = "#cdcdcd"
                    onReleased: loginButton.color = "white"
                    onClicked: {
                        if(srvLineEdit.text === "") {
                            srvLineEdit.focus = true
                            gToast.requestToast("旧密码不能为空","","");
                            return;
                        }
                        if(userLineEdit.text ===""){
                            gToast.requestToast("新密码不能为空","","");
                            return;
                        }
                        if(userLineEdit.text!==passWordEdit.text) {
                            gToast.requestToast("两次输入的新密码不一致","","");
                            return
                        }
                        if(srvLineEdit.text==userLineEdit.text){
                            gToast.requestToast("新密码不能与旧密码相同","","");
                            return
                        }

                        if(srvLineEdit.text === "") {
                            srvLineEdit.focus = true
                            gToast.requestToast("旧密码不能为空","","");

                        } else if(passWordEdit.text === "") {
                            passWordEdit.focus = true
                            gToast.requestToast("新密码不能为空","","");
                        } else {
                            loadingDialog.show();
                            var data = {oldPwd:srvLineEdit.text,newPwd:passWordEdit.text};
                            appClient.changedPwd(JSON.stringify(data));
                        }
                    }
                }
            }
            Text{
                anchors.left: parent.left
                anchors.leftMargin: 20
                anchors.right: parent.right
                anchors.rightMargin: 20
                anchors.top:loginButton.bottom
                anchors.topMargin: 20
                wrapMode: Text.Wrap
                text:'建议:密码长度为8-16位，至少有数字、字母或符号的两种组合，字母区分大小写'
                font.pixelSize: 26
                color:"#a5a5a5"
            }

            CIndicatorDialog {
                id:loadingDialog
                messageText: os.i18n.ctr(qsTr("正在处理中..."))
            }

        }
    }
}
