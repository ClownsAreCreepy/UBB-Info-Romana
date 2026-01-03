def __createdStudent(self):
    """
        Read a student and store in the apllication
    """
    id = input("Student id:").strip()
    name = input("Student name:").strip()
    street = input("Address - street:").strip()
    nr = input("Address - number:").strip()
    city = input("Address - city:").strip()
    try:
        self.__ctr.create(id, name,street,nr,city)
    except ValueError as msg:
        print (msg)
def __createdStudent(self):
    """
        Read a student and store in the apllication
    """
    id = input("Student id:").strip()
    name = input("Student name:").strip()
    street = input("Address - street:").strip()
    nr = input("Address - number:").strip()
    city = input("Address - city:").strip()
    try:
        self.__ctr.create(id, name,street,nr,city)
    except ValidationException as ex:
        print (ex)
    except DuplicatedIDException as ex:
        print (ex)
class ValidationException(Exception):
    def __init__(self,msgs):
        """
            Initialise
            msg is a list of strings (errors)
        """
        self.__msgs = msgs
    def getMsgs(self):
        return self.__msgs
    def __str__(self):
        return str(self.__msgs)