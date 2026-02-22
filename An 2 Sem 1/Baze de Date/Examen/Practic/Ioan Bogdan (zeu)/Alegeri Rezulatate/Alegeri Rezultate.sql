CREATE DATABASE Alegeri
Use Alegeri

-- 1.

CREATE TABLE Sectii
(
	id_s INT PRIMARY KEY IDENTITY (1,1),
	numar INT
)

CREATE TABLE Cetateni
(
	id_c INT PRIMARY KEY IDENTITY(1,1),
	nume NVARCHAR(100),
	prenume NVARCHAR(100),
	cnp NVARCHAR(15),
	id_sectie INT FOREIGN KEY REFERENCES Sectii(id_s)
)

CREATE TABLE Candidati
(
	id_c INT PRIMARY KEY IDENTITY(1,1),
	nume NVARCHAR(100),
	prenume NVARCHAR(100),
	data_nasterii DATE
)

CREATE TABLE Voturi
(
	id_v INT PRIMARY KEY IDENTITY(1,1),
	ora TIME,
	pe_lista_suplimentara BIT,
	id_cetatean INT FOREIGN KEY REFERENCES Cetateni(id_c),
	id_candidat INT FOREIGN KEY REFERENCES Candidati(id_c),
	id_sectie INT FOREIGN KEY REFERENCES Sectii(id_s)
)

CREATE TABLE Echipaje
(
	id_e INT PRIMARY KEY IDENTITY(1,1),
	numar INT,
	numar_membrii INT
)

CREATE TABLE Supravegheri
(
	id_s INT PRIMARY KEY IDENTITY(1,1),
	id_echipaj INT FOREIGN KEY REFERENCES Echipaje(id_e),
	id_sectie INT FOREIGN KEY REFERENCES Sectii(id_s)
)

-- 1.5
INSERT INTO Sectii (numar) VALUES
(1), -- 1
(2), -- 2
(3) -- 3

INSERT INTO Cetateni (nume, prenume, cnp, id_sectie) VALUES
('Popescu', 'Petru', '5041118082209', 1), -- 1
('Czako', 'Angel', '5050617082209', 2), -- 2
('Grigorean', 'Daniel', '5031118082209', 1), -- 3
('Russu', 'Mihaela', '4041118082209', 3), -- 4
('Balabuc', 'Mirabela', '4041118083309', 1) -- 5

INSERT INTO Candidati (nume, prenume, data_nasterii) VALUES
('Georgescu', 'Calin', '1930-02-23'), -- 1
('Simion', 'George', '1980-08-03'), -- 2
('Nicusor', 'Dan', '1975-12-27') -- 3

INSERT INTO Voturi (ora, pe_lista_suplimentara, id_cetatean, id_candidat, id_sectie) VALUES
('12:00:00', 0, 1, 3, 1), -- 1
('18:00:00', 1, 2, 1, 2), -- 2
('16:00:00', 1, 3, 2, 1), -- 3
('11:00:00', 0, 4, 3, 3), -- 4
('13:00:00', 0, 5, 3, 1) -- 5

INSERT INTO Echipaje (numar, numar_membrii) VALUES
(1, 10),
(2, 15),
(3, 13),
(4, 9)

INSERT INTO Supravegheri (id_echipaj, id_sectie) VALUES
(1, 1),
(2, 1),
(3, 2),
(2, 3)

GO
-- 2.
CREATE OR ALTER PROCEDURE dbo.CandidatCastigator 
	@id_sectie INT,
	@id_candidat INT OUTPUT
AS
BEGIN
	DECLARE @id_castigator INT

	-- Numaram voturile fiecarui candidat in acea sectie, sortam descrescator dupa nr voturi obtinute
	-- luam prima linie -> castigatorul
	SELECT TOP 1 @id_castigator = V.Candidat FROM (
	SELECT id_candidat as Candidat, COUNT(*) as Nr_voturi FROM Voturi
	WHERE id_sectie = @id_sectie
	GROUP BY id_candidat) V
	ORDER BY Nr_voturi DESC

	SET @id_candidat = @id_castigator

	-- Numaram cate voturi a obtinut castigatorul in acea sectie
	DECLARE @voturi_obtinute INT
	SELECT @voturi_obtinute = COUNT(*) FROM Voturi
	WHERE @id_sectie = id_sectie AND id_candidat = @id_castigator

	-- Numaram voturile care s-au depus in acea sectie
	DECLARE @voturi_totale INT
	SELECT @voturi_totale = COUNT(*) FROM Voturi
	WHERE @id_sectie = id_sectie

	RETURN @voturi_obtinute * 100 / @voturi_totale
END
GO

DECLARE @return_value INT, @id_candidat INT

EXEC @return_value = dbo.CandidatCastigator @id_sectie = 1, @id_candidat = @id_candidat OUTPUT

SELECT @id_candidat as N'CASTIGATOR'

SELECT @return_value as N'Procent voturi Totale'

GO
-- 3.
CREATE OR ALTER VIEW vw_VoturiGeorgescu
AS
SELECT CONVERT(VARCHAR(10), s.numar) + ': ' + CONVERT(VARCHAR(10), COUNT(*)) AS DATE FROM Voturi v
INNER JOIN Sectii s ON v.id_sectie = s.id_s
INNER JOIN Candidati c ON v.id_candidat = c.id_c
WHERE c.nume = 'Georgescu' AND c.prenume = 'Calin'
GROUP BY s.numar
HAVING COUNT(*) > 500
GO

SELECT * FROM vw_VoturiGeorgescu

Use master
DROP DATABASE Alegeri
