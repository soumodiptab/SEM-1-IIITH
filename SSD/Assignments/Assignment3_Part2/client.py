import requests
import random

CHEF_STATUS = False
cookies = {}
orders = []
menuitems = {}


def play_lucky_draw():
    """
    Performs a random percentage selection using chance weights
    Returns:
        item : discount/increase
    """
    draw = [-50, -25, -10, 0, 20]
    value = random.choices(draw, weights=(5, 10, 15, 20, 50), k=1)
    return value[0]


def pattern1():
    """
    Prints the pattern for losing
    """
    offset = 0
    x_start = 1 + offset
    x_end = 6 + offset
    y_start = 1
    y_end = 6
    for i in range(1, y_end + 1):
        for j in range(1, x_end + 1):
            if ((i == y_start) or (i == y_end)) and (
                    j > x_start and j < x_end):
                print('*', end="")
            elif ((j == x_start or j == x_end) and (
                    i != y_start and i != y_end)):
                print('*', end="")
            else:
                print(' ', end="")
        print()
    print()


def pattern2():
    """
    Prints the pattern for winning
    """
    offset = 0
    middle = 10
    x_start = 1 + offset
    x_end = 2 * 6 + middle + offset
    y_start = 1
    y_end = 5
    for i in range(1, y_end + 1):
        for j in range(1, x_end + 1):
            if ((i == y_start) or (i == y_end)) and (
                    (j > x_start and j < x_start + 5) or (
                    j > x_start + 16 and j < x_end)):
                print('*', end="")
            elif ((j == x_start or j == x_end or
                   j == x_start + 5 or j == x_start + 16) and (
                          i != y_start and i != y_end)):
                print('|', end="")
            else:
                print(' ', end="")
        print()
    print()
    for i in range(1, offset + 1):
        print(" ", end="")
    print("          {}")
    for i in range(1, offset + 1):
        print(" ", end="")
    print("    ______________")
    print()


def patterns(val):
    """Prints the patterns
    """
    if val < 0:
        pattern2()
    else:
        pattern1()


def promotional_offer_menu():
    """
        Prints the promotional offer menu
    """
    print("Promotional Offer : 'Test Your Luck'")
    print_line()
    print("There’s a 5% chance to get a 50% discount off the total bill")
    print("10% chance to get 25% discount")
    print("15% chance to get 10% discount")
    print("20% chance to get no discount")
    print("50% chance that the total amount increases by 20%")
    print_line()


def print_line():
    print('----------------------------------------------------------------------------')


def do_signup():
    username = input('Enter new username\n')
    password = input('Enter password\n')
    data = {'username': username, 'password': password}
    response = requests.post('http://localhost:8000//user/signup', json=data).json()
    print(response['msg'])


def do_logout():
    response = requests.get('http://localhost:8000//user/logout', cookies=cookies).json()
    print(response['msg'])


def menu():
    print_line()
    print('1. Preview menu')
    print('2. Order Item')
    print('3. Generate Bill')
    print('4. View Transactions')
    print('5. Logout')
    if CHEF_STATUS:
        print('6. Add item to menu')
    print_line()


def premenufetch():
    global menuitems
    menuitems = {}
    response = requests.get('http://localhost:8000//menu/fetch', cookies=cookies).json()
    menudata = response['items']
    if not menudata:
        return
    for item in menudata:
        menuitems[item['id']] = item


def displaymenuitems():
    global menuitems
    response = requests.get('http://localhost:8000//menu/fetch', cookies=cookies).json()
    menudata = response['items']
    if not menudata:
        print('NO items in MENU')
        return
    print_line()
    print('MENU')
    print_line()
    print('ID', '\t\t', 'HALF', '\t\t', 'FULL')
    menuitems = {}
    for item in menudata:
        menuitems[item['id']] = item
        print(item['id'], '\t\t', item['halfprice'], '\t\t', item['fullprice'])


def addmenuitem():
    itemid = int(input('Enter item id\n'))
    halfprice = int(input('Enter price of Half plate\n'))
    fullprice = int(input('Enter price of Full plate\n'))
    itemdata = {'id': itemid, 'half': halfprice, 'full': fullprice}
    response = requests.post('http://localhost:8000///menu/add', cookies=cookies, json=itemdata).json()
    print(response['msg'])


def viewbill(transaction):
    print_line()
    orderlist = transaction['orders']
    total = float(0)
    for order in orderlist:
        item_total = order['quantity'] * order['price']
        total += item_total
        print(f"Item {order['itemid']}\t[{order['plate']}] [{order['quantity']}]\t{item_total:.2f}")
    print('Total:', f"{total:.2f}")
    print(f"Tip Percentage: {transaction['tip']}%")
    total_after_tip = total + (total * transaction['tip']) / 100
    discounted_price = (total_after_tip * transaction['discount']) / 100
    print("Discount/Increase: ", end="")
    if discounted_price > 0:
        print("+", end="")
    print(f"{discounted_price:.2f}")
    final_total = total_after_tip + discounted_price
    print(f"Final Total: {final_total:.2f}")
    people = transaction['split']
    if people > 1:
        split_final_bill = final_total / people
        print("Bill for each person [", people, "] :", f"{split_final_bill:.2f}")
    print_line()
    return final_total


def viewtransactions():
    response = requests.get('http://localhost:8000///transaction/all', cookies=cookies).json()
    transactions = response['transactions']
    if not transactions:
        print('No Transactions Present')
        return
    i = 1
    for transaction in transactions:
        print(f"{i}. Total Bill: {transaction['total']}")
        i += 1
    print_line()
    print('Press 0 to exit and transaction no. to view previous bill')
    choice = int(input())
    if choice == 0:
        return
    elif choice > len(transactions):
        print('Wrong choice')
        return
    transactionid = transactions[choice - 1]['id']
    trandata = {'id': transactionid}
    response = requests.get('http://localhost:8000///transaction/fetch', cookies=cookies, json=trandata).json()
    viewbill(response)


def orderitem():
    item_id = int(input("Enter item id ?\n"))
    if item_id not in menuitems.keys():
        print('Wrong item id')
        return
    plate = input("Half or Full plate ?( Type - HALF / FULL )\n")
    if not (plate == 'FULL' or plate == 'HALF'):
        print('Wrong option')
        return
    quantity = int(input("How many do you want to order ?\n"))
    if plate == 'FULL':
        price = menuitems[item_id]['fullprice']
    else:
        price = menuitems[item_id]['halfprice']
    flag = False
    for order in orders:
        if order['itemid'] == item_id and order['plate'] == plate:
            order['quantity'] += quantity
            flag = True
            break
    if not flag:
        new_order = {'itemid': item_id, 'plate': plate, 'price': price, 'quantity': quantity}
        orders.append(new_order)
    print('Item has been ordered')


def generatebill():
    global orders
    if len(orders) == 0:
        print('No items ordered')
        return
    print_line()
    choice = int(input("Wanna add some tip ? * - * \n1 - 0%\n2 - 10%\n3 - 20%\n"))
    tip = 0
    if choice == 2:
        tip = 10
    elif choice == 3:
        tip = 20
    split_flag = input("Wanna split the bill ?(Y/N)\n")
    people = 1
    if split_flag == 'Y':
        people = int(input("How many people?\n"))
    promotional_offer_menu()
    lucky_flag = input("So do you want to try ?(Y/N)\n")
    discount = 0
    if lucky_flag == 'Y':
        discount = play_lucky_draw()
        patterns(discount)
        print("Discount/Increase : ", end="")
        if discount > 0:
            print("+", end="")
        print(f"{discount}%")
    new_transaction = {
        'tip': tip,
        'discount': discount,
        'split': people,
        'orders':orders
    }
    final_total=viewbill(new_transaction)
    new_transaction['total']=final_total
    orders=[]
    response = requests.post('http://localhost:8000//transaction/entry', cookies=cookies, json=new_transaction).json()
    print(response['msg'])

def postlogin():
    """
    Options available to the user/chef after logging in
    """
    premenufetch()
    while True:
        menu()
        choice = int(input())
        if choice == 1:
            displaymenuitems()
        elif choice == 2:
            orderitem()
        elif choice == 3:
            generatebill()
        elif choice == 4:
            viewtransactions()
        elif choice == 5:
            if len(orders) > 0:
                print('Items already ordered, generate bill first')
                continue
            do_logout()
            break
        elif choice == 6 and CHEF_STATUS:
            addmenuitem()


def do_login():
    global CHEF_STATUS
    username = input('Enter username\n')
    password = input('Enter password\n')
    data = {'username': username, 'password': password}
    response = requests.get('http://localhost:8000//user/login', json=data)
    cookies['session'] = response.cookies['session']
    responseJson = response.json()
    if 'ischef' in responseJson:
        CHEF_STATUS = responseJson['ischef']
        print(responseJson['msg'])
        postlogin()
    else:
        print(responseJson['msg'])


def init_menu():
    print_line()
    print('Welcome')
    print_line()
    print('1. Signup')
    print('2. Login')
    print('3. Exit')
    print_line()


if __name__ == '__main__':
    while (True):
        init_menu()
        choice = int(input())
        if choice == 1:
            do_signup()
        elif choice == 2:
            do_login()
        elif choice == 3:
            break
