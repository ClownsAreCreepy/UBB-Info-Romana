CREATE TABLE Legaturi_Eliminate (
	NumeTabelSt NVARCHAR(100),
	IdSt INT,
	NumeTabelDr NVARCHAR(100),
	IdDr INT,
)

-- Select-uri pentru ajutor (DEPRECATED)
SELECT * FROM Regizori
SELECT * FROM Filme f
INNER JOIN Regizori r ON f.id_regizor = r.id_r

-- ============================================================================
-- TRANSFORMARE 1: RELATIA 1:N -> N:1
-- Relatia dintre Regizori (1) si FILME (N)
-- Un regizor are mai multe filme (FK in Filme)
-- Vom inversa directia: Un Film va avea mai multi Regizori (FK in Regizori)
-- Asta inseamna ca mutam cheia externa din tabela 'Filme' in tabela 'Regizori'

-- 1. Adaugarea coloanei noi (viitoarea cheie externa)
-- Adaugam coloana id_film in Regizori. Deocamdata permitem NULL pentru a putea insera datele
ALTER TABLE Regizori
ADD id_film INT

-- 2. Migrarea Datelor (Cea mai mare valoare)
-- Trebuie sa populam Regizori.id_film
-- Problema: Un regizor are filmele cu ID-urile 2 si 3 (Nolan)
-- Solutie: Facem UPDATE cu un subquery care cauta MAX(id_f)

UPDATE Regizori
SET id_film = (
	SELECT MAX(id_f) FROM Filme f
	WHERE f.id_regizor = Regizori.id_r
	)

-- 3. Salvarea datelor pierdute
-- Acum ca Nolan (id 3) este legat de filmul 3, legatura cu filmul 2 vor disparea cand stergem coloana veche din Filme
-- Le salvam

INSERT INTO Legaturi_Eliminate (NumeTabelSt, IdSt, NumeTabelDr, IdDr)
SELECT 'Regizori', id_regizor, 'Filme', id_f FROM Filme f
WHERE id_regizor IS NOT NULL AND id_f <> ( -- Selectam doar filmele care NU au fost alese
	SELECT id_film FROM Regizori r
	WHERE r.id_r = f.id_regizor
)

SELECT * FROM Legaturi_Eliminate


-- 4. Stergere din coloana inainte sa stergem coloana
-- Daca nu, vor ramane mai multe inregistrari care aveau un singur Regizor, unde noi inversam relatia
DELETE FROM Filme
WHERE EXISTS(
	SELECT * FROM Legaturi_Eliminate as ls
	WHERE ls.NumeTabelDr = 'Filme' AND ls.IdDr = Filme.id_f
)

-- 5. Curatienie
-- Acum ca am mutat datele si am salvat istoricul, stergem vechea cheie externa din Filme

-- Intai stergem Constraint-ul
ALTER TABLE Filme
DROP CONSTRAINT fk_RegizorFilm

-- Apoi stergem coloana
ALTER TABLE Filme
DROP COLUMN id_regizor

-- 6. Finalizarea noii structuri
-- Adaugam constrangere de Foreign Key pe tabela Regizori catre Filme

ALTER TABLE Regizori
ADD CONSTRAINT fk_FilmRegizor FOREIGN KEY (id_film) REFERENCES Filme(id_f)

-- 7. Adaugam un film cu mai multi directori pentru a arata schimbarea

SELECT * FROM Regizori
SELECT * FROM Filme f
INNER JOIN Regizori r ON f.id_f = r.id_film


INSERT INTO Filme (titlu, durata, gen, id_compozitor) VALUES ('Twilight zone', '01:41:00', 'Dystopian Sci-fi', NULL)	-- id: 21

INSERT INTO Regizori (nume, varsta, nr_filme_realizate, id_film) VALUES ('George Miller', 80, 12, 21)

UPDATE Regizori SET id_film = 21 WHERE Regizori.id_r = 2 -- Spielberg


-- ============================================================================
-- TRANSFORMARE 2: RELATIA 1:N -> N:M
-- Relatia dintre Compozitori (1) si Filme (N)
-- Un compozitor are mai multe filme, realizata printr-o cheie externa in Filme
-- Transformam in M:N (Mai multi compozitori <-> Mai multe filme)
-- Pentru asta, avem nevoie de un tabel intermediar (Tabela de Legatura)

-- 1. Crearea tabelei de legatura
-- Acest tabel va tine minte perechile (id_film, id_compozitor)
CREATE TABLE Filme_Compozitori_Mix (
	id_film INT NOT NULL,
	id_compozitor INT NOT NULL,

	CONSTRAINT pk_FilmeCompozitori PRIMARY KEY (id_film, id_compozitor),
	CONSTRAINT fk_FilmMix FOREIGN KEY (id_film) REFERENCES Filme(id_f),
	CONSTRAINT fk_CompozitorMix FOREIGN KEY (id_compozitor) REFERENCES Compozitori(id_c)
)

-- Select-uri pentru ajutor (DEPRECATED)
SELECT * FROM Compozitori
SELECT * FROM Filme f
INNER JOIN Compozitori c ON f.id_compozitor = c.id_c

-- 2. Migrarea datelor
-- Luam toate legaturile existente acum in tabela Filme (acolo unde avem un compozitor setat), si le mutam in noua tabela de legatura
-- Nu pierdem nimic, deci nu avem nevoie de Legaturi_Eliminate

INSERT INTO Filme_Compozitori_Mix (id_film, id_compozitor)
SELECT id_f, id_compozitor FROM Filme
WHERE id_compozitor is NOT NULL

SELECT * FROM Filme_Compozitori_Mix

-- 3. Stergem vechea structura
-- Acum ca datele sunt in siguranta in tabelul nou, stergem coloana veche din Filme

-- Stergem constraint-ul vechi
ALTER TABLE Filme
DROP CONSTRAINT fk_CompozitorFilm

-- Stergem coloana
ALTER TABLE Filme
DROP COLUMN id_compozitor

-- 4. Adaugam mai multi compozitori la un film pentru a arata schimbarea

SELECT * FROM Compozitori
SELECT * FROM Filme_Compozitori_Mix
SELECT * FROM Filme

INSERT INTO Filme (titlu, durata, gen) VALUES ('Star Wars: Episode VI - Return of the Jedi', '02:11:00', 'Action Epic')	-- id: 22

INSERT INTO Filme_Compozitori_Mix (id_film, id_compozitor) VALUES (22, 1)
INSERT INTO Filme_Compozitori_Mix (id_film, id_compozitor) VALUES (22, 10)


-- ============================================================================
-- TRANSFORMARE 3: RELATIA M:N -> 1:N
-- Relatia dintre Filme (M) si Firme (N) (prin Publicatii)
-- Avem tabela de legatura 'Publicatii'. Vrem sa o simplificam la 1:N
-- Adica: Un Film apartine unei singure firme (FK in Filme)
-- Aici voim avea coliziuni (filme cu mai multe firme), deci trebuie sa stergem surplusul

-- Select-uri pentru ajutor (DEPRECATED)
SELECT * FROM Publicatii
SELECT * FROM Firme
SELECT * FROM Filme 

-- 1. Adaugarea coloanei noi
-- Pregatim locul in tabela Filme unde vom muta cheia externa
ALTER TABLE Filme
ADD id_firma INT

-- 2. Salvarea legaturilor ce vor fi sterse (Legaturi_Eliminate)
-- Pastram firma cu ID-ul cel mai mare
-- Orice firma care are un ID mai mic decat MAX-ul pentru filmul respectiv merge in istoric

INSERT INTO Legaturi_Eliminate (NumeTabelSt, IdSt, NumeTabelDr, IdDr)
SELECT 'Filme', id_film, 'Firme', id_firma FROM Publicatii p1
WHERE id_firma < (
	SELECT MAX(id_firma)
	FROM Publicatii p2
	WHERE p2.id_film = p1.id_film
)

SELECT * FROM Legaturi_Eliminate

-- 3. Curatarea tabeleui de legatura
-- Stergem ce trebuie sters ca sa putem adauga mai usor dupa
-- Stergem din Publicatii randurile pe care tocmai le-am salvat in istoric
-- Astfel, publicatii ramane curata (fiecare film apare o singura data)

DELETE FROM Publicatii
WHERE EXISTS (
	SELECT 1 FROM Legaturi_Eliminate le
	WHERE le.NumeTabelSt = 'Filme' 
	AND le.IdSt = Publicatii.id_film
	AND le.NumeTabelDr = 'Firme'
	AND le.IdDr = Publicatii.id_firma
)

-- 4. Migrarea datelor
-- Publicatii are o relatie 1:1 pentru filmele existente
-- Putem face update fara subquery cu MAX, pentru ca am curatat deja duplicatele

UPDATE Filme
SET id_firma = (
	SELECT id_firma FROM Publicatii
	WHERE Publicatii.id_film = Filme.id_f
)

-- 5. Drop la tabela veche
-- Nu mai avem nevoie de ea, datele bune sunt in Filme, cele pierdute sunt in Legaturi_Eliminate

DROP TABLE Publicatii

-- 6. Adaugam constraint de cheia externa pe tabela Filme
ALTER TABLE Filme
ADD CONSTRAINT fk_FirmaFilm FOREIGN KEY (id_firma) REFERENCES Firme(id_f)

SELECT * FROM Firme
SELECT * FROM Filme fi
INNER JOIN Firme fr ON fi.id_firma = fr.id_f

-- Nu mai adaug, deoarece se vede deja schimbarea


-- ============================================================================
-- TRANSFORMARE 4: RELATIA 1:N -> 1:1
-- Relatia dintre Filme (1) si Premii_Oscar (N)
-- Vrem sa restrictionam tabela astfel incat sa retina maxim un premiu per film
-- Asta inseamna ca Foreign Key-ul id_film trebuie sa devina UNIC

-- Select-uri pentru ajutor
SELECT * FROM Premii_Oscar
SELECT * FROM Filme f
INNER JOIN Premii_Oscar p ON f.id_f= p.id_film

-- 1. Salvarea inregistrarilor excedentare (Legaturi_Eliminate)
-- Ca de obicei, pastram ID-ul maxim
-- Orice premiu care are un ID mai mic decat MAX-ul filmului sau, pleaca in istoric

INSERT INTO Legaturi_Eliminate (NumeTabelSt, IdSt, NumeTabelDr, IdDr)
SELECT 'Filme', id_film, 'Premii_Oscar', id_o FROM Premii_Oscar p1
WHERE id_o < (
	SELECT MAX(id_o) FROM Premii_Oscar p2
	WHERE p2.id_film = p1.id_film
)

SELECT * FROM Legaturi_Eliminate

-- 2. Curatenie
-- Stergen premiile pe care tocmai le-am salvat
-- Lord Of the Rings va ramane cu un singur premiu (cel cu ID-ul cel mai mare)

DELETE FROM Premii_Oscar
WHERE EXISTS(
	SELECT 1 FROM Legaturi_Eliminate le
	WHERE le.NumeTabelSt = 'Filme'
	AND le.IdSt = Premii_Oscar.id_film
	AND le.NumeTabelDr = 'Premii_Oscar'
	AND le.IdDr = Premii_Oscar.id_o
)

-- 3. Adaugarea constrangerii de unicitate
-- Acum ca fiecare film apare o singura data in tabela de premii, putem aplica constrangerea UNIQUE pe cheia externa

ALTER TABLE Premii_Oscar
ADD CONSTRAINT uq_Film_Oscar UNIQUE (id_film)

-- Nu mai adaug, deoarece se vede deja schimbarea