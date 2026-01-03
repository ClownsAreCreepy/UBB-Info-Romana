from infrastructura.repo_clienti import *
from infrastructura.repo_clienti_file import *
from infrastructura.repo_filme import *
from infrastructura.repo_filme_file import *
from infrastructura.repo_inchirieri import *
from infrastructura.repo_inchirieri_file import *
from Validare.validare import *
from Erori.erori import *
import unittest



class TestRepoFilm(unittest.TestCase):

    def test_creeaza(self):
        film_nou = Film(1, "Se7en", "Thriller", "Film fain")

        self.assertEqual(film_nou.get_id(), 1)
        self.assertEqual(film_nou.get_titlu(),"Se7en")
        self.assertEqual(film_nou.get_gen(),"Thriller")
        self.assertEqual(film_nou.get_descriere(),"Film fain")


    def test_equal_lists(self):
        repo_1= repo_film()
        repo_1.adauga_film(Film(1, "Se7en", "Thriller", "Film fain"))
        repo_1.adauga_film(Film(2, "Hangover", "Comedy", "Film kinda fain"))

        repo_2 = repo_film()
        repo_2.adauga_film(Film(1, "Se7en", "Thriller", "Film fain"))
        repo_2.adauga_film(Film(2, "Hangover", "Comedy", "Film kinda fain"))

        repo_3 = repo_film()
        repo_3.adauga_film(Film(1, "Se7en", "Thriller", "Film fain"))
        repo_3.adauga_film(Film(2, "Hangover", "Comedy", "Film kinda fain"))
        repo_3.adauga_film(Film(3, "The Godfather", "Crime", "Film foarte fain"))

        self.assertTrue(repo_1.equal_lists(repo_2))
        self.assertTrue(repo_2.equal_lists(repo_1))
        self.assertFalse(repo_3.equal_lists(repo_1))
        self.assertFalse(repo_3.equal_lists(repo_2))


    def test_equal_film(self):
        film_1 = Film(1, "Se7en", "Thriller", "Film fain")
        film_2 = Film(2, "Hangover", "Comedy", "Film kinda fain")
        film_3 = Film(2, "Hangover", "Comedy", "Film kinda fain")

        self.assertTrue(film_3.equal_film(film_2))
        self.assertFalse(film_3.equal_film(film_1))


    def test_adaugare(self):
        film_nou= Film(1, "Se7en", "Thriller", "Film fain")

        rep_film= repo_film()
        rep_film.adauga_film(film_nou)
        self.assertEqual(rep_film.length,1)

        film_nou=Film(2, "Hangover", "Comedy", "Film kinda fain")

        rep_film.adauga_film(film_nou)
        self.assertEqual(rep_film.length,2)

        with self.assertRaises(ValueError) as context:
            rep_film.adauga_film(film_nou)

        self.assertEqual(str(context.exception),
                         "acest film a fost introdus deja \n")


    def test_stergere(self):
        rep_film= repo_film()
        film_adaugat= Film(1, "Se7en", "Thriller", "Film fain")
        rep_film.adauga_film(film_adaugat)

        film_adaugat = Film(2, "Hangover", "Comedy", "Film kinda fain")
        rep_film.adauga_film(film_adaugat)

        id_existent=1
        rep_film_solution = repo_film()
        rep_film_solution.adauga_film(film_adaugat)

        repo_rezultat= repo_film()
        repo_rezultat= rep_film.sterge_film(id_existent)
        self.assertTrue(repo_rezultat.equal_lists(rep_film_solution))

        id_inexistent=3
        with self.assertRaises(ValueError) as context:
            rep_film.sterge_film(id_inexistent)

        self.assertEqual(str(context.exception),
                         "filmul nu exista in lista de filme \n")


    def test_modificare(self):
        repo_1= repo_film()
        repo_1.adauga_film(Film(1, "Se7en", "Thriller", "Film fain"))
        repo_1.adauga_film(Film(2, "Hangover", "Comedy", "Film kinda fain"))

        repo_solutie = repo_film()
        repo_solutie.adauga_film(Film(1, "Se7en", "Thriller", "Film fain"))
        repo_solutie.adauga_film(Film(3, "The Godfather", "Crime", "Film foarte fain"))

        repo_rezultat= repo_1.modifica_film(2, Film(3, "The Godfather", "Crime", "Film foarte fain"))

        self.assertTrue(repo_rezultat.equal_lists(repo_solutie))

        with self.assertRaises(ValueError) as context:
            repo_1.modifica_film(4, Film(2, "Hangover", "Comedy", "Film kinda fain"))

        self.assertEqual(str(context.exception),
                         "filmul pe care doriti sa il modificati nu exista in lista de filme \n")


    def test_cautare_dupa_id(self):
        repo_1= repo_film()
        repo_1.adauga_film(Film(1, "Se7en", "Thriller", "Film fain"))
        repo_1.adauga_film(Film(2, "Hangover", "Comedy", "Film kinda fain"))
        repo_1.adauga_film(Film(3, "The Godfather", "Crime", "Film foarte fain"))

        film_cautat=Film(2, "Hangover", "Comedy", "Film kinda fain")
        film_rezultat=repo_1.cautare_film_dupa_id(2)
        self.assertTrue(film_rezultat.equal_film(film_cautat))

        with self.assertRaises(ValueError) as context:
            repo_1.cautare_film_dupa_id(5)

        self.assertEqual(str(context.exception),
                         "filmul cautat nu se afla in lista de filme \n")



class TestRepoFilmFile(unittest.TestCase):

    def setUp(self):
        repo = repo_film_file("D:\\Python\\Pycharm\\Programs\\Laborator 7-9\\Eu\\testare\\test_filme.txt")
        repo.vector = []
        repo.vector.append(Film(1, "Se7en", "Thriller", "Film fain"))
        repo.vector.append(Film(2, "Hangover", "Comedy", "Film kinda fain"))
        repo.vector.append(Film(3, "The Godfather", "Crime", "Film foarte fain"))

        repo.scriere_in_fisier()


    def tearDown(self):
        repo = repo_film_file("D:\\Python\\Pycharm\\Programs\\Laborator 7-9\\Eu\\testare\\test_filme.txt")

        repo.vector = []
        repo.scriere_in_fisier()


    def test_adaugare(self):
        film_nou= Film(4, "The Shawshank Redemption", "Drama", "Film feel-good")

        rep_film= repo_film_file("D:\\Python\\Pycharm\\Programs\\Laborator 7-9\\Eu\\testare\\test_filme.txt")
        rep_film.adauga_film(film_nou)
        self.assertEqual(rep_film.length,4)
        self.assertTrue(rep_film.vector[0].equal_film(Film(1, "Se7en", "Thriller", "Film fain")))
        self.assertTrue(rep_film.vector[1].equal_film(Film(2, "Hangover", "Comedy", "Film kinda fain")))
        self.assertTrue(rep_film.vector[2].equal_film(Film(3, "The Godfather", "Crime", "Film foarte fain")))
        self.assertTrue(rep_film.vector[3].equal_film(Film(4, "The Shawshank Redemption", "Drama", "Film feel-good")))

        film_nou=Film(5, "Transformers", "Actiune", "Film wow")

        rep_film.adauga_film(film_nou)
        self.assertEqual(rep_film.length,5)
        self.assertTrue(rep_film.vector[0].equal_film(Film(1, "Se7en", "Thriller", "Film fain")))
        self.assertTrue(rep_film.vector[1].equal_film(Film(2, "Hangover", "Comedy", "Film kinda fain")))
        self.assertTrue(rep_film.vector[2].equal_film(Film(3, "The Godfather", "Crime", "Film foarte fain")))
        self.assertTrue(rep_film.vector[3].equal_film(Film(4, "The Shawshank Redemption", "Drama", "Film feel-good")))
        self.assertTrue(rep_film.vector[4].equal_film(Film(5, "Transformers", "Actiune", "Film wow")))

        with self.assertRaises(ValueError) as context:
            rep_film.adauga_film(film_nou)

        self.assertEqual(str(context.exception),
                         "acest film a fost introdus deja \n")


    def test_stergere(self):
        rep_film= repo_film_file("D:\\Python\\Pycharm\\Programs\\Laborator 7-9\\Eu\\testare\\test_filme.txt")

        id_existent=1

        rep_film.sterge_film(id_existent)
        self.assertEqual(rep_film.length,2)
        self.assertTrue(rep_film.vector[0].equal_film(Film(2, "Hangover", "Comedy", "Film kinda fain")))
        self.assertTrue(rep_film.vector[1].equal_film(Film(3, "The Godfather", "Crime", "Film foarte fain")))

        with self.assertRaises(ValueError) as context:
            rep_film.sterge_film(id_existent)

        self.assertEqual(str(context.exception),
                         "filmul nu exista in lista de filme \n")


    def test_modificare(self):
        rep_film = repo_film_file("D:\\Python\\Pycharm\\Programs\\Laborator 7-9\\Eu\\testare\\test_filme.txt")

        rep_film.modifica_film(2, Film(6, "Everything Everywhere All At Once", "Sci-Fi", "Film damn"))

        self.assertEqual(rep_film.length,3)
        self.assertTrue(rep_film.vector[0].equal_film(Film(1, "Se7en", "Thriller", "Film fain")))
        self.assertTrue(rep_film.vector[1].equal_film(Film(6, "Everything Everywhere All At Once", "Sci-Fi", "Film damn")))
        self.assertTrue(rep_film.vector[2].equal_film(Film(3, "The Godfather", "Crime", "Film foarte fain")))

        with self.assertRaises(ValueError) as context:
            rep_film.modifica_film(4, Film(2, "Hangover", "Comedy", "Film kinda fain"))

        self.assertEqual(str(context.exception),
                         "filmul pe care doriti sa il modificati nu exista in lista de filme \n")


    def test_cautare_dupa_id(self):
        rep_film = repo_film_file("D:\\Python\\Pycharm\\Programs\\Laborator 7-9\\Eu\\testare\\test_filme.txt")

        film_cautat=Film(2, "Hangover", "Comedy", "Film kinda fain")
        film_rezultat=rep_film.cautare_film_dupa_id(2)
        self.assertTrue(film_rezultat.equal_film(film_cautat))

        with self.assertRaises(ValueError) as context:
            rep_film.cautare_film_dupa_id(5)

        self.assertEqual(str(context.exception),
                         "filmul cautat nu se afla in lista de filme \n")



class TestRepoClient(unittest.TestCase):

    def test_creeaza(self):
        client_nou = Client(1, "Popescu", "5041118082209")
        self.assertEqual(client_nou.get_id(), 1)
        self.assertEqual(client_nou.get_nume(), "Popescu")
        self.assertEqual(client_nou.get_cnp(), "5041118082209")


    def test_equal_lists(self):
        repo_1= repo_client()
        repo_1.adauga_client(Client(1, "Popescu", "5041118082209"))
        repo_1.adauga_client(Client(2, "Chiorean", "4050624082209"))

        repo_2= repo_client()
        repo_2.adauga_client(Client(1, "Popescu", "5041118082209"))
        repo_2.adauga_client(Client(2, "Chiorean", "4050624082209"))

        repo_3= repo_client()
        repo_3.adauga_client(Client(1, "Popescu", "5041118082209"))
        repo_3.adauga_client(Client(2, "Chiorean", "4050624082209"))
        repo_3.adauga_client(Client(3, "Oancea", "5051212082209"))

        self.assertTrue(repo_1.equal_lists(repo_2))
        self.assertTrue(repo_2.equal_lists(repo_1))

        self.assertFalse(repo_3.equal_lists(repo_1))
        self.assertFalse(repo_1.equal_lists(repo_3))


    def test_equal_client(self):
        client_1 = Client(1, "Popescu", "5041118082209")
        client_2 = Client(2, "Chiorean", "40506124082209")
        client_3 = Client(1, "Popescu", "5041118082209")

        self.assertFalse(client_1.equal_client(client_2))
        self.assertTrue(client_1.equal_client(client_3))


    def test_adaugare(self):
        rep_client=repo_client()
        self.assertEqual(rep_client.length, 0)

        client_adaugat = Client(1, "Popescu", "5041118082209")
        rep_client.adauga_client(client_adaugat)
        self.assertEqual(rep_client.length, 1)

        with self.assertRaises(ValueError) as context:
            rep_client.adauga_client(client_adaugat)

        self.assertEqual(str(context.exception),
                         "acest client a fost introdus deja \n")


    def test_stergere(self):
        rep_client = repo_client()
        rep_client.adauga_client(Client(1, "Popescu", "5041118082209"))
        rep_client.adauga_client(Client(2, "Chiorean", "40506124082209"))

        repo_solutie = repo_client()
        repo_solutie.adauga_client(Client(1, "Popescu", "5041118082209"))

        repo_rezultat = rep_client.sterge_client(2)
        self.assertTrue(repo_rezultat.equal_lists(repo_solutie))

        with self.assertRaises(ValueError) as context:
            repo_rezultat.sterge_client(2)

        self.assertEqual(str(context.exception),
                         "clientul nu exista in lista de clienti \n")


    def test_modificare(self):
        rep_client = repo_client()
        rep_client.adauga_client(Client(1, "Popescu", "5041118082209"))
        rep_client.adauga_client(Client(2, "Chiorean", "40506124082209"))

        repo_solutie = repo_client()
        repo_solutie.adauga_client(Client(3, "Oancea", "5051212082209"))
        repo_solutie.adauga_client(Client(2, "Chiorean", "4050624082209"))

        repo_rezultat = rep_client.modifica_client(1, Client(3, "Oancea", "5051212082209"))
        self.assertTrue(repo_rezultat.equal_lists(repo_solutie))

        with self.assertRaises(ValueError) as context:
            repo_rezultat.modifica_client(1, Client(3, "Oancea", "5051212082209"))

        self.assertEqual(str(context.exception),
                         "clientul pe care doriti sa il modificati nu exista in lista de clienti \n")


    def test_cautare_dupa_id(self):
        rep_client = repo_client()
        rep_client.adauga_client(Client(1, "Popescu", "5041118082209"))
        rep_client.adauga_client(Client(2, "Chiorean", "40506124082209"))
        rep_client.adauga_client(Client(3, "Oancea", "5051212082209"))

        client_cautat = Client(2, "Chiorean", "40506124082209")
        client_rezultat = rep_client.cautare_client_dupa_id(2)
        self.assertTrue(client_rezultat.equal_client(client_cautat))

        client_cautat = Client(3, "Oancea", "5051212082209")
        client_rezultat = rep_client.cautare_client_dupa_id(3)
        self.assertTrue(client_rezultat.equal_client(client_cautat))

        with self.assertRaises(ValueError) as context:
            rep_client.cautare_client_dupa_id(4)

        self.assertEqual(str(context.exception),
                         "clientul cautat nu se afla in lista de clienti \n")



class TestRepoClientFile(unittest.TestCase):

    def setUp(self):
        repo = repo_client_file("D:\\Python\\Pycharm\\Programs\\Laborator 7-9\\Eu\\testare\\test_clienti.txt")
        repo.vector = []
        repo.vector.append(Client(1, "Popescu", "5041118082209"))
        repo.vector.append(Client(2, "Chiorean", "40506124082209"))
        repo.vector.append(Client(3, "Oancea", "5051212082209"))

        repo.scriere_in_fisier()


    def tearDown(self):
        repo = repo_client_file("D:\\Python\\Pycharm\\Programs\\Laborator 7-9\\Eu\\testare\\test_clienti.txt")
        repo.vector = []

        repo.scriere_in_fisier()


    def test_adaugare(self):
        rep_client=repo_client_file("D:\\Python\\Pycharm\\Programs\\Laborator 7-9\\Eu\\testare\\test_clienti.txt")

        client_adaugat = Client(4, "Tarlea", "5051226082209")
        rep_client.adauga_client(client_adaugat)
        self.assertEqual(rep_client.length, 4)
        self.assertTrue(rep_client.vector[0].equal_client(Client(1, "Popescu", "5041118082209")))
        self.assertTrue(rep_client.vector[1].equal_client(Client(2, "Chiorean", "40506124082209")))
        self.assertTrue(rep_client.vector[2].equal_client(Client(3, "Oancea", "5051212082209")))
        self.assertTrue(rep_client.vector[3].equal_client(Client(4, "Tarlea", "5051226082209")))

        client_adaugat = Client(5, "Bedea", "5050810082209")
        rep_client.adauga_client(client_adaugat)
        self.assertEqual(rep_client.length, 5)
        self.assertTrue(rep_client.vector[0].equal_client(Client(1, "Popescu", "5041118082209")))
        self.assertTrue(rep_client.vector[1].equal_client(Client(2, "Chiorean", "40506124082209")))
        self.assertTrue(rep_client.vector[2].equal_client(Client(3, "Oancea", "5051212082209")))
        self.assertTrue(rep_client.vector[3].equal_client(Client(4, "Tarlea", "5051226082209")))
        self.assertTrue(rep_client.vector[4].equal_client(Client(5, "Bedea", "5050810082209")))

        with self.assertRaises(ValueError) as context:
            rep_client.adauga_client(client_adaugat)

        self.assertEqual(str(context.exception),
                         "acest client a fost introdus deja \n")


    def test_stergere(self):
        rep_client=repo_client_file("D:\\Python\\Pycharm\\Programs\\Laborator 7-9\\Eu\\testare\\test_clienti.txt")

        id_existent = 1

        rep_client.sterge_client(id_existent)
        self.assertEqual(rep_client.length, 2)
        self.assertTrue(rep_client.vector[0].equal_client(Client(2, "Chiorean", "40506124082209")))
        self.assertTrue(rep_client.vector[1].equal_client(Client(3, "Oancea", "5051212082209")))

        with self.assertRaises(ValueError) as context:
            rep_client.sterge_client(id_existent)

        self.assertEqual(str(context.exception),
                         "clientul nu exista in lista de clienti \n")


    def test_modificare(self):
        rep_client=repo_client_file("D:\\Python\\Pycharm\\Programs\\Laborator 7-9\\Eu\\testare\\test_clienti.txt")

        rep_client.modifica_client(2, Client(6, "Moldovan", "060104082209"))

        self.assertEqual(rep_client.length, 3)
        self.assertTrue(rep_client.vector[0].equal_client(Client(1, "Popescu", "5041118082209")))
        self.assertTrue(rep_client.vector[1].equal_client(Client(6, "Moldovan", "060104082209")))
        self.assertTrue(rep_client.vector[2].equal_client(Client(3, "Oancea", "5051212082209")))

        with self.assertRaises(ValueError) as context:
            rep_client.modifica_client(4, Client(2, "Chiorean", "6050624245038"))

        self.assertEqual(str(context.exception),
                         "clientul pe care doriti sa il modificati nu exista in lista de clienti \n")


    def test_cautare_dupa_id(self):
        rep_client=repo_client_file("D:\\Python\\Pycharm\\Programs\\Laborator 7-9\\Eu\\testare\\test_clienti.txt")

        client_cautat = Client(2, "Chiorean", "6050624245038")
        client_rezultat = rep_client.cautare_client_dupa_id(2)
        self.assertTrue(client_rezultat.equal_client(client_cautat))

        with self.assertRaises(ValueError) as context:
            rep_client.cautare_client_dupa_id(5)

        self.assertEqual(str(context.exception),
                         "clientul cautat nu se afla in lista de clienti \n")



class TestRepoInchirieri(unittest.TestCase):

    def test_creeaza(self):
        inchiriere_1=Inchirieri(1,5)

        self.assertEqual(inchiriere_1.get_id_film(),1)
        self.assertEqual(inchiriere_1.get_id_client(),5)
        self.assertEqual(inchiriere_1.get_status(),"incompleta")


    def test_status(self):
        inchiriere_1=Inchirieri(1,5)
        self.assertEqual(inchiriere_1.get_status(), "incompleta")

        inchiriere_1.set_status()
        self.assertEqual(inchiriere_1.get_status(), "completa")


    def test_adaugare(self):
        repo_1=repo_inchirieri()
        self.assertEqual(repo_1._length, 0)

        inchiriere_1=Inchirieri(1,5)
        repo_1.adaugare_inchiriere(inchiriere_1)

        self.assertEqual(repo_1._length, 1)
        self.assertEqual(repo_1._vector[repo_1._length-1], inchiriere_1)

        with self.assertRaises(RepoError) as context:
            repo_1.adaugare_inchiriere(inchiriere_1)

        self.assertEqual(str(context.exception),
                         "clientul a inchiriat deja filmul\n")


    def test_returnare(self):
        repo_1=repo_inchirieri()
        inchiriere_existenta=Inchirieri(1,5)

        with self.assertRaises(RepoError) as context:
            repo_1.returnare_film(inchiriere_existenta)

        self.assertEqual(str(context.exception),
                         "nu s-a gasit o astfel de inchiriere incompleta\n")

        repo_1.adaugare_inchiriere(inchiriere_existenta)

        repo_1.returnare_film(inchiriere_existenta)
        self.assertEqual(repo_1._vector[repo_1._length-1].get_status(), "completa")


    def test_setare_status_dupa_client(self):
        repo_1=repo_inchirieri()
        repo_1.adaugare_inchiriere(Inchirieri(1,5))
        repo_1.adaugare_inchiriere(Inchirieri(2,1))
        repo_1.adaugare_inchiriere(Inchirieri(4,1))
        repo_1.adaugare_inchiriere(Inchirieri(5,2))

        id_client=1
        repo_1.setare_status_dupa_client(id_client)

        for el in repo_1._vector:
            if el.get_id_client() ==id_client:
                self.assertEqual(el.get_status(),"completa")
            else:
                self.assertEqual(el.get_status(), "incompleta")


    def test_setare_status_dupa_film(self):
        repo_1 = repo_inchirieri()
        repo_1.adaugare_inchiriere(Inchirieri(1, 5))
        repo_1.adaugare_inchiriere(Inchirieri(2, 1))
        repo_1.adaugare_inchiriere(Inchirieri(3, 1))
        repo_1.adaugare_inchiriere(Inchirieri(5, 2))

        id_film = 2
        repo_1.setare_status_dupa_film(id_film)

        for el in repo_1._vector:
            if el.get_id_film() == id_film:
                self.assertEqual(el.get_status(), "completa")
            else:
                self.assertEqual(el.get_status(), "incompleta")



class TestRepoInchirieriFile(unittest.TestCase):

    def setUp(self):
        repo = repo_inchirieri_file("D:\\Python\\Pycharm\\Programs\\Laborator 7-9\\Eu\\testare\\test_inchirieri.txt")
        repo._vector = []
        repo._vector.append(Inchirieri(5, 1))
        repo._vector.append(Inchirieri(6, 2))
        repo._vector.append(Inchirieri(7, 2))

        repo.scriere_in_fisier()


    def tearDown(self):
        repo = repo_inchirieri_file("D:\\Python\\Pycharm\\Programs\\Laborator 7-9\\Eu\\testare\\test_inchirieri.txt")
        repo._vector = []

        repo.scriere_in_fisier()


    def test_adaugare(self):
        rep_inchirieri = repo_inchirieri_file("D:\\Python\\Pycharm\\Programs\\Laborator 7-9\\Eu\\testare\\test_inchirieri.txt")

        inchiriere_1 = Inchirieri(1, 1)
        rep_inchirieri.adaugare_inchiriere(inchiriere_1)


        self.assertEqual(rep_inchirieri._length, 4)
        self.assertEqual(rep_inchirieri._vector[0], Inchirieri(5, 1))
        self.assertEqual(rep_inchirieri._vector[1], Inchirieri(6, 2))
        self.assertEqual(rep_inchirieri._vector[2], Inchirieri(7, 2))
        self.assertEqual(rep_inchirieri._vector[3], Inchirieri(1, 1))

        inchiriere_1 = Inchirieri(9, 1)
        rep_inchirieri.adaugare_inchiriere(inchiriere_1)
        self.assertEqual(rep_inchirieri._length, 5)
        self.assertEqual(rep_inchirieri._vector[0], Inchirieri(5, 1))
        self.assertEqual(rep_inchirieri._vector[1], Inchirieri(6, 2))
        self.assertEqual(rep_inchirieri._vector[2], Inchirieri(7, 2))
        self.assertEqual(rep_inchirieri._vector[3], Inchirieri(1, 1))
        self.assertEqual(rep_inchirieri._vector[4], Inchirieri(9, 1))

        with self.assertRaises(RepoError) as context:
            rep_inchirieri.adaugare_inchiriere(inchiriere_1)

        self.assertEqual(str(context.exception),
                         "clientul a inchiriat deja filmul\n")


    def test_returnare(self):
        rep_inchirieri = repo_inchirieri_file("D:\\Python\\Pycharm\\Programs\\Laborator 7-9\\Eu\\testare\\test_inchirieri.txt")
        inchiriere_inexistenta=Inchirieri(9,9)

        with self.assertRaises(RepoError) as context:
            rep_inchirieri.returnare_film(inchiriere_inexistenta)

        self.assertEqual(str(context.exception),
                         "nu s-a gasit o astfel de inchiriere incompleta\n")

        inchiriere_existenta = Inchirieri(5, 1)

        rep_inchirieri.returnare_film(inchiriere_existenta)
        self.assertEqual(rep_inchirieri._vector[0].get_status(), "completa")
        self.assertEqual(rep_inchirieri._vector[1].get_status(), "incompleta")
        self.assertEqual(rep_inchirieri._vector[2].get_status(), "incompleta")



    def test_setare_status_dupa_client(self):
        rep_inchirieri = repo_inchirieri_file("D:\\Python\\Pycharm\\Programs\\Laborator 7-9\\Eu\\testare\\test_inchirieri.txt")

        id_client=1
        rep_inchirieri.setare_status_dupa_client(id_client)

        for el in rep_inchirieri._vector:
            if el.get_id_client() ==id_client:
                self.assertEqual(el.get_status(),"completa")
            else:
                self.assertEqual(el.get_status(), "incompleta")


    def test_setare_status_dupa_film(self):
        rep_inchirieri = repo_inchirieri_file(
            "D:\\Python\\Pycharm\\Programs\\Laborator 7-9\\Eu\\testare\\test_inchirieri.txt")

        id_film = 5
        rep_inchirieri.setare_status_dupa_film(id_film)

        for el in rep_inchirieri._vector:
            if el.get_id_film() == id_film:
                self.assertEqual(el.get_status(), "completa")
            else:
                self.assertEqual(el.get_status(), "incompleta")



if __name__ == '__main__':
    unittest.main()



