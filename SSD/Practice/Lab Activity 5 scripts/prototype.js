// Parent object

let userDetails = {
    username: "user",
    password: "password",
    displayInfo: function(){
        console.log("Username is " + this.username + " and password is " + this.password)
    }
}


let adminDetails = {
    isAdmin: true,
    username: "admin"
}

// Admin receiving properties from userDetails


Object.setPrototypeOf(adminDetails, userDetails)

let guestDetails = {
    username: "guest",
    password: ""
}

// Doing the same with Guest details

Object.setPrototypeOf(guestDetails, userDetails)

// Admin overrides only username. Notice the this. reference
adminDetails.displayInfo()

// Guest overrides username and password properties

guestDetails.displayInfo()


// Modifying the prototype's display info function
adminDetails.__proto__.displayInfo = function(){
    console.log("Display info modified")
}

guestDetails.displayInfo() // Prints 'Display info modified'