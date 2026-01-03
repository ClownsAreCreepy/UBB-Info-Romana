l = range(1,10)
try:
    poz = l.index(11)
except ValueError:
    pass
# element is not in the list

class MyClass:
    def __init__(self, id, name):
        self.id = id
        self.name = name

    def __eq__(self, ot):
        return self.id == ot.id


def testIndex():
    l = []
    for i in range(0, 200):
        ob = MyClass(i, "ad")
        l.append(ob)

    findObj = MyClass(32, "ad")
    print("positions:" + str(l.index(findObj)))