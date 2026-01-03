class Film:
    def __init__(self, id, titlu, gen, descriere):
        #self.__film_id = film_id
        #self.__film_tt = film_tt
        #self.__film_gen = film_gen
        self.__lista_atribuire = [id, titlu, gen, descriere]

    def get_id(self):
        return self.__lista_atribuire[0]

    def get_titlu(self):
        return self.__lista_atribuire[1]

    def get_gen(self):
        return self.__lista_atribuire[2]

    def get_descriere(self):
        return self.__lista_atribuire[3]

    def __str__(self):
        return f"Film ( id={self.get_id()}, titlu={self.get_titlu()}, gen={self.get_gen()}, descriere={self.get_descriere()})"

    def equal_film(self, other):
        return self.get_id()== other.get_id()