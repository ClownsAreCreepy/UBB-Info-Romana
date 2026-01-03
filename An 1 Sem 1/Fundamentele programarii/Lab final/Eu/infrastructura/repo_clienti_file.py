from infrastructura.repo_clienti import repo_client
from Domain.Client import *


class repo_client_file(repo_client):
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
                    nume = parti[1]
                    cnp = parti[2]
                    client_nou = Client(id, nume, cnp)
                    self.vector.append(client_nou)
            self.length = len(self.vector)


    def scriere_in_fisier(self):
        with open(self.cale_fisier, "w") as f:
            for el in self.vector:
                f.write(f"{el.get_id()}, {el.get_nume()}, {el.get_cnp()}\n")


    def adauga_client(self, client):
        self.citire_din_fisier()
        repo_client.adauga_client(self,client)
        self.scriere_in_fisier()

    def sterge_client(self, id_client):
        self.citire_din_fisier()
        repo_client.sterge_client(self,id_client)
        self.scriere_in_fisier()

    def modifica_client(self, id_client, client_nou):
        self.citire_din_fisier()
        repo_client.modifica_client(self,id_client,client_nou)
        self.scriere_in_fisier()

    def cautare_client_dupa_id(self, id_cautat):
        self.citire_din_fisier()
        return repo_client.cautare_client_dupa_id(self,id_cautat)