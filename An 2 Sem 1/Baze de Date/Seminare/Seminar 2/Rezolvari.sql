--Creem baza de date cu parc de distractii
CREATE DATABASE ParcDistractii
GO

USE ParcDistractii

--Creem tabel pentru sectiuni
CREATE TABLE Sectiuni
(
cod_s INT PRIMARY KEY IDENTITY(1,1),
nume NVARCHAR(100),
descriere NVARCHAR(1000)
);

--Creem tabel pentru atractii
CREATE TABLE Atractii
(
cod_a INT PRIMARY KEY IDENTITY(1,1),
nume NVARCHAR(100),
descriere NVARCHAR(1000),
varsta_min INT,
cod_sectiune INT FOREIGN KEY REFERENCES Sectiuni(cod_s) ON UPDATE CASCADE ON DELETE CASCADE
);

--Creem tabel pentru categorii de vizitatori
CREATE TABLE Categorii
(
cod_c INT PRIMARY KEY IDENTITY(1,1),
nume NVARCHAR(100)
);

--Creem tabel pentru vizitatori
CREATE TABLE Vizitatori
(
cod_v INT PRIMARY KEY IDENTITY(1,1),
nume NVARCHAR(100),
email NVARCHAR(100) UNIQUE,
cod_categorii INT FOREIGN KEY REFERENCES Categorii(cod_c) ON UPDATE CASCADE ON DELETE CASCADE
);

--Creem tabel pentru note
CREATE TABLE Note
(
cod_atractii INT,
cod_vizitatori INT,
nota REAL,
CONSTRAINT fk_AtractiiNote FOREIGN KEY (cod_atractii) REFERENCES Atractii(cod_a),
CONSTRAINT fk_VizitatoriNote FOREIGN KEY (cod_vizitatori) REFERENCES Vizitatori(cod_v),
CONSTRAINT pk_Note PRIMARY KEY (cod_atractii, cod_vizitatori),
CONSTRAINT ck_nota CHECK (nota BETWEEN 1 AND 10)
);


--Adaugarea a unor inregistrari noi in tabelul Sectiuni
INSERT INTO Sectiuni (nume, descriere) VALUES ('Sectiunea Centrala', 'Cea mai mare sectiune, cu de toate')
INSERT INTO Sectiuni (nume, descriere) VALUES ('Sectiunea Vest', 'Sectiunea cu mancare')
INSERT INTO Sectiuni (nume, descriere) VALUES ('Sectiunea Nord-Vest', 'Sectiunea cu piscina')
INSERT INTO Sectiuni (nume, descriere) VALUES ('Sectiunea Nord-Est', 'Sectiunea in-door, a doua cea mai mare')
INSERT INTO Sectiuni (nume, descriere) VALUES ('Sectiunea Est', 'Sectiunea cu jocuri unde primesti chestii')
INSERT INTO Sectiuni (nume, descriere) VALUES ('Sectiunea Sud-Est', 'Sectiunea bailor')
INSERT INTO Sectiuni (nume, descriere) VALUES ('Sectiunea Sud-Vest', 'Sectiunea pentru angajati')

--Adaugarea a unor inregistrari noi in tabelul Atractii, fara a mai specifica coloanele tabeluliui
INSERT INTO Atractii VALUES ('Rollercoaster', 'Cel mai rapid din parc', 12, 1)
INSERT INTO Atractii VALUES ('Bungee-Jumping', 'E foarte inalt', 16, 1)
INSERT INTO Atractii VALUES ('Cantina', 'Yum', 0, 2)
INSERT INTO Atractii VALUES ('Laser-Tag', 'Piu piu', 16, 4)
INSERT INTO Atractii VALUES ('Hit the bottles', 'Plusuri ca premii', 12, 5)
INSERT INTO Atractii VALUES ('Topogan cu apa', 'Cazi rapid', 10, 3)
INSERT INTO Atractii VALUES ('Veceu', 'Pentru dupa cantina', 0, 6)

--Adaugarea a unor inregistrari noi in tabelul Categorii
INSERT INTO Categorii VALUES ('Aia inalti')
INSERT INTO Categorii VALUES ('Aia scunzi')
INSERT INTO Categorii VALUES ('Minorii')
INSERT INTO Categorii VALUES ('Aia care nu is buni la info')
INSERT INTO Categorii VALUES ('Bogatii')
INSERT INTO Categorii VALUES ('Aia care mananca mult')
INSERT INTO Categorii VALUES ('Aia care fac pipi in piscina')

--Adaugarea a unor inregistrari noi in tabelul Vizitatori
INSERT INTO Vizitatori VALUES ('Petru', 'petru@gmail.com',2)
INSERT INTO Vizitatori VALUES ('Oana', 'oana@gmail.com',5)
INSERT INTO Vizitatori VALUES ('Dani', 'dani@gmail.com',1)
INSERT INTO Vizitatori VALUES ('Razvan', 'rezvan@gmail.com',7)
INSERT INTO Vizitatori VALUES ('Teo', 'teo@gmail.com',2)
INSERT INTO Vizitatori VALUES ('Miha', 'miha@gmail.com',4)
INSERT INTO Vizitatori VALUES ('Gabi', 'gabi@gmail.com',3)

--Adaugare a unor inregistrai noi in tabelul Note
INSERT INTO Note (cod_vizitatori, cod_atractii, nota) VALUES (1, 2, 10)
INSERT INTO Note (cod_vizitatori, cod_atractii, nota) VALUES (2, 4, 8.5)
INSERT INTO Note (cod_vizitatori, cod_atractii, nota) VALUES (4, 7, 1.8)
INSERT INTO Note (cod_vizitatori, cod_atractii, nota) VALUES (4, 6, 9)
INSERT INTO Note (cod_vizitatori, cod_atractii, nota) VALUES (6, 1, 5)
INSERT INTO Note (cod_vizitatori, cod_atractii, nota) VALUES (3, 5, 7)
INSERT INTO Note (cod_vizitatori, cod_atractii, nota) VALUES (7, 2, 10)


--Actualizam o inregistrare in toate tabelele
--Daca nu punem WHERE, se acualizeaza toate inregistrarile din tabel
UPDATE Sectiuni SET descriere='Cea mai veche sectiune, cu de toate' WHERE nume='Sectiunea Centrala'
UPDATE Atractii SET varsta_min='2' WHERE nume='Cantina'
UPDATE Categorii SET nume='Aia bogati' WHERE nume='Bogatii'
UPDATE Vizitatori SET email='dani@gmail.ro' WHERE cod_v=3
UPDATE Note SET nota=9 WHERE cod_vizitatori=1 and cod_atractii=2


--Stergem inregistrari din tabelele Note si Atractii
--Daca nu punem WHERE, se sterg toate inregistrarile din tabel
--DELETE FROM Sectiuni WHERE nume='Sectiunea Centrala'
DELETE FROM Note WHERE cod_atractii = 6 AND cod_vizitatori = 4
DELETE FROM Atractii WHERE cod_a = 5


--Returnarea tutror inregistrarilor din tabelul Sectiuni
SELECT * FROM Atractii

--Returnarea tuturor inregistrarilor din tabelul Sectiuni, specificand explicit numele coloanelor
SELECT cod_s, nume, descriere FROM Sectiuni

--Returnarea tuturor valorilor distincte din coloana varsta_min din tabelul Atractii
SELECT DISTINCT varsta_min FROM Atractii

--Returnarea numelui si descrierii atractiilor care au varsta minima recomandata egala cu 12
SELECT nume, descriere FROM Atractii WHERE varsta_min = 12

--Returnarea numelui si varstei minime recomandate ale atractiilor care au numele diferit de 'Castelul Negru'
SELECT nume, varsta_min FROM Atractii WHERE nume <> 'Castelul Negru'

--Returnam atractiile care au varsta minima recomandata mai mare sau egala cu 14
SELECT * FROM Atractii WHERE varsta_min <= 14

--Returnam atractiile care au varsta minima recomandata in afara intervalului [14, 18]
SELECT * FROM Atractii WHERE varsta_min NOT BETWEEN 14 AND 18

--Returnam atractiile care au varsta minima recomandata egala cu 12, 14 sau 16
SELECT * FROM Atractii WHERE varsta_min IN (12,14,16)


--Returnam vizitatorii pentru care numele incepe cu litera A
SELECT * FROM Vizitatori WHERE nume LIKE 'A%'

--Returnam vizitatorii pentru care numele se termina cu litera a
SELECT * FROM Vizitatori WHERE nume LIKE '%a'

--Returnam vizitatorii ale caror nume contine ana
SELECT * FROM Vizitatori WHERE nume LIKE '%ana%'

--Returnam vizitatorii ale caror nume se termina cu na si au 3 caractere
-- '%' - 0 sau mai multe caractere
-- '_' - un singur caracter
SELECT * FROM Vizitatori WHERE nume LIKE '_na'

--Returnam vizitatorii ale caror nume incepe cu litera A, B sau C
SELECT * FROM Vizitatori WHERE nume LIKE '[ABC]%'

--Returnam vizitatorii ale caror nume NU incepe cu litera A, B sau C
SELECT * FROM Vizitatori WHERE nume LIKE '[^ABC]%'

--Exercitiu pagina 21
--1. Inregistrarile din Categorii alea caror nume este pensionar sau copii
SELECT * FROM Categorii WHERE nume in ('pensionar', 'copii')

--2. Interogare care aifseaza toate sectiunile care incep cu litera C
SELECT * FROM Sectiuni WHERE nume LIKE 'S%'

--3. Interogare care afiseaza toate sectiunile care incep cu litera n si au cel putin doua caractere
SELECT * FROM Sectiuni WHERE nume LIKE 'N__%'


--Selectam vizitatorii care au email-ul null
SELECT * FROM Vizitatori WHERE email IS NULL


--Extragem numele categoriei, numele vizitatorului si adresa de email pentru toti vizitatorii care apartin unei categorii
--categorie - alias pentru coloana (C.nume)
--C - alias pentru tabel (Categorii)
SELECT C.nume AS categorie, V.nume, V.email FROM Categorii C, Vizitatori V WHERE C.cod_c = V.cod_categorii

--Interogarea poate fi rescrisa cu INNER JOIN
SELECT C.nume AS categorie, V.nume, V.email FROM Categorii C 
INNER JOIN Vizitatori V ON C.cod_c = V.cod_categorii

--Afisam numele categoriilor si adresa de email a vizitatorilor, incluzand si categoriile care nu au vizitatori asociati
SELECT C.nume, V.email FROM Categorii C
LEFT JOIN Vizitatori V ON C.cod_c = V.cod_categorii

--Afisam numele categoriilor si adresa de email a vizitatorilor, incluzand si vizitatorii care nu apartin unei categorii
SELECT C.nume, V.email FROM Categorii C
RIGHT JOIN Vizitatori V ON C.cod_c = V.cod_categorii

--Afisam numele categoriilor si adresa de email a vizitatorilor, incluzand atat vizitatorii care nu apartin unei categorii,
--cat si categoriile care nu au vizitatori asociati
SELECT C.nume, V.email FROM Categorii C
FULL JOIN Vizitatori V ON C.cod_c = V.cod_categorii


-- FUNCTII DE AGREGARE
--Se utilizeaza de obicei cu clauzele GROUP BY si HAVING
--Returnam numarul total de inregistrari din tabelul Categorii
SELECT COUNT(*) FROM Categorii

--Afisam numele categoriilor si numarul de vizitatori pentru fiecare categorie care are cel putin un vizitator
SELECT C.nume, COUNT(cod_v) nr_vizitatori FROM Categorii C
INNER JOIN Vizitatori V ON C.cod_c=V.cod_categorii
GROUP BY C.cod_c, C.nume

--Afisam numele categoriilor si numarul de vizitatori pentru fiecare categorie
SELECT C.nume, COUNT(cod_v) nr_vizitatori FROM Categorii C
LEFT JOIN Vizitatori V ON C.cod_c=V.cod_categorii
GROUP BY C.cod_c, C.nume

--Afisam numele atractiei si media aritmetica a notelor primite pentru toate atractiile care au primit note
SELECT A.nume, AVG(nota) medie_note FROM Atractii A
INNER JOIN Note N ON A.cod_a = N.cod_atractii
GROUP BY A.cod_a, A.nume

--Afisam numele atractiei si media aritmetica a notelor primite pentru toate atractiile care au primit note si au media aritmetica > 9
SELECT A.nume, AVG(nota) medie_note FROM Atractii A
INNER JOIN Note N ON A.cod_a = N.cod_atractii
GROUP BY A.cod_a, A.nume
HAVING AVG(nota) > 9


-- SUBINTEROGARI
--Afisam numele tuturor categoriilor care au cel putin un vizitator
SELECT nume FROM Categorii
WHERE cod_c IN ( SELECT cod_categorii FROM Vizitatori )

--Putem rescrie folosind INNER JOIN, dar ne trebe si DISTINCT
SELECT DISTINCT C.nume FROM Categorii C
INNER JOIN Vizitatori V ON C.cod_c = V.cod_categorii

--Putem rescrie si cu EXISTS
--EXISTS returneaza true daca rezultatul subinterogarii contine cel putin o inregistrare
SELECT C.nume FROM Categorii C
WHERE EXISTS ( SELECT * FROM Vizitatori V WHERE V.cod_categorii = C.cod_c)


--Exercitii pagian 32
--1. Afisati toti vizitatorii care nu au dat nicio nota unei atractii
SELECT * FROM Vizitatori V
WHERE V.cod_v NOT IN (SELECT N.cod_vizitatori FROM Note N WHERE N.cod_vizitatori = V.cod_v)

--2. Afisati numele vizitatorilor, nota si numele atractiei evaluate
SELECT V.nume, N.nota, A.nume FROM Note N
INNER JOIN Vizitatori V ON N.cod_vizitatori = V.cod_v
INNER JOIN Atractii A ON N.cod_atractii = A.cod_a

--3. Afiseaza numele vizitatorilor si numarul de note pe care l-au dat atractiilor (cu tot cu cei care nu au dat note)
SELECT V.nume, COUNT(N.cod_vizitatori) FROM Vizitatori V
LEFT JOIN Note N ON N.cod_vizitatori = V.cod_v
GROUP BY V.cod_v, V.nume

--4. Afiseaza valorile distincte ale notelor date atractiilor
SELECT DISTINCT N.nota FROM Note N
INNER JOIN Atractii A ON A.cod_a = N.cod_atractii

--Afisam atractiile care au primit cel putin o data nota 9
SELECT nume FROM Atractii
WHERE cod_a = ANY(SELECT cod_atractii FROM Note WHERE nota = 9)

--Putem sa rescriem cu IN
SELECT nume FROM Atractii
WHERE cod_a IN (SELECT cod_atractii FROM Note WHERE nota = 9)

--Afisam atractiile care NU au primit nota 9
SELECT nume FROM Atractii
WHERE cod_a <> ALL(SELECT cod_atractii FROM Note WHERE nota = 9)
AND cod_a IN (SELECT cod_atractii FROM Note)

--Putem sa rescriem cu NOT IN
SELECT nume FROM Atractii
WHERE cod_a NOT IN (SELECT cod_atractii FROM Note WHERE nota = 9)
AND cod_a IN (SELECT cod_atractii FROM Note)

--Exercitii de la pagina 35
--1. Afiseaza numele sectiunii, numele si descrierea atractiilor pentru toate sectiunile care au cel putin o atractie asociata (cu tot cu alea care nu au o sectiune)
SELECT S.nume, A.nume, A.descriere FROM Sectiuni S
LEFT JOIN Atractii A ON S.cod_s = A.cod_sectiune

--2. Afiseaza numele si varsta minima recomandata a atractiei si numarul de note primite pentru toate atractiile care au primit cel putin 2 note
SELECT A.nume, A.varsta_min, COUNT(A.cod_a) FROM Atractii A
INNER JOIN Note N ON A.cod_a = N.cod_atractii
GROUP BY A.varsta_min, A.nume
HAVING COUNT(A.cod_a) > 1

--3. Afisati numele categoriei, numele vizitatorului, nota, numele si descrierea atractiei pentru toate categoriile care au numele diferit de 'adult' si au vizitatori asociati care au dat cel putin o nota unei atractii
SELECT * FROM Vizitatori V
INNER JOIN Categorii C ON V.cod_categorii=C.cod_c
INNER JOIN Note N ON V.cod_v=N.cod_vizitatori
WHERE C.nume <> 'adult'


--Afisam numele atractiilor care nu au primit niciodata nota 9, dar au primit cel putin o data nota 10
SELECT nume FROM Atractii
WHERE cod_a IN (SELECT cod_atractii FROM NOTE WHERE nota = 10)
EXCEPT
SELECT nume FROM Atractii
WHERE cod_a IN (SELECT cod_atractii FROM Note WHERE nota = 9)

--In loc de except putem sa scriem UNION [ALL] daca am vrea sa aratam atractiile care au primit ori 9 ori 10
--UNION [ALL] va lua duplicate, UNION nu va lua

--In loc de UNION [ALL] putem sa scriem INTERSECT daca am vrea sa aratam atractiile care au primit si 9 si 10

--Exercitii de pe pagina 39
--1. Afisati nota maxima primita de catre fiecare atractie si numele atractiei
SELECT Max(N.nota), A.nume FROM Atractii A
INNER JOIN Note N ON A.cod_a = N.cod_atractii
GROUP BY A.cod_a, A.nume

--2. Afisati nota minima primita de catre fiecare atractie si numele atractiei
SELECT Min(N.nota), A.nume FROM Atractii A
INNER JOIN Note N ON A.cod_a = N.cod_atractii
GROUP BY A.cod_a, A.nume

--3. Afisati numele si adresa de email a vizitatorilor care nu apartin niciunei categorii
SELECT V.nume, V.email FROM Vizitatori V
LEFT JOIN Categorii C ON V.cod_categorii = C.cod_c
WHERE V.cod_categorii IS NULL

--4. Afisati numele si descrierea atractiilor care apartin unei sectiuni (codul de categorie sa nu fie NULL)
SELECT A.nume, A.descriere FROM Atractii A
LEFT JOIN Sectiuni S ON A.cod_sectiune = S.cod_s
WHERE A.cod_sectiune IS NOT NULL
