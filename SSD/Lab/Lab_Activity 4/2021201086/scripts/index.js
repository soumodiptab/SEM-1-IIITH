function sendtoP()
{
    let txt=document.getElementById("ptext").value;
    let pelement=document.getElementById("target");
    pelement.innerHTML=txt;
}
function addToList()
{
    let list=document.getElementById("listTarget");
    let newItem = document.createElement('li');
    let pelement=document.getElementById("target");
    newItem.textContent = pelement.innerHTML+" "+ new Date();
    newItem.addEventListener("mouseover",highlighter);
    newItem.addEventListener("mouseout",unhighlighter);
    list.appendChild(newItem);
}
function removeFromList()
{
    let list = document.getElementById('listTarget');
    list.removeChild(list.lastElementChild);
}
function highlighter(e)
{
    e.target.style.color="red";
}
function unhighlighter(e)
{
    e.target.style.color="black";
}
function changeFont()
{
    let listid=document.getElementById("listTarget");
    listid.style.fontFamily = listid.style.fontFamily==="Arial"?"auto":"Arial";
}