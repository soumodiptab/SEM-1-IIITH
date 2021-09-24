let userDetails = {
    username: "user",
    password: "password",
    get credentials(){
        return [this.username, this.password]
    },
    set credentials(creds){
        [this.username, this.password] = creds.split(" ");
    }
}

console.log(userDetails.credentials) // Returns ['user', 'password']

userDetails.credentials = "user2 pass2"

console.log(userDetails.credentials) // Returns ['user2', 'pass2']

// Masking properties (Sort of)

let adminDetails = {
    username: "admin",
    get password(){
        return this._password;
    },

    set password(password){
        this._password = password
    }
}

adminDetails.password = "pass"

console.log(adminDetails.password)

// The original property can still be accessed, but still using get & set is cleaner and additional checks can be performed
// In comparison to directly setting the property values

console.log(adminDetails._password)


// Using computed properties
let prop = "username"
let adminDetails2 = {get [prop](){return `value`}}

console.log(adminDetails2["username"])