import random
import csv


def print_line():
    """
    prints the lines for the menu
    """
    print("-----------------------------------------------------------")


def display_menu(items, header):
    """
    Displays the menu for the order selection

    Args:
        items : the items extracted from the menu.csv
        header : headers to be displayed
    """
    print("MENU")
    print_line()
    print(header[0], '\t', header[1], '\t', header[2])
    print_line()
    for k in items.keys():
        print(k, '\t\t', items[k][0], '\t\t', items[k][1])
        print_line()


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
    offset = 15
    x_start = 1 + offset
    x_end = 6 + offset
    y_start = 1
    y_end = 6
    for i in range(1, y_end + 1):
        for j in range(1, x_end + 1):
            if ((i == y_start) or (i == y_end)) and (
                    j > x_start and j < x_end):
                print('*', end="")
            elif((j == x_start or j == x_end) and (i != y_start and i != y_end)):
                print('*', end="")
            else:
                print(' ', end="")
        print()
    print()


def pattern2():
    """
    Prints the pattern for winning
    """
    offset = 15
    middle = 10
    x_start = 1 + offset
    x_end = 2 * 6 + middle + offset
    y_start = 1
    y_end = 5
    for i in range(1, y_end + 1):
        for j in range(1, x_end + 1):
            if ((i == y_start) or (i == y_end)) and (
                    (j > x_start and j < x_start + 5) or (j > x_start + 16 and j < x_end)):
                print('*', end="")
            elif((j == x_start or j == x_end or j == x_start + 5 or j == x_start + 16)
                 and (i != y_start and i != y_end)):
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
    """patterns [summary]

    Args:
        val (int): [asdas]
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


PATH = 'Menu.csv'
headers = []
rows = {}
"""
rows[0] - half
rows[1] - full
"""
file = open(PATH)
csvreader = csv.reader(file)
headers = next(csvreader)
for row in csvreader:
    rows[int(row[0])] = [int(row[1]), int(row[2])]
display_menu(rows, headers)
item_list = {}
"""
stores the item list that has been ordered in a dictionary
item_list[item_id]=[half,full]
"""
while True:
    item_id = int(input("Enter item id ?\n"))
    plate = int(input("Half or Full plate ?(1-full 2-half)\n"))
    qty = int(input("How many do you want to order ?\n"))
    more = input("Wanna add anymore items ?(Y/N)\n")
    if item_id not in item_list.keys():
        item_list[item_id] = [0, 0]
    if plate == 2:
        item_list[item_id][0] += qty
    else:
        item_list[item_id][1] += qty
    if more == 'N':
        break
print_line()
choice = int(
    input("Wanna add some tip ? * - * \n1 - 0%\n2 - 10%\n3 - 20%\n"))
tip = 0
if choice == 2:
    tip = 10
elif choice == 3:
    tip = 20
TOTAL = 0
for item_id in item_list.keys():
    TOTAL = float(TOTAL + item_list[item_id][0]
                  * rows[item_id][0] + item_list[item_id][1] * rows[item_id][1])
"""
finding the total of partial/full items from the booked order
"""
total_after_tip = TOTAL + TOTAL * (tip / 100)
print(f"TOTAL: {total_after_tip:.2f}")
split_flag = input("Wanna split the bill ?(Y/N)\n")
PEOPLE = 1
if split_flag == 'Y':
    PEOPLE = int(input("How many people?\n"))
    split_bill = total_after_tip / PEOPLE
    print("Total of each person [", PEOPLE, "] :", f"{split_bill:.2f}")
promotional_offer_menu()
lucky_flag = input("So do you want to try ?(Y/N)\n")
perc = 0
if lucky_flag == 'Y':
    perc = play_lucky_draw()
patterns(perc)
perc_value = total_after_tip * (perc / 100)
print("Discount/Increase: ", end="")
if(perc_value > 0):
    print("+", end="")
print(f"{perc_value:.2f}")
print_line()
final_total = 0
for item_id in item_list.keys():
    if item_list[item_id][0] != 0:
        print("Item ", item_id, "[Half][", item_list[item_id][0],
              "]: ", f"{item_list[item_id][0]*rows[item_id][0]:.2f}")
    if item_list[item_id][1] != 0:
        print("Item ", item_id, "[Full][", item_list[item_id]
              [1], "]: ", f"{item_list[item_id][1]*rows[item_id][1]:.2f}")
print("Total: ", f"{TOTAL:.2f}")
print("Tip Percentage: ", tip, "%")

print("Discount/Increase: ", end="")
if perc_value > 0:
    print("+", end="")
print(f"{perc_value:.2f}")
final_total = total_after_tip + perc_value
print(f"Final Total: {final_total:.2f}")
if split_flag == 'Y':
    split_final_bill = final_total / PEOPLE
    print("Bill for each person [", PEOPLE,
          "] :", f"{split_final_bill:.2f}")
