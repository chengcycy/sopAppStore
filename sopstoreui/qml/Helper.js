
.pragma library

function requestHttps(url,cb) {
    var httpRequest = new XMLHttpRequest()
    httpRequest.onreadystatechange = function() {
        if (httpRequest.readyState === XMLHttpRequest.HEADERS_RECEIVED) {
        } else if (httpRequest.readyState === XMLHttpRequest.DONE) {
            if (cb) {
                cb(httpRequest.responseText)
            }
        }
    }
    httpRequest.onerror = function() {
        console.log('error')
    }
    httpRequest.open('GET', encodeURI(url),true)
    httpRequest.send();
}
