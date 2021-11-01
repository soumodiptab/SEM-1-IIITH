offset = 15
middle = 10
x_start = 1+offset
x_end = 2*6+middle+offset
y_start = 1
y_end = 5
points_to_print = []
for i in range(1, y_end+1):
    for j in range(1, x_end+1):
        if ((i == y_start) or (i == y_end)) and ((j > x_start and j < x_start+5) or (j > x_start+16 and j < x_end)):
            print('*', end="")
        elif((j == x_start or j == x_end or j == x_start+5 or j == x_start+16) and (i != y_start and i != y_end)):
            print('|', end="")
        else:
            print(' ', end="")
    print()
print()
for i in range(1, offset+1):
    print(" ", end="")
print("          {}")
for i in range(1, offset+1):
    print(" ", end="")
print("    ______________")
