import random
import csv
import pprint


def print_line():
    """
    prints the lines for the menu
    """
    print("-----------------------------------------------------------")


def display_menu(rows, header):
    """
    Displays the menu for the order selection

    Args:
        rows : the items extracted from the menu.csv
        header : headers to be displayed
    """
    print("MENU")
    print_line()
    print(header[0], '\t', header[1], '\t', header[2])
    print_line()
    for k in rows.keys():
        print(k, '\t\t', rows[k][0], '\t\t', rows[k][1])
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
    print("You won")


def pattern2():
    print("You lose")


def patterns(val):
    if val < 0:
        pattern1()
    else:
        pattern2()


path = 'Menu.csv'
headers = []
rows = {}
"""
rows[0] - half
rows[1] - full
"""
file = open(path)
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
    qty =int(input(""))
    more = input("Wanna add anymore items ?(Y/N)\n")
    if item_id not in item_list.keys():
        item_list[item_id] = [0, 0]
    if plate == 2:
        item_list[item_id][0] += 1
    else:
        item_list[item_id][1] += 1
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
print("TOTAL:")
total = 0
for item_id in item_list.keys():
    total = total+item_list[item_id][0] * \
        rows[item_id][0]+item_list[item_id][1]*rows[item_id][1]
"""
finding the total of partial/full items from the booked order
"""
total_after_tip = total+total*(tip/100)
print(round(total_after_tip, 2))
split_flag = input("Wanna split the bill ?(Y/N)\n")
people = 1
if split_flag == 'Y':
    people = int(input("How many ?\n"))
    split_bill = total_after_tip/people
    print("Total of each person [", people, "] :\n", round(split_bill, 2))
lucky_flag = input(
    "Do you want to try our promotional offer 'Test your luck' ?(Y/N)\n")
perc = 0
if lucky_flag == 'Y':
    perc = play_lucky_draw()
patterns(perc)
print_line()
final_total = 0
for item_id in item_list.keys():
    if item_list[item_id][0] != 0:
        print("Item ", item_id, "[Half][", item_list[item_id]
              [0], "]: ", item_list[item_id][0]*rows[item_id][0])
    if item_list[item_id][1] != 0:
        print("Item ", item_id, "[Full][", item_list[item_id]
              [1], "]: ", item_list[item_id][1]*rows[item_id][1])
print("Total: ", total)
print("Tip Percentage: ", tip, "%")
print("Discount/Increase: ", perc, "%")
final_total = total_after_tip+total_after_tip*(perc/100)
print("Final Total: ", round(final_total, 2))
if split_flag == 'Y':
    split_final_bill = final_total/people
    print("Bill for each person [", people,
          "] :\n", round(split_final_bill, 2))
