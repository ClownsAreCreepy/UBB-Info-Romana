CREATE DATABASE Samsara
Use Samsara

-- 1.
CREATE TABLE Clienti
(
	id_c INT PRIMARY KEY IDENTITY(1,1),
	nume NVARCHAR(100),
	nr_telefon NVARCHAR(15)
)

CREATE TABLE Comenzi
(
	id_c INT PRIMARY KEY IDENTITY(1,1),
	adresa NVARCHAR(100),
	data DATE,
	id_client INT FOREIGN KEY REFERENCES Clienti(id_c)
)

CREATE TABLE Preparate
(
	id_p INT PRIMARY KEY IDENTITY(1,1),
	denumire NVARCHAR(100),
	cantitate INT,
	pret INT
)

CREATE TABLE Ingrediente
(
	id_i INT PRIMARY KEY IDENTITY(1,1),
	denumire NVARCHAR(100),
	calorii INT
)

CREATE TABLE Livrare
(
	id_l INT PRIMARY KEY IDENTITY(1,1),
	id_comanda INT FOREIGN KEY REFERENCES Comenzi(id_c),
	id_preparat INT FOREIGN KEY REFERENCES Preparate(id_p)
)

CREATE TABLE Mancare
(
	id_preparat INT FOREIGN KEY REFERENCES Preparate(id_p),
	id_ingredient INT FOREIGN KEY REFERENCES Ingrediente(id_i),
	CONSTRAINT pk_Mancare PRIMARY KEY (id_preparat, id_ingredient)
)

-- 2.
GO
CREATE OR ALTER PROCEDURE StergereIngredient
	@denumire NVARCHAR(100)
AS
BEGIN
	-- Gasim id-ul ingredientului cu acea denumire
	DECLARE @id_ingredient INT
	SELECT @id_ingredient = id_i FROM Ingrediente
	WHERE denumire = @denumire

	-- Cate ingrediente contin acel ingredient
	DECLARE @nr_comenzi_sterse INT

	SELECT @nr_comenzi_sterse = COUNT(*) FROM Livrare l
	INNER JOIN Preparate p ON l.id_preparat = p.id_p
	INNER JOIN Mancare m ON m.id_preparat = p.id_p
	WHERE m.id_ingredient = @id_ingredient
	
	-- Stergem acele comenzi din livrari ca sa evitam foreign key violation
	-- Folosim acelasi select ca mai sus

	DELETE FROM Livrare WHERE id_comanda IN (
	SELECT l.id_comanda FROM Livrare l
	INNER JOIN Preparate p ON l.id_preparat = p.id_p
	INNER JOIN Mancare m ON m.id_preparat = p.id_p
	WHERE m.id_ingredient = @id_ingredient)

	-- nu mai putem folosi select-ul de mai sus pentru a sterge comenzi din cauza ca
	-- in livrari nu mai avem comenzile care ne intereseaza

	-- daca o comanda nu mai exista in livrari trebuie stearsa
	-- nu are sens sa existe o comanda fara preparate anyway
	DELETE FROM Comenzi WHERE id_c NOT IN (SELECT id_comanda FROM Livrare)

	RETURN @nr_comenzi_sterse
END

-- 3.
GO
CREATE OR ALTER VIEW vw_ComenziBogdan
AS
SELECT c.data, SUM(p.pret) AS Suma FROM Livrare l
INNER JOIN Preparate p ON l.id_preparat = p.id_p
INNER JOIN Comenzi c ON l.id_comanda = c.id_c
INNER JOIN Clienti cl ON c.id_client = cl.id_c
WHERE cl.nume = 'Bogdan Ioan'
GROUP BY c.id_c, c.data