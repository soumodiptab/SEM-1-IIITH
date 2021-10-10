let fetchListButton = document.getElementById("fetchList")
let userList = document.getElementById("userList")


// Create an account on https://mockapi.io/ and paste the project id
let mockAPIId = "MOCK_API_ID";

fetchListButton.addEventListener("click", () => {
    let xhttp  = new XMLHttpRequest();
    xhttp.onreadystatechange = function(){
        if (xhttp.readyState === XMLHttpRequest.DONE && xhttp.status === 200){
            populateList(JSON.parse(xhttp.responseText))
        }

    }
    xhttp.open("GET", `https://${mockAPIId}.mockapi.io/user`)
    xhttp.send();
})

let a = []
a

function populateList(jsonRes){
    let limit = 100;
    jsonRes = jsonRes.slice(0, limit)
    userList.innerHTML = ""
    jsonRes.forEach((user) => {
        let userLi = document.createElement("li");
        userLi.innerHTML = `<img src="${user.avatar}" width="50"/> ${user.name}`
        userList.appendChild(userLi)
    })
}
