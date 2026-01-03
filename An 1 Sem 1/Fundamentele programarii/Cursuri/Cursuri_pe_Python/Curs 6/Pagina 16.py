class Student:
    def __init__(self, id, name, adr):
        """
        Create a new student
        id, name, address String
        """
        self.__id = id
        self.__name = name
        self.__adr = adr
    def getId(self):
        return self.__id
    def getName(self):
        return self.__name
    def getAdr(self):
        return self.__adr


def testCreateStudent():
    """
        Testing student creation
    """
    st = Student("1", "Ion", "Adr")
    assert st.getId() == "1"
    assert st.getName() == "Ion"
    assert st.getAdr() == "Adr"