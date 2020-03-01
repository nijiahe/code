var head=document.getElementById('head');
setAlphaOpacity(head,10);
setTimeout(function () {
    hyper.click();
},100);
console.log("travel.js");

//  ["2016-09-1","初入大学..."],
var travel=[
    ["2017-08-20","最开始自行接触计算机知识，其实是因为大一下学期C语言程序设计考试没通过..自行学习准备补考"],
    ["2017-09-15","补考通过。大二专业分方向，开始接触自身专业知识时，感受到我对我本身专业的兴趣不大。出于本身就对计算机知识的好奇，我抱着尝试的想法开始自学计算机知识"],
    ["2017-10-01","开始时是看的是黑马程序员2016年c、c++视频，虽然视频讲的知识一般没有书上面面俱到、有解释，但对初学仍是个很好的选择。内容如后续所示："],
    ["2017-10-02","开始学习C语言，包括小部分windows SDK编程"],
    ["2017-11-27","开始学习C++,包括基础数据结构和算法、设计模式"],
    ["2018-02-06","开始学习oracle和mysql数据库，包括在C中内嵌用法"],
    ["2018-02-11","开始学习linux系统使用、shell脚本、linux系统编程,包括基础计算机网络、操作系统、Apache服务器"],
    ["2018-04-11","开始学习cocos2dx游戏引擎，通过学习此引擎理解了一些c++的设计模式，并且很好的练习了c++"],
    ["2018-07-01","开始学习基于qt的窗口编程"],
    ["2018-07-11","直至此时，黑马2016c、c++视频学完，因为在使用cocos creator时，需要使用javascript或lua这类脚本语言，所以开始学习html、css、js相关知识，看黑马2018年前端视频教程"],
    ["2018-07-12","html、css、js"],
    ["2018-08-20","网页相关看完，此时基于学习c时，教程中多次提到的反汇编，和写windows驱动，开始学习Assemble Language，看的是小甲鱼基于《win32汇编语言：从实模式到保护模式》、windows SDK编程、逆向破解的视频教程"],
    ["2018-08-21","开始学习win32汇编、用汇编进行windows SDK编程、逆向基础，包括关于页、描述符等知识"],
    ["2018-10-14","在利用C写爬虫时，使用的库函数出现DNS解析错误的现象，但那时对计算机网络并不了解，所以开始学习计算机网络相关知识。从此时开始，获取知识的途径基本从视频教程完全转向书籍"],
    ["2018-10-15","阅读《tcp/ip详解卷一》和《计算机网络 谢希仁》，之后发掘前者更适合实践"],
    ["2018-11-15","学习完网络之后，决定接触下黑客这个这个让人始终崇拜和憧憬的领域"],
    ["2018-11-16","开始阅读《hacking：The art of exploitation》，书虽然比较老，但不失是本好书，由于是英文版，进度比较慢，" +
    "并且书中的环境是随书光盘中的 栈前金丝雀、ASLR、可执行保护，专门用于学习hack原理，一开始在面对我gcc编译出的汇编中的push es:[ds]和_chk_stack_fail_一头雾水，" +
    "幸好之后找到了原因是栈前金丝雀。之后在将这些安全措施都关上后顺利进行了下去。该书介绍了基于c介绍了如将自己精心构造的汇编代码通过环境变量、命令行参数、数组溢出" +
    "等手段注入于程序内，并通过覆盖栈中保存的rip或导入表等进行跳转。还有DDOS、中间人攻击、嗅探、数据包诈骗等知识，汇编代码重组变形、回绑端口获取root顶置式，" +
    "极大提升了我对c、c++的理解，对汇编的阅读能力，对网络协议的理解"],
    ["2019-01-22","介于《hacking：The art of exploitation》书中作者提出的猜测操作系统在每次新开进程时分配不可执行页作为栈环境、尝试用execve跳过，加上在汇编中、linux系统编程中遇到的页、" +
    "描述符表等，也升起了我对操作系统的好奇，开始学习操作系统"],
    ["2019-01-23","开始阅读《深入理解计算机系统》，接触到at&t格式汇编，并且对系统整体有了一个模糊的理性知识上的认识，但因为未学习过计算机组成，跳过此类部分"],
    ["2019-02-03","对于《深入理解计算机系统》中频繁出现的字眼'软硬件共同实现'，我对其不能理解。所以决定找一个操作系统进行实践"],
    ["2019-02-04","开始阅读《一个64位操作系统的设计与实现》，作者今年30左右，借鉴了前辈们的如余渊的《自己动手写操作系统》，实现了ia-32e模式的" +
    "多核调度操作系统。由于选择了和作者不一样的编译平台，阅读此书基本运用到了所有我之前学到的偏底层知识，包括不断使用gdb调试，对二进制文件进行objdump对照等，" +
    "通过此书也使我对系统整体如bootloader、初始化页表、控制中断、驱动、虚拟内存映射、进程切换、用户态和内核态的切换等知识有一个感性的认识"],
    ["2019-04-01","正式完全投入考研，期间就数学知识主要阅读、看过《普林斯顿微积分读本》、'MIT多变量微积分'、'MIT微分方程'、'MIT线性代数'、" +
    "《线性代数及其应用》、《概率导论》、《微积分学教程卷一》前一半，计算机知识有《c++ primer》"],
    ["2019-12-25","初试结束，就早已是心头病的算法部分，就此复试机会，阅读《数据结构c++版》、《算法导论》除第七章'算法选编'外的大多数、《挑战程序设计竞赛》除高级篇外的大多数"],
];
//["2020-02-29","今天，未完待续..."],

const lbtn=document.getElementById("lbtn");
const rbtn=document.getElementById("rbtn");
const date=document.getElementById("date");
const yangpizhi=document.getElementById("yangpizhi");

/* -1 indacate 2016.09.01,and */
const l_head = -1;
const l_tail = travel.length;
var point = -1;
lbtn.style.display = "none";
var destination_date = "2016-09-01";
var start_text = "本旅程根据我文件的修改日期以及记忆推导而出。</br>" +
    "2018-10-14前主要通过视频教程学习，之后主要通过书籍学习。</br>"+
    "大学的第一天：</br>" +
    "点击屏幕最右侧箭头开始旅程</br>";
var end_text = "时至今日，未完待续...";
showTextOnYangpizhi(start_text);
var text;
lbtn.onclick = function () {
    if (point <= l_head+1) { //此时点击lbtn会回到2016.09.01
        ;//之后应改为渐变
        lbtn.style.display = "none";
        rbtn.style.display = "block";
        /*text show message of List_head*/
        ChangeDateToAndShowText("2016-09-01",start_text);
    }  else {
        lbtn.style.display = "block";
        rbtn.style.display = "block";
        point--;
        /*text show message in the list*/
        ChangeDateToAndShowText(travel[point][0],travel[point][1]);
    }
}

rbtn.onclick = function() {
    if( point >= l_tail-1){//此时点击btn会到"2020.02.29,未完待续.."
        lbtn.style.display = "block";
        rbtn.style.display = "none";
        /*text show message of List_tail*/
        ChangeDateToAndShowText("2020-02-29",end_text);
    } else {
        lbtn.style.display = "block";
        rbtn.style.display = "block";
        point++;
        /*text show message in the list*/
        ChangeDateToAndShowText(travel[point][0],travel[point][1]);
    }
}

function getNextDate(date, day) {
    var dd = new Date(date);
    dd.setDate(dd.getDate() + day);
    var y = dd.getFullYear();
    var m = dd.getMonth() + 1 < 10 ? "0" + (dd.getMonth() + 1) : dd.getMonth() + 1;
    var d = dd.getDate() < 10 ? "0" + dd.getDate() : dd.getDate();
    return y + "-" + m + "-" + d;
};

//animation,increase date in the way of slow in both side and fast in middle
function speed_changer(velocity) {
    var gap = datedifference(date.textContent,destination_date);
    if(gap > 0){
        setTimeout(function () {
            date.textContent = getNextDate(date.textContent,1);
            speed_changer(velocity>1000/128? velocity/1.2:velocity);
        },velocity);
    } else if(gap < 0){
        setTimeout(function () {
            date.textContent = getNextDate(date.textContent,-1);
            speed_changer(velocity>1000/128? velocity/1.2:velocity);
        },velocity);
    }
    else {
        showTextOnYangpizhi(text);
    }
}


function ChangeDateToAndShowText(d_date,string){
    //头几天变化速度分别为1/4,1/8,1/16,1/32,之后固定在1/32
    destination_date =d_date;
    text=string;
    speed_changer(250);
}

function datedifference(sDate1, sDate2) {    //sDate1和sDate2是2006-12-18格式
    var dateSpan,
        tempDate,
        iDays;
    sDate1 = Date.parse(sDate1);
    sDate2 = Date.parse(sDate2);
    dateSpan = sDate2 - sDate1;
    iDays = Math.floor(dateSpan / (24 * 3600 * 1000));
    return iDays
};

function showTextOnYangpizhi(string){
    yangpizhi.innerHTML = "";
    var div = document.createElement("div");
    div.innerHTML=string;
    div.className="yangpizhi_context";
    yangpizhi.appendChild(div);
}

