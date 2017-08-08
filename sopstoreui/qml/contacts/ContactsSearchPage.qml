import QtQuick 2.0
import com.syberos.basewidgets 2.0
import "../component"

CPage {
    id: contactsSearchPage

    contentAreaItem: Item {
        anchors.fill: parent

        Rectangle {
            id: background
            anchors.fill: parent
            color: '#eef3ee'
        }

        TitleBar {
            id: titleBar
            tips: qsTr("搜索")
            showLeftIco: true
            showRightIco: false
            anchors.top: parent.top
            onClicked: {
                if (pos === 1) {
                    pageStack.pop()
                }
            }
        }

        SearchEdit {
            id: searchEditArea
            width: parent.width
            height: 64
            anchors.top: titleBar.bottom
            onButtonClick: {
                listModel.clear()
                var obj = JSON.parse(appClient.curUserInfo)
                var EnOS = {enterId: 454, orgId: obj.unitId, type: 2, name: text};
                appClient.queryEnOS(JSON.stringify(EnOS));
            }
        }

        Rectangle {
            id: searchResultTip
            anchors.top: searchEditArea.bottom
        }

        EnterpriseListContentListViewComponent {
            id: searchResultList
            width: parent.width
            anchors.top: searchResultTip.visible ? searchResultTip.bottom : searchEditArea.bottom
            anchors.bottom: parent.bottom
            model: listModel
        }
    }

    ListModel {
        id: listModel
        ListElement {
            itemID: ''
            name: ''
            orgName: ''
            position: ''
            telNum: ''
            mobileNum: ''
            isDepart: false
        }
    }

    Connections {
        target: appClient
        onCallback: {
            console.log('danger receive' + json)
            var obj = JSON.parse(json)
            if (obj.fName === 'searchEnOS') {
                for (var i = 0; i < obj.data.entUsers.length; i++) {
                    var item = {};
                    item.itemID = obj.data.entUsers[i].orgID + ''
                    item.name = obj.data.entUsers[i].enName
                    item.orgName = obj.data.entUsers[i].orgName
                    item.position = obj.data.entUsers[i].duty
                    item.telNum = obj.data.entUsers[i].telPhone
                    item.mobileNum = obj.data.entUsers[i].enMobile
                    listModel.append(item)
                    console.log('item:' + JSON.stringify(item))
                }
            }
        }
    }
}
