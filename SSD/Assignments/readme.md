# Things to do :
1. Create user
2. Login user



# Database :
1. Users-
    * userid - String - PK 
    * name - String
    * password - String
    * ischef - Boolean
2. Menu-
    * id
    * half
    * full
3. Order-
    * transactionid
    * itemid - id
    * half/full - boolean
    * qty
4. Transaction-
    * userid
    * transactionid (auto generated)
    * date
    * tip
    * discount
    * split
    * total

# Rest Endpoint :
* `/menu/add` : `POST` 
* `/menu/fetch` : `GET`
* `/user/create`: `POST` -> create new user in db
* `/user/login`: `POST` -> login user and add to session
* `/transaction/entry` :
* `/order/entry` :
* `/transaction/fetch` :

# Client script operations :
1. Options -
    * Signup - create a new user with ischef flag false
    * Login - take username and password and authenticate -> find if chef/user
2. Login user/Chef
    * User Login - Options: (do not allow logout while transaction taking place)
        * View Menu
        * Transaction from 3A
        * View previous Bills
        * Logout
    * Chef Login - Options:
        * View Menu
        * Transaction from 3A
        * View previous Bills
        * Add new item in menu
        * Logout