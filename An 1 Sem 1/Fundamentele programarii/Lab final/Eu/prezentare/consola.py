from business.service_film import *
from business.service_client import *


class Consola:
    def __init__(self, service_filme, service_clienti, service_inchirieri):
        self.service_filme = service_filme
        self.service_clienti = service_clienti
        self.service_inchirieri = service_inchirieri


#functiile de ui pentru clienti


    def __ui_adaugare_client(self):
        try:
            id_client = int(input("Introduceti id-ul clientului: "))
        except ValueError:
            print("id-ul trebuie sa fie un nr intreg \n")
            return

        nume_client = input("Introduceti numele clientului: ")
        cnp_client = input("Introduceti cnp-ul clientului: ")

        try:
            self.service_clienti.adaugare_client_validare(id_client,nume_client, cnp_client)
        except ValueError as ve:
            print(str(ve))

        print(self.service_clienti.repository)


    def __ui_stergere_client(self):
        try:
            id_client = int(input("Introduceti id-ul clientului: "))
        except ValueError:
            print("id-ul trebuie sa fie un nr intreg \n")
            return

        try:
            print(self.service_clienti.stergere_validare_client(id_client))
            self.service_inchirieri._repository_inchirieri.setare_status_dupa_client(id_client)
            print(self.service_inchirieri._repository_inchirieri)
        except ValueError as ve:
            print(str(ve))


    def __ui_modificare_client(self):
        try:
            id_client = int(input("Introduceti id-ul clientului: "))
        except ValueError:
            print("id-ul trebuie sa fie un nr intreg \n")
            return

        try:
            id_client_nou = int(input("Introduceti id-ul noului client: "))
        except ValueError:
            print("id-ul trebuie sa fie un nr intreg \n")
            return

        nume_client_nou= input("Introduceti numele noului client: ")
        cnp_client_nou = input("Introduceti cnp-ul noului client: ")
        client_nou=Client(id_client_nou, nume_client_nou, cnp_client_nou)

        try:
            self.service_clienti.modificare_validare_client(id_client, client_nou)
            print(self.service_clienti.repository)
        except ValueError as ve:
            print(str(ve))


    def __ui_cautare_client(self):
        try:
            id_client = int(input("Introduceti id-ul clientului cautat: "))
        except ValueError:
            print("id-ul trebui sa fie un nr intreg \n")
            return

        try:
            print(self.service_clienti.cautare_validare_client(id_client))
        except ValueError as ve:
            print(str(ve))


    def __ui_generare_clienti(self):
        try:
            times = int(input("Introduceti nr de clienti pe care il doriti generat: "))
        except ValueError as ve:
            print("trebuie sa fie un nr intreg \n")
            return

        try:
            self.service_clienti.adaugare_generare_random(times)
        except ValueError as ve:
            print(str(ve))
        print(self.service_clienti.repository)




#functiile de ui pentru filme


    def __ui_adaugare_film(self):
        try:
            id_film= int(input("Introduceti id-ul filmului: "))
        except ValueError:
            print("id-ul trebui sa fie un nr intreg \n")
            return

        titlu_film= input("Introduceti titlul filmului: ")
        gen_film= input("Introduceti genul filmului: ")
        descriere_film= input("Introduceti descrierea filmului: ")

        try:
            self.service_filme.adaugare_validare_film(id_film,titlu_film,gen_film,descriere_film)
        except ValueError as ve:
            print(str(ve))

        print(self.service_filme.repository)


    def __ui_stergere_film(self):
        try:
            id_film = int(input("Introduceti id-ul filmului: "))
        except ValueError:
            print("id-ul trebui sa fie un nr intreg \n")
            return

        try:
            print(self.service_filme.stergere_validare_film(id_film))
            self.service_inchirieri._repository_inchirieri.setare_status_dupa_film(id_film)
            print(self.service_inchirieri._repository_inchirieri)
        except ValueError as ve:
            print(str(ve))


    def __ui_modificare_film(self):
        try:
            id_film = int(input("Introduceti id-ul filmului: "))
        except ValueError:
            print("id-ul trebuie sa fie un nr intreg \n")
            return

        try:
            id_film_nou = int(input("Introduceti id-ul filmului: "))
        except ValueError:
            print("id-ul trebui sa fie un nr intreg \n")
            return

        titlu_film_nou= input("Introduceti titlul filmului: ")
        gen_film_nou= input("Introduceti genul filmului: ")
        descriere_film_nou= input("Introduceti descrierea filmului: ")

        film_nou = Film(id_film_nou, titlu_film_nou, gen_film_nou, descriere_film_nou)

        try:
            self.service_filme.modificare_validare_film(id_film, film_nou)
            print(self.service_filme.repository)
        except ValueError as ve:
            print(str(ve))


    def __ui_cautare_film(self):
        try:
            id_film = int(input("Introduceti id-ul filmului: "))
        except ValueError:
            print("id-ul trebui sa fie un nr intreg \n")
            return

        try:
            print(self.service_filme.cautare_validare_film(id_film))
        except ValueError as ve:
            print(str(ve))




# functiile de ui pentru inchirieri

    def __ui_adaugare_inchirieri(self):
        try:
            id_client = int(input("Introduceti id-ul clientului: "))
        except ValueError:
            print("id-ul trebui sa fie un nr intreg \n")
            return

        try:
            id_film = int(input("Introduceti id-ul filmului: "))
        except ValueError:
            print("id-ul trebui sa fie un nr intreg \n")
            return

        try:
            self.service_inchirieri.adaugare_validare_inchiriere(id_film ,id_client)
        except ValueError as ve:
            print(str(ve))
        except ValidationError as ve:
            print(str(ve))
        except RepoError as re:
            print(str(re))
        except ExistentialError as ee:
            print(str(ee))

        print(self.service_inchirieri._repository_inchirieri)


    def __ui_returnare_film(self):
        try:
            id_client = int(input("Introduceti id-ul clientului: "))
        except ValueError:
            print("id-ul trebui sa fie un nr intreg \n")
            return

        try:
            id_film = int(input("Introduceti id-ul filmului: "))
        except ValueError:
            print("id-ul trebui sa fie un nr intreg \n")
            return

        try:
            self.service_inchirieri.returnare_validare_film(id_film, id_client)
        except ValueError as ve:
            print(str(ve))
        except ValidationError as ve:
            print(str(ve))
        except RepoError as re:
            print(str(re))
        except ExistentialError as ee:
            print(str(ee))

        print(self.service_inchirieri._repository_inchirieri)


    def __ui_clienti_cu_filme_inchiriate(self):
        try:
            clienti_dto = self.service_inchirieri.clienti_cu_filme_inchiriate()
        except ExistentialError as ee:
            print(str(ee))
            return

        for i in range(len(clienti_dto)):
            print(clienti_dto[i])
        print()


    def __ui_filme_cele_mai_inchiriate(self):
        try:
            filme_dto = self.service_inchirieri.filme_cele_mai_inchiriate()
        except ExistentialError as ee:
            print(str(ee))
            return

        for i in range(len(filme_dto)):
            print(filme_dto[i])
        print()


    def __ui_top_30_clienti(self):
        try:
            clienti_dto = self.service_inchirieri.clienti_cu_cele_mai_multe_inchirieri()
        except ExistentialError as ee:
            print(str(ee))
            return

        for i in range(len(clienti_dto)):
            print(clienti_dto[i])
        print()


    def __ui_clienti_cu_peste_3_filme(self):
        try:
            clienti_dto = self.service_inchirieri.clienti_cu_peste_3_filme_inchiriate()
        except ExistentialError as ee:
            print(str(ee))
            return

        for i in range(len(clienti_dto)):
            print(clienti_dto[i])
        print()



# Meniu initial
    def __meniu_initial(self):
        print("-----------MENIU---PRINCIPAL-----------")
        print("client - Acceseaza meniul pentru clienti")
        print("film - Acceseaza meniul pentru filme")
        print("inchirieri - Acceseaza meniul pentru inchirieri")
        print("exit - Iesire din aplicatie")
        print("---------------------------------------")




# Meniu Clienti
    def __meniu_client(self):
        print("----------------CLIENT----------------")
        print("add- Adauga un client in lista")
        print("delete - Sterge un client din lista")
        print("change - Schimba un client din lista")
        print("search - Cauta un client din lista")
        print("generate - Genereaza un nr dat de clienti la intamplare si ii adauga in lista")
        print("exit - Iesire din meniul de clienti")
        print("--------------------------------------")


    def __ui_client(self):
        self.__meniu_client()
        comenzi = {"add":self.__ui_adaugare_client,
                   "delete":self.__ui_stergere_client,
                   "change":self.__ui_modificare_client,
                   "search":self.__ui_cautare_client,
                   "generate":self.__ui_generare_clienti}

        comanda = input("Introduceti comanda: ").lower().strip()

        while True:
            if comanda == "":
                continue
            if comanda == "exit":
                break
            elif comanda in comenzi:
                comenzi[comanda]()
            else:
                print("comanda introdusa nu este valida!!")
            self.__meniu_client()
            comanda = input("Introduceti comanda: ").lower().strip()




# Meniu Filme
    def __meniu_film(self):
        print("-----------------FILM-----------------")
        print("add - Adauga un film in lista")
        print("delete - Sterge un film din lista")
        print("change - Schimba un film din lista")
        print("search - Cauta un film din lista")
        print("exit - Iesire din meniul de film")

    def __ui_filme(self):
        self.__meniu_film()
        comenzi = {"add":self.__ui_adaugare_film,
                   "delete":self.__ui_stergere_film,
                   "change":self.__ui_modificare_film,
                   "search":self.__ui_cautare_film}
        comanda = input("Introduceti comanda: ").lower().strip()

        while True:
            if comanda == "":
                continue
            elif comanda == "exit":
                break
            elif comanda in comenzi:
                comenzi[comanda]()
            else:
                print("comanda introdusa nu este valida!!")
            self.__meniu_film()
            comanda = input("Introduceti comanda: ").lower().strip()




#Meniul Inchirieri
    def __meniu_inchirieri(self):
        print("--------------INCHIRIERI---------------")
        print("add - Creeaza o inchiriere de film facuta de un client")
        print("return - Returneaza un film inchiriat anterior de un client")
        print("sort - Tipareste clientii cu filme inchiriate ordonati dupa nume si nr de filme inchiriate")
        print("top - Tipareste cele mai populare 3 filme")
        print("30% - Tipareste primii 30% clienti cu cele mai multe filme inchiriate")
        print(">3 - Tipareste toti clientii cu 3 sau mai multe filme inchiriate")
        print("exit - Iesire din meniul de inchirieri")

    def __ui_inchirieri(self):
        self.__meniu_inchirieri()
        comenzi = {"add":self.__ui_adaugare_inchirieri,
                   "return":self.__ui_returnare_film,
                   "sort":self.__ui_clienti_cu_filme_inchiriate,
                   "top":self.__ui_filme_cele_mai_inchiriate,
                   "30%":self.__ui_top_30_clienti,
                   ">3":self.__ui_clienti_cu_peste_3_filme}
        comanda = input("Introduceti comanda: ").lower().strip()
        while True:
            if comanda == "":
                continue
            if comanda == "exit":
                break
            elif comanda in comenzi:
                comenzi[comanda]()
            else:
                print("comanda introdusa nu este valida!!")
            self.__meniu_inchirieri()
            comanda = input("Introduceti comanda: ").lower().strip()


    def run(self):
        self.__meniu_initial()
        comenzi = {"client":self.__ui_client,
                   "film":self.__ui_filme,
                   "inchirieri":self.__ui_inchirieri}
        comanda = input("Introduceti comanda: ").lower().strip()

        while True:
            if comanda == "":
                continue
            if comanda == "exit":
                break
            elif comanda in comenzi:
                comenzi[comanda]()
            else:
                print("comanda introdusa nu este valida!!")
            self.__meniu_initial()
            comanda = input("Introduceti comanda: ").lower().strip()