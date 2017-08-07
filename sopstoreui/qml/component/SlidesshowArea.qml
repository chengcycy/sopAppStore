import QtQuick 2.0
import com.syberos.basewidgets 2.0
CSwipeTabView{
    id:swipeTabview

    tabVisible: false
    tabPosition:Qt.BottomEdge

    function addPage(data){
        var component = Qt.createComponent(Qt.resolvedUrl("./SwipeTab.qml"));
        if (component.status === Component.Ready) {
            var obj  = component.createObject(swipeTabview);
            var jsonObj = JSON.parse(data);
            obj.imageSource = jsonObj.img;
            obj.url = jsonObj.url;
             obj.title = jsonObj.title;
        }
    }
    function startTimer(){
        timer.restart();
    }

    Timer{
        id:timer
        interval:10000
        repeat: true
        running: false
        onTriggered: {
            var index = (swipeTabview.currentIndex+1);
            if(index>=swipeTabview.count){
                index = 0;
            }
            swipeTabview.currentIndex = index;
        }
    }
}
