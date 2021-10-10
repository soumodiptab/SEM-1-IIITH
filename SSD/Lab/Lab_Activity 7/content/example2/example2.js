let success = document.getElementById("success")
let addUser = document.getElementById("addUser")
let username = document.getElementById("username")

let mockAPIId = "MOCK_API_ID";

addUser.addEventListener("click", () => {
    let value = username.value;
    if (value.length === 0){
        alert("Username len should be greater than 0")
        return
    }
    let xhttp  = new XMLHttpRequest();
    xhttp.onreadystatechange = function(){
        
        if (xhttp.readyState === XMLHttpRequest.DONE  && xhttp.status === 201){
            success.innerHTML = "Successfully added user"
        }

    }
    xhttp.open("POST", `https://${mockAPIId}.mockapi.io/user`)
    xhttp.setRequestHeader("Content-type", "application/json");
    xhttp.send(JSON.stringify({name: value}));
})
