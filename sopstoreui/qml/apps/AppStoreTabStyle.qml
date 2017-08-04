import QtQuick 2.3
import com.syberos.basewidgets 2.0
Rectangle {
    id: tabBar
    implicitHeight: 100
    anchors.left: parent.left
    anchors.right: parent.right
    anchors.leftMargin: 20
    color: lineColor

    /*! 标识动画是否正在进行，只读属性。*/
    readonly property bool animating: anchorAnimation.running

    /*! 该TabBar所在的CSwipeTabView，必须指定 */
    property QtObject tabView: null

    /*! 标签页间隔 */
    property int tabSpacing: 1

    /*! tabBar普通标题颜色 */
    property color titleColor: gUiConst.getValue("CT2")

    /*! tabBar高亮标题颜色 */
    property color titleHighlightColor: gUiConst.getValue("CT5")

    /*! tabBar标题字体大小 */
    property int titlePixelSize: gUiConst.getValue("S3")

    /*! 分割线颜色 */
    property color lineColor: gUiConst.getValue("CL1")

    state: tabView.tabPosition === Qt.TopEdge ?
               (tabView.tabVisible ? "top" : "top-hide") : (tabView.tabVisible ? "bottom" : "bottom-hide")
    states: [
        State {
            name: "top"
            AnchorChanges {
                target: tabBar
                anchors.top: parent.top
                anchors.bottom: undefined
            }
            AnchorChanges {
                target: shadow
                anchors.top: tabBar.bottom
                anchors.bottom: undefined
            }
            PropertyChanges {
                target: tabBar
                anchors.topMargin: 0
            }
        },
        State {
            name: "bottom"
            AnchorChanges {
                target: tabBar
                anchors.top: undefined
                anchors.bottom: parent.bottom
            }
            AnchorChanges {
                target: shadow
                anchors.top: undefined
                anchors.bottom: tabBar.top
            }
            PropertyChanges {
                target: tabBar
                anchors.bottomMargin: 0
            }
        },
        State {
            name: "top-hide"
            AnchorChanges {
                target: tabBar
                anchors.bottom: parent.top
                anchors.top: undefined
            }
            AnchorChanges {
                target: shadow
                anchors.top: tabBar.bottom
                anchors.bottom: undefined
            }
            PropertyChanges {
                target: tabBar
                anchors.bottomMargin: shadow.height
            }
        },
        State {
            name: "bottom-hide"
            AnchorChanges {
                target: tabBar
                anchors.bottom: undefined
                anchors.top: parent.bottom
            }
            AnchorChanges {
                target: shadow
                anchors.top: undefined
                anchors.bottom: tabBar.top
            }
            PropertyChanges {
                target: tabBar
                anchors.topMargin: shadow.height
            }
        }
    ]
    transitions: Transition {
        AnchorAnimation {
            id: anchorAnimation
            duration: gSystemUtils.durationRatio*100; easing.type: Easing.OutExpo
            onStarted: if(tabView.tabVisible) tabBar.visible = true;
            onStopped: if(!tabView.tabVisible) tabBar.visible = false;
        }
    }

    Row {
        id: row

        spacing: tabSpacing
        height: 48
        width: parent.width

        anchors.centerIn: parent
        Repeater {
            id: tabline
            model: tabView.tabModel

            delegate: Rectangle {
                width: tabText.contentWidth+20
                height: 48
                color: index !== tabView.currentIndex ? tabBar.color : titleColor
                radius: index !== tabView.currentIndex ? 0 : 20

                anchors.verticalCenter: parent.verticalCenter

                Text {
                    id: tabText
                    text: tab.title
                    anchors.centerIn: parent
                    color: index === tabView.currentIndex ? titleHighlightColor : titleColor
                    font.pixelSize: titlePixelSize
                }

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        tabView.currentIndex = index;
                    }
                }
            }
        }
    }

    Rectangle {
        id: shadow
        width: parent.width
        height: 1
        color: lineColor
    }
}
