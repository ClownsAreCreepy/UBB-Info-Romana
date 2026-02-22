-- Functie scalara verifica daca numele unei categorii exista in tabelul Categorii
CREATE FUNCTION ExistaCategorie(@nume VARCHAR(70))
RETURNS BIT AS
BEGIN
IF (EXISTS(SELECT * FROM Categorii WHERE nume=@nume))
	RETURN 1
RETURN 0
END
GO
-- Apelul functiei
PRINT dbo.ExistaCategorie('elevi')
GO

-- Modificam definitia a.i. sa returneze valoare de tip VARCHAR(20)
ALTER FUNCTION ExistaCategorie(@nume VARCHAR(70))
RETURNS VARCHAR(20) AS
BEGIN
IF (EXISTS(SELECT * FROM Categorii WHERE nume=@nume))
	RETURN 'Exista'
RETURN 'Nu exista'
END
GO

-- Stergem functiei
DROP FUNCTION dbo.ExistaCategorie
GO

-- Functie de tip inline table-valued returneaza numele atractiilor, nota primita si email-ul vizitatorului 
-- pentru care toate atractiile care au varsta minima recomandata egala cu parametrul
CREATE FUNCTION ReturneazaNoteAtractii(@varsta_min INT)
RETURNS TABLE AS
RETURN SELECT A.nume, N.nota, V.email FROM Atractii A
INNER JOIN Note N ON A.cod_a = N.cod_atractii
INNER JOIN Vizitatori V ON N.cod_vizitatori = V.cod_v
WHERE A.varsta_min = @varsta_min
GO

SELECT * FROM dbo.ReturneazaNoteAtractii(12)
GO

-- Functia multi-statement table-valued returneaza un tabel care contine atractile evaluate de catre vizitatorul
-- care are email-ul dat ca parametru
-- tabelul returnat contine numele atractiei, nota primita, adresa de email a vizitatorului si tipul evaluarii
-- daca nota e mai mica decat 5, atunci evaluare va fi negativa. Altfel, pozitiva
CREATE FUNCTION NoteAtractii(@email VARCHAR(100))
RETURNS @NoteAtractii TABLE (atractie VARCHAR(100), email VARCHAR(100), nota REAL, tip_evaluare VARCHAR(10)) AS
BEGIN
INSERT INTO @NoteAtractii (atractie, nota, email)
SELECT A.nume, N.nota, V.email FROM Atractii A
INNER JOIN Note N ON A.cod_a = N.cod_atractii
INNER JOIN Vizitatori V ON N.cod_vizitatori = V.cod_v
WHERE V.email = @email
UPDATE @NoteAtractii SET tip_evaluare='pozitiva' WHERE nota>=5.0
UPDATE @NoteAtractii SET tip_evaluare='negativa' WHERE nota<5.0
RETURN
END
GO

SELECT * FROM dbo.NoteAtractii('petru@gmail.com')
GO

-- Exercitii pagina 11
-- 1. Sa se creeze o functie scalara care primeste numele unei categorii si returneaza codul acesteia
CREATE FUNCTION CodCategorie(@nume NVARCHAR(100))
RETURNS INT AS
BEGIN
	DECLARE @cod INT
	
	SELECT @cod = C.cod_c FROM Categorii C
	WHERE C.nume=@nume
	
	RETURN @cod
END
GO

PRINT dbo.CodCategorie('Aia batrani')
GO

-- 2. Functie tip inline table valued care returneaza toate sectiunile al caror nume se termina cu o litera data ca parametru de intrare
-- si au cel putin 2 caractere

CREATE OR ALTER FUNCTION EndSectiuni(@litera CHAR)
RETURNS TABLE AS
	RETURN SELECT * FROM Sectiuni S
	WHERE S.nume like '_%' + @litera
GO

SELECT * FROM dbo.EndSectiuni('a')
GO


-- ============================
-- VIEW
-- Crearea unui view:
-- CREATE VIEW view_name AS <select_statement>

-- Modificarea unui view:
-- ALTER VIEW view_name AS <select_statement>

-- Stergerea unui view:
-- DROP VIEW view_name

-- View care returneaza numele atractiilor, nota, numele si email-ul vizitatorilor
CREATE VIEW vw_NoteAtractii
AS
SELECT A.nume AS atractie, N.nota, V.nume, V.email FROM Atractii A
INNER JOIN Note N ON A.cod_a=N.cod_atractii
INNER JOIN Vizitatori V ON N.cod_vizitatori=V.cod_v
GO

SELECT * FROM vw_NoteAtractii
GO

-- Modificam definitia view-ului a.i. luam doar notele care sunt intre 5 si 7
ALTER VIEW vw_NoteAtractii
AS
SELECT A.nume AS atractie, N.nota, V.nume, V.email FROM Atractii A
INNER JOIN Note N ON A.cod_a=N.cod_atractii
INNER JOIN Vizitatori V ON N.cod_vizitatori = V.cod_v
WHERE N.nota BETWEEN 5.0 AND 7.0
GO

SELECT * FROM vw_NoteAtractii
GO

-- Cand interogam view-ul putem specifica explicit coloanele pe care dorim sa le returnam in result-set
SELECT atractie, nota, nume FROM vw_NoteAtractii
GO

-- Afisam definitia unui view
-- PRINT OBJECT_DEFINITION(OBJECT_ID('schema_name.view_name'))
-- EXEC sp_helptext 'schema_name.view_name'


-- Exercitii pagina 19
-- 1. View care afiseaza toate Categoriile al caror nume este egal cu 'pensionari' sau 'copii'
CREATE OR ALTER VIEW vw_CategoriiNume
AS
SELECT * FROM Categorii
WHERE nume='Aia batrani' OR nume='Aia inalti'
GO

SELECT * FROM vw_CategoriiNume
GO

-- 2. View care afiseaza toate sectiunile al caror nume incepe cu litera c
CREATE OR ALTER VIEW vw_SectiuniNume
AS
SELECT * FROM Sectiuni
WHERE nume = '%t'
GO

SELECT * FROM vw_SectiuniNume
GO

-- 3. View care afiseaza numele vizitatorilor, nota si numele atractiei
CREATE OR ALTER VIEW vw_Note
AS
SELECT V.nume AS vizitator, N.nota, A.nume AS atractie FROM Vizitatori V
INNER JOIN Note N ON N.cod_vizitatori = V.cod_v
INNER JOIN Atractii A ON N.cod_atractii = A.cod_a
GO

SELECT * FROM vw_Note
GO


-- ============================
-- TABELE SISTEM
-- sys.objects = contine cate o inregistrare pentru fiecare obiect creat in baza de date
-- sys.columns = contine cate o inregistrare pentru fiecare coloana a unui obiect care are coloane
-- sys.databases = contine care o inregistrare pentru fiecare baza de date existenta pe server

SELECT * FROM sys.objects
SELECT * FROM sys.columns
SELECT * FROM sys.databases


-- ============================
-- TRIGGER
-- DML: INSERT, UPDATE, DELETE
-- DDL: CREATE, ALTER, DROP

-- Trigger DML 
-- CREATE TRIGGER trigger_name
-- ON { table | view }
-- [ WITH <dml_trigger_option> [ ,...n] ]
-- { FOR | AFTER | INSTEAD OF }
-- { [ INSERT ] [ , ] [ UPDATE ] [ , ] [ DELETE ] }
-- [ WITH APPEND ]
-- [ NOT FOR REPLICATION ]
-- AS { sql_statement [ ; ] [ ,...n ] | EXTERNAL NAME
-- <method_specifier [ ; ] > }

-- FOR, AFTER: Trigger-ul se executa dupa ce s-a executat evenimentul declansator
-- INSTEAD OF: Trigger-ul se executa in locul evenimentului declansator

-- Daca se definesc mai multe trigger-e pe aceeasi actiune (eveniment), ele se executa in ordine aleatorie

-- Cand se executa un trigger, sunt disponibile doua tabele speciale:
--  inserted
--  deleted

-- Trigger care impiedica adaugarea unor inregistrari noi in tabelul Categorii
GO
CREATE TRIGGER IntroducereCategorie ON Categorii INSTEAD OF INSERT
AS
BEGIN
	RAISERROR('Momentan nu se pot insera date in acest tabel', 16, 1)
END


-- Trigger insereaza fiecare inregistrare stearsa din tabelul Categorii intr-un tabel numit CategoriiEliminate

CREATE TABLE CategoriiEliminate
(
cod_e INT PRIMARY KEY IDENTITY,
cod_c INT,
nume VARCHAR(70),
data_si_ora_eliminarii DATETIME
)
GO

CREATE TRIGGER EliminareCategorie ON Categorii AFTER DELETE
AS
BEGIN
	INSERT INTO CategoriiEliminate (cod_c, nume, data_si_ora_eliminarii)
	SELECT cod_c, nume, GETDATE() FROM deleted
END
GO

-- Trigger inregistreaza in ModificariNote toate modificarile de note
CREATE TABLE ModificareNote
(
cod_m INT PRIMARY KEY IDENTITY,
cod_a INT,
cod_v INT,
nota_initiala REAL,
nota_actualizata REAL,
data_si_ora_actualizarii DATETIME
)

GO
CREATE TRIGGER ActualizareNota ON NOTE FOR UPDATE
AS
BEGIN
INSERT INTO ModificareNote (cod_a, cod_v, nota_initiala, nota_actualizata, data_si_ora_actualizarii)
SELECT i.cod_atractii, i.cod_vizitatori, d.nota, i.nota, GETDATE() FROM inserted i
INNER JOIN deleted d ON i.cod_atractii = d.cod_atractii AND i.cod_vizitatori = d.cod_vizitatori
END


-- OUTPUT
-- Se actualizeaza numele categoriei cu valoarea seniori si se afiseaza intr-un result-set codul, valoarea veche a numelui,
-- valoarea noua a numelui, data curenta si numele login-ului care a realizat modificarea

UPDATE Categorii SET nume='pensionari'
OUTPUT inserted.cod_c, deleted.nume nume_initial, inserted.nume nume_actual, GETDATE() AS data_si_ora, SUSER_SNAME() AS server_user
WHERE nume='seniori'


-- ============================
-- Cursoare
-- proceseaza pe rand fiecare inregistrare dintr-un result set

-- Fetch - luam o inregistrare din cursor
-- FETCH FIRST - returneaza prima inregistrare
-- FETCH NEXT - returneaza inregistrarea care urmeaza dupa ultima inregistrare returnata
-- FETCH PRIOR - returneaza inregistrarea care se afla inaintea ultimei inregistrari returnate
-- FETCH LAST - returneaza ultima inregistrare din cursor

-- FETCH ABSOLUTE n - ia a n-a inregistrare din cursor
-- FETCH RELATIVE n - ia a n-a inregistrare dupa/inainte ultima inregistrare returnata

-- DECLARE cursor_name CURSOR [ LOCAL | GLOBAL ]
-- [ FORWARD_ONLY | SCROLL ]
-- [ STATIC | KEYSET | DYNAMIC | FAST_FORWARD ]
-- [ READ_ONLY | SCOLL_LOCKS | OPTIMISTIC ]
-- [ TYPE_WARNING ]
-- FOR select_statement
-- [ FOR UPDATE [ OF column_name [ ,...n ] ] ]

-- Exemplu cursor
DECLARE @nume VARCHAR (100), @email VARCHAR(100), @categorie VARCHAR(70)

DECLARE cursorVizitatori CURSOR FAST_FORWARD FOR
SELECT V.nume, V.email, C.nume FROM Vizitatori V
INNER JOIN Categorii C ON V.cod_categorii = C.cod_c

OPEN cursorVizitatori 
FETCH NEXT FROM cursorVizitatori INTO @nume, @email, @categorie
WHILE @@FETCH_STATUS=0
BEGIN
PRINT 'Vizitatorul ' + @nume + ', ' + @email + ' face parte din categoria ' + @categorie
FETCH NEXT FROM cursorVizitatori INTO @nume, @email, @categorie
END
CLOSE cursorVizitatori 
DEALLOCATE cursorVizitatori 

-- Exercitii pagina 42
-- 1. Trigger care impiedica executia operatiilor de stergere din tabelul Categorii si afiseaza mesaj
GO
CREATE TRIGGER StergereCategorie ON Categorii INSTEAD OF DELETE
AS
BEGIN
	RAISERROR('Momentan nu se pot sterge date din acest tabel', 16, 1)
END

-- 2.Alt trigger pentru insert, update sau delete
GO
CREATE TRIGGER ModificareVizitatori ON Vizitatori INSTEAD OF INSERT
AS
BEGIN
	RAISERROR('Momentan nu se pot modifica date din acest tabel', 16, 1)
END