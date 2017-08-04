import QtQuick 2.0
import com.syberos.basewidgets 2.0
import "../component"

Rectangle {
    property var curOrg: ({})

    color: "#efeef4"

    Component.onCompleted: {
        titleModel.clear()
        listModel.clear()
        var obj = JSON.parse(appClient.curUserInfo)
        titleModel.append({orgID: obj.unitId, orgName: obj.unitName, operType: 4})
        var EnOS = {enterId: 454, orgId: obj.unitId, type: 4}
        appClient.queryEnOS(JSON.stringify(EnOS))
        console.log('curUserInfo:' + appClient.curUserInfo)
    }

    TitleBar {
        id: titleBar
        anchors.top: parent.top
        tips: qsTr("通讯录")
        ico:"qrc:/res/images/search.png"
    }

    EnterpriseListTitleListViewComponent {
        id: organizationTitle
        height: 63
        width: parent.width
        anchors.top: titleBar.bottom
        model: titleModel
    }

    EnterpriseListContentListViewComponent {
        id: organizationContentList
        width: parent.width
        anchors.top: organizationTitle.bottom
        anchors.bottom: parent.bottom
        model: listModel
    }

    ListModel {
        id: titleModel
        ListElement {
            orgID: ''
            orgName: ''
            operType: 4
        }
    }

    ListModel {
        id: listModel
        ListElement {
            itemID: ''
            name: ''
            orgName: ''
            isDepart: true
            subOrgCount: 0
            subMemberCount: 0
        }
    }

    Connections {
        target: appClient
        onCallback: {
            var obj = JSON.parse(json)
            if (obj.fName === 'queryEnOS') {
                for (var i = 0; i < obj.data.depts.length; i++) {
                    var item = {};
                    item.itemID = obj.data.depts[i].orgID + ''
                    item.name = obj.data.depts[i].orgName
                    item.subOrgCount = obj.data.depts[i].subOrgNum
                    item.subMemberCount = obj.data.depts[i].subUserNum
                    item.isDepart = true
                    listModel.append(item)
                    console.log('item:' + JSON.stringify(item))
                }
                for (var i = 0; i < obj.data.entUsers.length; i++) {
                    var item = {};
                    item.itemID = obj.data.entUsers[i].orgID + ''
                    item.name = obj.data.entUsers[i].enName
                    item.orgName = obj.data.entUsers[i].orgName
                    item.isDepart = false
                    listModel.append(item)
                    console.log('item:' + JSON.stringify(item))
                }
            }
        }
    }

    Connections {
        target: organizationTitle
        onClickOrg: {
            listModel.clear()
        }
    }

    Connections {
        target: organizationContentList
        onClickOrg: {
            titleModel.append({orgID: id, orgName: name, operType: type})
            listModel.clear()
        }
    }
}
