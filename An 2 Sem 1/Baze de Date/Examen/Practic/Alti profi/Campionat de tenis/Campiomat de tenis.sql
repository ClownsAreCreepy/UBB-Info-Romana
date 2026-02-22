CREATE DATABASE Campionat_Tenis
USE Campionat_Tenis


-- 1. Creem
CREATE TABLE Turnee
(
	id_t INT PRIMARY KEY IDENTITY,
	locatie NVARCHAR(100),
	inceput TIME,
	final TIME
)

CREATE TABLE Jucatori
(
	id_j INT PRIMARY KEY IDENTITY,
	nume NVARCHAR(100),
	nr_puncte INT,
	valoare_premii INT

)

CREATE TABLE Arene
(
	id_a INT PRIMARY KEY IDENTITY,
	nume NVARCHAR(100)
)

CREATE TABLE Partide
(
	id_p INT PRIMARY KEY IDENTITY,
	id_j1 INT FOREIGN KEY REFERENCES Jucatori(id_j),
	id_j2 INT FOREIGN KEY REFERENCES Jucatori(id_j),
	id_a INT FOREIGN KEY REFERENCES Arene(id_a),
	id_t INT FOREIGN KEY REFERENCES Turnee(id_t),
	data_desfasurarii DATETIME,
	castigator INT FOREIGN KEY REFERENCES Jucatori(id_j),
	puncte_j1 INT,
	puncte_j2 INT,
	premiu_j1 INT,
	premiu_j2 INT
)

-- 1,5. Adaugam in tabele
INSERT INTO Turnee (locatie, inceput, final) VALUES
('Cetate Deva', '12:00:00', '14:00:00'), -- 1
('Bejan', '15:00:00', '17:00:00'), -- 2
('Bejan', '17:00:00', '19:00:00') -- 3

INSERT INTO Jucatori (nume, nr_puncte, valoare_premii) VALUES
('Petru', 200, 500), -- 1
('David', 300, 900), -- 2
('Calin', 250, 750), -- 3
('Oana', 100, 0) -- 4

INSERT INTO Arene (nume) VALUES
('Mihai Viteazul'), -- 1
('Mihai Eminescu'), -- 2
('Mihai I') -- 3

INSERT INTO Partide (id_j1, id_j2, id_a, id_t, data_desfasurarii, castigator, puncte_j1, puncte_j2, premiu_j1, premiu_j2) VALUES
(1, 2, 1, 1, '2025-12-22 12:00:00', 2, 100, 200, 25, 50), -- 1
(1, 3, 2, 1, '2025-12-23 12:00:00', 3, 100, 200, 25, 50), -- 2
(1, 4, 1, 2, '2026-06-29 15:00:00', 1, 200, 100, 50, 25), -- 3
(2, 3, 1, 1, '2025-12-23 12:00:00', 2, 200, 100, 50, 25), -- 4
(2, 3, 1, 1, '2025-12-24 12:00:00', 2, 200, 100, 50, 25) -- 5
GO

-- 2. Procedura stocata
CREATE OR ALTER PROCEDURE adaugaPartida
	@id_t INT,
	@id_j1 INT,
	@id_j2 INT,
	@puncte_j1 INT,
	@puncte_j2 INT,
	@premii_j1 INT,
	@premii_j2 INT,
	@castigator INT,
	@id_a INT,
	@data_desfasurarii DATETIME
AS
BEGIN
	INSERT INTO Partide (id_j1, id_j2, id_a, id_t, data_desfasurarii, castigator, puncte_j1, puncte_j2, premiu_j1, premiu_j2) VALUES
	(@id_j1, @id_j2, @id_a, @id_t, @data_desfasurarii, @castigator, @puncte_j1, @puncte_j2, @premii_j1, @premii_j2)
END
GO

EXECUTE adaugaPartida 2, 3, 4, 200, 100, 50, 25, 3, 2, '2026-06-29 16:00:00'  
GO


-- 3. View
CREATE OR ALTER VIEW vw_PartideCastigate
AS
SELECT j.nume,COUNT(p.id_p) AS PartideCastigatoare FROM Jucatori j
LEFT JOIN Partide p ON j.id_j = p.castigator
GROUP BY j.nume, j.id_j
GO

SELECT * FROM vw_PartideCastigate ORDER BY PartideCastigatoare DESC
GO

-- 4. Functie
CREATE OR ALTER FUNCTION uf_totalPuncteSiPremii (@id_j INT)
RETURNS @tabelRezultat TABLE (TotalPuncte INT, TotalPremii INT)
AS
BEGIN
	DECLARE @puncte_totale INT
	DECLARE @premii_totale INT

	SELECT @puncte_totale = j.nr_puncte, @premii_totale = j.valoare_premii FROM Jucatori j
	WHERE j.id_j = @id_j

	SELECT @puncte_totale = @puncte_totale + ISNULL(SUM(p.puncte_j1), 0), @premii_totale = @premii_totale + ISNULL(SUM(p.premiu_j1), 0) FROM Partide p
	WHERE p.id_j1 = @id_j

	SELECT @puncte_totale = @puncte_totale + ISNULL(SUM(p.puncte_j2), 0), @premii_totale = @premii_totale + ISNULL(SUM(p.premiu_j2), 0) FROM Partide p
	WHERE p.id_j2 = @id_j

	INSERT INTO @tabelRezultat (TotalPuncte, TotalPremii)
	VALUES (@puncte_totale, @premii_totale)

	RETURN
END
GO

SELECT * FROM uf_totalPuncteSiPremii(1)

-- USE master
-- DROP DATABASE Campionat_Tenis