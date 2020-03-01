var head=document.getElementById('head');
(function head_style(){
    function show() {
        setAlphaOpacity(head,255);
    };

    function hide(){
        setAlphaOpacity(head,30);
    };
    head.onmouseover=show;
    head.onmouseout = hide;
})();

var s = 1;

function scrollFunc(e) {
    // e存在就用e不存在就用windon.event
    e = e || window.event;
// 先判断是什么浏览器
    if (e.wheelDelta) {
        // 浏览器IE，谷歌
        if (e.wheelDelta > 0) {
//当滑轮向上滚动时
//             console.log("滑轮向上滚动");
            if (s == 0) {
                //向下滑动
                setAlphaOpacity(head,255);
                s = 1;
            }
        }
        if (e.wheelDelta < 0) {
//当滑轮向下滚动时
//             console.log("滑轮向下滚动");
            if (s == 1) {
                //向上滑动
                setAlphaOpacity(head,20);
                s = 0;
            }
        }
    } else if (e.detail) {
        //浏览器Firefox
        if (e.detail > 0) {
//当滑轮向上滚动时
//             console.log("滑轮向上滚动");
            if (s == 0) {
                //向下滑动
                setAlphaOpacity(head,255);
                s = 1;
            }
        }
        if (e.detail < 0) {
            //当滑轮向下滚动时
            // console.log("滑轮向下滚动");
            if (s == 1) {
                //向上滑动
                setAlphaOpacity(head,10);
                s = 0;
            }
        }
    }
}

//给页面绑定滑轮滚动事件
if (document.addEventListener) {
    //firefox浏览器
    document.addEventListener('DOMMouseScroll', scrollFunc, false);
}
//ie 谷歌浏览器
window.onmousewheel = document.onmousewheel = scrollFunc;

function getAlphaOpacity(elm){
    elm=typeof elm=="string"?document.getElementById(elm):elm;
    if(document.all){  //IE
        return elm.style.filter;
    }else{             //FF
        return elm.style.opacity;
    }
}

function setAlphaOpacity(elm,value){
    elm=typeof elm=="string"?document.getElementById(elm):elm;
    if(document.all){  //IE
        elm.style.filter='alpha(opacity='+value+')';
    }else{             //FF
        elm.style.opacity=value/100;
    }
}