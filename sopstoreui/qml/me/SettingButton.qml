import QtQuick 2.0
import com.syberos.basewidgets 2.0

Rectangle{
    id:comp

    property string leftText: ""
    property url rightImg:""
    property string rigthText: ""
    property url leftSource: leftArrow.source
    property bool showLine:true
    property bool editable:false
    property int  rightTextMaxLen: 254
    property int textsize: 16
    signal clicked()

    height: 46
    color: "#ffffff"
    anchors.left: parent.left
    anchors.right: parent.right

    Text{
        id:leftTip

        text:leftText
        font.pixelSize: textsize
        color: "#585758"
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: leftArrow.right
        anchors.leftMargin: 15
    }
    Text {
        id:rigthText

        text:comp.rigthText
        font.pixelSize: textsize
        width: 165
        elide: Text.ElideRight
        clip:true
        color: "#545454"
        maximumLineCount: 0.5
        horizontalAlignment:Text.AlignRight
        onTextChanged: {
            rigthText.width = setWidth();
        }
        anchors{
            right: arrowTip.left
            rightMargin: 5
            verticalCenter: parent.verticalCenter
        }
        function setWidth(){
            var tmp = rigthText.contentWidth + 5;
            if(tmp>rightTextMaxLen){
                return rightTextMaxLen;
            }else if(tmp < 165){
                return 165;
            }else{
                return tmp;
            }
        }
    }
    Image {
        id: arrowTip

        visible: comp.editable
        source: "qrc:/res/newUi/ic_next_more@2x.png"
        height: 30
        width: 30
        anchors{
            right: parent.right
            rightMargin: 11
            verticalCenter: parent.verticalCenter
        }
    }
    Image{
        id:leftArrow
        source: ""
        visible: comp.editable
        height: 18
        width: 18
        anchors{
            left: parent.left
            rightMargin: 14
            verticalCenter: parent.verticalCenter
        }
    }
    CLine{
        visible: comp.showLine
        anchors.bottom: parent.bottom
        color:"#dddfeb"
        anchors.left:parent.left
        anchors.right: parent.right
        anchors.leftMargin: 42
    }
    MouseArea{
        anchors.fill: parent
        onPressed: parent.color = "#cdcdcd"
        onReleased: parent.color = "#ffffff"
        onCanceled: parent.color = "#ffffff"
        onClicked: {
            emit: comp.clicked();
        }
    }
}
