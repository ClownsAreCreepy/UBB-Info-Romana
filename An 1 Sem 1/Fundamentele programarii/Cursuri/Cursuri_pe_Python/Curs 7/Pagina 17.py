class Student:
    def __init__(self, id, name):
        self.__name = name
        self.__id = id
    def getId(self):
        return self.__id
    def getName(self):
        return self.__name


class Professor:
    def __init__(self, id, name, course):
        self.__id = id
        self.__name = name
        self.__course = course
    def getId(self):
        return self.__id
    def getName(self):
        return self.__name
    def getCourse(self):
        return self.__course


l = [Student(1, "Ion"), Professor("1", "Popescu", "FP"), Student(31, "Ion2"),
Student(11, "Ion3"), Professor("2", "Popescu3", "asd")]
#Mine: for el in l:
    #Mine: print el.getName()+" id "+str(el.getId())
def myPrint(st):
    print(el.getName(), " id ", el.getId())
#Mine: for el in l:
    #Mine: myPrint(el)