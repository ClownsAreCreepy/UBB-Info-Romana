CREATE DATABASE Spital
USE Spital

-- 1. Creem
CREATE TABLE Departamente
(
	id_d INT PRIMARY KEY IDENTITY,
	nume NVARCHAR(100),
	non_stop BIT,
)

CREATE TABLE Doctori
(
	id_d INT PRIMARY KEY IDENTITY,
	nume NVARCHAR(100),
	data_nasterii DATE,
	id_departamente INT FOREIGN KEY REFERENCES Departamente(id_d) ON DELETE CASCADE
)

CREATE TABLE Pacienti
(
	id_p INT PRIMARY KEY IDENTITY,
	nume NVARCHAR(100),
	data_nasterii DATE
)

CREATE TABLE Boli
(
	id_b INT PRIMARY KEY IDENTITY,
	denumire NVARCHAR(100)
)

CREATE TABLE Tratamente
(
	id_t INT PRIMARY KEY IDENTITY,
	descriere NVARCHAR(1000)
)

CREATE TABLE Responsabilitati
(
	id_doctor INT FOREIGN KEY REFERENCES Doctori(id_d),
	id_pacient INT FOREIGN KEY REFERENCES Pacienti(id_p),

	CONSTRAINT pk_Responsabilitati PRIMARY KEY (id_doctor, id_pacient)
)

CREATE TABLE Afectiuni
(
	id_pacienti INT FOREIGN KEY REFERENCES Pacienti(id_p),
	id_boala INT FOREIGN KEY REFERENCES Boli(id_b),

	CONSTRAINT pk_Afectiuni PRIMARY KEY (id_pacienti, id_boala)
)

CREATE TABLE Vindecari
(
	id_boala INT FOREIGN KEY REFERENCES Boli(id_b),
	id_tratament INT FOREIGN KEY REFERENCES Tratamente(id_t),

	CONSTRAINT pk_Vindecari PRIMARY KEY (id_boala, id_tratament)
)


-- 1,5. Inseram
INSERT INTO Departamente (nume, non_stop) VALUES
('Diagnostica', 1), -- 1
('ER', 1), -- 2
('Pediatrie', 0), -- 3
('Chirurgie', 0) -- 4

INSERT INTO Doctori (nume, data_nasterii, id_departamente) VALUES
('House', '1960-11-04', 1), -- 1
('Chase', '1980-07-13', 4), -- 2
('Foreman', '1978-02-28', 1), -- 3
('Taub', '1960-11-03', 1), -- 4
('Michael', '1950-03-29', 2), -- 5
('13', '1987-05-20', 1) -- 6

INSERT INTO Pacienti (nume, data_nasterii) VALUES
('Schwarz', '1940-10-14'), -- 1
('Dibala', '1943-06-14'), -- 2
('Wilson', '1960-04-18'), -- 3
('Lisa', '1970-12-09'), -- 4
('House', '1960-11-04'), -- 5
('13', '1987-05-20') -- 6

INSERT INTO Boli (denumire) VALUES
('Hungtinton"s'), -- 1
('Cancer'), -- 2
('Racism'), -- 3
('Common Cold'), -- 4
('Kidney stone'), -- 5
('Depression') -- 6

INSERT INTO Tratamente (descriere) VALUES
('A lot of water'), -- 1
('Introspection'), -- 2
('Nothing you can do really'), -- 3
('Just stop being sad'), -- 4
('Aspirin'), -- 5
('Morphine') -- 6

INSERT INTO Responsabilitati (id_doctor, id_pacient) VALUES
(6, 6), -- 1
(1, 5), -- 2
(1, 2), -- 3
(1, 3), -- 4
(2, 2), -- 5
(3, 6) -- 6

INSERT INTO Afectiuni (id_pacienti, id_boala) VALUES
(1, 2), -- 1
(2, 3), -- 2
(3, 2), -- 3
(4, 2), -- 4
(5, 2), -- 5
(6, 1), -- 6
(5, 6), -- 7
(5, 3) -- 8

INSERT INTO Vindecari (id_boala, id_tratament) VALUES
(1, 3), -- 1
(2, 1), -- 2
(3, 2), -- 3
(4, 1), -- 4
(5, 1), -- 5
(6, 4), -- 6
(6, 1), -- 7
(5, 6), -- 8
(5, 3) -- 9


-- 2. Interogare
SELECT nume FROM Departamente
WHERE nume LIKE '%pediatrie%'
GO

-- 3. Functie
CREATE OR ALTER FUNCTION uf_BoliDese()
RETURNS INT
AS
BEGIN
	DECLARE @boli INT
	SELECT @boli = COUNT(id_boala) FROM (
		SELECT id_boala FROM Afectiuni
		GROUP BY id_boala
		HAVING COUNT(id_boala) > 3) AS BoliDese

	RETURN @boli
END
GO

PRINT dbo.uf_BoliDese()
GO


-- 3. View 1
CREATE OR ALTER VIEW vw_LiteraADes
AS
SELECT t.descriere FROM Tratamente t
INNER JOIN Vindecari v ON t.id_t = v.id_tratament
WHERE t.descriere LIKE 'A%'
GROUP BY t.id_t, t.descriere
HAVING COUNT(t.id_t) > 2
GO

SELECT * FROM vw_LiteraADes
GO

-- 4. View 2
CREATE OR ALTER VIEW vw_DepartamentePline
AS
SELECT d.nume FROM Departamente d
INNER JOIN Doctori dr ON d.id_d = dr.id_departamente
WHERE non_stop = 1
GROUP BY d.id_d, d.nume
HAVING COUNT(*) > 3
GO

SELECT * FROM vw_DepartamentePline

-- USE master
-- DROP DATABASE Spital