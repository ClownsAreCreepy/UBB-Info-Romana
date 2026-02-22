CREATE DATABASE Biblioteca
Use Biblioteca


-- 1. Creem
CREATE TABLE Librarii
(
	id_l INT PRIMARY KEY IDENTITY(1,1),
	nume NVARCHAR(100),
	adresa NVARCHAR(200)
)

CREATE TABLE Domenii
(
	id_d INT PRIMARY KEY IDENTITY(1,1),
	descriere NVARCHAR(100)
)

CREATE TABLE Carti
(
	id_c INT PRIMARY KEY IDENTITY(1,1),
	titlu NVARCHAR(100),
	id_domeniu INT FOREIGN KEY REFERENCES Domenii(id_d),
	id_librarie INT FOREIGN KEY REFERENCES Librarii(id_l)
)


CREATE TABLE Autori
(
	id_a INT PRIMARY KEY IDENTITY(1,1),
	nume NVARCHAR(100)
)

CREATE TABLE Publicatii
(
	id_carte INT FOREIGN KEY REFERENCES Carti(id_c),
	id_autor INT FOREIGN KEY REFERENCES Autori(id_a),

	CONSTRAINT pk_Publicati PRIMARY KEY (id_carte, id_autor)
)

CREATE TABLE Achizitii
(
	id_a INT PRIMARY KEY IDENTITY(1,1),
	id_carte INT FOREIGN KEY REFERENCES Carti(id_c),
	id_librarie INT FOREIGN KEY REFERENCES Librarii(id_l),
	data_achizitie DATE
)

-- 1.5 Inseram sa verificam ca urmatoarele subpuncte merg
INSERT INTO  Librarii (nume,adresa) VALUES
('Mihai Viteazul', 'str Mihai Viteazul, nr 1601'), -- 1
('Mihai Eminescu', 'str Mihai Eminescu, nr 1889'), -- 2
('Mihai I', 'str Mihai Intai, nr 2017') -- 3

INSERT INTO Domenii (descriere) VALUES
('literatura'), -- 1
('stiintific'), -- 2
('carte de telefon') -- 3

INSERT INTO Carti (titlu, id_domeniu, id_librarie) VALUES
('To Kill a Mockingbird', 1, 1), -- 1
('Game of Thrones', 1, 2), -- 2
('Atomic Habits', 2, 1), -- 3
('Sunrise Nights', 1, 1), -- 4
('Winds of Winter', 1, 1), -- 5
('How to get loads of bitches', 2, 1) -- 6

INSERT INTO Autori(nume) VALUES
('Harper Lee'), -- 1
('Ion Creanga'), -- 2
('George R. R. Martin'), -- 3
('Jeff Zentner'), -- 4
('Brittany Cavallaro') -- 5

INSERT INTO Publicatii (id_carte, id_autor) VALUES
(1, 1), -- 1
(2, 3), -- 2
(4, 4), -- 3
(4, 5), -- 4
(5, 3) -- 5
GO

INSERT INTO Achizitii (id_carte, id_librarie, data_achizitie) VALUES
(1, 1, '2013.11.13'), -- 1
(4, 1, '2009.09.21'), -- 2
(4, 1, '2014.02.03'), -- 3
(2, 2, '2020.08.04') -- 4
GO


-- 2. Procedura Stocata
CREATE OR ALTER PROCEDURE adaugaPublicatie (@nume NVARCHAR(100), @id_carte INT)
AS
BEGIN
	-- Daca nu exista autor cu numele dat, il adaugam
	IF NOT EXISTS (SELECT 1 FROM Autori WHERE @nume = nume)
		INSERT INTO Autori (nume) VALUES (@nume) 

	-- Aflam id-ul autorului cu numele dat
	DECLARE @id_autor INT

	SELECT @id_autor=id_a FROM Autori
	WHERE @nume = nume

	-- Afisam mesaj daca asociatia exista deja
	IF EXISTS (SELECT 1 FROM Publicatii WHERE @id_autor = id_autor AND @id_carte = id_carte)
	BEGIN
		PRINT 'Autorul si cartea data sunt deja asociate!'
		RETURN
	END

	-- Adaugam in publicatii relatia
	INSERT INTO Publicatii (id_carte, id_autor) VALUES (@id_carte, @id_autor)
END
GO

EXECUTE adaugaPublicatie 'Popescu Petru', 7
GO


-- 3. View
CREATE OR ALTER VIEW vw_CartiCumparate
AS
SELECT l.nume, COUNT(*) AS Nr_carti_cumparate FROM Achizitii a
INNER JOIN Librarii l ON a.id_librarie = l.id_l
WHERE YEAR(a.data_achizitie) > 2010
GROUP BY l.id_l, l.nume
HAVING COUNT(*) < 5
GO

SELECT * FROM vw_CartiCumparate ORDER BY Nr_carti_cumparate DESC
GO


-- 4. Function
CREATE OR ALTER FUNCTION uf_ScrisaDeNrAutori(@nr_autori INT)
RETURNS TABLE 
AS
RETURN SELECT TOP 100 PERCENT l.nume, l.adresa, c.titlu, @nr_autori AS NrAutori FROM Publicatii p
INNER JOIN Carti c ON p.id_carte = c.id_c
INNER JOIN Achizitii a ON a.id_carte = c.id_c
INNER JOIN Librarii l ON a.id_librarie = l.id_l
GROUP BY p.id_carte,l.nume, l.adresa, c.titlu
HAVING COUNT(*) = @nr_autori
ORDER BY c.titlu
GO

SELECT * FROM uf_ScrisaDeNrAutori(2)
GO

-- Use master
-- DROP DATABASE Biblioteca