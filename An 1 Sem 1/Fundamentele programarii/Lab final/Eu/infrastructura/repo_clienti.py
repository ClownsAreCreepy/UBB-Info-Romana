from Domain.Client import *


class repo_client:
    def __init__(self):
        self.vector = []
        self.length = 0

    def __str__(self):
        string = ""
        for element in self.vector:
            string += str(element)
            string += "; \n"

        return string

    def equal_lists(self, other):
        verificare = True
        if self.length != other.length:
            verificare = False
        else:
            for index in range(0, self.length):
                if self.vector[index].get_id() != other.vector[index].get_id():
                    verificare = False
                    break

        return verificare

    def adauga_client(self, clientu):
        for element in self.vector:
            if element.get_id() == clientu.get_id():
                raise ValueError("acest client a fost introdus deja \n")

        self.vector.append(clientu)
        self.length = len(self.vector)

    def sterge_client(self, id_client):
        c = 0
        verificare = False
        for element in self.vector:
            if element.get_id() == id_client:
                verificare = True
                self.vector.remove(element)
                break
            c += 1
        self.length = len(self.vector)
        if verificare != True:
            raise ValueError("clientul nu exista in lista de clienti \n")
        return self

    def modifica_client(self, id_client, client_nou):
        verificare = False
        for index in range(0, self.length):
            if self.vector[index].get_id() == id_client:
                verificare = True
                self.vector[index] = client_nou
                break

        if verificare == False:
            raise ValueError("clientul pe care doriti sa il modificati nu exista in lista de clienti \n")

        return self

    def cautare_client_dupa_id(self, id_cautat):
        verificare = False

        for el in self.vector:
            if el.get_id() == id_cautat:
                verificare = True
                return el

        if verificare == False:
            raise ValueError("clientul cautat nu se afla in lista de clienti \n")
