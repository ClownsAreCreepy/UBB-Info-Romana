from Domain.Inchirieri import *
from Erori.erori import RepoError
from infrastructura.repo_clienti import *
from infrastructura.repo_filme import *

class repo_inchirieri:
    def __init__(self):
        self._vector=[]
        self._length=0

    def __str__(self):
        string=""
        for element in self._vector:
            if element.get_status() == "incompleta":
                string+= str(element)
            string+="; \n"
        return string

    def adaugare_inchiriere(self, inchiriere):
        for el in self._vector:
            if el.get_id_film() == inchiriere.get_id_film() and el.get_id_client() == inchiriere.get_id_client() and el.get_status() == "incompleta":
                raise RepoError("clientul a inchiriat deja filmul\n")
        self._vector.append(inchiriere)
        self._length+=1


    def returnare_film(self, inchiriere):
        gasit = False
        for el in self._vector:
            if el == inchiriere:
                gasit=True
                if el.get_status() == "incompleta":
                    el.set_status()
        if not gasit:
            raise RepoError("nu s-a gasit o astfel de inchiriere incompleta\n")


    def setare_status_dupa_client(self, id_client):
        for el in self._vector:
            if el.get_id_client() == id_client:
                el.set_status()


    def setare_status_dupa_film(self, id_film):
        for el in self._vector:
            if el.get_id_film() == id_film:
                el.set_status()