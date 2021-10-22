#read list comprehension
#Higher order functions
x=10
y='Hello world'
items=[10,20]
def greeting(name):
    print("Hello "+name)
g=greeting
print(type(greeting))
print(type(g))
g(y)
#Why use this anwyway?
# In python everything is an object e