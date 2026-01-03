from Validare.validare import *
from infrastructura.repo_clienti import *
from infrastructura.repo_clienti_file import *
import random

class service_client:
    def __init__(self, validare, repository):
        self.validare = validare
        self.repository = repository

    def adaugare_client_validare(self, id_client, nume_client, cnp_client):
        client_adaugat = Client(id_client, nume_client, cnp_client)
        self.validare.validare_client(client_adaugat)
        self.repository.adauga_client(client_adaugat)

    def stergere_validare_client(self, id_client):
        self.validare.validare_id(id_client)
        self.repository.sterge_client(id_client)
        return self.repository

    def modificare_validare_client(self, id_client, client_nou):
        self.validare.validare_id(id_client)
        self.validare.validare_client(client_nou)
        self.repository.modifica_client(id_client, client_nou)
        return self.repository

    def cautare_validare_client(self, id_client):
        self.validare.validare_id(id_client)
        client_rezultat = self.repository.cautare_client_dupa_id(id_client)

        if client_rezultat != None:
            return client_rezultat

    def adaugare_generare_random(self,times):
        index = times
        self.validare.validare_id(times)
        while index > 0:
            lista_nume = ["Marian", "Alexandru", "Ana", "Laura", "Maria", "Mihai", "Anabela", "Kara", "Andrei", "Olga","Alexa"]
            nume_random = random.choice(lista_nume)
            id_random = random.randrange(1, 1000000, 1)
            cnp_random = str(random.randrange(1000000000000, 9999999999999, 1))

            try:
                self.adaugare_client_validare(id_random,nume_random,cnp_random)
            except ValueError:
                index += 1
            index -= 1