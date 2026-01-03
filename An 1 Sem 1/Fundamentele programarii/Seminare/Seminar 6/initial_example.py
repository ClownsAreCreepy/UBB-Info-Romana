from colorama import Fore, Style


class MyClass:
    # class attribute
    number_of_instances = 0

    def __init__(self):
        # instance attributes
        self.elements = []

        #https://realpython.com/python-double-underscore/#single-leading-underscore-in-python-names
        # _ -> semnalizeaza camp care ar trebui folosit doar intern (dar teoretic este accesibil
        # si din afara clasei)
        self._y = 102
        # __ -> name mangling, singura modalitate de a accesa campul este prin instructiune
        # de tip o1._MyClass__x, unde o1 este obiect de tipul MyClass
        self.__x = 0

        # modify class attribute
        # ce se intampla daca aici am spune self.number_of_instances++?
        MyClass.number_of_instances += 1

    def add_element(self, x):
        self.elements.append(x)

    def _single_underscore_method(self):
        print("Printing from a method with an underscore...")

    def __dunderscore_method(self):
        print("Printing from a method with two leading underscores...")


o1 = MyClass()
print(o1._y)
o1._single_underscore_method()


#this will fail
#print(o1.__x)
o1._MyClass__dunderscore_method()
print(o1._MyClass__x)
print("Number of instances after creating o1:", MyClass.number_of_instances)

o2 = MyClass()
print("Number of instances after creating o2:", MyClass.number_of_instances)
print("Number of instances after creating o2 (o1.number_of_instances):", o1.number_of_instances)
print("Number of instances after creating o2 (o2.number_of_instances):", o2.number_of_instances)

print("o1 elements", o1.elements)
print("o2 elements", o2.elements)
print(Fore.GREEN + "After executing o2.add_element(10):"+Style.RESET_ALL)
o2.add_element(10)

print("o1 elements:", o1.elements)
print("o2 elements:", o2.elements)
