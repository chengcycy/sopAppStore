import QtQuick 2.0

Item {
    id:tabStyle

    width: 100
    height: 120
    signal msgTabClick()
    property var tips:""
    /**
    @brief 被使用的CTabView
    */
    property Item tabview

    /**
    @brief 用于设置当前标签的数据，其有currentIndex，index以及title内容
    */
    property alias styleData:viewData
    /*
      * since 14.7.3
    @brief 现实title的Text，用户可通过此设置text的相关属性
    */
    property alias text:txt

    property alias imgSource:img

    QtObject{
        id:viewData
        property int index:-1
        property int currentIndex:0
        property string title
    }

    Rectangle{
        id:rectBack

        anchors.fill: parent
        color:"white"
        z:parent.z-1
    }

    Rectangle {
        anchors.top: parent.top
        width: parent.width
        height:2
        z:parent.z+2
        radius: 2
        color: "#e8e8e8"
    }

    Image {
        id: img
        anchors.top: parent.top
        anchors.topMargin: 20
        anchors.horizontalCenter: parent.horizontalCenter
        sourceSize: Qt.size(59, 53)
        smooth: true
        asynchronous: true
        source: index === tabview.currentIndex? tabview.getTab(index).imgActiveSource : tabview.getTab(index).imgSource
    }

    Rectangle {
        id: noreadMessageLogo
        anchors.left: img.right
        anchors.leftMargin: -width / 2 +2
        anchors.top: img.top
        anchors.topMargin: -height / 2 + 10
        height: tiptxt.contentHeight+12
        width: height

        radius: height/2
        color: "#f3362e"
        visible: tabview.getTab(index).newMessage
        Text{
            id:tiptxt
            text:tips
            font.pixelSize: 24
            color:"white"
            anchors.centerIn: parent
        }
    }

    Text {
        id:txt
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 15
        anchors.horizontalCenter: parent.horizontalCenter
        z:parent.z+2
        width:Math.min(parent.width-2,implicitWidth)//margin
        font.pixelSize: 22
        clip:true
        color:index === tabview.currentIndex? "#023958" : "#A5A5A5"
        text:tab.title
    }

    MouseArea {
        anchors.fill: parent

        onClicked: {
//            rectBack.color='blue'

            if(tabView.currentIndex != index){
                tabView.currentIndex = index
            }
            else{
                if(index == 0){
                    emit:msgTabClick();
                }
            }
        }
        onDoubleClicked: {
//            rectBack.color='blue'
            if(tabView.currentIndex !== index) {
                tabView.currentIndex = index
            } else if(index === 0) {
            }
        }
        onPressed: rectBack.color='#cdcdcd'
        onCanceled: rectBack.color='white'
        onReleased: rectBack.color='white'
    }
}

