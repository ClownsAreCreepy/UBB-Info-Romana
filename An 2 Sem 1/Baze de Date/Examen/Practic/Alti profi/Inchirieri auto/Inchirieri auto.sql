CREATE DATABASE Inchirieri_auto
USE Inchirieri_auto


-- 1. Creem
CREATE TABLE Clienti
(
	id_c INT PRIMARY KEY IDENTITY,
	nume NVARCHAR(100),
	prenume NVARCHAR(100)
)

CREATE TABLE Angajati
(
	id_a INT PRIMARY KEY IDENTITY,
	nume NVARCHAR(100),
	prenume NVARCHAR(100)
)

CREATE TABLE Marci
(
	id_m INT PRIMARY KEY IDENTITY,
	denumire NVARCHAR(100)
)

CREATE TABLE Autovehicule
(
	id_a INT PRIMARY KEY IDENTITY,
	nr_inmatriculare NVARCHAR(100),
	tip_motor NVARCHAR(100),
	id_marca INT FOREIGN KEY REFERENCES Marci(id_m)
)

CREATE TABLE Inchirieri
(
	id_i INT PRIMARY KEY IDENTITY,
	id_angajat INT FOREIGN KEY REFERENCES Angajati(id_a),
	id_client INT FOREIGN KEY REFERENCES Clienti(id_c),
	id_autovehicul INT FOREIGN KEY REFERENCES Autovehicule(id_a),
	data_inchiriere DATETIME,
	data_returnare DATETIME
)

-- 1,5. Inseram date
INSERT INTO Clienti (nume, prenume) VALUES
('Popescu', 'Petru'), -- 1
('Czako', 'Angel'), -- 2
('Ambra', 'Rizzeto') -- 3

INSERT INTO Angajati (nume, prenume) VALUES
('Grigorean', 'Daniel'), -- 1
('Oancea', 'Vlad'), -- 2
('Russu', 'Mihaela') -- 3

INSERT INTO Marci (denumire) VALUES
('Audi'), -- 1
('BMW'), -- 2
('Toyota') -- 3

INSERT INTO Autovehicule (nr_inmatriculare, tip_motor, id_marca) VALUES
('B 58 PKW', 'benzina', 1), -- 1
('HD 59 JUD', 'motorina', 2), -- 2
('BV 01 AAA', 'benzina', 1), -- 3
('B 777 LVF', 'aer magic', 3) -- 4

INSERT INTO Inchirieri (id_angajat, id_client, id_autovehicul, data_inchiriere, data_returnare) VALUES
(2, 1, 1, '2025-12-03 12:00:00', '2026-01-01 12:00:00'), -- 3 
(2, 3, 2, '2025-11-18 10:45:00', '2025-11-21 18:30:00'), -- 5
(3, 2, 3, '2025-06-13 16:30:00', '2025-08-01 12:00:00') -- 6
GO

-- 2. Procedura stocata
CREATE OR ALTER PROCEDURE adaugaSauModificaInchirieri
	@id_angajat INT,
	@id_autovehicul INT,
	@id_client INT,
	@data_inchirerii DATETIME,
	@data_returnarii DATETIME,
	@tip_operatie BIT
AS
BEGIN
	IF @tip_operatie = 1
		INSERT INTO Inchirieri (id_angajat, id_client, id_autovehicul, data_inchiriere, data_returnare) VALUES
			(@id_angajat, @id_client, @id_autovehicul, @data_inchirerii, @data_returnarii)
	ELSE
		UPDATE Inchirieri SET data_inchiriere = @data_inchirerii, data_returnare = @data_returnarii
			WHERE id_angajat=@id_angajat AND id_autovehicul=@id_autovehicul AND id_client=@id_client
END

EXECUTE adaugaSauModificaInchirieri 3, 2, 1, '2026-01-01 12:00:00', '2026-02-15 12:45:00', 0
SELECT * FROM Inchirieri
GO

-- 3. View
CREATE OR ALTER VIEW vw_InchirieriLunaCurentaMaraca
AS
SELECT a.nume, a.prenume, COUNT(*) AS TotalInchirieri FROM Angajati a
INNER JOIN Inchirieri i ON a.id_a = i.id_angajat
INNER JOIN Autovehicule au ON au.id_a = i.id_autovehicul
INNER JOIN Marci m ON m.id_m = au.id_marca
WHERE m.denumire = 'Audi' AND 
	YEAR(i.data_inchiriere) = YEAR(GETDATE()) AND MONTH(i.data_inchiriere) = MONTH(GETDATE())
GROUP BY a.id_a, a.nume, a.prenume
GO

SELECT * FROM vw_InchirieriLunaCurentaMaraca ORDER BY nume
GO

-- 4. Functie
CREATE OR ALTER FUNCTION uf_AutovehiculeLibere (@data DATETIME)
RETURNS TABLE
AS
RETURN 
	SELECT a.nr_inmatriculare AS [Numar autovehicul], m.denumire AS Marca, a.tip_motor AS [Tip Motorizare] FROM Autovehicule a
	INNER JOIN Marci m ON a.id_marca = m.id_m
	WHERE a.id_a NOT IN 
		(SELECT id_autovehicul FROM Inchirieri
				WHERE data_inchiriere <= @data AND data_returnare >= @data
		)
GO

SELECT * FROM uf_AutovehiculeLibere('2026-01-01 12:00:00')

-- Use master
-- DROP DATABASE Inchirieri_auto