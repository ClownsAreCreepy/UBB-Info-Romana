CREATE DATABASE Justitie
USE Justitie

-- 1.

CREATE TABLE Magistrati
(
	id_m INT PRIMARY KEY IDENTITY(1,1),
	nume NVARCHAR(100),
	prenume NVARCHAR(100),
	ani_experienta INT
)

CREATE TABLE Grefieri
(
	id_g INT PRIMARY KEY IDENTITY(1,1),
	nume NVARCHAR(100),
	prenume NVARCHAR(100)
)

CREATE TABLE TipuriDosare
(
	id_t INT PRIMARY KEY IDENTITY(1,1),
	nume NVARCHAR(100)
)

CREATE TABLE Dosare
(
	id_d INT PRIMARY KEY IDENTITY(1,1),
	numar INT,
	complexitate INT,
	id_tip INT FOREIGN KEY REFERENCES TipuriDosare(id_t)
)

CREATE TABLE CompletFond
(
	id_cf INT PRIMARY KEY IDENTITY(1,1),
	id_dosar INT FOREIGN KEY REFERENCES Dosare(id_d),
	id_mag INT FOREIGN KEY REFERENCES Magistrati(id_m) UNIQUE,
	id_gref INT FOREIGN KEY REFERENCES Grefieri(id_g)
)

CREATE TABLE CompletApel
(
	id_ca INT PRIMARY KEY IDENTITY(1,1),
	id_dosar INT FOREIGN KEY REFERENCES Dosare(id_d),
	id_mag1 INT FOREIGN KEY REFERENCES Magistrati(id_m) UNIQUE,
	id_mag2 INT FOREIGN KEY REFERENCES Magistrati(id_m) UNIQUE,
	id_gref INT FOREIGN KEY REFERENCES Grefieri(id_g)
)

CREATE TABLE CompletRecurs
(
	id_cr INT PRIMARY KEY IDENTITY(1,1),
	id_dosar INT FOREIGN KEY REFERENCES Dosare(id_d),
	id_mag1 INT FOREIGN KEY REFERENCES Magistrati(id_m) UNIQUE,
	id_mag2 INT FOREIGN KEY REFERENCES Magistrati(id_m) UNIQUE,
	id_mag3 INT FOREIGN KEY REFERENCES Magistrati(id_m) UNIQUE,
	id_gref INT FOREIGN KEY REFERENCES Grefieri(id_g)
)
/*
CREATE TABLE Complet
(
    id_c INT PRIMARY KEY IDENTITY(1,1)
	id_dosar INT FOREIGN KEY REFERENCES Dosare(id_d),
    id_tip INT FOREIGN KEY REFERENCES TipuriDosare(id_t),
	id_mag1 INT FOREIGN KEY REFERENCES Magistrati(id_m),
	id_mag2 INT FOREIGN KEY REFERENCES Magistrati(id_m) NULL,
	id_mag3 INT FOREIGN KEY REFERENCES Magistrati(id_m) NULL,
	id_gref INT FOREIGN KEY REFERENCES Grefieri(id_g)

)
*/
-- 2.
GO
CREATE OR ALTER PROCEDURE AsignDosar
    @id_dosar INT,
    @id_magistrat_recuzat INT
AS
    DECLARE @tip_dosar NVARCHAR(100)
   
    SELECT @tip_dosar = t.nume FROM Dosare d 
    INNER JOIN TipuriDosare t ON d.id_tip = t.id_t 
    WHERE d.id_d = @id_dosar

    DECLARE @id_m1 INT, @id_m2 INT, @id_m3 INT, @id_g INT

    IF @tip_dosar = 'fond'
    BEGIN
    
        SELECT TOP 1 @id_m1 = id_mag, @id_g = id_gref FROM CompletFond
        WHERE id_mag <> @id_magistrat_recuzat
        GROUP BY id_mag, id_gref
        HAVING COUNT(*) < 5
        
        IF @id_m1 IS NOT NULL
            INSERT INTO CompletFond (id_dosar, id_mag, id_gref) VALUES (@id_dosar, @id_m1, @id_g)
        ELSE
            PRINT 'Complet indisponibil'
    END

    ELSE IF @tip_dosar = 'apel'
    BEGIN
        SELECT TOP 1 @id_m1 = id_mag1, @id_m2 = id_mag2, @id_g = id_gref
        FROM CompletApel
        WHERE id_mag1 <> @id_magistrat_recuzat AND id_mag2 <> @id_magistrat_recuzat
        GROUP BY id_mag1, id_mag2, id_gref
        HAVING COUNT(*) < 5

        IF @id_m1 IS NOT NULL
            INSERT INTO CompletApel (id_dosar, id_mag1, id_mag2, id_gref)
            VALUES (@id_dosar, @id_m1, @id_m2, @id_g)
        ELSE
            PRINT 'Complet indisponibil' 
    END

    ELSE IF @tip_dosar = 'recurs'
    BEGIN
        SELECT TOP 1 @id_m1 = id_mag1, @id_m2 = id_mag2, @id_m3 = id_mag3, @id_g = id_gref FROM CompletRecurs
        WHERE id_mag1 <> @id_magistrat_recuzat 
          AND id_mag2 <> @id_magistrat_recuzat 
          AND id_mag3 <> @id_magistrat_recuzat
        GROUP BY id_mag1, id_mag2, id_mag3, id_gref
        HAVING COUNT(*) < 5

        IF @id_m1 IS NOT NULL
            INSERT INTO CompletRecurs (id_dosar, id_mag1, id_mag2, id_mag3, id_gref) 
            VALUES (@id_dosar, @id_m1, @id_m2, @id_m3, @id_g)
        ELSE
            PRINT 'Complet indisponibil'
    END
GO

-- 3.
CREATE OR ALTER VIEW vw_NrDosare
AS
SELECT 
    COUNT(*) AS [Nr Dosare], AVG(d.complexitate) as [Medie Complexitate] FROM Dosare d
    INNER JOIN (
    SELECT id_dosar FROM CompletFond
    WHERE id_mag IN (SELECT id_m FROM Magistrati WHERE nume = 'Ioan' AND prenume = 'Bogdan')
      AND id_gref IN (SELECT id_g FROM Grefieri WHERE nume = 'Suciu' AND prenume = 'Dan')
    UNION ALL
    SELECT id_dosar FROM CompletApel
    WHERE (id_mag1 IN (SELECT id_m FROM Magistrati WHERE nume = 'Ioan' AND prenume = 'Bogdan')
        OR id_mag2 IN (SELECT id_m FROM Magistrati WHERE nume = 'Ioan' AND prenume = 'Bogdan'))
      AND id_gref IN (SELECT id_g FROM Grefieri WHERE nume = 'Suciu' AND prenume = 'Dan')
    UNION ALL
    SELECT id_dosar FROM CompletRecurs
    WHERE (id_mag1 IN (SELECT id_m FROM Magistrati WHERE nume = 'Ioan' AND prenume = 'Bogdan')
        OR id_mag2 IN (SELECT id_m FROM Magistrati WHERE nume = 'Ioan' AND prenume = 'Bogdan')
        OR id_mag3 IN (SELECT id_m FROM Magistrati WHERE nume = 'Ioan' AND prenume = 'Bogdan'))
      AND id_gref IN (SELECT id_g FROM Grefieri WHERE nume = 'Suciu' AND prenume = 'Dan')) v ON d.id_d = v.id_dosar
GO

-- USE master
-- DROP DATABASE Justitie