// One of the ways to create inheritance chain before ES6

/*************************************************************** */


// Parent class
function constructUserDetails(username, password){
    this.username = username;
    this.password = password;
    this.isAdmin = false;
}

constructUserDetails.prototype.displayUserInfo = function(){
    console.log("Username is " + this.username + " and password is " + this.password);
    console.log("Is admin? " + this.isAdmin)
}

// Child class
function constructAdminDetails(username, password){
    constructUserDetails.call(this, username, password);
    this.isAdmin = true;
}

constructAdminDetails.prototype = Object.create(constructUserDetails.prototype)

// Parent instance

let user = new constructUserDetails("user", "password");
user.displayUserInfo()

let admin = new constructAdminDetails("admin", "pass");
admin.displayUserInfo()


/*************************************************************** */


// Using ES6 classes

class constructUserDetailsClass {
    constructor(username, password){
        this.username = username;
        this.password = password;
        this.isAdmin = false;
    }

    displayUserInfo(){
        console.log("Username is " + this.username + " and password is " + this.password);
        console.log("Is admin? " + this.isAdmin)
    }
}


class constructAdminDetailsClass extends constructUserDetailsClass {
    constructor(username, password){
        super(username, password);
        this.isAdmin = true;
    }
}

let userC = new constructUserDetailsClass("user", "password");
userC.displayUserInfo()

let adminC = new constructAdminDetailsClass("admin", "pass");
adminC.displayUserInfo()


// The above is just a syntatic sugar of the previous snippet