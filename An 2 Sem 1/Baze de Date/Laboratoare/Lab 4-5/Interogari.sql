--			==== LAB 2 ====

--Adaugarea unor inregistrari noi in tabelul Regizori
INSERT INTO Regizori VALUES ('Quentin Tarantino', 40, 15)  --1
INSERT INTO Regizori VALUES ('Steven Spielberg', 50, 30)  --2
INSERT INTO Regizori VALUES ('Christopher Nolan', 45, 10)  --3
INSERT INTO Regizori VALUES ('Luc Besson', 55, 5)  --4
INSERT INTO Regizori VALUES ('Tim Burton', 54, 32)  --5
INSERT INTO Regizori VALUES ('James Gunn', 56, 13)  --6 
INSERT INTO Regizori VALUES ('Charles Laughton', 126, 1)  --7
INSERT INTO Regizori VALUES ('David Fincher', 22, 59)  --8
INSERT INTO Regizori VALUES ('Francis Ford Coppola', 70, 40)  --9
INSERT INTO Regizori VALUES ('George Lucas', 80, 6)  --10

--Adaugarea unor inregistrari noi in tabelul Compozitori
INSERT INTO Compozitori VALUES ('John Williams', 90, 'Violoncel')  --1
INSERT INTO Compozitori VALUES ('Hans Zimmer', 80, 'Pian')  --2
INSERT INTO Compozitori VALUES ('Howard Shore', 85, 'Trompeta')  --3
INSERT INTO Compozitori VALUES ('Danny Elfman', 60, 'Fluier')  --4
INSERT INTO Compozitori VALUES ('Ennio Morricone', 95, 'Elastic')  --5
INSERT INTO Compozitori VALUES ('James Horner', 50, 'Voce')  --6
INSERT INTO Compozitori VALUES ('Ludwig Goransson', 40, 'Chitara')  --7
INSERT INTO Compozitori VALUES ('Mozart',269 , 'Vioara')  --8
INSERT INTO Compozitori VALUES ('Nino Rota', 114, 'Pian')  --9
INSERT INTO Compozitori VALUES ('Thomas Newman', 45, 'Xilofon')  --10

--Adaugarea unor inregistrari noi in tabelul Actori
INSERT INTO Actori VALUES ('Leonardo DiCaprio', 40, 200)  --1
INSERT INTO Actori VALUES ('Christian Bale', 41, 150)  --2
INSERT INTO Actori VALUES ('Arnold Schwartzeneger', 60, 1000)  --3
INSERT INTO Actori VALUES ('Brad Pitt', 50, 750)  --4
INSERT INTO Actori VALUES ('Johnny Depp', 60, 860)  --5
INSERT INTO Actori VALUES ('Will Smith', 55, 1050)  --6
INSERT INTO Actori VALUES ('Henry Fonda', 120, 240)  --7
INSERT INTO Actori VALUES ('Heath Ledger', 48, 50)  --8
INSERT INTO Actori VALUES ('Willem Dafoe', 76, 1500)  --9
INSERT INTO Actori VALUES ('Robert Pattison', 30, 430)  --10

--Adaugarea unor inregistrari noi in tabelul Filme
INSERT INTO Filme VALUES ('Once upon a time... in Hollywood', '02:41:00', 'Period Drama', 1, 5)  --1
INSERT INTO Filme VALUES ('Batman Begins', '02:20:00', 'Superhero Action Epic', 3, 2)  --2
INSERT INTO Filme VALUES ('Inception', '02:28:00', 'Action Epic', 3, 2)  --3
INSERT INTO Filme VALUES ('Edward Scissorhands', '01:25:00', 'Dark Fantasy', 5, 4)  --4
INSERT INTO Filme VALUES ('Fight Club', '02:19:00', 'Dark Comedy', 8, NULL)  --5
INSERT INTO Filme VALUES ('Superman', '02:09:00', 'Superhero Action Epic', 6, NULL)  --6
INSERT INTO Filme VALUES ('Titanic', '02:19:00', 'Romance', NULL, 6)  --7
INSERT INTO Filme VALUES ('Schindlers list', '02:15:00', 'Docudrama', 2, 1)  --8
INSERT INTO Filme VALUES ('The Lord of the Rings: The Return of the King', '03:21:00', 'Adventure Epic', NULL, 3)  --9
INSERT INTO Filme VALUES ('The Godfather', '02:55:00', 'Gangster', 9, 9)  --10

--Adaugarea unor inregistrari noi in tabelul Utilizatori
INSERT INTO Utilizatori VALUES ('ClownsAreCreepy', 20, 'Romania')  --1
INSERT INTO Utilizatori VALUES ('Agressive-Ente', 20, 'Germania')  --2
INSERT INTO Utilizatori VALUES ('B0nk', 20, 'Romania')  --3
INSERT INTO Utilizatori VALUES ('antony', 20, 'Sudeia')  --4
INSERT INTO Utilizatori VALUES ('Nicoltina', 19, 'Romania')  --5
INSERT INTO Utilizatori VALUES ('geo_mommy', 20, 'Italia')  --6
INSERT INTO Utilizatori VALUES ('the_angel', 20, 'Romania')  --7
INSERT INTO Utilizatori VALUES ('alexinio', 19, 'Romania')  --8
INSERT INTO Utilizatori VALUES ('DarkLion641314', 22, 'Moldova')  --9
INSERT INTO Utilizatori VALUES ('klin', 20, 'Romania')  --10

--Adaugarea unor inregistrari noi in tabelul Recenzii
INSERT INTO Recenzii VALUES (1, 1, 7, 'Kinda overrated imo ngl')  --1
INSERT INTO Recenzii VALUES (8, 5, 9, 'OMG CE FRUMOS !!!!!!!!!!! am plans')  --2
INSERT INTO Recenzii VALUES (2, 7, 8, 'Nush nu l-am vazut')  --3
INSERT INTO Recenzii VALUES (6, 5, 10, 'OMG CE FRUMOS !!!!!!!!!!! am plans mult ce sexy e superman')  --4
INSERT INTO Recenzii VALUES (3, 10, 9, 'Ba e fain')  --5
INSERT INTO Recenzii VALUES (4, 7, 10, 'He me frfr its so deep')  --6
INSERT INTO Recenzii VALUES (5, 4, 8, 'Jättebra film, jag såg den på TV.')  --7
INSERT INTO Recenzii VALUES (5, 9, 10, 'So sigma')  --8
INSERT INTO Recenzii VALUES (9, 8, 4, 'Sus')  --9
INSERT INTO Recenzii VALUES (7, 3, 10, 'OMG ME AND DENIS')  --10
INSERT INTO Recenzii VALUES (5, 5, 9, 'O fost fain fight club m-o pus razvan sa ma uit')  --11

--Adaugarea unor inregistrari noi in tabelul Critici_Oficiali
INSERT INTO Critici_Oficiali VALUES (1, 'Intotdeauna are dreptate')
INSERT INTO Critici_Oficiali VALUES (7, 'Crede ca orice edgy pseudointellectual = deep')
INSERT INTO Critici_Oficiali VALUES (10, 'Gusturi bune CATEODATA')

--Adaugarea unor inregistrari noi in tabelul Premii_Oscar
INSERT INTO Premii_Oscar VALUES (1, 'Best Production Design', 2020)  --1
INSERT INTO Premii_Oscar VALUES (3, 'Best Cinematography', 2011)  --2
INSERT INTO Premii_Oscar VALUES (3, 'Best Editing', 2011)  --3
INSERT INTO Premii_Oscar VALUES (7, 'Best Picture', 1998)  --4
INSERT INTO Premii_Oscar VALUES (7, 'Best Director', 1998)  --5
INSERT INTO Premii_Oscar VALUES (7, 'Best Cinematography', 1998)  --6
INSERT INTO Premii_Oscar VALUES (7, 'Best Music', 1998)  --7
INSERT INTO Premii_Oscar VALUES (8, 'Best Picture', 1994)  --8
INSERT INTO Premii_Oscar VALUES (8, 'Best Director', 1994)  --9
INSERT INTO Premii_Oscar VALUES (8, 'Best Cinematography', 1994)  --10
INSERT INTO Premii_Oscar VALUES (9, 'Best Picture', 2004)  --11
INSERT INTO Premii_Oscar VALUES (9, 'Best Director', 2004)  --12
INSERT INTO Premii_Oscar VALUES (9, 'Best Writing', 2004)  --13
INSERT INTO Premii_Oscar VALUES (9, 'Best Editing', 2004)  --14
INSERT INTO Premii_Oscar VALUES (9, 'Best Art Direction', 2004)  --15
INSERT INTO Premii_Oscar VALUES (9, 'Best Costume Design', 2004)  --16
INSERT INTO Premii_Oscar VALUES (9, 'Best Makeup', 2004)  --17
INSERT INTO Premii_Oscar VALUES (9, 'Best Original Score', 2004)  --18
INSERT INTO Premii_Oscar VALUES (9, 'Best Original Song', 2004)  --19
INSERT INTO Premii_Oscar VALUES (9, 'Best Sound Mixing', 2004)  --20
INSERT INTO Premii_Oscar VALUES (9, 'Best Visual Effects', 2004)  --21
INSERT INTO Premii_Oscar VALUES (10, 'Best Picture', 1973)  --22
INSERT INTO Premii_Oscar VALUES (10, 'Best Actor in Leading Role', 1973)  --23

--Adaugarea unor inregistrari noi in tabelul Roluri
INSERT INTO Roluri VALUES (1, 1, 'Leading', 'Rick Dalton')
INSERT INTO Roluri VALUES (1, 4, 'Supporting', 'Cliff Booth')
INSERT INTO Roluri VALUES (2, 2, 'Leading', 'Bruce Wayne')
INSERT INTO Roluri VALUES (3, 1, 'Leading', 'Cobb')
INSERT INTO Roluri VALUES (4, 5, 'Leadin', 'Edward Scissorhands')
INSERT INTO Roluri VALUES (5, 4, 'Supporting', 'Tyler Durden')
INSERT INTO Roluri VALUES (7, 1, 'Leading', 'Jack Dawson')

--Adaugarea unor inregistrari noi in tabelul Firme
INSERT INTO Firme VALUES ('Warner Bros', 'USA') --1
INSERT INTO Firme VALUES ('Universal', 'USA') --2
INSERT INTO Firme VALUES ('20th Century Studios', 'USA') --3
INSERT INTO Firme VALUES ('Petru Popescu Firm', 'Romania') --4
INSERT INTO Firme VALUES ('Paramount', 'USA') --5

--Adaugarea unor inregistrari noi in tabelul Publicatii
INSERT INTO Publicatii VALUES (2,1)
INSERT INTO Publicatii VALUES (3,1)
INSERT INTO Publicatii VALUES (4,3)
INSERT INTO Publicatii VALUES (5,3)
INSERT INTO Publicatii VALUES (7,3)
INSERT INTO Publicatii VALUES (7,5)
INSERT INTO Publicatii VALUES (8,2)
INSERT INTO Publicatii VALUES (10,5)

--			==== INTEROGATIONS ====
--1. Afiseaza titlul filmului, numele regizorului si numele compozitorului pentru filme cu durata mai mare de 2 ore jumate
SELECT F.titlu, R.nume AS regizor, C.nume AS compozitor FROM Filme F
INNER JOIN Regizori R ON F.id_regizor = R.id_r
INNER JOIN Compozitori C ON F.id_compozitor = C.id_c
WHERE F.durata > '02:30:00'

--2. Pentru fiecare firma din SUA, afiseaza numele firmei si genurile DISTINCTE ale filmelor pe care le-a publicat
SELECT DISTINCT Fir.nume, Fil.gen FROM Firme Fir
INNER JOIN Publicatii P ON P.id_firma = Fir.id_f
INNER JOIN Filme Fil ON P.id_film = Fil.id_f
WHERE Fir.tara_origine = 'USA'

--3. Calculeaza media notelor per regizor (nume regizor, medie), dar afiseaza doar regizorii cu cel putin 2 recenzii totale
SELECT Reg.nume, AVG(Rec.nota) FROM Regizori Reg
INNER JOIN Filme F ON F.id_regizor = Reg.id_r
INNER JOIN Recenzii Rec ON Rec.id_film = F.id_f
GROUP BY Reg.id_r, Reg.nume
HAVING COUNT(Reg.id_r) >= 2

--4. Pentru fiecare gen cu minim 2 recenzii si nota medie mai mare de 8, aratati titlul filmul, numarul de recenzii si media notelor
SELECT F.titlu, COUNT(F.id_f) AS nr_recenzii, AVG(R.nota) AS media_notelor FROM Filme F
INNER JOIN Recenzii R ON R.id_film = F.id_f
GROUP BY F.id_f, F.titlu
HAVING COUNT(F.id_f) >= 2 AND AVG(R.nota) >= 8

--5. Afiseaza numele criticilor, numarul de recenzii si media notelor care au cel putin o recenzie
SELECT U.nume, COUNT(U.id_u) AS nr_recenzii, AVG(R.nota) AS media_notelor FROM Critici_Oficiali C
INNER JOIN Utilizatori U ON C.id_u = U.id_u
INNER JOIN Recenzii R ON R.id_utilizator = U.id_u
GROUP BY U.id_u, U.nume

--6. Afisati numele tarile distincte ale utilizatorilor care au dat recenzii la filme cu durata de peste 3 ore
SELECT DISTINCT U.tara_de_origine FROM Utilizatori U
INNER JOIN Recenzii R ON R.id_utilizator = U.id_u
INNER JOIN Filme F ON R.id_film = F.id_f
WHERE F.durata > '03:00:00'

--7. Pentru fiecare actor, afiseaza numele actorului si numarul de rolui 'Leading' pe care le are
SELECT A.nume, COUNT(R.id_actor) AS roluli_principale FROM Actori A
INNER JOIN Roluri R ON R.id_actor = A.id_a
WHERE R.tip = 'Leading'
GROUP BY A.id_a, A.nume

--8. Afiseaza titlul filmelor si numarul de firme care le-a publicat care au fost publicat de minim 2 firme
SELECT Fil.titlu, COUNT(Fil.id_f) AS nr_firme FROM Filme Fil
INNER JOIN Publicatii P ON Fil.id_f = P.id_film
INNER JOIN Firme Fir ON Fir.id_f = P.id_firma
GROUP BY Fil.id_f, Fil.titlu
HAVING COUNT(Fil.id_f) >= 2 

--9. Afiseaza titlul filmului, numele regizorului si numarul total de premii oscar ale filmului ????
SELECT F.titlu, R.nume, COUNT(F.id_f) AS nr_premii FROM Filme F
LEFT JOIN Regizori R ON F.id_regizor = R.id_r
INNER JOIN Premii_Oscar P ON P.id_film = F.id_f
GROUP BY F.id_f, F.titlu, R.nume

--10. Afisati numele compozitorilor cu varsta intre 40 si 100 si media notelor filmelor la care au compus
SELECT C.nume, AVG(R.nota) AS media_notelor FROM Compozitori C
INNER JOIN Filme F ON F.id_compozitor = C.id_c
INNER JOIN Recenzii R ON R.id_film = F.id_f
WHERE C.varsta BETWEEN 40 AND 100
GROUP BY C.id_c, C.nume
