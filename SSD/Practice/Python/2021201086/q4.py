# Creating a parent class called Animal
class Animal:
    def __init__(self):
        self.attrib = 'I am an animal'
        self.legs = 4

    def animal_call(self):
        print('Animal Call')

    def animal_fun(self):
        print('Animal Function')

# Creating a child class that inherits from Parent called dog

# This specifies the inheritance of which class it is inheriting from
class Dog(Animal):
    def __init__(self):
        super().__init__()
        self.attrib = 'I am a dog'

    def animal_call(self):
        print('Barking')


class Cat(Animal):
    def __init__(self):
        super().__init__()
        self.attrib = 'I am a cat'

    def animal_call(self):
        print('Meow...')


# This is the parent class object
animal = Animal()
# This will print the parent class attrib
print(animal.attrib)
# this will call animal's version of animal call
animal.animal_call()
# Create instance of dog
labrador = Dog()

# Show attributes and methods of dog ,ie. child class
print(labrador.attrib)
# Calls the chile function
labrador.animal_call()
# gets the parent attribute through inheritance
print(labrador.legs)
# calls the parent function
labrador.animal_fun()

new_cat = Cat()

new_cat.animal_call()

print(new_cat.legs)

new_cat.animal_fun()
