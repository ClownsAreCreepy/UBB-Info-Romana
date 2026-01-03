class Inchirieri:
    def __init__(self, id_film, id_client):
        '''
            Initializeaza obiectul pe care il construim - inchirierea
            :param id_film: un nr natural unic, reprezentand id-ul t
            :param nume: un string reprezentand numele si prenumele elevului
        '''
        self.__id_film = id_film
        self.__id_client = id_client
        self.__status = "incompleta"

    def get_id_film(self):
         return self.__id_film

    def get_id_client(self):
         return self.__id_client

    def get_status(self):
        return self.__status

    def set_status(self):
        self.__status = "completa"

    def __str__(self):
        return f"inchiriere (id_film={self.__id_film}, id_client={self.__id_client})"  #!!!!!!!!!

    def __eq__(self, other):
        return self.get_id_film() == other.get_id_film() and self.get_id_client() == other.get_id_client()