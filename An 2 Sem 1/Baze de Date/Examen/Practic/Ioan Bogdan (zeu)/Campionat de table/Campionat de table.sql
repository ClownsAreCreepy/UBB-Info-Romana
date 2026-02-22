CREATE DATABASE Campionat
USE Campionat

-- 1.

CREATE TABLE Angajati
(
	id_a INT PRIMARY KEY IDENTITY(1,1),
	nume NVARCHAR(100),
	nr_contract NVARCHAR(100)
)

CREATE TABLE Mese
(
	id_m INT PRIMARY KEY IDENTITY(1,1),
	numar INT,
	culoare NVARCHAR(20)
)

CREATE TABLE Meciuri
(
	id_m INT PRIMARY KEY IDENTITY(1,1),
	data_meci DATE,
	id_a1 INT FOREIGN KEY REFERENCES Angajati(id_a),
	id_a2 INT FOREIGN KEY REFERENCES Angajati(id_a),
	id_masa INT FOREIGN KEY REFERENCES Mese(id_m),
	id_castigator INT FOREIGN KEY REFERENCES Angajati(id_a)
)

CREATE TABLE Mutari
(
	id_m INT PRIMARY KEY IDENTITY(1,1),
	id_jucator INT FOREIGN KEY REFERENCES Angajati(id_a),
	id_meci INT FOREIGN KEY REFERENCES Meciuri(id_m),
	zar_1 INT CHECK (zar_1 BETWEEN 1 AND 6),
	zar_2 INT CHECK (zar_2 BETWEEN 1 AND 6),
	piesa_mutata_de_la VARCHAR(10),
	piesa_mutata_la VARCHAR(10)
)

CREATE TABLE Spectatori
(
	id_spectatori INT FOREIGN KEY REFERENCES Angajati(id_a),
	id_meci INT FOREIGN KEY REFERENCES Meciuri(id_m),
	CONSTRAINT pk_Spectatori PRIMARY KEY (id_spectatori, id_meci)
)

-- 1.5
INSERT INTO Mese (numar, culoare) VALUES
(1, 'rosu'),
(2, 'albastru'),
(3, 'verde')

INSERT INTO Angajati (nume, nr_contract) VALUES
('Popescu Petru', 'CLF3215'), -- 1
('Gregory House', 'CLF3216'), -- 2
('L to the OG', 'CLF3217'), -- 3
('James Wilson', 'CLF3218'), -- 4
('Chris Chan', 'CLF3219') -- 5

INSERT INTO Meciuri (data_meci, id_a1, id_a2, id_masa, id_castigator) VALUES
(GETDATE(), 1, 2, 1, 1), -- 1
(GETDATE(), 1, 3, 1, 3), -- 2
(GETDATE(), 2, 3, 2, 3), -- 3
(GETDATE(), 4, 2, 3, 2), -- 4
(GETDATE(), 5, 1, 1, 2), -- 5
(GETDATE(), 5, 3, 3, 1) -- 6

INSERT INTO Mutari (id_jucator, id_meci, zar_1, zar_2, piesa_mutata_de_la, piesa_mutata_la) VALUES
(1, 1, 2, 2,'1-2', '2-3'), -- 1
(2, 1, 3, 3,'1-2', '2-3'), -- 2
(3, 3, 2, 7,'1-2', '2-3'), -- 3
(3, 3, 6, 6,'1-2', '2-3'), -- 4
(2, 4, 1, 1,'1-2', '2-3') -- 5

INSERT INTO Spectatori (id_spectatori, id_meci) VALUES
(3, 1),
(3, 4),
(1, 3),
(4, 1),
(5, 1),
(2, 2)

-- 2.
GO
CREATE OR ALTER PROCEDURE Premiu
	@id_participant INT
AS
BEGIN
	DECLARE @meciuri_castigate INT,
			@spectatori_prezenti INT,
			@meci_nespectat INT

	-- Calculam meciurile castigate de el
	SELECT @meciuri_castigate = COUNT(*) FROM Meciuri
	WHERE id_castigator = @id_participant

	PRINT @meciuri_castigate

	-- Calculam spectatori prezenti la meciurile lui
	SELECT @spectatori_prezenti = COUNT(*) FROM Spectatori s
	INNER JOIN Meciuri m ON m.id_m = s.id_meci
	WHERE m.id_a1 = @id_participant OR m.id_a2 = @id_participant

	PRINT @spectatori_prezenti

	-- Calculam meciurile nespectate de el
	-- Luam doar meciurile in care nu a participat
	-- Si numaram la cate nu a fost spectator
	SELECT @meci_nespectat = COUNT(*) FROM Meciuri m
	WHERE m.id_a1 <> @id_participant AND m.id_a2 <> @id_participant
		  AND NOT EXISTS (
			SELECT 1 FROM Spectatori s
			WHERE s.id_meci = m.id_m
			AND s.id_spectatori = @id_participant
		 )

	PRINT @meci_nespectat

	DECLARE @premiu INT
	SET @premiu = @meciuri_castigate * 100 + @spectatori_prezenti * 10 - @meci_nespectat * 10

	IF @premiu < 0
		RETURN 0
	
	RETURN @premiu

END
GO

DECLARE @return INT

EXEC @return = dbo.Premiu 1
SELECT @return

GO
-- 3.
CREATE OR ALTER VIEW vw_CLF3215Duble
AS
SELECT COUNT(*) AS Dublue FROM Mutari mut
INNER JOIN Meciuri meciuri ON mut.id_meci = meciuri.id_m
INNER JOIN Angajati a ON mut.id_jucator = a.id_a
WHERE mut.zar_1 = mut.zar_2 AND a.nr_contract = 'CLF3215'
GO

SELECT * FROM vw_CLF3215Duble

-- Use master
-- DROP DATABASE Campionat
