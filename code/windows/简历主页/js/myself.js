var xingxings = document.getElementsByClassName("xingxing_container");

for(var i=0;i<xingxings.length;i++){
    var num = xingxings[i].textContent;
    xingxings[i].innerHTML = "";
    for(var j=0;j<5;j++){
        var xingxing = document.createElement('div');
        if(num>=1){
            xingxing.className="full_xing xingxing";
            num-=1;
        } else if(num==0) {
            xingxing.className="empty_xing xingxing";
        } else { //hafl
            xingxing.className="half_xing xingxing";
            num-=0.5;
        }
        xingxings[i].appendChild(xingxing);
    }
}
