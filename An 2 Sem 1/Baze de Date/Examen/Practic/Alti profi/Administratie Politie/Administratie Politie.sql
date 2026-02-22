CREATE DATABASE Administratie_Politie
USE Administratie_Politie

-- 1. Creem
CREATE TABLE Sectii
(
	id_s INT PRIMARY KEY IDENTITY,
	denumire NVARCHAR(100),
	adresa NVARCHAR(100)
)

CREATE TABLE Sectoare
(
	id_s INT PRIMARY KEY IDENTITY,
	denumire NVARCHAR(100)
)

CREATE TABLE Grade
(
	id_g INT PRIMARY KEY IDENTITY,
	denumire NVARCHAR(100)
)

CREATE TABLE Politisti
(
	id_p INT PRIMARY KEY IDENTITY,
	nume NVARCHAR(100),
	id_sectie INT FOREIGN KEY REFERENCES Sectii(id_s) ON DELETE CASCADE,
	id_grad INT FOREIGN KEY REFERENCES Grade(id_g) ON DELETE CASCADE
)

CREATE TABLE Programari
(
	id_sector INT FOREIGN KEY REFERENCES Sectoare(id_s),
	id_politist INT FOREIGN KEY REFERENCES Politisti(id_p),
	data_intrare DATETIME,
	data_iesire DATETIME,

	CONSTRAINT pk_Programari PRIMARY KEY (id_sector, id_politist)
)


-- 1,5. Inseram
INSERT INTO Sectii (denumire, adresa) VALUES
('Mihai Viteazul', 'str Mihai Viteazul, nr 1601'), -- 1
('Mihai Eminescu', 'str Mihai Eminescu, nr 1889'), -- 2
('Mihai I', 'str Mihai Intai, nr 2017') -- 3


INSERT INTO Sectoare (denumire) VALUES
('Sector I'), -- 1
('Sector II'), -- 2
('Sector III') -- 3

INSERT INTO Grade (denumire) VALUES
('Politist normal'), -- 1
('Politist interesant'), -- 2
('Politist delicios') -- 3

INSERT INTO Politisti (nume, id_sectie, id_grad) VALUES
('Popescu Petru', 1, 2), -- 1
('Czako Angel', 2, 3), -- 2
('Grigorean Daniel', 2, 1), -- 3
('Bedea Calin', 3, 2) -- 4

INSERT INTO Programari (id_sector, id_politist, data_intrare, data_iesire) VALUES
(2, 1, '2025-12-29 12:00:00', '2025-12-29 20:00:00'), -- 1
(2, 2, '2025-12-29 20:00:00', '2025-12-30 06:00:00'), -- 2
(1, 3, '2026-01-01 12:00:00', '2026-01-01 20:00:00'), -- 3
(3, 1, '2025-12-29 16:00:00', '2025-12-30 00:00:00'), -- 4
(3, 4, '2026-01-01 14:00:00', '2026-01-01 22:00:00') -- 5
GO

-- 2. Procedure
CREATE OR ALTER PROCEDURE adaugaSauModifficaProgramare
	@id_politist INT,
	@id_sector INT,
	@data_intrare DATETIME,
	@data_iesire DATETIME
AS
BEGIN
	IF EXISTS(SELECT 1 FROM Programari WHERE @id_politist = id_politist AND @id_sector = id_sector)
		UPDATE Programari
			SET data_intrare = @data_intrare, data_iesire = @data_iesire
			WHERE id_sector = @id_sector AND id_politist = @id_politist
	ELSE
		INSERT INTO Programari (id_sector, id_politist, data_intrare, data_iesire) VALUES
		(@id_sector, @id_politist, @data_intrare, @data_iesire)
END
GO

EXECUTE adaugaSauModifficaProgramare 1, 1, '2026-01-01 13:00:00', '2026-01-01 21:00:00'

SELECT * FROM Programari
GO


-- 3. View
CREATE OR ALTER VIEW vw_OreMunca
AS
SELECT p.nume AS Nume, si.denumire AS Sectie, g.denumire AS Grad, COUNT(p.id_p) * 8 AS [Nr Ore] FROM Programari pr
INNER JOIN Politisti p ON pr.id_politist = p.id_p
INNER JOIN Sectoare s ON pr.id_sector = s.id_s
INNER JOIN Sectii si ON p.id_sectie = si.id_s
INNER JOIN Grade g ON p.id_grad = g.id_g
WHERE YEAR(pr.data_intrare) = YEAR(GETDATE()) AND MONTH(pr.data_intrare) = '01'
GROUP BY p.id_p, p.nume, si.denumire, g.denumire
GO

SELECT * FROM vw_OreMunca ORDER BY Sectie, Nume
GO

-- 4. Function
CREATE OR ALTER FUNCTION uf_MultipleProgramari(@data DATETIME)
RETURNS TABLE
AS
RETURN 
	SELECT p.nume As Nume, si.denumire AS Sectie, g.denumire AS Grad FROM Programari pr
	INNER JOIN Politisti p ON pr.id_politist = p.id_p
	INNER JOIN Sectii si ON p.id_sectie = si.id_s
	INNER JOIN Grade g ON p.id_grad = g.id_g
	INNER JOIN Sectoare s ON pr.id_sector = s.id_s
	WHERE pr.data_intrare <= @data AND pr.data_iesire >= @data
	GROUP BY p.id_p, p.nume, si.denumire, g.denumire
	HAVING COUNT(*) > 1
GO

SELECT * FROM uf_MultipleProgramari('2025-12-29 18:00:00')


-- USE master
-- DROP DATABASE Adminstratie_Poitie