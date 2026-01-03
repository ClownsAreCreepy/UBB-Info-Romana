from infrastructura.repo_clienti_file import repo_client_file
from testare.test_validare import *
from testare.test_repo import *
from testare.test_servicii import *
from prezentare.consola import *


#validator
validator_film=validare_film()
validator_client=validare_client()
validator_inchiriere=validare_inchiriere()

#repository
repository_client_file = repo_client_file("D:\\Python\\Pycharm\\Programs\\Laborator 7-9\\Eu\\Clienti.txt")

repository_client = repo_client()
repository_client.adauga_client(Client(1, "Popescu", "5041118082209"))
repository_client.adauga_client(Client(2, "Chiorean", "6050624245038"))
repository_client.adauga_client(Client(3, "Oancea", "5051212082209"))
repository_client.adauga_client(Client(4, "Tarlea", "5051226082209"))
repository_client.adauga_client(Client(5, "Bedea", "5050810082209"))
repository_client.adauga_client(Client(6, "Moldovan", "060104082209"))
repository_client.adauga_client(Client(7, "Czako", "5050617082209"))
repository_client.adauga_client(Client(8, "Popescu", "6060706082209"))
repository_client.adauga_client(Client(9, "Contz", "5050711082209"))
repository_client.adauga_client(Client(10, "Talanga", "6051013082209"))

repository_film_file = repo_film_file("D:\\Python\\Pycharm\\Programs\\Laborator 7-9\\Eu\\Filme.txt")

repository_film = repo_film()
repository_film.adauga_film(Film(1, "Se7en", "Thriller", "Film fain"))
repository_film.adauga_film(Film(2, "Hangover", "Comedy", "Film kinda fain"))
repository_film.adauga_film(Film(3, "The Godfather", "Crime", "Film foarte fain"))
repository_film.adauga_film(Film(4, "The Shawshank Redemption", "Drama", "Film feel-good"))
repository_film.adauga_film(Film(5, "Transformers", "Actiune", "Film wow"))
repository_film.adauga_film(Film(6, "Everything Everywhere All At Once", "Sci-Fi", "Film damn"))
repository_film.adauga_film(Film(7, "Alien", "Horror", "Film SCARY"))
repository_film.adauga_film(Film(8, "Apocalypse Now", "War", "Film pew-pew"))
repository_film.adauga_film(Film(9, "Fight Club", "Drama", "Film filosofic D:"))
repository_film.adauga_film(Film(10, "Titanic", "Romance", "Film :'( "))

repository_inchirieri_file = repo_inchirieri_file("D:\\Python\\Pycharm\\Programs\\Laborator 7-9\\Eu\\Inchirieri.txt")
repository_inchirieri_file.citire_din_fisier()

repository_inchirieri = repo_inchirieri()
repository_inchirieri.adaugare_inchiriere(Inchirieri(5,2))
repository_inchirieri.adaugare_inchiriere(Inchirieri(6,2))
repository_inchirieri.adaugare_inchiriere(Inchirieri(7,2))
repository_inchirieri.adaugare_inchiriere(Inchirieri(1,1))
repository_inchirieri.adaugare_inchiriere(Inchirieri(9,1))
repository_inchirieri.adaugare_inchiriere(Inchirieri(4,1))
repository_inchirieri.adaugare_inchiriere(Inchirieri(10,4))
repository_inchirieri.adaugare_inchiriere(Inchirieri(3,3))
repository_inchirieri.adaugare_inchiriere(Inchirieri(5,4))
repository_inchirieri.adaugare_inchiriere(Inchirieri(10,9))




#services
serv_client = service_client(validator_client, repository_client)
serv_film = service_film(validator_film, repository_film)
serv_inchirieri = service_inchirieri(validator_inchiriere, repository_inchirieri, repository_client, repository_film)

serv_client_file = service_client(validator_client, repository_client_file)
serv_film_file = service_film(validator_film, repository_film_file)
serv_inchirieri_file = service_inchirieri(validator_inchiriere, repository_inchirieri_file, repository_client_file, repository_film_file)


#consola
ui=Consola(serv_film, serv_client, serv_inchirieri)
#ui=Consola(serv_film_file, serv_client_file, serv_inchirieri_file)
ui.run()

#1234567890123