import QtQuick 2.0
import com.syberos.basewidgets 2.0
import "../component"

Item{
    z:slides.z+22
    height: 30
    width:slides.count*30+(slides.count-1)*6
    
    anchors.bottom: slides.bottom
    anchors.bottomMargin: 20
    anchors.right: slides.right
    anchors.rightMargin: 30
    
    Row{
        id: slidesIndex
        spacing: 6
        
        Repeater {
            id: tabline
            model: slides.tabModel
            
            delegate: Rectangle {
                height: 30
                width:height
                radius: height/2
                
                color: index === slides.currentIndex ? "red" : "gray"
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        slides.currentIndex = index;
                    }
                }
            }
        }
    }
}
