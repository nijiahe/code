const stars = document.getElementsByClassName('star');
const hyper = document.getElementById('hyper');

for(var i=0;i<stars.length;i++){
    let x = `${Math.random() * 200}vmax`
    let y = `${Math.random() * 100}vh`
    let z = `${Math.random() * 200 - 100}vmin`
    let rx = `${Math.random() * 360}deg`
    stars[i].style.setProperty('--x', x)
    stars[i].style.setProperty('--y', y)
    stars[i].style.setProperty('--z', z)
    stars[i].style.setProperty('--rx', rx)
}

hyper.addEventListener('click', e => {
    if (hyper.textContent == '让星星停下') {
        for(var i=0;i<stars.length;i++){
            stars[i].style.animationName = null;
            //stars[i].style.animationIterationCount = 1;
        }
        hyper.textContent = '让星星飞逝';

    } else {
        for(var i=0;i<stars.length;i++){
            let delay = `${Math.random() * 900}ms`;
            stars[i].style.animationDelay = delay;
            stars[i].style.animationName = 'hyper';
        }
        hyper.textContent = '让星星停下';
    }
    document.documentElement.classList.toggle('hyper');
})