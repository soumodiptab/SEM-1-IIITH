offset = 15
x_start = 1+offset
x_end = 6+offset
y_start = 1
y_end = 6
for i in range(1, y_end+1):
    for j in range(1, x_end+1):
        if ((i == y_start) or (i == y_end)) and (j > x_start and j < x_end):
            print('*', end="")
        elif((j == x_start or j == x_end) and (i != y_start and i != y_end)):
            print('*', end="")
        else:
            print(' ', end="")
    print()
print()

