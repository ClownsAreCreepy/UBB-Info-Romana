from infrastructura.repo_inchirieri import repo_inchirieri
from Domain.Inchirieri import *


class repo_inchirieri_file(repo_inchirieri):
    def __init__(self, cale_fisier):
        super().__init__()
        self.cale_fisier = cale_fisier
    '''
    def __str__(self):
        string = ""
        for element in self.vector:
            string += str(element)
            string += "; \n"

        return string
    '''

    def citire_din_fisier(self):
        with open(self.cale_fisier, "r") as f:
            self._vector = []
            lines = f.readlines()
            for line in lines:
                line = line.strip()
                if line !="":
                    parti = line.split(",")
                    id_film = int(parti[0])
                    id_client = int(parti[1])
                    inchiriere_noua = Inchirieri(id_film, id_client)
                    self._vector.append(inchiriere_noua)
            self._length = len(self._vector)


    def scriere_in_fisier(self):
        with open(self.cale_fisier, "w") as f:
            for el in self._vector:
                f.write(f"{el.get_id_film()}, {el.get_id_client()}\n")


    def adaugare_inchiriere(self, inchiriere):
        self.citire_din_fisier()
        repo_inchirieri.adaugare_inchiriere(self,inchiriere)
        self.scriere_in_fisier()


    def returnare_film(self, inchiriere):
        self.citire_din_fisier()
        repo_inchirieri.returnare_film(self,inchiriere)

    def setare_status_dupa_client(self, id_client):
        self.citire_din_fisier()
        repo_inchirieri.setare_status_dupa_client(self, id_client)

    def setare_status_film(self, id_film):
        self.citire_din_fisier()
        repo_inchirieri.setare_status_dupa_film(self, id_film)