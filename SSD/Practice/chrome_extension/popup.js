document.addEventListener('click', function (e) {
    e = e || window.event;
    var target = e.target || e.srcElement,
        text = target.textContent || target.innerText;
    console.log(target);
}, false);