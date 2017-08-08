import QtQuick 2.0
import com.syberos.basewidgets 2.0
import "../component"

Rectangle{
    id:textComponent

    property int    fontSize: 28
    property alias  leftText: left.text
    property alias  rigthText: rightLbl.text
    property bool   canEdible : false
    property bool   isLast:false
    property int    leftTextMargin: 30
    property string icoSource
    property int    icoSize: 40
    height: 86
    width:parent.width
    signal clicked();
    RectHeadComponent{
        id:ico

        iconSource: icoSource
        width: icoSize
        height: width

        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left
        anchors.leftMargin: 30

    }

    Text{
        id:left

        font.pixelSize: textComponent.fontSize
        color: "#545454"
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: ico.right
        anchors.leftMargin:leftTextMargin

    }

    Image{
        id:arrow

        visible: textComponent.canEdible
        source:"qrc:/res/images/arrow_right.png"
        width: 40
        height: width

        anchors.verticalCenter: parent.verticalCenter
        anchors.right: parent.right
        anchors.rightMargin: 30
    }

    Text{
        id:rightLbl

        font.pixelSize: textComponent.fontSize
        color: "#A5A5A5"
        width:480
        elide:Text.ElideRight
        horizontalAlignment:Text.AlignRight
        visible: rigthText !== ""
        anchors.verticalCenter: parent.verticalCenter
        anchors.right: textComponent.canEdible ?arrow.left :parent.right
        anchors.rightMargin:textComponent.canEdible ?4 :20
    }
    CLine{
        id:line

        height: 1
        visible: !isLast

        anchors.right: parent.right
        anchors.left: parent.left
        anchors.leftMargin:30
        anchors.bottom: parent.bottom
    }
    MouseArea{
        anchors.fill: parent
        onPressed: parent.color = "#dddfed"
        onReleased: parent.color = "#ffffff"
        onCanceled: parent.color = "#ffffff"
        onClicked: {
            emit:textComponent.clicked();
//            if(rigthText!== ""){
//                gToast.requestToast(rigthText,"","");
//            }
        }
    }
}
