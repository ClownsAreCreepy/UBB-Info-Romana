from Domain.Client import *
from Domain.Film import *

class Client_DTO():
    def __init__(self, id_client, nume_client, nr_inchirieri):
        self.id_client = id_client
        self.nume_client = nume_client
        self.nr_inchirieri = nr_inchirieri

    def get_id_client(self):
        return self.id_client

    def get_nume_client(self):
        return self.nume_client

    def get_nr_inchirieri(self):
        return self.nr_inchirieri

    def __str__(self):
        return f"{self.nume_client} - {self.nr_inchirieri} inchirieri"

    def __eq__(self, other):
        return (self.get_id_client() == other.get_id_client() and self.get_nr_inchirieri() == other.get_nr_inchirieri())

class Film_DTO():
     def __init__(self, id_film, titlu_film, nr_inchirieri):
         self.id_film = id_film
         self.titlu_film = titlu_film
         self.nr_inchirieri = nr_inchirieri

     def get_id_film(self):
         return self.id_film

     def get_titlu_film(self):
         return self.titlu_film

     def get_nr_inchirieri(self):
         return self.nr_inchirieri

     def __str__(self):
         return f"{self.get_titlu_film()} - {self.get_nr_inchirieri()} inchirieri"

     def __eq__(self, other):
         return self.get_id_film() == other.get_id_film() and self.get_nr_inchirieri() == other.get_nr_inchirieri()