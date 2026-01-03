from Erori.erori import *
from Domain.Client import *
from Domain.Film import *
from Domain.Inchirieri import *

class validare_film:

    def validare_film(self, film):
        erori=""
        if film.get_id()<0:
            erori += "id-ul introdus nu poate fi negativ \n"
        if film.get_titlu() == "":
            erori += "numele filmului nu poate sa fie vid \n"
        if film.get_gen() == "":
            erori += "genul filmului nu poate sa fie vid \n"
        if film.get_descriere() == "":
            erori += "descrierea filmului nu poate sa fie vida \n"

        if erori != "":
            raise ValueError(erori)

    def validare_id(self, id):
        if id<0:
            raise ValueError("id-ul introdus nu poate fi negativ \n")

    def validare_nume(self, nume):
        if nume == "":
            raise ValueError("numele filmului nu poate sa fie vid \n")


class validare_client:

    def validare_client(self, client):
        erori = ""
        if client.get_id()<0:
            erori += "id-ul introdus nu poate fi negativ \n"
        if client.get_nume() == "":
            erori += "numele clientului nu poate fi negativ \n"
        if len(client.get_cnp())!=13 or client.get_cnp().isdigit()==False:
            erori += "cnp-ul clientului a fost introdus gresit \n"

        if erori != "":
            raise ValueError(erori)

    def validare_id(self, id):
        if id < 0:
            raise ValueError("id-ul introdus nu poate fi negativ \n")

    def validare_nume(self, nume):
        if nume == "":
            raise ValueError("numele clientului nu poate sa fie vid \n")

class validare_inchiriere:

    def validare_inchiriere(self, inchiriere):
        erori = ""
        if inchiriere.get_id_client() < 0:
            erori += "id-ul clientului nu poate fi negativ \n"
        if inchiriere.get_id_film() < 0:
            erori += "id-ul filmului nu poate fi negativ \n"

        if erori != "":
            raise ValidationError(erori)

    def validare_id(self, id):
        if id < 0:
            raise ValueError("id-ul introdus nu poate fi negativ \n")