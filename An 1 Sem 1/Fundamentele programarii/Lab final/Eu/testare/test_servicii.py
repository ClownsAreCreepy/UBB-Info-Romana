from lib2to3.fixes.fix_input import context
from wsgiref.validate import validator

from Validare.validare import *
from business.service_client import *
from business.service_film import *
from business.service_inchirieri import *
from Domain.DTO import *
import unittest



class TestFilm(unittest.TestCase):

    def test_adaugare_validare_film(self):
        repo_1=repo_film()
        validator= validare_film()
        service_1= service_film(validator,repo_1)

        service_1.adaugare_validare_film(1, "Se7en", "Thriller", "Film fain")
        self.assertEqual(service_1.repository.length, 1)

        with self.assertRaises(Exception) as context:
            service_1.adaugare_validare_film(-1, "", "", "")

        self.assertEqual(str(context.exception),
                         "id-ul introdus nu poate fi negativ \nnumele filmului nu poate sa fie vid \ngenul filmului nu poate sa fie vid \ndescrierea filmului nu poate sa fie vida \n")

        with self.assertRaises(Exception) as context:
            service_1.adaugare_validare_film(1, "Se7en", "Thriller", "Film fain")

        self.assertEqual(str(context.exception),
                         "acest film a fost introdus deja \n")


    def test_stergere_validare_film(self):
        repo_1=repo_film()
        repo_1.adauga_film(Film(1, "Se7en", "Thriller", "Film fain"))
        repo_1.adauga_film(Film(2, "Hangover", "Comedy", "Film kinda fain"))
        repo_1.adauga_film(Film(3, "The Godfather", "Crime", "Film foarte fain"))

        validator= validare_film()
        service_1= service_film(validator,repo_1)

        repo_2=repo_film()
        repo_2.adauga_film(Film(1, "Se7en", "Thriller", "Film fain"))
        repo_2.adauga_film(Film(2, "Hangover", "Comedy", "Film kinda fain"))

        repo_rezultat = service_1.stergere_validare_film(3)
        self.assertTrue(repo_2.equal_lists(repo_rezultat))

        with self.assertRaises(Exception) as context:
            service_1.stergere_validare_film(4)

        self.assertEqual(str(context.exception),
                         "filmul nu exista in lista de filme \n")

        with self.assertRaises(Exception) as context:
            service_1.stergere_validare_film(-1)

        self.assertEqual(str(context.exception),
                         "id-ul introdus nu poate fi negativ \n")


    def test_modificare_validare_film(self):
        repo_1=repo_film()
        repo_1.adauga_film(Film(1, "Se7en", "Thriller", "Film fain"))
        repo_1.adauga_film(Film(2, "Hangover", "Comedy", "Film kinda fain"))

        film_nou=Film(3, "The Godfather", "Crime", "Film foarte fain")

        repo_solutie=repo_film()
        repo_solutie.adauga_film(Film(1, "Se7en", "Thriller", "Film fain"))
        repo_solutie.adauga_film(film_nou)

        validator= validare_film()
        service_1= service_film(validator,repo_1)

        repo_rezultat=service_1.modificare_validare_film(2,film_nou)
        self.assertTrue(repo_solutie.equal_lists(repo_rezultat))

        with self.assertRaises(Exception) as context:
            service_1.modificare_validare_film(-1,film_nou)

        self.assertEqual(str(context.exception),
                         "id-ul introdus nu poate fi negativ \n")

        with self.assertRaises(Exception) as context:
            service_1.modificare_validare_film(2,Film(-1, "", "", ""))

        self.assertEqual(str(context.exception),
                         "id-ul introdus nu poate fi negativ \nnumele filmului nu poate sa fie vid \ngenul filmului nu poate sa fie vid \ndescrierea filmului nu poate sa fie vida \n")

        with self.assertRaises(Exception) as context:
            service_1.modificare_validare_film(5,Film(9, "Fight Club", "Drama", "Film filosofic D:"))

        self.assertEqual(str(context.exception),
                         "filmul pe care doriti sa il modificati nu exista in lista de filme \n")


    def test_cautare_validare_film(self):
        repo_1=repo_film()
        repo_1.adauga_film(Film(1, "Se7en", "Thriller", "Film fain"))
        repo_1.adauga_film(Film(2, "Hangover", "Comedy", "Film kinda fain"))
        repo_1.adauga_film(Film(3, "The Godfather", "Crime", "Film foarte fain"))

        valid=validare_film()
        service_1= service_film(valid,repo_1)

        film_cautat=Film(3, "The Godfather", "Crime", "Film foarte fain")
        film_rezultat=service_1.cautare_validare_film(3)
        self.assertTrue(film_rezultat.equal_film(film_cautat))

        with self.assertRaises(Exception) as context:
            service_1.cautare_validare_film(-1)

        self.assertEqual(str(context.exception),
                         "id-ul introdus nu poate fi negativ \n")

        with self.assertRaises(Exception) as context:
            service_1.cautare_validare_film(5)

        self.assertEqual(str(context.exception),
                         "filmul cautat nu se afla in lista de filme \n")



class TestFilmFile(unittest.TestCase):

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


    def test_adaugare_validare_film(self):
        rep_film = repo_film_file("D:\\Python\\Pycharm\\Programs\\Laborator 7-9\\Eu\\testare\\test_filme.txt")
        validator= validare_film()
        service_1= service_film(validator,rep_film)

        service_1.adaugare_validare_film(4, "The Shawshank Redemption", "Drama", "Film feel-good")
        self.assertEqual(rep_film.length, 4)
        self.assertTrue(rep_film.vector[0].equal_film(Film(1, "Se7en", "Thriller", "Film fain")))
        self.assertTrue(rep_film.vector[1].equal_film(Film(2, "Hangover", "Comedy", "Film kinda fain")))
        self.assertTrue(rep_film.vector[2].equal_film(Film(3, "The Godfather", "Crime", "Film foarte fain")))
        self.assertTrue(rep_film.vector[3].equal_film(Film(4, "The Shawshank Redemption", "Drama", "Film feel-good")))

        service_1.adaugare_validare_film(5, "Transformers", "Actiune", "Film wow")
        self.assertEqual(rep_film.length, 5)
        self.assertTrue(rep_film.vector[0].equal_film(Film(1, "Se7en", "Thriller", "Film fain")))
        self.assertTrue(rep_film.vector[1].equal_film(Film(2, "Hangover", "Comedy", "Film kinda fain")))
        self.assertTrue(rep_film.vector[2].equal_film(Film(3, "The Godfather", "Crime", "Film foarte fain")))
        self.assertTrue(rep_film.vector[3].equal_film(Film(4, "The Shawshank Redemption", "Drama", "Film feel-good")))
        self.assertTrue(rep_film.vector[4].equal_film(Film(5, "Transformers", "Actiune", "Film wow")))


        with self.assertRaises(Exception) as context:
            service_1.adaugare_validare_film(-1, "", "", "")

        self.assertEqual(str(context.exception),
                         "id-ul introdus nu poate fi negativ \nnumele filmului nu poate sa fie vid \ngenul filmului nu poate sa fie vid \ndescrierea filmului nu poate sa fie vida \n")

        with self.assertRaises(Exception) as context:
            service_1.adaugare_validare_film(1, "Se7en", "Thriller", "Film fain")

        self.assertEqual(str(context.exception),
                         "acest film a fost introdus deja \n")


    def test_stergere_validare_film(self):
        rep_film = repo_film_file("D:\\Python\\Pycharm\\Programs\\Laborator 7-9\\Eu\\testare\\test_filme.txt")
        validator = validare_film()
        service_1 = service_film(validator, rep_film)

        service_1.stergere_validare_film(1)
        self.assertEqual(rep_film.length, 2)
        self.assertTrue(rep_film.vector[0].equal_film(Film(2, "Hangover", "Comedy", "Film kinda fain")))
        self.assertTrue(rep_film.vector[1].equal_film(Film(3, "The Godfather", "Crime", "Film foarte fain")))

        with self.assertRaises(Exception) as context:
            service_1.stergere_validare_film(4)

        self.assertEqual(str(context.exception),
                         "filmul nu exista in lista de filme \n")

        with self.assertRaises(Exception) as context:
            service_1.stergere_validare_film(-1)

        self.assertEqual(str(context.exception),
                         "id-ul introdus nu poate fi negativ \n")


    def test_modificare_validare_film(self):
        rep_film = repo_film_file("D:\\Python\\Pycharm\\Programs\\Laborator 7-9\\Eu\\testare\\test_filme.txt")
        validator = validare_film()
        service_1 = service_film(validator, rep_film)

        service_1.modificare_validare_film(2, Film(6, "Everything Everywhere All At Once", "Sci-Fi", "Film damn"))

        self.assertEqual(rep_film.length, 3)
        self.assertTrue(rep_film.vector[0].equal_film(Film(1, "Se7en", "Thriller", "Film fain")))
        self.assertTrue(rep_film.vector[1].equal_film(Film(6, "Everything Everywhere All At Once", "Sci-Fi", "Film damn")))
        self.assertTrue(rep_film.vector[2].equal_film(Film(3, "The Godfather", "Crime", "Film foarte fain")))

        with self.assertRaises(Exception) as context:
            service_1.modificare_validare_film(-1,Film(9, "Fight Club", "Drama", "Film filosofic D:"))

        self.assertEqual(str(context.exception),
                         "id-ul introdus nu poate fi negativ \n")

        with self.assertRaises(Exception) as context:
            service_1.modificare_validare_film(2,Film(-1, "", "", ""))

        self.assertEqual(str(context.exception),
                         "id-ul introdus nu poate fi negativ \nnumele filmului nu poate sa fie vid \ngenul filmului nu poate sa fie vid \ndescrierea filmului nu poate sa fie vida \n")

        with self.assertRaises(Exception) as context:
            service_1.modificare_validare_film(5,Film(9, "Fight Club", "Drama", "Film filosofic D:"))

        self.assertEqual(str(context.exception),
                         "filmul pe care doriti sa il modificati nu exista in lista de filme \n")


    def test_cautare_validare_film(self):
        rep_film = repo_film_file("D:\\Python\\Pycharm\\Programs\\Laborator 7-9\\Eu\\testare\\test_filme.txt")
        validator = validare_film()
        service_1 = service_film(validator, rep_film)

        film_cautat = Film(2, "Hangover", "Comedy", "Film kinda fain")
        film_rezultat = service_1.cautare_validare_film(2)
        self.assertTrue(film_rezultat.equal_film(film_cautat))

        with self.assertRaises(Exception) as context:
            service_1.cautare_validare_film(-1)

        self.assertEqual(str(context.exception),
                         "id-ul introdus nu poate fi negativ \n")

        with self.assertRaises(Exception) as context:
            service_1.cautare_validare_film(5)

        self.assertEqual(str(context.exception),
                         "filmul cautat nu se afla in lista de filme \n")



class TestClient(unittest.TestCase):

    def test_adaugare_validare_client(self):
        repo_1=repo_client()
        valid=validare_client()
        service_1= service_client(valid,repo_1)

        service_1.adaugare_client_validare(1, "Popescu", "5041118082209")
        self.assertEqual(service_1.repository.length, 1)

        with self.assertRaises(ValueError) as context:
            service_1.adaugare_client_validare(-1, "", "")

        self.assertEqual(str(context.exception),
                         "id-ul introdus nu poate fi negativ \nnumele clientului nu poate fi negativ \ncnp-ul clientului a fost introdus gresit \n")

        with self.assertRaises(ValueError) as context:
            service_1.adaugare_client_validare(1, "Popescu","5041118082209")

        self.assertEqual(str(context.exception),
                         "acest client a fost introdus deja \n")


    def test_stergere_validare_client(self):
        repo_1=repo_client()
        repo_1.adauga_client(Client(1, "Popescu", "5041118082209"))
        repo_1.adauga_client(Client(2, "Chiorean", "6050624082209"))
        repo_1.adauga_client(Client(3, "Oancea", "5051212082209"))

        valid=validare_client()
        service_1= service_client(valid,repo_1)

        repo_2=repo_client()
        repo_2.adauga_client(Client(1, "Popescu", "5041118082209"))
        repo_2.adauga_client(Client(2, "Chiorean", "6050624082209"))

        repo_rezultat=service_1.stergere_validare_client(3)
        self.assertTrue(repo_rezultat.equal_lists(repo_2))

        with self.assertRaises(ValueError) as context:
            service_1.stergere_validare_client(5)

        self.assertEqual(str(context.exception),
                         "clientul nu exista in lista de clienti \n")

        with self.assertRaises(ValueError) as context:
            service_1.stergere_validare_client(-1)

        self.assertEqual(str(context.exception),
                         "id-ul introdus nu poate fi negativ \n")


    def test_modificare_validare_client(self):
        repo_1=repo_client()
        repo_1.adauga_client(Client(1, "Popescu", "5041118082209"))
        repo_1.adauga_client(Client(2, "Chiorean", "6050624082209"))
        repo_1.adauga_client(Client(3, "Oancea", "5051212082209"))

        client_nou = Client(4, "Tarlea", "5051226082209")

        repo_solutie=repo_client()
        repo_solutie.adauga_client(Client(1, "Popescu", "5041118082209"))
        repo_solutie.adauga_client(client_nou)
        repo_solutie.adauga_client(Client(3, "Oancea", "5051226082209"))

        valid=validare_client()
        service_1= service_client(valid,repo_1)
        repo_rezultat=service_1.modificare_validare_client(2, client_nou)
        self.assertTrue(repo_rezultat.equal_lists(repo_solutie))

        with self.assertRaises(ValueError) as context:
            service_1.modificare_validare_client(-1, client_nou)

        self.assertEqual(str(context.exception),
                         "id-ul introdus nu poate fi negativ \n")

        with self.assertRaises(ValueError) as context:
            service_1.modificare_validare_client(2, Client(-1, "", ""))

        self.assertEqual(str(context.exception),
                         "id-ul introdus nu poate fi negativ \nnumele clientului nu poate fi negativ \ncnp-ul clientului a fost introdus gresit \n")

        with self.assertRaises(ValueError) as context:
            service_1.modificare_validare_client(5, client_nou)

        self.assertEqual(str(context.exception),
                         "clientul pe care doriti sa il modificati nu exista in lista de clienti \n")


    def test_cautare_validare_client(self):
        repo_1=repo_client()
        repo_1.adauga_client(Client(1, "Popescu", "5041118082209"))
        repo_1.adauga_client(Client(2, "Chiorean", "6050624082209"))
        repo_1.adauga_client(Client(3, "Oancea", "5051226082209"))

        valid=validare_client()
        service_1= service_client(valid,repo_1)

        client_cautat=Client(1, "Popescu", "5041118082209")
        client_rezultat = service_1.cautare_validare_client(1)
        assert(client_rezultat.equal_client(client_cautat))

        try:
            service_1.cautare_validare_client(-1)
            assert(False)
        except ValueError as ve:
            assert(str(ve) == "id-ul introdus nu poate fi negativ \n")

        try:
            service_1.cautare_validare_client(4)
            assert(False)
        except ValueError as ve:
            assert(str(ve) == "clientul cautat nu se afla in lista de clienti \n")


    def test_adaugare_generare_random(self):
        repo_1=repo_client()
        valid=validare_client()
        service_1= service_client(valid,repo_1)

        service_1.adaugare_generare_random(5)
        self.assertEqual(repo_1.length, 5)

        repo_2=repo_client()
        service_2= service_client(valid,repo_2)

        with self.assertRaises(ValueError) as context:
            service_1.adaugare_generare_random(-1)

        self.assertEqual(str(context.exception),
                         "id-ul introdus nu poate fi negativ \n")



class TestClientFile(unittest.TestCase):

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


    def test_adaugare_validare_client(self):
        rep_client = repo_client_file("D:\\Python\\Pycharm\\Programs\\Laborator 7-9\\Eu\\testare\\test_clienti.txt")
        validator = validare_client()
        service_1 = service_client(validator, rep_client)

        service_1.adaugare_client_validare(4, "Tarlea", "5051226082209")
        self.assertEqual(rep_client.length, 4)
        self.assertTrue(rep_client.vector[0].equal_client(Client(1, "Popescu", "5041118082209")))
        self.assertTrue(rep_client.vector[1].equal_client(Client(2, "Chiorean", "40506124082209")))
        self.assertTrue(rep_client.vector[2].equal_client(Client(3, "Oancea", "5051212082209")))
        self.assertTrue(rep_client.vector[3].equal_client(Client(4, "Tarlea", "5051226082209")))

        service_1.adaugare_client_validare(5, "Bedea", "5050810082209")
        self.assertEqual(rep_client.length, 5)
        self.assertTrue(rep_client.vector[0].equal_client(Client(1, "Popescu", "5041118082209")))
        self.assertTrue(rep_client.vector[1].equal_client(Client(2, "Chiorean", "40506124082209")))
        self.assertTrue(rep_client.vector[2].equal_client(Client(3, "Oancea", "5051212082209")))
        self.assertTrue(rep_client.vector[3].equal_client(Client(4, "Tarlea", "5051226082209")))
        self.assertTrue(rep_client.vector[4].equal_client(Client(5, "Bedea", "5050810082209")))

        with self.assertRaises(ValueError) as context:
            service_1.adaugare_client_validare(-1, "", "")

        self.assertEqual(str(context.exception),
                         "id-ul introdus nu poate fi negativ \nnumele clientului nu poate fi negativ \ncnp-ul clientului a fost introdus gresit \n")

        with self.assertRaises(ValueError) as context:
            service_1.adaugare_client_validare(1, "Popescu","5041118082209")

        self.assertEqual(str(context.exception),
                         "acest client a fost introdus deja \n")


    def test_stergere_validare_client(self):
        rep_client = repo_client_file("D:\\Python\\Pycharm\\Programs\\Laborator 7-9\\Eu\\testare\\test_clienti.txt")
        validator = validare_client()
        service_1 = service_client(validator, rep_client)

        id_existent = 1

        service_1.stergere_validare_client(id_existent)
        self.assertEqual(rep_client.length, 2)
        self.assertTrue(rep_client.vector[0].equal_client(Client(2, "Chiorean", "40506124082209")))
        self.assertTrue(rep_client.vector[1].equal_client(Client(3, "Oancea", "5051212082209")))

        with self.assertRaises(ValueError) as context:
            service_1.stergere_validare_client(5)

        self.assertEqual(str(context.exception),
                         "clientul nu exista in lista de clienti \n")

        with self.assertRaises(ValueError) as context:
            service_1.stergere_validare_client(-1)

        self.assertEqual(str(context.exception),
                         "id-ul introdus nu poate fi negativ \n")


    def test_modificare_validare_client(self):
        rep_client = repo_client_file("D:\\Python\\Pycharm\\Programs\\Laborator 7-9\\Eu\\testare\\test_clienti.txt")
        validator = validare_client()
        service_1 = service_client(validator, rep_client)

        client_nou = Client(6, "Moldovan", "5060104082209")

        service_1.modificare_validare_client(2, client_nou)

        self.assertEqual(rep_client.length, 3)
        self.assertTrue(rep_client.vector[0].equal_client(Client(1, "Popescu", "5041118082209")))
        self.assertTrue(rep_client.vector[1].equal_client(Client(6, "Moldovan", "060104082209")))
        self.assertTrue(rep_client.vector[2].equal_client(Client(3, "Oancea", "5051212082209")))

        with self.assertRaises(ValueError) as context:
            service_1.modificare_validare_client(-1, client_nou)

        self.assertEqual(str(context.exception),
                         "id-ul introdus nu poate fi negativ \n")

        with self.assertRaises(ValueError) as context:
            service_1.modificare_validare_client(2, Client(-1, "", ""))

        self.assertEqual(str(context.exception),
                         "id-ul introdus nu poate fi negativ \nnumele clientului nu poate fi negativ \ncnp-ul clientului a fost introdus gresit \n")

        with self.assertRaises(ValueError) as context:
            service_1.modificare_validare_client(5, client_nou)

        self.assertEqual(str(context.exception),
                         "clientul pe care doriti sa il modificati nu exista in lista de clienti \n")


    def test_cautare_validare_client(self):
        rep_client = repo_client_file("D:\\Python\\Pycharm\\Programs\\Laborator 7-9\\Eu\\testare\\test_clienti.txt")
        validator = validare_client()
        service_1 = service_client(validator, rep_client)

        client_cautat = Client(2, "Chiorean", "6050624245038")
        client_rezultat = service_1.cautare_validare_client(2)
        self.assertTrue(client_rezultat.equal_client(client_cautat))

        try:
            service_1.cautare_validare_client(-1)
            assert(False)
        except ValueError as ve:
            assert(str(ve) == "id-ul introdus nu poate fi negativ \n")

        try:
            service_1.cautare_validare_client(4)
            assert(False)
        except ValueError as ve:
            assert(str(ve) == "clientul cautat nu se afla in lista de clienti \n")


    def test_adaugare_generare_random(self):
        rep_client = repo_client_file("D:\\Python\\Pycharm\\Programs\\Laborator 7-9\\Eu\\testare\\test_clienti.txt")
        validator = validare_client()
        service_1 = service_client(validator, rep_client)

        service_1.adaugare_generare_random(5)
        self.assertEqual(rep_client.length, 8)

        with self.assertRaises(ValueError) as context:
            service_1.adaugare_generare_random(-1)

        self.assertEqual(str(context.exception),
                         "id-ul introdus nu poate fi negativ \n")



class TestInchirieri(unittest.TestCase):


    def test_adaugare_validare_inchirieri(self):
        repo_1=repo_inchirieri()
        validator=validare_inchiriere()

        repo_c = repo_client()
        repo_f = repo_film()

        repo_c.adauga_client(Client(1, "Popescu", "5041118082209"))
        repo_c.adauga_client(Client(2, "Chiorean", "6050624082209"))

        repo_f.adauga_film(Film(1,"Se7en", "Thriller", "Film fain"))
        repo_f.adauga_film(Film(2, "Hangover", "Comedy", "Film kinda fain"))

        service_1=service_inchirieri(validator,repo_1,repo_c,repo_f)

        id_client = 1
        id_film = 2

        id_client_invalid = -1
        id_film_invalid = -2

        id_client_inexistent = 3
        id_film_inexistent = 4

        self.assertEqual(service_1._repository_inchirieri._length, 0)
        service_1.adaugare_validare_inchiriere(id_film, id_client)

        self.assertEqual(service_1._repository_inchirieri._length, 1)

        with self.assertRaises(ValidationError) as context:
            service_1.adaugare_validare_inchiriere(id_film_invalid, id_client_invalid)

        self.assertEqual(str(context.exception),
                        "id-ul clientului nu poate fi negativ \nid-ul filmului nu poate fi negativ \n")

        with self.assertRaises(RepoError) as context:
            service_1.adaugare_validare_inchiriere(id_film, id_client)

        self.assertEqual(str(context.exception),
                         "clientul a inchiriat deja filmul\n")

        with self.assertRaises(ExistentialError) as context:
            service_1.adaugare_validare_inchiriere(id_film_inexistent, id_client_inexistent)
        self.assertEqual(str(context.exception),
                         "clientul caruia ii atribuiti inchirierea nu exista \nfilmul nu exista \n")



    def test_returnare_validare_film(self):
        repo_1 = repo_inchirieri()
        validator = validare_inchiriere()

        repo_c = repo_client()
        repo_f = repo_film()

        repo_c.adauga_client(Client(1, "Popescu", "5041118082209"))
        repo_c.adauga_client(Client(2, "Chiorean", "6050624082209"))

        repo_f.adauga_film(Film(1, "Se7en", "Thriller", "Film fain"))
        repo_f.adauga_film(Film(2, "Hangover", "Comedy", "Film kinda fain"))

        service_1=service_inchirieri(validator,repo_1,repo_c,repo_f)

        id_client = 1
        id_film = 2

        id_client_invalid = -1
        id_film_invalid = -2

        id_client_inexistent = 3
        id_film_inexistent = 4

        with self.assertRaises(RepoError) as context:
            service_1.returnare_validare_film(id_film, id_client)

        self.assertEqual(str(context.exception),
                         "nu s-a gasit o astfel de inchiriere incompleta\n")

        service_1.adaugare_validare_inchiriere(id_film, id_client)
        service_1.adaugare_validare_inchiriere(1,2)

        service_1.returnare_validare_film(1,2)
        self.assertEqual(service_1._repository_inchirieri._vector[0].get_status(), "incompleta")
        self.assertEqual(service_1._repository_inchirieri._vector[1].get_status(), "completa")

        with self.assertRaises(ValidationError) as context:
            service_1.returnare_validare_film(id_film_invalid, id_client_invalid)

        self.assertEqual(str(context.exception),
                         "id-ul clientului nu poate fi negativ \nid-ul filmului nu poate fi negativ \n")

        with self.assertRaises(ExistentialError) as context:
            service_1.returnare_validare_film(id_film_inexistent, id_client_inexistent)

        self.assertEqual(str(context.exception),
                         "clientul caruia ii atribuiti returnarea nu exista \nfilmul nu exista \n")


    def test_sortare_clienti_dupa_nume_si_nr_inchirieri(self):
        repo_c = repo_client()
        repo_f = repo_film()
        repo_i = repo_inchirieri()

        service_1 = service_inchirieri(None, repo_i, repo_c, repo_f)

        clienti_inchirieri = {
            1: Client_DTO(1, "Popescu", 3),
            2: Client_DTO(2, "Chiorean", 5),
            3: Client_DTO(3, "Oancea", 2)
        }

        lista_sortata = service_1.sortare_clienti_dupa_nume_si_nr_inchirieri(clienti_inchirieri)
        self.assertEqual(lista_sortata[0].nume_client, "Chiorean")
        self.assertEqual(lista_sortata[1].nume_client, "Oancea")
        self.assertEqual(lista_sortata[2].nume_client, "Popescu")
        self.assertEqual(lista_sortata[0].nr_inchirieri, 5)


    def test_clienti_cu_filme_inchiriate(self):
        repo_c=repo_client()
        repo_f=repo_film()
        repo_i=repo_inchirieri()

        service_1 = service_inchirieri(None, repo_i, repo_c, repo_f)

        repo_c.adauga_client(Client(1, "Popescu", "5041118082209"))
        repo_c.adauga_client(Client(2, "Chiorean", "6050624082209"))
        repo_c.adauga_client(Client(3, "Oancea", "5051226082209"))
        repo_c.adauga_client(Client(4, "Tarlea", "5051226082209"))

        repo_f.adauga_film(Film(1, "Se7en", "Thriller", "Film fain"))
        repo_f.adauga_film(Film(2, "Hangover", "Comedy", "Film kinda fain"))
        repo_f.adauga_film(Film(3, "The Godfather", "Crime", "Film foarte fain"))
        repo_f.adauga_film(Film(4, "The Shawshank Redemption", "Drama", "Film feel-good"))
        repo_f.adauga_film(Film(5, "Transformers", "Actiune", "Film wow"))

        with self.assertRaises(ExistentialError) as context:
            clienti_dto = service_1.clienti_cu_filme_inchiriate()

        self.assertEqual(str(context.exception),
                         "nu exista inchirieri incomplete\n")

        repo_i.adaugare_inchiriere(Inchirieri(1,1))
        repo_i.adaugare_inchiriere(Inchirieri(2, 3))
        repo_i.adaugare_inchiriere(Inchirieri(3, 2))
        repo_i.adaugare_inchiriere(Inchirieri(5, 1))

        clienti_dto = service_1.clienti_cu_filme_inchiriate()
        self.assertEqual(len(clienti_dto), 3)
        client_dto_solutie = [ Client_DTO(2, "Chiorean" , 1),
                               Client_DTO(3, "Oancea" , 1),
                               Client_DTO(1, "Popescu" , 2)]
        self.assertEqual(clienti_dto, client_dto_solutie)


    def test_top_3_filme(self):
        repo_c = repo_client()
        repo_f = repo_film()
        repo_i = repo_inchirieri()

        service_1 = service_inchirieri(None, repo_i, repo_c, repo_f)

        filme_dto = {1: Film_DTO(1, "Se7en", 3),
                 2: Film_DTO(2, "Hangover", 5),
                 3: Film_DTO(3, "The Godfather", 2),
                 4: Film_DTO(4, "The Shawshank Redemption", 5),
                 5: Film_DTO(5, "Transformers", 2),}

        rezultat = service_1.top_3_filme(filme_dto)
        self.assertEqual(len(rezultat), 3)

        solutie = [Film_DTO(2, "Hangover", 5),
                   Film_DTO(4, "The Shawshank Redemption", 5),
                   Film_DTO(1, "Se7en", 3)]

        self.assertEqual(rezultat, solutie)


    def test_filme_cele_mai_inchiriate(self):
        repo_c = repo_client()
        repo_f = repo_film()
        repo_i = repo_inchirieri()

        service_1 = service_inchirieri(None, repo_i, repo_c, repo_f)

        repo_c.adauga_client(Client(1, "Popescu", "5041118082209"))
        repo_c.adauga_client(Client(2, "Chiorean", "6050624082209"))
        repo_c.adauga_client(Client(3, "Oancea", "5051226082209"))
        repo_c.adauga_client(Client(4, "Tarlea", "5051226082209"))

        repo_f.adauga_film(Film(1, "Se7en", "Thriller", "Film fain"))
        repo_f.adauga_film(Film(2, "Hangover", "Comedy", "Film kinda fain"))
        repo_f.adauga_film(Film(3, "The Godfather", "Crime", "Film foarte fain"))
        repo_f.adauga_film(Film(4, "The Shawshank Redemption", "Drama", "Film feel-good"))
        repo_f.adauga_film(Film(5, "Transformers", "Actiune", "Film wow"))

        with self.assertRaises(ExistentialError) as context:
            clienti_dto = service_1.filme_cele_mai_inchiriate()

        self.assertEqual(str(context.exception),
                         "nu exista inchirieri de filme\n")

        repo_i.adaugare_inchiriere(Inchirieri(1, 1))
        repo_i.adaugare_inchiriere(Inchirieri(2, 3))
        repo_i.adaugare_inchiriere(Inchirieri(2, 2))
        repo_i.adaugare_inchiriere(Inchirieri(5, 1))
        repo_i.adaugare_inchiriere(Inchirieri(5, 2))
        repo_i.adaugare_inchiriere(Inchirieri(1, 4))
        repo_i.adaugare_inchiriere(Inchirieri(1, 2))

        filme_dto = service_1.filme_cele_mai_inchiriate()
        self.assertEqual(len(filme_dto), 3)

        filme_dto_solutie = [Film_DTO(1, "Se7en", 3),
                             Film_DTO(2, "Hangover", 2),
                             Film_DTO(5, "Transformers", 2)]

        self.assertEqual(filme_dto, filme_dto_solutie)


    def test_sortare_clienti_dupa_nr_inchirieri(self):
        repo_c = repo_client()
        repo_f = repo_film()
        repo_i = repo_inchirieri()

        service_1 = service_inchirieri(None, repo_i, repo_c, repo_f)

        clienti_inchirieri = {
            1: Client_DTO(1, "Popescu", 3),
            2: Client_DTO(2, "Chiorean", 5),
            3: Client_DTO(3, "Oancea", 2)
        }

        lista_sortata = service_1.sortare_clienti_dupa_nr_inchirieri(clienti_inchirieri)
        self.assertEqual(lista_sortata[0].nume_client, "Chiorean")
        self.assertEqual(lista_sortata[1].nume_client, "Popescu")
        self.assertEqual(lista_sortata[2].nume_client, "Oancea")
        self.assertEqual(lista_sortata[0].nr_inchirieri, 5)


    def test_top_30_clienti(self):
        repo_c = repo_client()
        repo_f = repo_film()
        repo_i = repo_inchirieri()

        service_1 = service_inchirieri(None, repo_i, repo_c, repo_f)

        clienti_dto = { 1: Client_DTO(1, "Popescu", 3),
                        2: Client_DTO(2, "Chiorean", 5),
                        3: Client_DTO(3, "Oancea", 2),
                        4: Client_DTO(4, "Tarlea", 5),
                        5: Client_DTO(5, "Bedea", 2)}

        rezultat = service_1.top_30_clienti(clienti_dto)
        self.assertEqual(len(clienti_dto), 5)

        solutie = [Client_DTO(2, "Chiorean", 5)]

        self.assertEqual(rezultat, solutie)


    def test_clienti_cu_cele_mai_multe_inchirieri(self):
        repo_c = repo_client()
        repo_f = repo_film()
        repo_i = repo_inchirieri()

        service_1 = service_inchirieri(None, repo_i, repo_c, repo_f)

        repo_c.adauga_client(Client(1, "Popescu", "5041118082209"))
        repo_c.adauga_client(Client(2, "Chiorean", "6050624082209"))
        repo_c.adauga_client(Client(3, "Oancea", "5051226082209"))
        repo_c.adauga_client(Client(4, "Tarlea", "5051226082209"))
        repo_c.adauga_client(Client(5, "Bedea", "5050810082209"))
        repo_c.adauga_client(Client(6, "Moldovan", "060104082209"))
        repo_c.adauga_client(Client(7, "Czako", "5050617082209"))

        repo_f.adauga_film(Film(1, "Se7en", "Thriller", "Film fain"))
        repo_f.adauga_film(Film(2, "Hangover", "Comedy", "Film kinda fain"))
        repo_f.adauga_film(Film(3, "The Godfather", "Crime", "Film foarte fain"))
        repo_f.adauga_film(Film(4, "The Shawshank Redemption", "Drama", "Film feel-good"))
        repo_f.adauga_film(Film(5, "Transformers", "Actiune", "Film wow"))

        with self.assertRaises(ExistentialError) as context:
            clienti_dto = service_1.clienti_cu_filme_inchiriate()

        self.assertEqual(str(context.exception),
                         "nu exista inchirieri incomplete\n")

        repo_i.adaugare_inchiriere(Inchirieri(1, 1))
        repo_i.adaugare_inchiriere(Inchirieri(2, 3))
        repo_i.adaugare_inchiriere(Inchirieri(2, 2))
        repo_i.adaugare_inchiriere(Inchirieri(5, 1))
        repo_i.adaugare_inchiriere(Inchirieri(5, 2))
        repo_i.adaugare_inchiriere(Inchirieri(1, 4))
        repo_i.adaugare_inchiriere(Inchirieri(1, 2))

        clienti_dto = service_1.clienti_cu_cele_mai_multe_inchirieri()
        self.assertEqual(len(clienti_dto), 2)

        clienti_dto_solutie = [Client_DTO(2, "Chiorean",3),
                               Client_DTO(1, "Popescu", 2),]

        self.assertEqual(clienti_dto, clienti_dto_solutie)


    def testare_minim_3_filme_inchiriate(self):
        repo_c = repo_client()
        repo_f = repo_film()
        repo_i = repo_inchirieri()

        service_1 = service_inchirieri(None, repo_i, repo_c, repo_f)

        clienti_inchirieri = {
            1: Client_DTO(1, "Popescu", 7),
            2: Client_DTO(2, "Chiorean", 2),
            3: Client_DTO(3, "Oancea", 9),
            4: Client_DTO(4, "Tarlea", 3)}

        rezultat = service_1.minim_3_filme_inchiriate(clienti_inchirieri)
        self.assertEqual(len(rezultat), 3)

        solutie = [Client_DTO(1, "Popescu", 7),
                   Client_DTO(3, "Oancea", 9),
                   Client_DTO(4, "Tarlea", 3)]

        self.assertEqual(rezultat, solutie)


    def test_clienti_cu_peste_3_filme_inchiriate(self):
        repo_c = repo_client()
        repo_f = repo_film()
        repo_i = repo_inchirieri()

        service_1 = service_inchirieri(None, repo_i, repo_c, repo_f)

        repo_c.adauga_client(Client(1, "Popescu", "5041118082209"))
        repo_c.adauga_client(Client(2, "Chiorean", "6050624082209"))
        repo_c.adauga_client(Client(3, "Oancea", "5051226082209"))
        repo_c.adauga_client(Client(4, "Tarlea", "5051226082209"))

        repo_f.adauga_film(Film(1, "Se7en", "Thriller", "Film fain"))
        repo_f.adauga_film(Film(2, "Hangover", "Comedy", "Film kinda fain"))
        repo_f.adauga_film(Film(3, "The Godfather", "Crime", "Film foarte fain"))
        repo_f.adauga_film(Film(4, "The Shawshank Redemption", "Drama", "Film feel-good"))
        repo_f.adauga_film(Film(5, "Transformers", "Actiune", "Film wow"))

        with self.assertRaises(ExistentialError) as context:
            clienti_dto = service_1.clienti_cu_peste_3_filme_inchiriate()

        self.assertEqual(str(context.exception),
                         "nu exista inchirieri incomplete\n")

        repo_i.adaugare_inchiriere(Inchirieri(1, 1))

        with self.assertRaises(ExistentialError) as context:
            clienti_dto = service_1.clienti_cu_peste_3_filme_inchiriate()

        self.assertEqual(str(context.exception),
                         "nu exista clienti asa de dedicati\n")

        repo_i.adaugare_inchiriere(Inchirieri(2, 3))
        repo_i.adaugare_inchiriere(Inchirieri(2, 2))
        repo_i.adaugare_inchiriere(Inchirieri(5, 1))
        repo_i.adaugare_inchiriere(Inchirieri(5, 2))
        repo_i.adaugare_inchiriere(Inchirieri(1, 4))
        repo_i.adaugare_inchiriere(Inchirieri(1, 2))

        clienti_dto = service_1.clienti_cu_cele_mai_multe_inchirieri()
        self.assertEqual(len(clienti_dto), 1)

        clienti_dto_solutie = [Client_DTO(2, "Chiorean", 3)]

        self.assertEqual(clienti_dto, clienti_dto_solutie)


    def test_bubble_sort(self):
        repo_c = repo_client()
        repo_f = repo_film()
        repo_i = repo_inchirieri()

        service_1 = service_inchirieri(None, repo_i, repo_c, repo_f)

        clienti_inchirieri = [
            Client_DTO(1, "Popescu", 3),
            Client_DTO(2, "Chiorean", 5),
            Client_DTO(3, "Oancea", 2)
        ]

        lista_sortata = service_1.bubble_sort(clienti_inchirieri,key = lambda x:x.get_nume_client())
        self.assertEqual(lista_sortata[0].nume_client, "Chiorean")
        self.assertEqual(lista_sortata[1].nume_client, "Oancea")
        self.assertEqual(lista_sortata[2].nume_client, "Popescu")
        self.assertEqual(lista_sortata[0].nr_inchirieri, 5)


    def test_shell_sort(self):
        repo_c = repo_client()
        repo_f = repo_film()
        repo_i = repo_inchirieri()

        service_1 = service_inchirieri(None, repo_i, repo_c, repo_f)

        clienti_inchirieri = [
            Client_DTO(1, "Popescu", 3),
            Client_DTO(2, "Chiorean", 5),
            Client_DTO(3, "Oancea", 2)
        ]

        lista_sortata = service_1.shell_sort(clienti_inchirieri, key=lambda x: (x.get_nume_client()))
        self.assertEqual(lista_sortata[0].nume_client, "Chiorean")
        self.assertEqual(lista_sortata[1].nume_client, "Oancea")
        self.assertEqual(lista_sortata[2].nume_client, "Popescu")
        self.assertEqual(lista_sortata[0].nr_inchirieri, 5)



class TestInchirieriFile(unittest.TestCase):

    def setUp(self):
        repo_f = repo_film_file("D:\\Python\\Pycharm\\Programs\\Laborator 7-9\\Eu\\testare\\test_filme.txt")
        repo_f.vector = []
        repo_f.vector.append(Film(1, "Se7en", "Thriller", "Film fain"))
        repo_f.vector.append(Film(2, "Hangover", "Comedy", "Film kinda fain"))
        repo_f.vector.append(Film(3, "The Godfather", "Crime", "Film foarte fain"))

        repo_c = repo_client_file("D:\\Python\\Pycharm\\Programs\\Laborator 7-9\\Eu\\testare\\test_clienti.txt")
        repo_c.vector = []
        repo_c.vector.append(Client(1, "Popescu", "5041118082209"))
        repo_c.vector.append(Client(2, "Chiorean", "40506124082209"))
        repo_c.vector.append(Client(3, "Oancea", "5051212082209"))

        repo_i = repo_inchirieri_file("D:\\Python\\Pycharm\\Programs\\Laborator 7-9\\Eu\\testare\\test_inchirieri.txt")
        repo_i._vector = []
        repo_i._vector.append(Inchirieri(3, 1))
        repo_i._vector.append(Inchirieri(2, 2))
        repo_i._vector.append(Inchirieri(3, 2))

        repo_f.scriere_in_fisier()
        repo_c.scriere_in_fisier()
        repo_i.scriere_in_fisier()


    def tearDown(self):
        repo_f = repo_film_file("D:\\Python\\Pycharm\\Programs\\Laborator 7-9\\Eu\\testare\\test_filme.txt")
        repo_f.vector = []

        repo_c = repo_client_file("D:\\Python\\Pycharm\\Programs\\Laborator 7-9\\Eu\\testare\\test_clienti.txt")
        repo_c.vector = []

        repo_i = repo_inchirieri_file("D:\\Python\\Pycharm\\Programs\\Laborator 7-9\\Eu\\testare\\test_inchirieri.txt")
        repo_i._vector = []

        repo_f.scriere_in_fisier()
        repo_c.scriere_in_fisier()
        repo_i.scriere_in_fisier()


    def testare_adaugare_validare_inchirieri(self):
        rep_filme = repo_film_file("D:\\Python\\Pycharm\\Programs\\Laborator 7-9\\Eu\\testare\\test_filme.txt")
        rep_clienti = repo_client_file("D:\\Python\\Pycharm\\Programs\\Laborator 7-9\\Eu\\testare\\test_clienti.txt")
        rep_inchirieri = repo_inchirieri_file("D:\\Python\\Pycharm\\Programs\\Laborator 7-9\\Eu\\testare\\test_inchirieri.txt")

        validator = validare_inchiriere()
        service_1 = service_inchirieri(validator, rep_inchirieri, rep_clienti, rep_filme)

        service_1.adaugare_validare_inchiriere(1,1)

        self.assertEqual(rep_inchirieri._length, 4)
        self.assertEqual(rep_inchirieri._vector[0], Inchirieri(3, 1))
        self.assertEqual(rep_inchirieri._vector[1], Inchirieri(2, 2))
        self.assertEqual(rep_inchirieri._vector[2], Inchirieri(3, 2))
        self.assertEqual(rep_inchirieri._vector[3], Inchirieri(1, 1))

        service_1.adaugare_validare_inchiriere(2,1)
        self.assertEqual(rep_inchirieri._length, 5)
        self.assertEqual(rep_inchirieri._vector[0], Inchirieri(3, 1))
        self.assertEqual(rep_inchirieri._vector[1], Inchirieri(2, 2))
        self.assertEqual(rep_inchirieri._vector[2], Inchirieri(3, 2))
        self.assertEqual(rep_inchirieri._vector[3], Inchirieri(1, 1))
        self.assertEqual(rep_inchirieri._vector[4], Inchirieri(2, 1))

        with self.assertRaises(ValidationError) as context:
            service_1.adaugare_validare_inchiriere(-3, -5)

        self.assertEqual(str(context.exception),
                         "id-ul clientului nu poate fi negativ \nid-ul filmului nu poate fi negativ \n")

        with self.assertRaises(RepoError) as context:
            service_1.adaugare_validare_inchiriere(1, 1)

        self.assertEqual(str(context.exception),
                         "clientul a inchiriat deja filmul\n")

        with self.assertRaises(ExistentialError) as context:
            service_1.adaugare_validare_inchiriere(10, 10)
        self.assertEqual(str(context.exception),
                         "clientul caruia ii atribuiti inchirierea nu exista \nfilmul nu exista \n")


    def test_returnare_validare_film(self):
        rep_filme = repo_film_file("D:\\Python\\Pycharm\\Programs\\Laborator 7-9\\Eu\\testare\\test_filme.txt")
        rep_clienti = repo_client_file("D:\\Python\\Pycharm\\Programs\\Laborator 7-9\\Eu\\testare\\test_clienti.txt")
        rep_inchirieri = repo_inchirieri_file("D:\\Python\\Pycharm\\Programs\\Laborator 7-9\\Eu\\testare\\test_inchirieri.txt")

        validator = validare_inchiriere()
        service_1 = service_inchirieri(validator, rep_inchirieri, rep_clienti, rep_filme)

        id_client = 1
        id_film = 2

        id_client_invalid = -1
        id_film_invalid = -2

        id_client_inexistent = 6
        id_film_inexistent = 4

        with self.assertRaises(RepoError) as context:
            service_1.returnare_validare_film(id_film, id_client)

        self.assertEqual(str(context.exception),
                         "nu s-a gasit o astfel de inchiriere incompleta\n")

        service_1.adaugare_validare_inchiriere(id_film, id_client)
        service_1.adaugare_validare_inchiriere(1, 2)

        self.assertEqual(rep_inchirieri._vector[0].get_status(), "incompleta")
        self.assertEqual(rep_inchirieri._vector[1].get_status(), "incompleta")
        self.assertEqual(rep_inchirieri._vector[2].get_status(), "incompleta")
        self.assertEqual(rep_inchirieri._vector[3].get_status(), "incompleta")
        self.assertEqual(rep_inchirieri._vector[4].get_status(), "incompleta")

        service_1.returnare_validare_film(2, 1)
        self.assertEqual(rep_inchirieri._vector[0].get_status(), "incompleta")
        self.assertEqual(rep_inchirieri._vector[1].get_status(), "incompleta")
        self.assertEqual(rep_inchirieri._vector[2].get_status(), "incompleta")
        self.assertEqual(rep_inchirieri._vector[3].get_status(), "completa")
        self.assertEqual(rep_inchirieri._vector[4].get_status(), "incompleta")

        with self.assertRaises(ValidationError) as context:
            service_1.returnare_validare_film(id_film_invalid, id_client_invalid)

        self.assertEqual(str(context.exception),
                         "id-ul clientului nu poate fi negativ \nid-ul filmului nu poate fi negativ \n")

        with self.assertRaises(ExistentialError) as context:
            service_1.returnare_validare_film(id_film_inexistent, id_client_inexistent)

        self.assertEqual(str(context.exception),
                         "clientul caruia ii atribuiti returnarea nu exista \nfilmul nu exista \n")


    def test_sortare_clienti_dupa_nume_si_nr_inchirieri(self):
        rep_filme = repo_film_file("D:\\Python\\Pycharm\\Programs\\Laborator 7-9\\Eu\\testare\\test_filme.txt")
        rep_clienti = repo_client_file("D:\\Python\\Pycharm\\Programs\\Laborator 7-9\\Eu\\testare\\test_clienti.txt")
        rep_inchirieri = repo_inchirieri_file("D:\\Python\\Pycharm\\Programs\\Laborator 7-9\\Eu\\testare\\test_inchirieri.txt")

        service_1 = service_inchirieri(None, rep_inchirieri, rep_clienti, rep_filme)

        clienti_inchirieri = {
            1: Client_DTO(1, "Popescu", 3),
            2: Client_DTO(2, "Chiorean", 5),
            3: Client_DTO(3, "Oancea", 2)
        }

        lista_sortata = service_1.sortare_clienti_dupa_nume_si_nr_inchirieri(clienti_inchirieri)
        self.assertEqual(lista_sortata[0].nume_client, "Chiorean")
        self.assertEqual(lista_sortata[1].nume_client, "Oancea")
        self.assertEqual(lista_sortata[2].nume_client, "Popescu")
        self.assertEqual(lista_sortata[0].nr_inchirieri, 5)


    def test_clienti_cu_filme_inchiriate(self):
        rep_filme = repo_film_file("D:\\Python\\Pycharm\\Programs\\Laborator 7-9\\Eu\\testare\\test_filme.txt")
        rep_clienti = repo_client_file("D:\\Python\\Pycharm\\Programs\\Laborator 7-9\\Eu\\testare\\test_clienti.txt")
        rep_inchirieri = repo_inchirieri_file("D:\\Python\\Pycharm\\Programs\\Laborator 7-9\\Eu\\testare\\test_inchirieri.txt")

        service_1 = service_inchirieri(None, rep_inchirieri, rep_clienti, rep_filme)

        rep_clienti.adauga_client(Client(4, "Tarlea", "5051226082209"))

        rep_filme.adauga_film(Film(4, "The Shawshank Redemption", "Drama", "Film feel-good"))
        rep_filme.adauga_film(Film(5, "Transformers", "Actiune", "Film wow"))

        with self.assertRaises(ExistentialError) as context:
            clienti_dto = service_1.clienti_cu_filme_inchiriate()

        self.assertEqual(str(context.exception),
                         "nu exista inchirieri incomplete\n")

        rep_inchirieri.adaugare_inchiriere(Inchirieri(5, 3))

        clienti_dto = service_1.clienti_cu_filme_inchiriate()

        self.assertEqual(len(clienti_dto), 3)

        client_dto_solutie = [Client_DTO(2, "Chiorean", 2),
                              Client_DTO(3, "Oancea", 1),
                              Client_DTO(1, "Popescu", 1)]

        self.assertEqual(clienti_dto, client_dto_solutie)

    def test_top_3_filme(self):
        rep_filme = repo_film_file("D:\\Python\\Pycharm\\Programs\\Laborator 7-9\\Eu\\testare\\test_filme.txt")
        rep_clienti = repo_client_file("D:\\Python\\Pycharm\\Programs\\Laborator 7-9\\Eu\\testare\\test_clienti.txt")
        rep_inchirieri = repo_inchirieri_file("D:\\Python\\Pycharm\\Programs\\Laborator 7-9\\Eu\\testare\\test_inchirieri.txt")

        service_1 = service_inchirieri(None, rep_inchirieri, rep_clienti, rep_filme)

        filme_dto = {1: Film_DTO(1, "Se7en", 3),
                     2: Film_DTO(2, "Hangover", 5),
                     3: Film_DTO(3, "The Godfather", 2),
                     4: Film_DTO(4, "The Shawshank Redemption", 5),
                     5: Film_DTO(5, "Transformers", 2), }

        rezultat = service_1.top_3_filme(filme_dto)
        self.assertEqual(len(rezultat), 3)

        solutie = [Film_DTO(2, "Hangover", 5),
                   Film_DTO(4, "The Shawshank Redemption", 5),
                   Film_DTO(1, "Se7en", 3)]

        self.assertEqual(rezultat, solutie)

    def test_filme_cele_mai_inchiriate(self):
        rep_filme = repo_film_file("D:\\Python\\Pycharm\\Programs\\Laborator 7-9\\Eu\\testare\\test_filme.txt")
        rep_clienti = repo_client_file("D:\\Python\\Pycharm\\Programs\\Laborator 7-9\\Eu\\testare\\test_clienti.txt")
        rep_inchirieri = repo_inchirieri_file("D:\\Python\\Pycharm\\Programs\\Laborator 7-9\\Eu\\testare\\test_inchirieri.txt")

        service_1 = service_inchirieri(None, rep_inchirieri, rep_clienti, rep_filme)

        rep_clienti.adauga_client(Client(4, "Tarlea", "5051226082209"))

        rep_filme.adauga_film(Film(4, "The Shawshank Redemption", "Drama", "Film feel-good"))
        rep_filme.adauga_film(Film(5, "Transformers", "Actiune", "Film wow"))

        with self.assertRaises(ExistentialError) as context:
            clienti_dto = service_1.filme_cele_mai_inchiriate()

        self.assertEqual(str(context.exception),
                         "nu exista inchirieri de filme\n")

        rep_inchirieri.adaugare_inchiriere(Inchirieri(5, 1))
        rep_inchirieri.adaugare_inchiriere(Inchirieri(1, 2))
        rep_inchirieri.adaugare_inchiriere(Inchirieri(1, 4))
        rep_inchirieri.adaugare_inchiriere(Inchirieri(1, 3))

        filme_dto = service_1.filme_cele_mai_inchiriate()
        self.assertEqual(len(filme_dto), 3)

        filme_dto_solutie = [Film_DTO(1, "Se7en", 3),
                             Film_DTO(3, "The Godfather", 2),
                             Film_DTO(2, "Hangover", 1)]

        self.assertEqual(filme_dto, filme_dto_solutie)

    def test_sortare_clienti_dupa_nr_inchirieri(self):
        rep_filme = repo_film_file("D:\\Python\\Pycharm\\Programs\\Laborator 7-9\\Eu\\testare\\test_filme.txt")
        rep_clienti = repo_client_file("D:\\Python\\Pycharm\\Programs\\Laborator 7-9\\Eu\\testare\\test_clienti.txt")
        rep_inchirieri = repo_inchirieri_file("D:\\Python\\Pycharm\\Programs\\Laborator 7-9\\Eu\\testare\\test_inchirieri.txt")

        service_1 = service_inchirieri(None, rep_inchirieri, rep_clienti, rep_filme)

        clienti_inchirieri = {
            1: Client_DTO(1, "Popescu", 3),
            2: Client_DTO(2, "Chiorean", 5),
            3: Client_DTO(3, "Oancea", 2)
        }

        lista_sortata = service_1.sortare_clienti_dupa_nr_inchirieri(clienti_inchirieri)
        self.assertEqual(lista_sortata[0].nume_client, "Chiorean")
        self.assertEqual(lista_sortata[1].nume_client, "Popescu")
        self.assertEqual(lista_sortata[2].nume_client, "Oancea")
        self.assertEqual(lista_sortata[0].nr_inchirieri, 5)

    def test_top_30_clienti(self):
        rep_filme = repo_film_file("D:\\Python\\Pycharm\\Programs\\Laborator 7-9\\Eu\\testare\\test_filme.txt")
        rep_clienti = repo_client_file("D:\\Python\\Pycharm\\Programs\\Laborator 7-9\\Eu\\testare\\test_clienti.txt")
        rep_inchirieri = repo_inchirieri_file("D:\\Python\\Pycharm\\Programs\\Laborator 7-9\\Eu\\testare\\test_inchirieri.txt")

        service_1 = service_inchirieri(None, rep_inchirieri, rep_clienti, rep_filme)

        clienti_dto = {1: Client_DTO(1, "Popescu", 3),
                       2: Client_DTO(2, "Chiorean", 5),
                       3: Client_DTO(3, "Oancea", 2),
                       4: Client_DTO(4, "Tarlea", 5),
                       5: Client_DTO(5, "Bedea", 2)}

        rezultat = service_1.top_30_clienti(clienti_dto)
        self.assertEqual(len(clienti_dto), 5)

        solutie = [Client_DTO(2, "Chiorean", 5)]

        self.assertEqual(rezultat, solutie)

    def test_clienti_cu_cele_mai_multe_inchirieri(self):
        rep_filme = repo_film_file("D:\\Python\\Pycharm\\Programs\\Laborator 7-9\\Eu\\testare\\test_filme.txt")
        rep_clienti = repo_client_file("D:\\Python\\Pycharm\\Programs\\Laborator 7-9\\Eu\\testare\\test_clienti.txt")
        rep_inchirieri = repo_inchirieri_file("D:\\Python\\Pycharm\\Programs\\Laborator 7-9\\Eu\\testare\\test_inchirieri.txt")

        service_1 = service_inchirieri(None, rep_inchirieri, rep_clienti, rep_filme)

        rep_clienti.adauga_client(Client(4, "Tarlea", "5051226082209"))
        rep_clienti.adauga_client(Client(5, "Bedea", "5050810082209"))
        rep_clienti.adauga_client(Client(6, "Moldovan", "060104082209"))
        rep_clienti.adauga_client(Client(7, "Czako", "5050617082209"))

        rep_filme.adauga_film(Film(4, "The Shawshank Redemption", "Drama", "Film feel-good"))
        rep_filme.adauga_film(Film(5, "Transformers", "Actiune", "Film wow"))

        with self.assertRaises(ExistentialError) as context:
            clienti_dto = service_1.clienti_cu_filme_inchiriate()

        self.assertEqual(str(context.exception),
                         "nu exista inchirieri incomplete\n")

        rep_inchirieri.adaugare_inchiriere(Inchirieri(5, 1))
        rep_inchirieri.adaugare_inchiriere(Inchirieri(5, 2))
        rep_inchirieri.adaugare_inchiriere(Inchirieri(1, 4))
        rep_inchirieri.adaugare_inchiriere(Inchirieri(1, 2))

        clienti_dto = service_1.clienti_cu_cele_mai_multe_inchirieri()
        self.assertEqual(len(clienti_dto), 2)

        clienti_dto_solutie = [Client_DTO(2, "Chiorean", 4),
                               Client_DTO(1, "Popescu", 2)]

        self.assertEqual(clienti_dto, clienti_dto_solutie)

    def testare_minim_3_filme_inchiriate(self):
        rep_filme = repo_film_file("D:\\Python\\Pycharm\\Programs\\Laborator 7-9\\Eu\\testare\\test_filme.txt")
        rep_clienti = repo_client_file("D:\\Python\\Pycharm\\Programs\\Laborator 7-9\\Eu\\testare\\test_clienti.txt")
        rep_inchirieri = repo_inchirieri_file("D:\\Python\\Pycharm\\Programs\\Laborator 7-9\\Eu\\testare\\test_inchirieri.txt")

        service_1 = service_inchirieri(None, rep_inchirieri, rep_clienti, rep_filme)

        clienti_inchirieri = {
            1: Client_DTO(1, "Popescu", 7),
            2: Client_DTO(2, "Chiorean", 2),
            3: Client_DTO(3, "Oancea", 9),
            4: Client_DTO(4, "Tarlea", 3)}

        rezultat = service_1.minim_3_filme_inchiriate(clienti_inchirieri)
        self.assertEqual(len(rezultat), 3)

        solutie = [Client_DTO(1, "Popescu", 7),
                   Client_DTO(3, "Oancea", 9),
                   Client_DTO(4, "Tarlea", 3)]

        self.assertEqual(rezultat, solutie)

    def test_clienti_cu_peste_3_filme_inchiriate(self):
        rep_filme = repo_film_file("D:\\Python\\Pycharm\\Programs\\Laborator 7-9\\Eu\\testare\\test_filme.txt")
        rep_clienti = repo_client_file("D:\\Python\\Pycharm\\Programs\\Laborator 7-9\\Eu\\testare\\test_clienti.txt")
        rep_inchirieri = repo_inchirieri_file("D:\\Python\\Pycharm\\Programs\\Laborator 7-9\\Eu\\testare\\test_inchirieri.txt")

        service_1 = service_inchirieri(None, rep_inchirieri, rep_clienti, rep_filme)

        rep_clienti.adauga_client(Client(4, "Tarlea", "5051226082209"))

        rep_filme.adauga_film(Film(4, "The Shawshank Redemption", "Drama", "Film feel-good"))
        rep_filme.adauga_film(Film(5, "Transformers", "Actiune", "Film wow"))

        with self.assertRaises(ExistentialError) as context:
            clienti_dto = service_1.clienti_cu_peste_3_filme_inchiriate()

        self.assertEqual(str(context.exception),
                         "nu exista inchirieri incomplete\n")

        rep_inchirieri.adaugare_inchiriere(Inchirieri(1, 1))

        with self.assertRaises(ExistentialError) as context:
            clienti_dto = service_1.clienti_cu_peste_3_filme_inchiriate()

        self.assertEqual(str(context.exception),
                         "nu exista clienti asa de dedicati\n")

        rep_inchirieri.adaugare_inchiriere(Inchirieri(5, 2))
        rep_inchirieri.adaugare_inchiriere(Inchirieri(1, 4))
        rep_inchirieri.adaugare_inchiriere(Inchirieri(1, 2))

        clienti_dto = service_1.clienti_cu_cele_mai_multe_inchirieri()
        self.assertEqual(len(clienti_dto), 1)

        clienti_dto_solutie = [Client_DTO(2, "Chiorean", 4)]

        self.assertEqual(clienti_dto, clienti_dto_solutie)

    def test_bubble_sort(self):
        rep_filme = repo_film_file("D:\\Python\\Pycharm\\Programs\\Laborator 7-9\\Eu\\testare\\test_filme.txt")
        rep_clienti = repo_client_file("D:\\Python\\Pycharm\\Programs\\Laborator 7-9\\Eu\\testare\\test_clienti.txt")
        rep_inchirieri = repo_inchirieri_file(
            "D:\\Python\\Pycharm\\Programs\\Laborator 7-9\\Eu\\testare\\test_inchirieri.txt")

        service_1 = service_inchirieri(None, rep_inchirieri, rep_clienti, rep_filme)

        clienti_inchirieri = [
            Client_DTO(1, "Popescu", 3),
            Client_DTO(2, "Chiorean", 5),
            Client_DTO(3, "Oancea", 2)
        ]

        lista_sortata = service_1.bubble_sort(clienti_inchirieri, key=lambda x: x.get_nume_client())
        self.assertEqual(lista_sortata[0].nume_client, "Chiorean")
        self.assertEqual(lista_sortata[1].nume_client, "Oancea")
        self.assertEqual(lista_sortata[2].nume_client, "Popescu")
        self.assertEqual(lista_sortata[0].nr_inchirieri, 5)

    def test_shell_sort(self):
        rep_filme = repo_film_file("D:\\Python\\Pycharm\\Programs\\Laborator 7-9\\Eu\\testare\\test_filme.txt")
        rep_clienti = repo_client_file("D:\\Python\\Pycharm\\Programs\\Laborator 7-9\\Eu\\testare\\test_clienti.txt")
        rep_inchirieri = repo_inchirieri_file(
            "D:\\Python\\Pycharm\\Programs\\Laborator 7-9\\Eu\\testare\\test_inchirieri.txt")

        service_1 = service_inchirieri(None, rep_inchirieri, rep_clienti, rep_filme)

        clienti_inchirieri = [
            Client_DTO(1, "Popescu", 3),
            Client_DTO(2, "Chiorean", 5),
            Client_DTO(3, "Oancea", 2)
        ]

        lista_sortata = service_1.shell_sort(clienti_inchirieri, key=lambda x: (x.get_nume_client()))
        self.assertEqual(lista_sortata[0].nume_client, "Chiorean")
        self.assertEqual(lista_sortata[1].nume_client, "Oancea")
        self.assertEqual(lista_sortata[2].nume_client, "Popescu")
        self.assertEqual(lista_sortata[0].nr_inchirieri, 5)


if __name__ == '__main__':
    unittest.main()