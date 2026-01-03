class Address:
    """
      Represent an address
    """


    def __init__(self, street, nr, city):
        self.__street = street
        self.__nr = nr
        self.__city = city


    def getStreet(self):
        return self.__street


    def getNr(self):
        return self.__nr


    def getCity(self):
        return self.__city
class Student:
    """
      Represent a student
    """

    def __init__(self, id, name, adr):
        """
         Create a new student
         id, name String
         address - Address
        """
        self.__id = id
        self.__name = name
        self.__adr = adr


def getId(self):
    """
      Getter method for id
    """
    return self.__id


def testCreateStudent():
    """
      Testing student creation
      Feature 1 - add a student
      Task 1 - Create student
    """
    st = Student("1", "Ion", Address("Adr", 1, "Cluj"))
    assert st.getId() == "1"
    assert st.getName() == "Ion"
    assert st.getAdr().getStreet() == "Adr"

    st = Student("2", "Ion2", Address("Adr2", 1, "Cluj"))
    assert st.getId() == "2"
    assert st.getName() == "Ion2"
    assert st.getAdr().getStreet() == "Adr2"
    assert st.getAdr().getCity() == "Cluj"