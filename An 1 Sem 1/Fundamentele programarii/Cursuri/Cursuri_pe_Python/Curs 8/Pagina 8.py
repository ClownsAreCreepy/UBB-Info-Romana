def __createdStudent(self):
    """     Read a student and store in the apllication    """
    id = input("Student id:").strip()
    name = input("Student name:").strip()
    street = input("Address - street:").strip()
    nr = input("Address - number:").strip()
    city = input("Address - city:").strip()
    try:
        self.__ctr.create(id, name,street,nr,city)
    except StudentCRUDException as ex:
        print (ex)


class ValidationException(StudentCRUDException):
    def __init__(self,msgs):
        """
            msg is a list of strings (errors)
        """
        self.__msgs = msgs
    def getMsgs(self):
        return self.__msgs
    def __str__(self):
        return str(self.__msgs)

class RepositorException(StudentCRUDException):
    """
        Base class for the exceptions in the repository
    """
    def __init__(self, msg):
        self.__msg = msg
    def getMsg(self):
        return self.__msg
    def __str__(self):
        return self.__msg
class DuplicatedIDException(RepositorException):
    def __init__(self):
        RepositorException.__init__(self, "Duplicated ID")