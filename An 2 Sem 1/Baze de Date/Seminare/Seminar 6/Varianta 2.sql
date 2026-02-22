CREATE DATABASE ReviewRestaurant
USE ReviewRestaurant


--1. Creem
CREATE TABLE TipuriRestaurant
(
	id_t INT PRIMARY KEY IDENTITY,
	nume NVARCHAR(100),
	descriere NVARCHAR(300)
)

CREATE TABLE Orase
(
	id_o INT PRIMARY KEY IDENTITY,
	nume NVARCHAR(100)
)

CREATE TABLE Restaurante
(
	id_r INT PRIMARY KEY IDENTITY,
	nume NVARCHAR(100),
	adresa NVARCHAR(100),
	nr_telefon NVARCHAR(20),
	id_oras INT FOREIGN KEY REFERENCES Orase(id_o) ON DELETE CASCADE,
	id_tip INT FOREIGN KEY REFERENCES TipuriRestaurant(id_t) ON DELETE CASCADE
)

CREATE TABLE Utilizatori
(
	id_u INT PRIMARY KEY IDENTITY,
	nume NVARCHAR(100),
	email NVARCHAR(100),
	parola NVARCHAR(100)
)

CREATE TABLE Note
(
	id_restaurant INT FOREIGN KEY REFERENCES Restaurante(id_r) ON DELETE CASCADE,
	id_utilizator INT FOREIGN KEY REFERENCES Utilizatori(id_u) ON DELETE CASCADE,
	nota FLOAT,

	CONSTRAINT pk_Note PRIMARY KEY (id_restaurant, id_utilizator)
)


-- 1,5. Inseram
INSERT INTO TipuriRestaurant (nume, descriere) VALUES
('Romanesc', 'Mamaliga si spanac'), -- 1
('Turcesc', 'Shaorma si nationalism'), -- 2
('Chinez', 'Avem pui shanghai') -- 3

INSERT INTO Orase (nume) VALUES
('Deva'), -- 1
('Baia mare'), -- 2
('Cluj') -- 3

INSERT INTO Restaurante (nume, adresa, nr_telefon, id_oras, id_tip) VALUES
('La Turku', 'langa cantina umf', '0755 523 532', 3, 2), -- 1
('Camera lui Petru', 'Casa Buftea', '0741 162 829', 3, 1), -- 2
('Casa lui Petru', 'Pe deal', '0737 759 783', 1, 1), -- 3
('Casa lui Oana', 'Parc', '07 something', 2, 3) -- 4

INSERT INTO Utilizatori (nume, email, parola) VALUES
('ClownsAreCreepy', 'petrupopescut@gmail.com', 'pass'), -- 1
('Bonk', 'oana@gmail.com', 'a1r2t3i4s5t6'), -- 2
('Nicol', 'bianca@gmail.com', '<3Motorcycles'), -- 3
('Chris', 'tarlea@gmail.com', 'iHateMinorities') -- 4

INSERT INTO Note (id_restaurant, id_utilizator, nota) VALUES
(1, 1, 9), -- 1
(2, 1, 8), -- 2
(3, 1, 10), -- 3
(3, 4, 8.5), -- 4
(3, 2, 4) -- 5
GO


-- 2. Procedura
CREATE OR ALTER PROCEDURE adaugaNota
	@id_restaurant INT,
	@id_utilizator INT,
	@nota FLOAT
AS
	IF EXISTS (SELECT 1 FROM Note WHERE id_restaurant = @id_restaurant AND id_utilizator = @id_utilizator)
		UPDATE Note
			SET nota = @nota
			WHERE @id_restaurant = id_restaurant AND @id_utilizator = id_utilizator
	ELSE
		INSERT INTO Note (id_restaurant, id_utilizator, nota) VALUES
			(@id_restaurant, @id_utilizator, @nota)
GO


-- 3. Functie
CREATE OR ALTER FUNCTION uf_findByEmail(@email NVARCHAR(100))
RETURNS TABLE
AS
RETURN 
	SELECT 
		t.nume AS [Tip Restaurantului],
		r.nume AS [Nume Restaurant], 
		r.nr_telefon AS [Telefon Restaurant], 
		o.nume AS [Orasul Restaurantului], 
		n.nota AS [Nota], 
		u.nume AS [Nume Utilizator],
		u.email AS [Email Utilizator]
	FROM Note n
	INNER JOIN Restaurante r ON n.id_restaurant = r.id_r
	INNER JOIN Utilizatori u ON n.id_utilizator = u.id_u
	INNER JOIN TipuriRestaurant t ON r.id_tip = t.id_t
	INNER JOIN Orase o ON r.id_oras = o.id_o
	WHERE u.email = @email
GO

SELECT * FROM uf_findByEmail('petrupopescut@gmail.com')


-- USE master
-- DROP DATABASE ReviewRestaurant
