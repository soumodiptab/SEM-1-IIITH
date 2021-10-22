# * represents variable arguments(extended arguments)
def hypervolume(*length):
    a = 1
    for v in length:
        a *= v
    print(a)


def tag(name, **kwargs):
    print(name)
    print(kwargs)


# in printf we can give variable no. of arguments
#print("abc", "azc", "as4", "asd")
hypervolume()
hypervolume(2, 3, 4)
tag('img', src="iiit.jpg", alt="knowledge", border=1)
