-- 'CREATE' - Daca procedura nu exista, va fi creata
-- 'ALTER' - Daca procedura exista, va fi modificata
-- 'Cluj Napoca' - Valoare default pentru parametru
CREATE OR ALTER PROCEDURE AdaugaPersoana @nume VARCHAR(100), @prenume VARCHAR(100),
@localitate VARCHAR(100) = 'Cluj-Napoca'
AS
BEGIN
INSERT INTO Persoane (nume, prenume, localitate) VALUES
(@nume, @prenume, @localitate)
END
-- Apelul procedurii stocate
EXEC AdaugaPersoana 'Pop', 'Andrei', 'Sibiu'
GO

-- Procedura stocata adauga o constrangere de valoare implicita pentru varsta_min
CREATE PROCEDURE AdaugaConstrangereDefault
AS
BEGIN
ALTER TABLE Atractii
ADD CONSTRAINT df_varsta_min DEFAULT 12 FOR varsta_min
END
-- Apelam procedura
EXEC AdaugaConstrangereDefault
GO

-- Procedura returneaza inforamtii pentru toate atractiile care au varsta minima recomandata egala cu parametrul de intrare
CREATE OR ALTER PROCEDURE ReturneazaAtractiiCuVarstaMin @varsta_min INT
AS 
BEGIN
SELECT nume, descriere, varsta_min FROM Atractii
WHERE varsta_min = @varsta_min
END
-- Apelam
EXEC ReturneazaAtractiiCuVarstaMin @varsta_min = 12
GO

-- Procedura returneaza prin intermediul parametrului de iesire ce e mai sus
CREATE OR ALTER PROCEDURE ReturneazaAtractiiCuVarstaMin @varsta_min INT, @nr_atractii INT OUTPUT
AS
BEGIN
SELECT @nr_atractii=COUNT(*) FROM Atractii WHERE varsta_min = @varsta_min
END
GO

-- Apelam cu parametru de output
DECLARE @nr_atractii AS INT
SET @nr_atractii = 0
EXEC ReturneazaAtractiiCuVarstaMin 12, @nr_atractii = @nr_atractii OUTPUT
PRINT @nr_atractii
GO

-- Nu executam atat procedura, cat si exec-ul. Executam intai procedure, apoi exec-ul separat


-- Exercitii pagina 10
-- 1. Procedura care insereaza o sectiune nou in tabelul Sectiuni
-- Procedura are doi parametrii de intrare: nume si descriere
CREATE OR ALTER PROCEDURE AddNewSection @nume NVARCHAR(100), @descriere NVARCHAR(100)
AS
BEGIN
INSERT INTO Sectiuni (nume, descriere) VALUES (@nume, @descriere)
END

EXEC AddNewSection 'Sectiunea Noua', 'Sectiunea sub constructie'
GO

-- 2. Procedura care actualizeaza adresa de email a unui vizitator
-- Procedura are 2 parametrii de intrare: cod si noua adresa de email
CREATE OR ALTER PROCEDURE UpdateEmail @cod_v INT, @email NVARCHAR(100)
AS
BEGIN
UPDATE Vizitatori SET email = @email
WHERE cod_v = @cod_v
END

EXEC UpdateEmail 7, 'gagi@gmail.com'
GO

-- 3. Procedura returneaza numele, adresa de email si numele total de note pt toti vizitatorii care au dat cel putin o nota
CREATE OR ALTER PROCEDURE ReturnActiveVizitatori
AS
BEGIN
SELECT V.nume, V.email, COUNT(V.cod_v) AS nr_note FROM Vizitatori V
INNER JOIN Note N ON V.cod_v = N.cod_vizitatori
GROUP BY V.nume, V.email, V.cod_v
END

EXEC ReturnActiveVizitatori
GO


-- RAISERROR( {msg_id | msg_str | @local_variable} {, severity, state})
-- severity e intre 0 si 18
CREATE OR ALTER PROCEDURE ReturneazaAtractiiCuVarstaMin @varsta_min INT, @nr_atractii INT OUTPUT
AS
BEGIN
SELECT @nr_atractii = COUNT(*) FROM Atractii WHERE varsta_min = @varsta_min
IF (@nr_atractii = 0)
	RAISERROR('Nu a fost returnata nicio atractie!', 16, 1)
END
GO

DECLARE @nr_atractii as INT
SET @nr_atractii = 0
EXEC ReturneazaAtractiiCuVarstaMin 90, @nr_atractii OUTPUT
PRINT @nr_atractii

-- Stergem procedurile stocate cu DROP PROCEDURE
DROP PROCEDURE ReturneazaAtractiiCuVarstaMin
GO

-- Variabilele globale in SQL incept cu @@
-- @@ERROR contine numarul celei mai recente de erori
-- @@IDENTITY contine valoarea campului IDENTITY AL ULTIMEI INREGISTRARI INSERATE
-- @@ROWCOUNT contine numarul de inregistrari afectate de cea mai recenta instructiune executata
-- @@SERVERNAME contine numele instantei
-- @@SPID contine ID-ul de sesiune al procesului de utilizator curent
-- @@VERSION contine informatii in legatura cu sistemul

-- SET NOCOUNT ON - opreste returnarea mesajului cu numarul de inregistrari afectate de ultima instructiune
-- Putem si SET NOCOUNT OFF
-- @@ROWCOUNT va fi modificata intotdeauna


-- Exemplu procedura care executa cod SQL in mod dinamic
CREATE OR ALTER PROCEDURE ReturneazaDateDinTabel @nume_tabel VARCHAR(100)
AS
BEGIN
EXEC('SELECT * FROM ' + @nume_tabel)
END

EXEC ReturneazaDateDinTabel Vizitatori
GO


-- In loc de EXEC putem folosi sp_executesql pentru performanta mai buna
DECLARE @sql NVARCHAR(100)
SET @sql = N'SELECT nume, descriere FROM Sectiuni WHERE nume<>@nume'
EXEC sp_executesql @sql, N'@nume AS VARCHAR(100)', @nume=N'Sectiunea Centrala'
GO

-- Exemplu de procedura stocata care returneaza STATUS CODES:
CREATE PROCEDURE VerificaVarstaMin @cod_a INT
AS
BEGIN
IF ((SELECT varsta_min FROM Atractii WHERE cod_a = @cod_a) = 12)
	RETURN 1
ELSE
	RETURN 2
END

-- Se apeleaza astfel
DECLARE @status INT
EXEC @status = VerificaVarstaMin 1
SELECT 'Status' = @status
GO


-- Exercitii pagina 25
-- 1. Procedura insereaza o categorie noua
CREATE PROCEDURE AdaugaCategorie @categorie NVARCHAR(100)
AS
BEGIN
IF ((SELECT cod_c FROM Categorii WHERE nume = @categorie) IS NOT NULL)
	PRINT 'Categoria exista deja!'
ELSE
	INSERT INTO Categorii VALUES (@categorie)
END

EXEC AdaugaCategorie 'Aia inalti'
SELECT * FROM Sectiuni
GO

-- 2. Procedura insereaza o atractie noua
CREATE OR ALTER PROCEDURE AdaugaAtractii @nume NVARCHAR(100), @descriere NVARCHAR(100), @varsta_min INT, @nume_sectiune NVARCHAR(100)
AS
BEGIN
IF ((SELECT cod_s FROM Sectiuni WHERE nume = @nume_sectiune) IS NULL)
	INSERT INTO Sectiuni VALUES (@nume_sectiune, NULL)

DECLARE @cod_sectiune INT
SELECT @cod_sectiune = cod_s FROM Sectiuni WHERE nume = @nume_sectiune

INSERT INTO Atractii VALUES (@nume, @descriere, @varsta_min, @cod_sectiune)
END

SELECT * FROM Atractii
SELECT * FROM Sectiuni
EXEC AdaugaAtractii 'Painball', 'Piu piu colorat', 14, 'Sectiunea Sud-Est'
EXEC AdaugaAtractii 'Damn', 'Idk', 7, 'Sectiunea mama please name it mama i sectiune sud nord'
GO

-- 3. Procedura verifica daca exista un vizitator caruia ii corespunde adresa de email data
CREATE OR ALTER PROCEDURE VerificaEmail @email NVARCHAR(100)
AS
BEGIN
DECLARE @cod_vizitator INT
SELECT @cod_vizitator = cod_v FROM Vizitatori WHERE email = @email

IF (@cod_vizitator IS NULL)
	PRINT 'Vezi ca nu exista lol'
ELSE
	PRINT @cod_vizitator
END

SELECT * FROM Vizitatori
EXEC VerificaEmail 'dani@gmail.ro'
GO


-- Sintaxa WHILE
-- WHILE boolean expression
--	   { sql_statement | statement_block | BREAK | CONTINUE }


-- GOTO - executa salt in executie la o portiune din cod marcata label
-- Label: some sql statements
-- GOTO Label


-- WAITFOR - blocheaza executia pana cand un interval de timp specificat e atins sau pana ceva modifica sau returneaza o inregistrare
-- WAITFOR
--	   { DELAY 'time_to_pass' | TIME 'time_to_execute | 
--	   [ (recieve statement ) | (get_conversation_group_statement ) ] 
--     [ , TIMEOUT timeout ]}

-- Exemplu: 
-- WAITFOR TIME '22:00' (executia continua la 22:00)
-- WAITFOR DELAY '03:00:00' (executia continua peste 3 ore)


-- THROW [ {error nymber | @local_variable },
--		  { message | @local_variable },
--		  { state | @local_variable } ] [ ; ]

-- Exemplu:
-- THROW 50002, N'Inregistrarea nu exista!', 1;

-- BEGIN TRY
-- { sql_statement | statement block }
-- END TRY
-- BEGIN CATCH
-- [ { sql_statement | statement block } ]
-- END CATCH
-- [ ; ]


-- Exercitii pagina 34
-- 1. Procedura sterge o atractie, daca aceasta nu are note
CREATE OR ALTER PROCEDURE StergeAtractie @nume_atractie NVARCHAR(100)
AS
BEGIN
DECLARE @cod_a INT
SELECT @cod_a = cod_a FROM Atractii WHERE @nume_atractie = nume

DECLARE @nr_note INT
SELECT @nr_note = COUNT(cod_atractii) FROM Note N
WHERE @cod_a = cod_atractii

IF (@nr_note = 0)
	DELETE FROM Atractii WHERE cod_a = @cod_a
ELSE
	PRINT 'Atractia aleasa are note!'
END

SELECT * FROM Atractii A
LEFT JOIN Note N ON N.cod_atractii = A.cod_a

EXEC StergeAtractie 'Damn'
GO

-- 2. Procedura insereaza o nota
CREATE OR ALTER PROCEDURE AdaugaNota @cod_atractie INT, @cod_vizitator INT, @nota INT
AS
BEGIN
IF ( (SELECT COUNT(cod_a) FROM Atractii WHERE cod_a = @cod_atractie) = 0)
	THROW 50002, N'Atractia nu exista!', 1

IF ( (SELECT COUNT(cod_v) FROM Vizitatori WHERE cod_v = @cod_vizitator) = 0)
	THROW 50003, N'Vizitatorul nu exista!', 1

IF ( @nota NOT BETWEEN 1 AND 10)
	THROW 50004, N'Nota trebuie sa fie intre 1 si 10!', 2

INSERT INTO Note (cod_atractii, cod_vizitatori, nota) VALUES (@cod_atractie, @cod_vizitator, @nota)
END

SELECT * FROM Vizitatori
SELECT * FROM Atractii
SELECT * FROM Note
EXEC AdaugaNota 3, 2, 8
GO

-- 3. Insereaza 50 de atractii
CREATE OR ALTER PROCEDURE Adauga50Atractii
AS
BEGIN
	DECLARE @nume NVARCHAR(100), @descriere NVARCHAR(300), @varsta_min INT, @cod_sectiune INT
	DECLARE @i INT = 1

	WHILE @i <= 50
		BEGIN
				SET @nume = 'Atractia ' + CAST(@i AS NVARCHAR(10))
				SET @descriere = 'Descriere automata generata la ' + CONVERT(NVARCHAR(30), GETDATE())
				SET @varsta_min = FLOOR(RAND() * 22)		-- intre 0 si 21
 				SET @cod_sectiune = FLOOR(RAND() * 9 + 1)   -- intre 1 si 9

				INSERT INTO Atractii VALUES (@nume, @descriere, @varsta_min, @cod_sectiune)
				SET @i = @i + 1
		END
END

SELECT * FROM Sectiuni
SELECT * FROM Atractii
EXEC Adauga50Atractii
