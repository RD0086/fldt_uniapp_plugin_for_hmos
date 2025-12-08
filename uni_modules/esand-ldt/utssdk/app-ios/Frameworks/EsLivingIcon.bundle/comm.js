class HttpUtils{
    getHttpRequest(type, path, useAjax){
        const Http = new XMLHttpRequest();
        const url=`http://127.0.0.1:32195${path}`;
        Http.open(type, url, useAjax);
        return Http;
    }
    
    showToast(title, content){
        const Http = this.getHttpRequest("POST", "/show_toast", true)
        Http.send(JSON.stringify({title, content}));
    }
    
    getConfig(){
        const Http = this.getHttpRequest("POST", "/get_config", false)
        Http.send();
        return Http.responseText;
    }
    
    uploadIDAndName(idNumber, idName, token, res){
        const Http = this.getHttpRequest("POST", "/upload_id_name", true);
        Http.onload = (e) => {
            if (Http.readyState === 4) {
              if (Http.status === 200) {
                  putLog("上传成功");
                  res(Http.responseText);
              }
            }
        };
        
        let requestBody = JSON.stringify({id:idNumber, name:idName, token:token});
        putLog(requestBody);
        Http.send(requestBody);
    }
    
    RPVAuthn(){
        const Http = this.getHttpRequest("POST", "/rpv_auth", true);
        putLog("开始实人认证");
        Http.send();
    }
    
    getOCRFrontResult(){
        const Http = this.getHttpRequest("POST", "/get_ocr_front_result", false);
        Http.send();
        return Http.responseText;
    }
    
    takeFrontPic(res){
        const xhr = this.getHttpRequest("POST", "/take_front_pic", true);
        xhr.onload = (e) => {
          if (xhr.readyState === 4) {
            if (xhr.status === 200) {
                res(xhr.responseText);
            } else {
                InputUserInfo.showToast("错误", "系统错误，请联系管理员:FRONT");
            }
          }
        };
        xhr.send(null);
    }
    
    takeBackPic(res){
        const xhr = this.getHttpRequest("POST", "/take_back_pic", true);
        xhr.onload = (e) => {
          if (xhr.readyState === 4) {
            if (xhr.status === 200) {
                res(xhr.responseText);
            } else {
                InputUserInfo.showToast("错误", "系统错误，请联系管理员:FRONT");
            }
          }
        };
        xhr.send(null);
    }
    
    isOpenOcr(){
        const xhr = this.getHttpRequest("POST", "/open_ocr", false);
        xhr.send(null);
        return xhr.responseText;
    }
}

var InputUserInfo = new HttpUtils();

function putLog(text){
    const Http = new XMLHttpRequest();
    const url='http://127.0.0.1:32195/put_log';
    Http.open("POST", url, true);
    Http.send(text);
}

function getParameterByName(name, url) {
   if (!url) url = window.location.href;
   name = name.replace(/[\[\]]/g, '\\$&');
   var regex = new RegExp('[?&]' + name + '(=([^&#]*)|&|#|$)'),
       results = regex.exec(url);
   if (!results) return null;
   if (!results[2]) return '';
   return decodeURIComponent(results[2].replace(/\+/g, ' '));
}

/**
 * 创建一个inputeElement
 * @param name 对象的名字
 * @param value 对象的值
 * @returns {HTMLInputElement}
 */
function createInput(name,value){
    let input =document.createElement("input");
    input.type="hidden";
    input.name=name;
    input.value=value;
    return input;
}

function getOCRBackResult(){
    const Http = new XMLHttpRequest();
    const url='http://127.0.0.1:32195/get_ocr_back_result';
    Http.open("POST", url, false);
    Http.send();
    return Http.responseText;
}

function exit(){
    const Http = new XMLHttpRequest();
    const url='http://127.0.0.1:32195/exit';
    Http.open("POST", url);
    Http.send();
}

function getToken(){
    const Http = new XMLHttpRequest();
    const url='http://127.0.0.1:32195/get_token';
    Http.open("POST", url, false);
    Http.send();
    return Http.responseText;
}
