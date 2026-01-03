from infrastructura.repo_filme import *
from infrastructura.repo_filme_file import *

class service_film:
    def __init__(self, validare, repository):
        self.validare = validare
        self.repository = repository

    def adaugare_validare_film(self, id_film, nume_film, gen_film, descriere_film):
        film_adaugat = Film(id_film, nume_film, gen_film, descriere_film)
        self.validare.validare_film(film_adaugat)
        self.repository.adauga_film(film_adaugat)

    def stergere_validare_film(self, id_film):
        self.validare.validare_id(id_film)
        self.repository.sterge_film(id_film)
        return self.repository

    def modificare_validare_film(self, id_film, film_nou):
        self.validare.validare_id(id_film)
        self.validare.validare_film(film_nou)
        self.repository.modifica_film(id_film,film_nou)
        return self.repository

    def cautare_validare_film(self, id_film):
        self.validare.validare_id(id_film)
        film_rezultat = self.repository.cautare_film_dupa_id(id_film)

        if film_rezultat !=None:
            return film_rezultat