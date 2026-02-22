CREATE DATABASE Caleidoscop
Use Caleidoscop

-- 1.
CREATE TABLE Episoade
(
	id_e INT PRIMARY KEY IDENTITY(1,1),
	nume NVARCHAR(100),
	DURATA INT, -- secunde
	ordine INT
)

CREATE TABLE Utilizatori
(
	id_u INT PRIMARY KEY IDENTITY(1,1),
	nume NVARCHAR(100),
	email NVARCHAR(100)
)

CREATE TABLE Vizionari
(
	id_utilizator INT FOREIGN KEY REFERENCES Utilizatori(id_u),
	id_episod INT FOREIGN KEY REFERENCES Episoade(id_e),
	CONSTRAINT pk_Vizionari PRIMARY KEY(id_utilizator, id_episod)
)

CREATE TABLE Actori
(
	id_a INT PRIMARY KEY IDENTITY(1,1),
	nume NVARCHAR(100)
)

CREATE TABLE Roluri
(
	id_actor INT FOREIGN KEY REFERENCES Actori(id_a),
	id_episod INT FOREIGN KEY REFERENCES Episoade(id_e),
	CONSTRAINT pk_Roluri PRIMARY KEY (id_actor, id_episod)
)

CREATE TABLE Replici
(
	id_r INT PRIMARY KEY IDENTITY(1,1),
	cuvinte NVARCHAR(1000),
	timp TIME,
	id_actor INT FOREIGN KEY REFERENCES Actori(id_a),
	id_episod INT FOREIGN KEY REFERENCES Episoade(id_e)
)

-- 2.
GO
CREATE OR ALTER PROCEDURE Play
	@id_utilizator INT
AS
BEGIN
	-- verificam daca a vazut deja 9 sau 8 episoade
	DECLARE @nr_episoade_vauzte INT, @id_episod INT
	SELECT @nr_episoade_vauzte = COUNT(*) FROM Vizionari
	WHERE id_utilizator = @id_utilizator

	IF @nr_episoade_vauzte = 9
		RETURN
	IF @nr_episoade_vauzte = 8
	BEGIN
		
		SELECT @id_episod = id_e FROM Episoade
		WHERE ordine = 9
		
		INSERT INTO Vizionari VALUES (@id_utilizator, @id_episod)
		RETURN
	END

	-- Calculam urmatorul episod
	DECLARE @urmatorul_episod INT
	SET @urmatorul_episod = FLOOR(1 + RAND() * 8)

	-- Cat timp episodul nu e noua si nu e un episod pe care utilizatorul l-a vazut deja, generam un nr nou
	WHILE @urmatorul_episod <> 9 AND
		EXISTS (SELECT 1 FROM Vizionari v
					INNER JOIN Episoade e ON v.id_episod = e.id_e
					WHERE v.id_utilizator = @id_utilizator AND e.ordine = @urmatorul_episod)
		SET @urmatorul_episod = FLOOR(1 + RAND() * 8)

	SELECT @id_episod = id_e FROM Episoade WHERE ordine = @urmatorul_episod

	INSERT INTO Vizionari VALUES (@id_utilizator, @id_episod)
END
GO

-- 3.
SELECT a.nume + ': ' + r.cuvinte FROM Replici r
INNER JOIN Actori a ON r.id_actor = a.id_a
INNER JOIN Episoade e ON r.id_episod = e.id_e
ORDER BY e.ordine, r.timp

Use master
DROP DATABASE Caleidoscop