import QtQuick 2.0
import com.syberos.basewidgets 2.0
CPageStackWindow {

    keyHandle: false
    onBackKey: {

        var url =startPage.webViewPage.url.toString();
        console.log('log:'+url)
        if(mainApp.pageType(url) === 0||mainApp.pageType(url) === -1 || !startPage.webViewPage.canGoBack){
            hide();
        }else{
            startPage.webViewPage.goBack();
        }
    }

    initialPage:H5AppPage{
        id: startPage
        anchors.fill: parent
        color: "#F7F7FA"
        orientationLock: CPageOrientation.LockPortrait

        onStateChanged: {
            if (status == CPageStatus.WillShow) {
                gScreenInfo.setWindowProperty("STATUSBAR_VISIBLE",true)
                gScreenInfo.setWindowProperty("STATUSBAR_STYLE","transBlack")
            } else if (status == CPageStatus.Show) {

            }
        }
    }
}
