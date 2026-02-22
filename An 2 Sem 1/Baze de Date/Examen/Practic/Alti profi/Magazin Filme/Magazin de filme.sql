CREATE DATABASE MagazinFilme
USE MagazinFilme


-- 1. Creem
CREATE TABLE TipFilm
(
	id_t INT PRIMARY KEY IDENTITY,
	descriere NVARCHAR(100)
)

CREATE TABLE Regizori
(
	id_r INT PRIMARY KEY IDENTITY,
	nume NVARCHAR(100),
	data_nasterii DATE
)

CREATE TABLE Filme
(
	id_f INT PRIMARY KEY IDENTITY,
	titlu NVARCHAR(100),
	durata TIME,
	an_aparitie INT,
	pret_inchiriere INT,
	id_tip INT FOREIGN KEY REFERENCES TipFilm(id_t) ON DELETE CASCADE,
	id_regizor INT FOREIGN KEY REFERENCES Regizori(id_r) ON DELETE CASCADE
)

CREATE TABLE Tari
(
	id_t INT PRIMARY KEY IDENTITY,
	nume NVARCHAR(100)
)

CREATE TABLE Actori
(
	id_a INT PRIMARY KEY IDENTITY,
	nume NVARCHAR(100) UNIQUE,
	id_tara INT FOREIGN KEY REFERENCES Tari(id_t) ON DELETE CASCADE,
)

CREATE TABLE Clienti
(
	id_c INT PRIMARY KEY IDENTITY,
	nume NVARCHAR(100),
)

CREATE TABLE Roluri
(
	id_film INT FOREIGN KEY REFERENCES Filme(id_f),
	id_actor INT FOREIGN KEY REFERENCES Actori(id_a),

	CONSTRAINT pk_Roluri PRIMARY KEY (id_film, id_actor)
)

CREATE TABLE Inchirieri
(
	id_i INT PRIMARY KEY IDENTITY,
	id_film INT FOREIGN KEY REFERENCES Filme(id_f),
	id_client INT FOREIGN KEY REFERENCES Clienti(id_c),
	data_inchiriere DATETIME,
	data_returnare DATETIME
)


-- 1,5. Inseram date
INSERT INTO TipFilm (descriere) VALUES
('Drama'), -- 1
('Comedie'), -- 2
('Sci-Fi') -- 3

INSERT INTO Regizori (nume, data_nasterii) VALUES
('Quentin Tarantino', '1970-10-15'), -- 1
('Charles Laughton', '1890-08-29'), -- 2
('Christopher Nolan', '1967-03-21') -- 3

INSERT INTO Filme (titlu, durata, an_aparitie, pret_inchiriere, id_tip, id_regizor) VALUES
('Pulp Fiction', '02:45:00', 1990, 20, 1, 1), -- 1
('Inception', '2:30:00', 2012, 17, 3, 3), -- 2
('The Night of the Hunter', '1:30:00', 1954, 34, 1, 2), -- 3
('The Prestige', '2:15:00', 2006, 40, 1, 1) -- 4

INSERT INTO Tari (nume) VALUES
('USA'), -- 1
('Canada'), -- 2
('UK') -- 3

INSERT INTO Actori (nume, id_tara) VALUES
('Tom Hardy', 3), -- 1
('Hugh Jackman', 3), -- 2
('Joseph Gordon-Levitt', 2), -- 3
('Michael Caine', 3) -- 4

INSERT INTO Clienti (nume) VALUES
('Popescu Petru'), -- 1
('Oana Chiorean'), -- 2
('Czako Angel'), -- 3
('Calin Bedea') -- 4

INSERT INTO Roluri (id_film, id_actor) VALUES
(2, 1), -- 1
(2, 3), -- 2
(2, 4), -- 3
(4, 2), -- 4
(4, 4) -- 5

INSERT INTO Inchirieri (id_film, id_client, data_inchiriere, data_returnare) VALUES
(1, 1, '2025-12-03 18:40:00', '2025-12-20 19:00:00'), -- 1
(3, 1, '2025-09-30 13:00:00', '2025-10-13 12:20:00'), -- 2
(4, 3, '2025-11-06 21:00:00', '2025-11-23 13:35:00'), -- 3
(4, 4, '2026-01-01 08:43:00', '2025-01-20 15:13:00'), -- 4
(4, 1, '2026-01-04 08:45:00', '2025-02-02 08:45:00') -- 5


-- 2. Interogare
SELECT * FROM Filme
WHERE titlu like '%poveste%'
GO

-- 3. View
CREATE OR ALTER VIEW vw_ActoriFaimosi
AS
SELECT a.* FROM Actori a
INNER JOIN Roluri r ON a.id_a = r.id_actor
GROUP BY a.id_a, a.id_tara, a.nume
HAVING COUNT(a.id_a) > 3
GO

SELECT * FROM vw_ActoriFaimosi
GO


-- 3. Procedura stocata
CREATE OR ALTER PROCEDURE filmeIcky
AS
BEGIN
	SELECT f.* FROM Filme f
	LEFT JOIN Inchirieri i ON f.id_f = i.id_film
	WHERE i.id_client IS NULL
END

EXECUTE filmeIcky
GO


-- 4. Functie
CREATE OR ALTER FUNCTION uf_ClientiBogati2021 ()
RETURNS INT
AS
BEGIN
	DECLARE @rez INT

	SELECT @rez=COUNT(DISTINCT i.id_client) FROM Inchirieri i
	INNER JOIN Filme f ON f.id_f = i.id_film
	INNER JOIN Clienti c ON c.id_c = i.id_client
	WHERE f.pret_inchiriere > 30 AND YEAR(i.data_inchiriere) = 2021

	RETURN ISNULL(@rez, 0)
END
GO

SELECT dbo.uf_ClientiBogati2021() AS NumarClienti


-- Use master
-- DROP DATABASE MagazinFilme
