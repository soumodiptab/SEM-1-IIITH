# SSD ASSIGNMENT 3-A
A group of friends ordered food for pickup from the menu items provided in csv. Write an interactive 
python code that accepts input and displays output via command line and calculates the total bill. It should follow the below steps sequentially.


### DISPLAYING THE MENU:
```
MENU
-----------------------------------------------------------
Item no          Half Plate      Full Plate
-----------------------------------------------------------
1                20              30
-----------------------------------------------------------
2                210             400
-----------------------------------------------------------
3                460             600
-----------------------------------------------------------
4                500             650
-----------------------------------------------------------
5                400             800
-----------------------------------------------------------
6                450             600
-----------------------------------------------------------
7                320             400
-----------------------------------------------------------
8                360             450
-----------------------------------------------------------
9                220             400
-----------------------------------------------------------
```
### Item ordering format
```
Enter item id ?
1
Half or Full plate ?(1-full 2-half)
2
How many do you want to order ?
3
Wanna add anymore items ?(Y/N)
Y 
```
Items can be ordered in any sequence and the number of plates and the size of plate(Half/Full) needs to be given according to the format mentioned above.

Additional orders can be given(even to the same item), to quit N must be pressed.

### Tipping
```
-----------------------------------------------------------
Wanna add some tip ? * - * 
1 - 0%
2 - 10%
3 - 20%
2
TOTAL: 506.00
```
The tip needs to be provided either `(1/2/3)` for the mentioned percentages.

The total will then be displayed along with the tip.

### Splitting the Bill
```
Wanna split the bill ?(Y/N)
Y
How many people?
3
Total of each person [ 3 ] : 168.67
```
If the bill needs to be split is asked. If bill split is chosen display the total of each person.
### Promotional Offer
```
Promotional Offer : 'Test Your Luck'
-----------------------------------------------------------
There’s a 5% chance to get a 50% discount off the total bill
10% chance to get 25% discount
15% chance to get 10% discount
20% chance to get no discount
50% chance that the total amount increases by 20%
-----------------------------------------------------------
So do you want to try ?(Y/N)
Y
                **** 
               *    *
               *    *
               *    *
               *    *
                **** 
Discount Increase/Decrease : 0.00
```
In the promotional offer section take input whether to participate in the lucky draw.
The lucky draw has a weighted probabilty.
### Final Bill
```
Discount Increase/Decrease : 0.00
-----------------------------------------------------------
Item  1 [Half][ 3 ]:  60.00
Item  2 [Full][ 1 ]:  400.00
Total:  460.00
Tip Percentage:  10 %
Discount/Increase:  0.00
Final Total: 506.00
Bill for each person [ 3 ] : 168.67
```
The final bill is printed where all the same items with same plate are merged together and the total of each sub section is displayed.
If in case bill was split then the total of each person is displayed.