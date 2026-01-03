l = range(1,10)
found = 4 in l

class MyClass2:
    def __init__(self):
        self.l = []
    def add(self,obj):
        self.l.append(obj)
    def __iter__(self):
        """
            Return an iterator object
        """
        self.iterPoz = 0
        return self

    def __next__(self):
        """
        Return the next element in the iteration
        raise StopIteration exception if we are at the end
        """
        if (self.iterPoz >= len(self.l)):
            raise StopIteration()

    def testIn():
        container = MyClass2()
        for i in range(0, 200):
            container.add(MyClass(i, "ad"))
        findObj = MyClass(20, "asdasd")
        print(findObj in container)

#we can use any iterable in a for
container = MyClass2()
for el in container:
    print (el)