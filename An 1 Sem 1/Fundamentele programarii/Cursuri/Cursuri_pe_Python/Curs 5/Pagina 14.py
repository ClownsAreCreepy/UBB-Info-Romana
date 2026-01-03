class Student:
    def __init__(self,nume, prenume):
        self.__nume = nume
        self.__prenume = prenume
    def getNume(self):
        return self.__nume
    def getFullName(self):
        return "{} {}".format(self.__nume,self.__prenume)

print (Student.__dict__)


st1 = Student("Ion","Vasilescu")
#Mine:print (st1.__dict__)