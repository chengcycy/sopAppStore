import QtQuick 2.3
import com.syberos.basewidgets 2.0

FocusScope {
    id: root
    implicitWidth: gScreenInfo.displayWidth
    implicitHeight: gScreenInfo.displayHeight
    clip: true

    /*! 控件的标签导航栏，可自己定义代替默认的，cake */
    property Item tabBar: null

    /*! 当前标签页的索引值，改变时切换标签 */
    property int currentIndex: 0

    /*! 标签页的数量 */
    readonly property int count: tabModel.count

    /*! 标签是否可见 */
    property bool tabVisible: true

    /*!
        \qmlproperty enumeration CTabView::tabPosition
        标签栏位置，取值为：

        \list
        \li Qt.TopEdge (default) - 位于顶部
        \li Qt.BottomEdge - 位于底部
        \endlist
    */
    property int tabPosition: Qt.TopEdge

    /*! 包含CTab的ListModel，自定义的tabBar可以获取标签title */
    property ListModel tabModel: ListModel { }


    property color theme: "#000000"

    /*! \internal */
    default property alias data: stack.data

    /*! 获取位于 \a index 的 \l CTab 控件. */
    function getTab(index) {
        var data = tabModel.get(index)
        return data && data.tab
    }

    /*! \internal */
    function __setOpacities() {
        for (var i = 0; i < tabModel.count; ++i) {
            var child = tabModel.get(i).tab;
            child.visible = (i == currentIndex ? true : false);
        }
    }

    Item{
        id: stack
//        color: theme

        anchors.left: root.left
        anchors.right: root.right
        anchors.bottom: tabPosition == Qt.TopEdge ? parent.bottom : tabBar.top
        anchors.top: tabPosition == Qt.TopEdge ? tabBar.bottom : parent.top

        property bool completed: false

        Component.onCompleted: {
            addTabs(stack.children)
            completed = true
        }

        onChildrenChanged: {
            if (completed)
                stack.addTabs(stack.children)
        }

        function addTabs(tabs) {
            var tabAdded = false
            for (var i = 0 ; i < tabs.length ; ++i) {
                var tab = tabs[i]
                if (tab.hasOwnProperty("__inserted") && !tab.__inserted) {
                    tab.__inserted = true
                    tab.parent = stack
                    tabModel.append({tab: tab})
                    tabAdded = true
                }
            }
            if (tabAdded)
                __setOpacities()
        }
    }

    onCurrentIndexChanged: __setOpacities()

    onChildrenChanged: stack.addTabs(root.children)

    Component.onCompleted: {
        if(!tabBar) {
            tabBar = Qt.createComponent("CTabBar.qml").createObject(root, {tabView: root});
        } else
            tabBar.parent = root;
    }
    onTabBarChanged: {
        tabBar.parent = root;
    }
}
