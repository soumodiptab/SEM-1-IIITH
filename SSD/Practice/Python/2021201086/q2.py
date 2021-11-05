import sys


def split(number):
    return [int(digit) for digit in number]


def check_paindrome(x):
    number = x
    rev_number = 0
    while(number > 0):
        digit = number % 10
        rev_number = rev_number*10+digit
        number = number//10
    if(x == rev_number):
        print('TRUE')
    else:
        print('FALSE')


number_string = sys.argv[1]
if(len(sys.argv) <= 1):
    print('TRUE')
    exit(0)
#number_string = input()
digits = split(number_string)

val = 0
for d in digits:
    val = val*2+d

check_paindrome(val)
