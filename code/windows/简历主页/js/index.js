const yangpizhi=document.getElementById("yangpizhi");

function showTextOnYangpizhi(string){
    yangpizhi.innerHTML = "";
    var div = document.createElement("div");
    div.innerHTML=string;
    div.className="yangpizhi_context";
    yangpizhi.appendChild(div);
}

var str= "网站介绍：本网站用于存放研究生复试用个人介绍<br/><br/>" +
    "注意：Microsoft Edge可能由于渲染引擎不佳" +
    "会出现CPU占用率过高的情况，或者浏览器版本过低导致某些属性不支持。可通过左下角的\"让星星停止\"来让背景停止运转<br/><br/>" +
    "谷歌和火狐打开效果更佳<br/><br/>" +
    "点击上方导航栏其它部分进行浏览，需要通过nginx自带的访问验证<br/><br/>" +
    "测试结果：<br/>" +
    "ie 11.6 支持，但不支持星星<br/>" +
    "chrome 76 支持，体验最佳<br/>" +
    "Microsoft EdgeHTML 18.18363 支持，但cpu占用过高<br/>" +
    "Firebox 73 支持，但效果不佳，可能是由于Firebox是在虚拟机中的"

showTextOnYangpizhi(str);
