function constructUserDetails(){
    this.username = "user";
    this.password = "password";
    this.displayInfo = function(){
        console.log("Username is " + this.username + " and password is " + this.password)
    }
}


// Creating a new instance using constructor
let user = new constructUserDetails();

user.displayInfo()


// Let's create another instance and try modifying the property
let user2 = new constructUserDetails();

user2.username = "newUser"

user2.displayInfo() // Displays newUser as username

user.displayInfo() // Still prints user as username


// Set the prototype of the constructor. New instances will point ot this prototype and will have access to the same properties
constructUserDetails.prototype.isAdmin = false;

console.log(user.isAdmin)

// All the instances will point to the same prototype. Therefore, any modifications in prototype will be reflected by all the instances

user.__proto__.isAdmin = true;

console.log(user2.isAdmin) // This will print true as well

// However, directly modifying the properties would create a new property in the instance, shadowing the original property of prototype

user.isAdmin = false;


console.log(user.isAdmin) // prints false
console.log(user2.isAdmin) // Still prints true