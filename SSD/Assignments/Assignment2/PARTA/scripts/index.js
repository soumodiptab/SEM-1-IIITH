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
contentclear();
document.getElementById("home").style.display = "block";