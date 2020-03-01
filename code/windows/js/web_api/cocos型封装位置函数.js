//传入的元素的相应属性
function getAttrValue(elem,attr)
{
    return elem.currentStyle?elem.currentStyle[attr]:window.getComputedStyle(elem,null)[attr]||0;
}

//得到相对于父亲节点的坐标,外边距不包括在内
function getPosition(elem) {
    return {
        x:elem.offsetLeft,
        y:elem.offsetTop
    }
}
//设置相对于父节点的坐标
function setPosition(elem,x,y) {
    //还要去除margin带来的影响
    elem.style.left = x-parseInt(getAttrValue(elem,"margin-left"))+"px";
    elem.style.top = y-parseInt(getAttrValue(elem,"margin-top"))+"px";
}
//得到相对于浏览器的坐标
function getWindowPosition(elem) {
    var this_position = getPosition(elem);
    //document为浏览器,无offset属性
    if(elem.parentNode!=document)
    {
        var parent_position = getWindowPosition(elem.parentNode);
        return {
            x:parent_position.x+this_position.x,
            y:parent_position.y+this_position.y
        }

    }
    else
    {
        return {
            x:this_position.x,
            y:this_position.y
        }
    }
}
function setWindowPosition(elem,x,y) {
    var windowPosition = getWindowPosition(elem.parentNode);
    setPosition(elem,x-windowPosition.x,y-windowPosition.y);
}
//得到元素实际的大小(即元素的width和height属性)
function getContentSize(elem) {
    return {
        width:parseInt(getAttrValue(elem,"width")),
        height:parseInt(getAttrValue(elem,"height"))
    }
}

//传入元素可视区域的大小
function getVisiableSize(elem) {
    return {
        width:elem.clientWidth,
        height:elem.clientHeight
    }
}
//设置元素长宽
function setContentSize(elem,width,height)
{
    elem.style.width=width+"px";
    elem.style.height=height+"px";
}

//得到元素四个角的x 和 y
function getBoundingBox(elem) {
    var position = getPosition(elem);
    var size = getVisiableSize(elem);
    return {
        min_x:position.x,
        min_y:position.y,
        max_x:position.x+size.width,
        max_y:position.y+size.height
    }
}







/*以下代码用于事件中获取一些属性*/
var event={
    //得到事件的兼容代码
    getEvent:function (e) {
        return e?e:window.event;
    },
    //得到可视区域X的兼容代码
    getClientX:function (e) {
        return this.getEvent(e).clientX;
    },
    //得到可视区域Y的兼容代码
    getClientY:function (e) {
        return this.getEvent(e).clientY;
    },
    //得到卷出去的区域的兼容代码
    getScroll:function()  {
        return {
            left:window.pageYOffset||document.body.scrollLeft||document.documentElement.scrollLeft||0,
            top:window.pageYOffset||document.body.scrollTop||document.documentElement.scrollTop||0
        }
    },
    getEventWindowPositoin:function (e) {
        return {
            x:this.getEvent(e).pageX?this.getEvent(e).pageX:this.getClientX(e)+this.getScroll().left,
            y:this.getEvent(e).pageY?this.getEvent(e).pageY:this.getClientY(e)+this.getScroll().top
        }
    },
};