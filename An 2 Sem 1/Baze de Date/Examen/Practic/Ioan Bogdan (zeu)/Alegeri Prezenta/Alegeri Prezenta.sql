CREATE DATABASE Alegeri
Use Alegeri

-- 1.
CREATE TABLE Sectii
(
	id_s INT PRIMARY KEY IDENTITY(1,1),
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

CREATE TABLE Voturi
(
	id_v INT PRIMARY KEY IDENTITY(1,1),
	ora TIME,
	pe_lista_suplimentara BIT,
	id_cetatean INT FOREIGN KEY REFERENCES Cetateni(id_c) UNIQUE,
	id_sectie INT FOREIGN KEY REFERENCES Sectii(id_s)
)

CREATE TABLE Caterings
(
	id_c INT PRIMARY KEY IDENTITY(1,1),
	nume NVARCHAR(100),
	cif NVARCHAR(100)
)

CREATE TABLE Sectii_Caterings
(
	id_s INT PRIMARY KEY IDENTITY(1,1),
	id_sectie INT FOREIGN KEY REFERENCES Sectii(id_s),
	id_catering INT FOREIGN KEY REFERENCES Caterings(id_c)
)


-- 1.5
INSERT INTO Sectii (numar) VALUES
(1),
(2),
(3)

INSERT INTO Cetateni (nume, prenume, cnp, id_sectie) VALUES
('Chiorean', 'Oana', '5041118082209', 1),
('Marc', 'Bianca', '4041118082209', 3),
('Russu', 'Mihaela', '5044418082209', 1),
('Rusu', 'Mihai', '5043338082209', 2)

INSERT INTO Voturi (ora, pe_lista_suplimentara, id_cetatean, id_sectie) VALUES
('12:00:00', 0, 1, 1),
('16:00:00', 1, 2, 2),
('19:00:00', 0, 3, 1)

GO
-- 2.
CREATE OR ALTER PROCEDURE dbo.AdaugareVot
	@id_cetatean INT,
	@id_sectie INT
AS
BEGIN
	
	-- Daca exista cetateanul, afisam un mesaj si returnam 1
	DECLARE @nume NVARCHAR(100), @prenume NVARCHAR(100)
	
	IF EXISTS (SELECT 1 FROM Voturi
				WHERE id_cetatean = @id_cetatean)
	BEGIN
		SELECT @nume = nume, @prenume = prenume FROM Cetateni WHERE id_c = @id_cetatean
		PRINT N'Cetateanul ' + @nume + ' ' + @prenume + ' a votat deja!'
		RETURN 1
	END

	-- Vedem daca a votat acuma la aceeasi sectie la care e arondat

	DECLARE @pe_liste_suplimentare BIT, @sectia_cetateanului INT
	SELECT @sectia_cetateanului = id_sectie FROM Cetateni
	WHERE id_c = @id_cetatean

	IF @sectia_cetateanului = @id_sectie
		SET @pe_liste_suplimentare = 0
	ELSE
		SET @pe_liste_suplimentare = 1

	INSERT INTO Voturi (ora, pe_lista_suplimentara, id_cetatean, id_sectie) VALUES
	(GETDATE(), @pe_liste_suplimentare, @id_cetatean, @id_sectie)
END
GO

DECLARE @return_value INT

DELETE FROM Voturi WHERE id_cetatean = 4

EXEC @return_value = dbo.AdaugareVot @id_cetatean = 4, @id_sectie = 3
SELECT @return_value

SELECT * FROM Voturi


GO
-- 3.
CREATE OR ALTER VIEW vw_VoturiIntreOre
AS
SELECT '12-13' AS Ora, COUNT(*) AS [Numar de voturi] FROM Voturi
WHERE DATEPART(HOUR, Ora) = 12
UNION
SELECT '13-14' AS Ora, COUNT(*) AS [Numar de voturi] FROM Voturi
WHERE DATEPART(HOUR, Ora) = 13 
UNION
SELECT '14-15' AS Ora, COUNT(*) AS [Numar de voturi] FROM Voturi
WHERE DATEPART(HOUR, Ora) = 14 
GO

SELECT * FROM vw_VoturiIntreOre

-- Use master
-- DROP DATABASE Alegeri