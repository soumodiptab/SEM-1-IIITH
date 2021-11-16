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
    * plate - HALF/FULL
    * quantity
    * price
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
* `/user/signup`: `POST` -> create new user in db
* `/user/login`: `GET` -> login user and add to session and send cookie
* `/user/logout`: `GET` -> logout user from session and make cookie invalid
* `/transaction/entry` : `POST` -> Store the transaction in database
* `/transaction/fetch` : `GET`-> Fetch details of single transaction(transaction id)
* `/transaction/all` : `GET`-> Fetch all transactions

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
# Transaction structure:

```json
{
   "total": 1246.90,
   "tip": 10.00,
   "discount": -133,
   "split": 5,
   "orders": [
      {
         "itemid": 1,
         "plate": "FULL",
         "quantity": 3,
         "price": 120
      },
      {
         "itemid": 1,
         "plate": "HALF",
         "quantity": 3,
         "price": 234
      },
      {
         "itemid": 2,
         "plate": "FULL",
         "quantity": 3,
         "price": 245
      }
   ]
}
```