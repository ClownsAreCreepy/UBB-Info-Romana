from Domain.Film import *

class repo_film:
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

    def adauga_film(self, filmu):
        for element in self.vector:
            if element.get_id() == filmu.get_id():
                raise ValueError("acest film a fost introdus deja \n")

        self.vector.append(filmu)
        self.length = len(self.vector)

    def sterge_film(self, id_film):
        c=0
        verificare=False
        for element in self.vector:
            if element.get_id() == id_film:
                verificare = True
                self.vector.pop(c)
                break
            c+=1
        self.length = len(self.vector)
        if verificare != True:
            raise ValueError("filmul nu exista in lista de filme \n")
        return self

    def modifica_film(self, id_film, film_nou):
        verificare=False
        for index in range(0, self.length):
            if self.vector[index].get_id() == id_film:
                verificare = True
                self.vector[index] = film_nou
                break


        if verificare == False:
            raise ValueError("filmul pe care doriti sa il modificati nu exista in lista de filme \n")

        return self

    def cautare_film_dupa_id(self, id_cautat):
        verificare = False

        for el in self.vector:
            if el.get_id() == id_cautat:
                verificare = True
                return el

        if verificare == False:
            raise ValueError("filmul cautat nu se afla in lista de filme \n")
