import QtQuick 2.0
import com.syberos.basewidgets 2.0
CPage {
    id: loginPage

    signal loginClicked(string userName,string passwd)

    statusBarHoldEnabled: false
    onStatusChanged: {
        if (status === CPageStatus.WillShow) {
            gScreenInfo.setStatusBar(true)
            gScreenInfo.setStatusBarStyle("transwhite")
        }
    }
    contentAreaItem: Item {
        anchors.fill :parent
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

            Image {
                id: logoImage
                source: "qrc:/res/images/logo.png"

                anchors.top: parent.top
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.topMargin: 114
                smooth: true
            }
            Text{
                id:title
                text:qsTr("智慧企业运行平台")
                font.pixelSize: 36

                anchors.top: logoImage.bottom
                anchors.topMargin: 10
                anchors.horizontalCenter: parent.horizontalCenter
            }

            Rectangle {
                id: inputBackGround

                anchors.top: title.bottom
                width: parent.width - 80
                height: 200
                anchors.topMargin: 72
                anchors.horizontalCenter: parent.horizontalCenter
                border.color: "#094a84"
                border.width: 2
                radius: 13
                color: "#fefefe"
                opacity: 0.4
            }
            Image {
                id:srvTip

                anchors{
                    left: inputBackGround.left
                    leftMargin: 29
                    verticalCenter: srvLineEdit.verticalCenter
                }
                width: 38
                fillMode: Image.PreserveAspectFit
                source: "qrc:/res/images/server.png"
            }

            CLineEdit {
                id: srvLineEdit
                anchors.top: inputBackGround.top
                anchors.left: srvTip.right
                anchors.right:inputBackGround.right
                anchors.topMargin: 10
                anchors.leftMargin: 30
                anchors.rightMargin: 45

                height: 105
                passwordLabelEnabled: false
                clip: true

                text:"刘霞"
                font.pixelSize: 30
                placeholderText:os.i18n.ctr(qsTr("请输入用户名"))
                inputMethodHints: Qt.ImhPreferLatin/*|Qt.ImhPreferNumbers*/
                inputMethodHintExtensions: {
                    var args = {};
                    args["enterKeyText"] = "next";
                    return args;
                }

                onTextChanged: {
//                    passWordEdit.text = ""

                    if(loginPage.state !== "hidden") {
                        loginPage.state = "hidden"
                    }
                }

                onKeyPressed: {
                    if (key === Qt.Key_Return)
                    {
                        userLineEdit.forceActiveFocus()
                    }
                }
            }
            CLine {
                id: linePassword
                width: parent.width - 80
                border.color: inputBackGround.border.color
                border.width: 2
                height: 1
                anchors.top: srvTip.bottom
                anchors.topMargin: 20
                anchors.left:inputBackGround.left
                anchors.right: inputBackGround.right
                z: parent.z+2
                color:inputBackGround.border.color
            }

            Image {
                id: srvPwd

                anchors{
                    left: inputBackGround.left
                    leftMargin: 29
                    verticalCenter: passWordEdit.verticalCenter
                }
                width: 38
                fillMode: Image.PreserveAspectFit
                source: "qrc:/res/images/password.png"
            }

            CLineEdit {
                id: passWordEdit
                anchors.top: linePassword.bottom
                anchors.left: srvPwd.right
                anchors.right: inputBackGround.right
                anchors.leftMargin: 30
                anchors.rightMargin: 45

                clearLabelRightMargin:40
                height: 105
                passwordLabelEnabled: false
                echoMode: TextInput.Password
                clip: true
                text:"123456"
                font.pixelSize: 30
                placeholderText: os.i18n.ctr(qsTr("请输入密码"))
                inputMethodHints: Qt.ImhPreferLatin
                inputMethodHintExtensions: {
                    var args = {};
                    args["enterKeyText"] = "login";
                    return args;
                }

                onKeyPressed: {
                    if (key === Qt.Key_Return)
                    {
                        filckableInput.login()
                    }
                }
                CButton{
                    id: seePassword;
                    anchors.right: parent.right
                    iconSource: passWordEdit.echoMode === TextInput.Normal ? "qrc:/res/images/echo_normal.png" : "qrc:/res/images/echo_pwd.png"
                    backgroundEnabled: false
                    width: 40
                    height: parent.height
                    onReleased: {
                        if(containsMouse){
                            passWordEdit.echoMode = passWordEdit.echoMode === TextInput.Normal ? TextInput.Password : TextInput.Normal;
                        }
                    }
                }
            }


            CButton {
                id: loginButton

                anchors.top: inputBackGround.bottom
                anchors.topMargin: 46
                anchors.horizontalCenter: parent.horizontalCenter
                height:108
                width:parent.width - 80

                opacity:  pressed ? 1.0:0.7
                text:os.i18n.ctr(qsTr("登 录")) // "登 录"
                textColor:  "white"
                pixelSize: 43

                backgroundComponent: Rectangle {
                    anchors.fill: parent
                    color:"#0c2559"
                    radius: 16
                    border.width: 3
                    border.color: "#002a41"
                }

                onClicked: filckableInput.login()
            }
            function login() {
                if(srvLineEdit.text ===""){
                    gToast.requestToast("用户名不能为空","","");
                    return;
                }
                if(passWordEdit.text ===""){
                    gToast.requestToast("密码不能为空","","");
                    return;
                }
                if(passWordEdit.text === "") {
                    passWordEdit.focus = true
                    gToast.requestToast("密码不能为空","","");
                } else {
                    emit: loginClicked(srvLineEdit.text,passWordEdit.text);
                }
            }
        }
    }
}
