function getAttrValue(elem,attr)
{
    return elem.currentStyle?elem.currentStyle[attr]:window.getComputedStyle(elem,null)[attr]||0;
}

function animate(elem,json,fn)
{
    //先暂停elem元素的这个动作防止叠加
    window.clearInterval(elem._timeID);
    elem._timeID = window.setInterval(function () {
        //用来记录是否所有的属性都达到目标值的标志
        var flag=true;
        for(var key in json)
        {
            if(key=="zIndex")
            {
                elem.style[key]=json[key];
            }
            else if(key=="opacity")
            {
                //得到元素当前对应属性的值
                var current_value = getAttrValue(elem,key)*100;
                //目标属性值与当前属性值之差
                var space_value = json[key]*100 - current_value;
                //每个间隔移动的距离
                var v = Math.ceil(Math.abs(space_value)/10);
                //如果目标的x大于当前,就向前进
                if(space_value > 0)
                {
                    elem.style[key] = (current_value + v)/10;
                    flag = false;
                }
                //如果目标的x小于当前,就往后退
                else if(space_value <0)
                {
                    elem.style[key] = (current_value - v)/100;
                    flag = false;
                }
            }
            else
            {
                //得到元素当前对应属性的值
                var current_value = parseInt(getAttrValue(elem,key));
                //目标属性值与当前属性值之差
                var space_value = json[key] - current_value;
                //每个间隔移动的距离
                var v = Math.ceil(Math.abs(space_value)/10);
                //如果目标的x大于当前,就向前进
                if(space_value > 0)
                {
                    elem.style[key] = current_value + v + "px";
                    flag = false;
                }
                //如果目标的x小于当前,就往后退
                else if(space_value <0)
                {
                    elem.style[key] = current_value - v + "px";
                    flag = false;
                }
            }
        };
        //如果已经到达目的地,清理函数,并执行回调函数
        if(flag)
        {
            window.clearInterval(elem._timeID);
            //如果有回调函数,执行回调函数
            if(fn)
            {
                fn();
            }
        }
        },20);


}