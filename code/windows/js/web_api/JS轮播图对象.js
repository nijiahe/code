/*
封装了一个轮播图对象
传入参数为父级ul类,轮播图结构应满足
div
    ul
        li.map_list_item
        li.map_list_item
        li.map_list_item
        ……
    div.left_button
    div.right_button
    div.map_nav
        .map_nav_item
        .map_nav_item
        .map_nav_item
        ……
结构
div结构应设置位置为相对位置,li应设置位置为相对位置
*/


function Sowing_map(div_elem) {
    //轮播图li数组
    /*this.li_items = div_elem.getElementsByClassName("map_list_item");
    this.map_num = this.li_items.length - 1;
    this.show = div_elem.querySelector(".show");
    this.nav_list = div_elem.querySelectorAll(".map_nav_item");*/
    var nav_list = div_elem.querySelectorAll(".map_nav_item");
    var li_items = div_elem.getElementsByClassName("map_list_item");
    var show = div_elem.querySelector(".show");
    var map_num = li_items.length - 1;
    var left_button;
    var right_button;
    //设置左侧按钮
    this.setLeftButton = function (className) {
        left_button = div_elem.querySelector(className);
        left_button.onclick = function () {
            for (var i = 0; i < nav_list.length; i++) {
                if (nav_list[i].id == "red") {
                    if (i == 0) {
                        show.style.left = -li_items[map_num].offsetLeft + "px";
                        nav_list[map_num - 1].onclick();
                    }
                    else {
                        nav_list[i - 1].onclick();
                    }
                    break;
                }
            }
        };
    };
    //设置右侧按钮
    this.setRightButton = function (className) {
        right_button = div_elem.querySelector(className);
        right_button.onclick = function () {
            for (var i = 0; i < nav_list.length; i++) {
                if (nav_list[i].id == "red") {
                    if(i==0)
                    {
                        show.style.left = 0 + "px";
                        nav_list[1].onclick();
                    }
                    else
                    {
                        nav_list[i + 1].onclick();
                    }
                    if(i == map_num-1)
                    {
                        nav_list[0].id="red";
                    }
                    break;
                }
            }
        };
    };
    //设置图片圆形导航点
    this.setNavItems = function () {
        for (var i = 0; i < nav_list.length; i++) {
            nav_list[i].list_num = i;
            nav_list[i].onclick = function () {
                for (var i = 0; i < nav_list.length; i++) {
                    nav_list[i].id = "";
                }
                this.id = "red";
                var target_x = li_items[this.list_num].offsetLeft;
                var ac_time = 1000;
                var every_time = 25;
                var X_length = Math.abs(target_x + show.offsetLeft);
                var v = X_length * every_time / ac_time;

                window.clearInterval(show._timeID);
                show._timeID = window.setInterval(function () {
                    //当前间隔移动的距离
                    var current_x = v;
                    //相差的值
                    X_length = Math.abs(target_x + show.offsetLeft);
                    if (X_length < current_x) {
                        current_x = X_length;
                    }
                    if (-show.offsetLeft < target_x) {
                        show.style.left = show.offsetLeft - current_x + "px";
                    }
                    else if (-show.offsetLeft > target_x) {
                        show.style.left = show.offsetLeft + current_x + "px";
                    }
                    else {
                        window.clearInterval(show._timeID);
                    }
                }, every_time);
            };
        }
    };
    var autoPlayID;
    this.autoPlay = function ()
    {
        window.clearInterval(autoPlayID);
        autoPlayID = window.setInterval(function(){
            right_button.onclick();
        },2000);
        console.log(" play this.autoPlayID"+autoPlayID);
    }

    this.unAutoPaly = function () {
        window.clearInterval(autoPlayID);
        console.log(" stop this.autoPlayID"+autoPlayID);
    };

    //鼠标进入时的事件
    show.onmouseover = this.unAutoPaly;

    //鼠标出去时的事件
    show.onmouseout = this.autoPlay;
}