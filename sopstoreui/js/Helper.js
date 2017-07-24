.pragma library

var BASE = 'http://localhost:9999/';

function requestFormHttp(url,json,cb){

    var xhr = null;
    xhr=new XMLHttpRequest();
    if(xhr == null){
        return;
    }
    xhr.onreadystatechange = function() {
        if(xhr.readyState === XMLHttpRequest.DONE) {
            if(cb) {
                cb(xhr.responseText.toString());
            }
        }else{
            console.log('status:'+xhr.readyState)
        }
    }
    xhr.open('POST', BASE+url,true);
    xhr.setRequestHeader('Content-Type', 'application/json');
    xhr.setRequestHeader("Content-Length", 200);

    var strJson = JSON.stringify(json);
    xhr.send(strJson)
}
//打开app
function openApp(jsonObj,cb){
  var path = '/openApp';
  requestFormHttp(path,jsonObj,cb);
}
//安装app
function installApp(jsonObj,cb){
  var path = '/installApp';
  requestFormHttp(path,jsonObj,cb);
}
//卸载app
function unInstallApp(jsonObj,cb){
  var path = '/unInstallApp';
  requestFormHttp(path,jsonObj,cb);
}

//reqData
function reqData(jsonObj,cb){
  var path = '/reqData';
  requestFormHttp(path,jsonObj,cb);
}

function requestFormHttpTest(cb){

    var url = ' http://172.17.40.47/CASIC/interfaces/304DaiBanInterface.jsp?userName=王鸿志&PID=220223197109281511&webService=';
    var xhr = null;
    xhr=new XMLHttpRequest();
    if(xhr == null){
        return;
    }
    xhr.onreadystatechange = function() {
        if(xhr.readyState === XMLHttpRequest.DONE) {
            if(cb) {
                cb(xhr.responseText);
            }
        }else{
            console.log('status:'+xhr.readyState)
        }
    }
    xhr.open('GET',url,true);
    xhr.send(null)
}

