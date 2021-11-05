import sys
input_string = sys.argv[1]
list = input_string.split(' ')
filtered_list = [x for x in list if x]
number_list = sorted(filtered_list, key=lambda i: float(i))
output_list = []
for num in number_list:
    output_list.append(int(num))
print(output_list)
