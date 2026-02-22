--1. Creeaza baza propriu-zisa

CREATE DATABASE GestiuneTrenuri
GO

USE GestiuneTrenuri

CREATE TABLE Tipuri_Tren
(
	id_t INT PRIMARY KEY IDENTITY (1,1),
	descriere VARCHAR(100)
)

CREATE TABLE Trenuri
(
	id_t INT PRIMARY KEY IDENTITY (1,1),
	nume VARCHAR(100),
	id_tip INT FOREIGN KEY REFERENCES Tipuri_Tren(id_t) ON UPDATE CASCADE ON DELETE CASCADE
)

CREATE TABLE Statii
(
	id_s INT PRIMARY KEY IDENTITY (1,1),
	nume VARCHAR(100)
)

CREATE TABLE Rute
(
	id_r INT PRIMARY KEY IDENTITY (1,1),
	nume VARCHAR(100),
	id_tren INT FOREIGN KEY REFERENCES Trenuri(id_t) ON UPDATE CASCADE ON DELETE CASCADE
)

CREATE TABLE Intersectii
(
	id_statii INT FOREIGN KEY REFERENCES Statii(id_s) ON UPDATE CASCADE ON DELETE CASCADE,
	id_rute INT FOREIGN KEY REFERENCES Rute(id_r) ON UPDATE CASCADE ON DELETE CASCADE,
	ora_sosirii TIME,
	ora_plecarii TIME,

	CONSTRAINT pk_Intersectii PRIMARY KEY (id_statii, id_rute)
)


-- 1,5. Inseram date sa ne putem verifica la 2 si 3

INSERT INTO Tipuri_Tren (descriere) VALUES ('Trenuri frumoase')		-- 1
INSERT INTO Tipuri_Tren (descriere) VALUES ('Trenuri urate')		-- 2
INSERT INTO Tipuri_Tren (descriere) VALUES ('Trenuri bengoase')		-- 3
INSERT INTO Tipuri_Tren (descriere) VALUES ('Trenuri asa si asa')	-- 4
INSERT INTO Tipuri_Tren (descriere) VALUES ('Trenuri chircotase')	-- 5

INSERT INTO Trenuri (nume, id_tip) VALUES ('Trenul lui Petru', 1)	-- 1
INSERT INTO Trenuri (nume, id_tip) VALUES ('Trenul Oanei', 2)	-- 2
INSERT INTO Trenuri (nume, id_tip) VALUES ('Trenul lui Angel', 4)	-- 3
INSERT INTO Trenuri (nume, id_tip) VALUES ('Trenul lui Dani', 3)	-- 4
INSERT INTO Trenuri (nume, id_tip) VALUES ('Trenul lui Bianca', 1)	-- 5
INSERT INTO Trenuri (nume, id_tip) VALUES ('Trenul lui Madam Buftea', 4)	-- 6

INSERT INTO Statii (nume) VALUES ('Deva') -- 1
INSERT INTO Statii (nume) VALUES ('Cluj') -- 2
INSERT INTO Statii (nume) VALUES ('Baia Mare') -- 3
INSERT INTO Statii (nume) VALUES ('Brasov') -- 4
INSERT INTO Statii (nume) VALUES ('Paltinis') -- 5
INSERT INTO Statii (nume) VALUES ('Arad') -- 6

INSERT INTO Rute (nume, id_tren) VALUES ('Deva - Simeria', 3) -- 1
INSERT INTO Rute (nume, id_tren) VALUES ('Simeria - Deva', 3) -- 2
INSERT INTO Rute (nume, id_tren) VALUES ('Brasov - Paltinis', 4) -- 3
INSERT INTO Rute (nume, id_tren) VALUES ('Deva - Cluj', 1) -- 4
INSERT INTO Rute (nume, id_tren) VALUES ('Arad - Gorj', 4) -- 5
INSERT INTO Rute (nume, id_tren) VALUES ('Rasnov - Bucuresti', 4) -- 6
INSERT INTO Rute (nume, id_tren) VALUES ('Cluj - Asia', 2) -- 8

INSERT INTO Intersectii(id_statii, id_rute, ora_plecarii, ora_sosirii) VALUES (1, 1, '07:59:59', '8:00:00') -- 1
INSERT INTO Intersectii(id_statii, id_rute, ora_plecarii, ora_sosirii) VALUES (1, 2, '11:00:00', '12:00:00') -- 2
INSERT INTO Intersectii(id_statii, id_rute, ora_plecarii, ora_sosirii) VALUES (4, 3, '05:59:59', '6:00:00') -- 3
INSERT INTO Intersectii(id_statii, id_rute, ora_plecarii, ora_sosirii) VALUES (5, 3, '12:00:00', '12:30:00') -- 4
INSERT INTO Intersectii(id_statii, id_rute, ora_plecarii, ora_sosirii) VALUES (1, 4, '08:59:59', '9:00:00') -- 5
INSERT INTO Intersectii(id_statii, id_rute, ora_plecarii, ora_sosirii) VALUES (2, 4, '11:00:00', '12:00:00') -- 6
INSERT INTO Intersectii(id_statii, id_rute, ora_plecarii, ora_sosirii) VALUES (6, 5, '08:59:59', '09:00:00') -- 7

-- Am incurcat sosirea cu plecarea, my bad

-- 2. Procedura stocata

GO
CREATE OR ALTER PROCEDURE dbo.AddIntersection 
	@id_statie INT,
	@id_ruta INT,
	@ora_plecarii TIME,
	@ora_sosirii TIME
AS
BEGIN
	IF EXISTS (SELECT 1 FROM Intersectii WHERE @id_ruta = id_rute AND @id_statie = id_statii)
	BEGIN

		UPDATE Intersectii
		SET ora_plecarii = @ora_plecarii, ora_sosirii = @ora_sosirii
		WHERE id_rute = @id_ruta AND id_statii = @id_statie

		RETURN
	END
	
	INSERT INTO Intersectii (id_statii, id_rute, ora_plecarii, ora_sosirii) VALUES (@id_statie, @id_ruta, @ora_plecarii, @ora_sosirii)
END
GO

-- Verificare
EXECUTE dbo.AddIntersection @id_statie=2, @id_ruta=8, @ora_plecarii='07:59:59', @ora_sosirii='08:00:00'
EXECUTE dbo.AddIntersection @id_statie=2, @id_ruta=8, @ora_plecarii='08:00:00', @ora_sosirii='07:59:59'

SELECT * FROM Intersectii


-- 3. View

-- Adaugam sa avem Deva-Cluj cu toate statiile
EXECUTE dbo.AddIntersection @id_statie=3, @id_ruta=4, @ora_plecarii='11:35:00', @ora_sosirii='11:30:00'
EXECUTE dbo.AddIntersection @id_statie=4, @id_ruta=4, @ora_plecarii='12:40:00', @ora_sosirii='12:35:00'
EXECUTE dbo.AddIntersection @id_statie=5, @id_ruta=4, @ora_plecarii='14:50:00', @ora_sosirii='14:45:00'
EXECUTE dbo.AddIntersection @id_statie=6, @id_ruta=4, @ora_plecarii='18:05:00', @ora_sosirii='18:00:00'
GO

-- Metoda Miha
CREATE OR ALTER VIEW vw_Rute_Toate_Statii
AS
SELECT nume FROM Rute r
WHERE (SELECT COUNT(*) FROM Statii) = (SELECT COUNT(*) FROM Intersectii WHERE id_rute = R.id_r)
GO

-- Metoda profei
CREATE OR ALTER VIEW vw_Rute_Toate_Statii_V2
AS
SELECT nume FROM Rute r
INNER JOIN Intersectii i ON i.id_rute = r.id_r
GROUP BY id_r, nume
HAVING COUNT(*) = (SELECT COUNT(*) FROM Statii)
GO


-- Verificare
SELECT * FROM vw_Rute_Toate_Statii
SELECT * FROM vw_Rute_Toate_Statii_V2


-- Scoatem baza de date sa mai avem memorie
USE master
DROP DATABASE GestiuneTrenuri