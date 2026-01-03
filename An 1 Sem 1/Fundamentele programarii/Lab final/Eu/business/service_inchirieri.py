from infrastructura.repo_inchirieri import *
from infrastructura.repo_inchirieri_file import  *
from Validare.validare import *
from Erori.erori import *
from Domain.DTO import *
import math

class service_inchirieri:

    def __init__(self, validator, repository_inchirieri, repository_clienti, repository_filme):
        self._repository_inchirieri = repository_inchirieri
        self._repository_clienti = repository_clienti
        self._repository_filme = repository_filme
        self._validator = validator


    def adaugare_validare_inchiriere(self, id_film, id_client):
        inchiriere_noua = Inchirieri(id_film, id_client)
        self._validator.validare_inchiriere(inchiriere_noua)
        erori=""


        try:
            verificare_1=self._repository_clienti.cautare_client_dupa_id(inchiriere_noua.get_id_client())
        except ValueError:
            erori += "clientul caruia ii atribuiti inchirierea nu exista \n"

        try:
            verificare_2=self._repository_filme.cautare_film_dupa_id(inchiriere_noua.get_id_film())
        except ValueError:
            erori += "filmul nu exista \n"

        if erori !="":
            raise ExistentialError(erori)

        self._repository_inchirieri.adaugare_inchiriere(inchiriere_noua)


    def returnare_validare_film(self, id_film, id_client):
        inchiriere = Inchirieri(id_film, id_client)
        self._validator.validare_inchiriere(inchiriere)
        erori=""

        try:
            verificare_1 = self._repository_clienti.cautare_client_dupa_id(id_client)
        except ValueError:
            erori +="clientul caruia ii atribuiti returnarea nu exista \n"

        try:
            verificare_2 = self._repository_filme.cautare_film_dupa_id(id_film)
        except ValueError:
            erori +="filmul nu exista \n"

        if erori !="":
            raise ExistentialError(erori)

        self._repository_inchirieri.returnare_film(inchiriere)


    def shell_sort(self, data, *, key=lambda x: x, reverse=False, gap=None):
        if gap is None:
            gap = len(data) // 2
        if gap == 0:
            return data
        for j in range(gap, len(data)):
            i = j
            while i >= gap:
                if reverse:
                    if key(data[i]) > key(data[i - gap]):
                        data[i], data[i - gap] = data[i - gap], data[i]
                else:
                    if key(data[i]) < key(data[i - gap]):
                        data[i], data[i - gap] = data[i - gap], data[i]
                i-=gap
        return self.shell_sort(data, key=key, reverse=reverse, gap=gap // 2)


    def bubble_sort(self, data, *, key=lambda x:x , cmp = lambda x,y:x>y, reverse = False):
       def bubble_odata(data,n):
           if n<=1:
               return
           for i in range(n-1):
               if reverse:
                   if not cmp(key(data[i]), key(data[i+1])):
                       data[i], data[i+1] = data[i+1], data[i]
               else:
                   if cmp(key(data[i]), key(data[i-1])):
                       data[i], data[i+1] = data[i+1], data[i]
           bubble_odata(data, n-1)
       bubble_odata(data, len(data))
       return data


    def sortare_clienti_dupa_nume_si_nr_inchirieri(self, clienti_inchirieri):
        lista_dtos = []
        for i in clienti_inchirieri:
            lista_dtos.append(clienti_inchirieri[i])
        return sorted(lista_dtos, key=lambda x:(x.get_nume_client(), -x.get_nr_inchirieri()))


    def clienti_cu_filme_inchiriate(self):
        clienti_inchirieri = {}
        for inchiriere in self._repository_inchirieri._vector:
            if inchiriere.get_status() == "incompleta":
                id_client = inchiriere.get_id_client()
                if id_client not in clienti_inchirieri:
                    client = self._repository_clienti.cautare_client_dupa_id(id_client)
                    clienti_inchirieri[id_client] = Client_DTO(id_client, client.get_nume(), 0)
                clienti_inchirieri[id_client].nr_inchirieri += 1
        if clienti_inchirieri != {}:
            return self.sortare_clienti_dupa_nume_si_nr_inchirieri(clienti_inchirieri)
        else:
            raise ExistentialError("nu exista inchirieri incomplete\n")


    def top_3_filme(self, filme_inchirieri):
        maxim = [Film_DTO(None,None,0)]*3
        for inchiriere in filme_inchirieri.values():
            if inchiriere.get_nr_inchirieri() > maxim[0].get_nr_inchirieri():
                maxim[2] = maxim[1]
                maxim[1] =maxim[0]
                maxim[0] = inchiriere
            elif inchiriere.get_nr_inchirieri() > maxim[1].get_nr_inchirieri():
                maxim[2] = maxim[1]
                maxim[1] = inchiriere
            elif inchiriere.get_nr_inchirieri() > maxim[2].get_nr_inchirieri():
                maxim[2] = inchiriere
        for i in range(3):
            if maxim[i] == Film_DTO(None,None,0):
                maxim[i] = "nu avem destule filme :("
        return maxim


    def filme_cele_mai_inchiriate(self):
        filme_inchirieri = {}
        for inchiriere in self._repository_inchirieri._vector:
            id_film = inchiriere.get_id_film()
            if id_film not in filme_inchirieri:
                film = self._repository_filme.cautare_film_dupa_id(id_film)
                filme_inchirieri[id_film] = Film_DTO(id_film, film.get_titlu(), 0)
            filme_inchirieri[id_film].nr_inchirieri += 1
        if filme_inchirieri != {}:
            return self.top_3_filme(filme_inchirieri)
        else:
            raise ExistentialError("nu exista inchirieri de filme\n")


    def sortare_clienti_dupa_nr_inchirieri(self, clienti_inchirieri):
        lista_dtos = []
        for i in clienti_inchirieri:
            lista_dtos.append(clienti_inchirieri[i])
        return self.bubble_sort(lista_dtos, key = lambda x:x.get_nr_inchirieri(), reverse=True)
        return lista_dtos


    def top_30_clienti(self, clienti_inchirieri):
        clienti_inchirieri = self.sortare_clienti_dupa_nr_inchirieri(clienti_inchirieri)
        if self._repository_clienti.length<3:
            procentaj = 1
        else:
            procentaj = round(self._repository_clienti.length*30/100)
        return clienti_inchirieri [:procentaj]


    def clienti_cu_cele_mai_multe_inchirieri(self):
        clienti_inchirieri = {}
        for inchiriere in self._repository_inchirieri._vector:
            if inchiriere.get_status() == "incompleta":
                id_client = inchiriere.get_id_client()
                if id_client not in clienti_inchirieri:
                    client = self._repository_clienti.cautare_client_dupa_id(id_client)
                    clienti_inchirieri[id_client] = Client_DTO(id_client, client.get_nume(), 0)
                clienti_inchirieri[id_client].nr_inchirieri += 1
        if clienti_inchirieri:
            return self.top_30_clienti(clienti_inchirieri)
        else:
            raise ExistentialError("nu exista inchirieri incomplete\n")


    def minim_3_filme_inchiriate(self, clienti_inchirieri):
        lista_clienti = []
        for client_dto in clienti_inchirieri.values():
            if client_dto.get_nr_inchirieri() > 2:
                lista_clienti.append(client_dto)
        if lista_clienti != []:
            return lista_clienti
        else:
            raise ExistentialError("nu exista clienti asa de dedicati\n")


    def clienti_cu_peste_3_filme_inchiriate(self):
        clienti_inchirieri = {}
        for inchiriere in self._repository_inchirieri._vector:
            if inchiriere.get_status() == "incompleta":
                id_client = inchiriere.get_id_client()
                if id_client not in clienti_inchirieri:
                    client = self._repository_clienti.cautare_client_dupa_id(id_client)
                    clienti_inchirieri[id_client] = Client_DTO(id_client, client.get_nume(), 0)
                clienti_inchirieri[id_client].nr_inchirieri += 1
        if clienti_inchirieri != {}:
            return self.minim_3_filme_inchiriate(clienti_inchirieri)
        else:
            raise ExistentialError("nu exista inchirieri incomplete\n")