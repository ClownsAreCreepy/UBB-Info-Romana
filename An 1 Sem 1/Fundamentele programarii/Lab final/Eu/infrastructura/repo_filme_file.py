from infrastructura.repo_filme import repo_film
from Domain.Film import *


class repo_film_file(repo_film):
    def __init__(self, cale_fisier):
        super().__init__()
        self.cale_fisier = cale_fisier


    def citire_din_fisier(self):
        with open(self.cale_fisier, "r") as f:
            self.vector = []
            lines = f.readlines()
            for line in lines:
                line = line.strip()
                if line !="":
                    parti = line.split(",")
                    id = int(parti[0])
                    titlu = parti[1]
                    gen = parti[2]
                    descriere = parti[3]
                    film_nou = Film(id, titlu, gen, descriere)
                    self.vector.append(film_nou)
            self.length = len(self.vector)


    def scriere_in_fisier(self):
        with open(self.cale_fisier, "w") as f:
            for el in self.vector:
                f.write(f"{el.get_id()}, {el.get_titlu()}, {el.get_gen()}, {el.get_descriere()}\n")


    def adauga_film(self, film):
        self.citire_din_fisier()
        repo_film.adauga_film(self,film)
        self.scriere_in_fisier()

    def sterge_film(self, id_film):
        self.citire_din_fisier()
        repo_film.sterge_film(self,id_film)
        self.scriere_in_fisier()

    def modifica_film(self, id_film, film_nou):
        self.citire_din_fisier()
        repo_film.modifica_film(self,id_film,film_nou)
        self.scriere_in_fisier()

    def cautare_film_dupa_id(self, id_cautat):
        self.citire_din_fisier()
        return repo_film.cautare_film_dupa_id(self,id_cautat)