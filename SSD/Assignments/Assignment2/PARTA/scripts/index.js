function navfunction() {
  var x = document.getElementById("myTopnav");
  if (x.className === "topnav") {
    x.className += " responsive";
  } else {
    x.className = "topnav";
  }
}
function contentclear()
{
    var i, content;
    content = document.getElementsByClassName("content");
    for (i = 0; i < content.length; i++) {
      content[i].style.display = "none";
    }
}
function openContent(e, name) {
    var i,tab;
    contentclear();
    tab = document.getElementsByClassName("tabs");
    for (i = 0; i < tab.length; i++) {
      tab[i].className = tab[i].className.replace("active", "");
    }
    document.getElementById(name).style.display = "block";
    e.currentTarget.className += " active";
  }
function datesetter()
{
  var x=document.getElementById("date");
  x.innerHTML=new Date();
  displayloop();
}
function displayloop(){
  mytime=setTimeout('datesetter()',1000)
  }
contentclear();
document.getElementById("home").style.display = "block";
datesetter();