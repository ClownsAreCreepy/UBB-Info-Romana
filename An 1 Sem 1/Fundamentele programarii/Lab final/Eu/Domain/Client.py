class Client:
    def __init__(self, id, nume, cnp):
        self.__id = id
        self.__nume = nume
        self.__cnp = cnp

    def get_id(self):
        return self.__id

    def get_nume(self):
        return self.__nume

    def get_cnp(self):
        return self.__cnp

    def equal_client(self, other):
        return self.get_id() == other.get_id()

    def __str__(self):
        return f"client (id={self.__id}, nume={self.__nume}, cnp={self.__cnp})"