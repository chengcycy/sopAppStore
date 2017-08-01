import QtQuick 2.0
import com.syberos.basewidgets 2.0
import "../component"

Rectangle{
    color:"#efeef4"

    TitleBar{
        id:tBar
        tips: qsTr("应用")
        ico:"qrc:/res/images/store_n.png"
        anchors.top: parent.top
    }
    SlidesshowArea
    {
        id:slides
        width:parent.width
        height: 360
        anchors.top: tBar.bottom
    }
    SlidesshowIndicator {
    }

    function slidesshow(){
        slides.visible = false;
        tBar.showLoad = true;
        tBar.showRightIco = false;
        var obj = {type: "5"}
        appClient.slidesshow(JSON.stringify(obj));
    }

    Component.onCompleted: {
        slidesshow();
    }
    Connections{
        target: appClient
        onCallback:{
            var obj = JSON.parse(json)
            if(obj.fName === 'slidesshow'){
                for(var i=0;i<obj.data.length;++i){
                    slides.addPage(JSON.stringify(obj.data[i]));
                }
                tBar.showLoad = false;
                tBar.showRightIco = true;
                slides.visible = true;
                slides.startTimer();
            }
        }
    }
}
