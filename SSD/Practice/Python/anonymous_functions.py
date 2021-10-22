d = {'apple': 18, 'orange': 23, 'kiwi': 3}


# def abc(x):
#     for k,v in x.items():
#         return y


# print(sorted(d.items(), abc(d.items())))

# Lamda Expressions : lambda arguments - expression
print(d.items())
print(sorted(d.items(), key=lambda x: x[1]))  # sorted on value
print(sorted(d.items(), key=lambda x: x[0]))  # sorted on key
# d.items() -> gives key-value pair
# lambda x  referes to d.items and x[0] refers to the key and x[1] refers to the value
