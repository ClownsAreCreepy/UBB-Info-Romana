-- Validam textul sa fie ok
CREATE OR ALTER FUNCTION dbo.uf_ValideazaText (@text NVARCHAR(100))
RETURNS BIT
AS
BEGIN
	DECLARE @rezultat BIT = 0
	IF @text IS NOT NULL AND LEN(@text) >= 1
		SET @rezultat = 1
	RETURN @rezultat
END
GO

-- Validam sa existe filmul
CREATE OR ALTER FUNCTION dbo.uf_ExistaFilm (@id_film INT)
RETURNS BIT
AS
BEGIN
	IF EXISTS (SELECT 1 FROM Filme WHERE id_f = @id_film)
		RETURN 1
	RETURN 0
END
GO

-- Validam sa existe firma
CREATE OR ALTER FUNCTION dbo.uf_ExistaFirma (@id_firma INT)
RETURNS BIT
AS
BEGIN
	IF EXISTS (SELECT 1 FROM Firme WHERE id_f = @id_firma)
		RETURN 1
	RETURN 0
END
GO

-- =============== Firme ===============
-- CREATE
CREATE OR ALTER PROCEDURE sp_Firme_Create
	@nume NVARCHAR(100),
	@tara NVARCHAR(100),
	@mesaj NVARCHAR(255) OUTPUT
AS
BEGIN
	SET NOCOUNT ON -- stops "1 row affected"

	IF dbo.uf_ValideazaText(@nume) = 0
	BEGIN
		SET @mesaj = 'Eroare: Numele firmei trebuie sa aiba minim un caracter!'
		RETURN
	END

	IF dbo.uf_ValideazaText(@tara) = 0
	BEGIN
		SET @mesaj = 'Eroare: Tara de unde provine firma trebuie sa aiba minim un caracter!'
		RETURN
	END
	
	IF EXISTS (SELECT 1 FROM Firme WHERE nume = @nume)
	BEGIN
		SET @mesaj = 'Eroare: O firma cu acest nume exista deja in baza de date!'
		RETURN
	END

	BEGIN TRY
		INSERT INTO Firme (nume, tara_origine)
		VALUES (@nume, @tara)
		
		SET @mesaj = 'Succes: Firma ' + @nume + ' a fost adaugata!'
	END TRY
	BEGIN CATCH
		SET @mesaj = 'Eroare SQL: ' + ERROR_MESSAGE()
	END CATCH
END
GO

--READ
CREATE OR ALTER PROCEDURE sp_Firme_Read
	@id_firma INT = NULL -- optional
AS
BEGIN
	SET NOCOUNT ON

	IF @id_firma IS NOT NULL
	BEGIN
		IF dbo.uf_ExistaFirma(@id_firma) = 0
		BEGIN
			PRINT 'Eroare: Nu exista nicio firma cu ID-ul ' + CAST(@id_firma AS VARCHAR(10)) + '!'
			RETURN
		END
	END

	SELECT * FROM Firme WHERE (@id_firma IS NULL OR id_f = @id_firma)
END
GO

-- UPDATE
CREATE OR ALTER PROCEDURE sp_Firme_Update
	@id_firma INT,
	@nume_nou NVARCHAR(100),
	@tara_noua NVARCHAR(100),
	@mesaj NVARCHAR(255) OUTPUT
AS
BEGIN
	SET NOCOUNT ON

	IF dbo.uf_ExistaFirma(@id_firma) = 0
	BEGIN
		SET @mesaj = 'Eroare: ID-ul firmei nu exista!'
		RETURN
	END

	IF dbo.uf_ValideazaText(@nume_nou) = 0
	BEGIN
		SET @mesaj = 'Eroare: Numele nou este invalid!'
		RETURN
	END

	IF dbo.uf_ValideazaText(@tara_noua) = 0
	BEGIN
		SET @mesaj = 'Eroare: Numele tarii actualizate este invalid!'
	END

	IF EXISTS (SELECT 1 FROM Firme WHERE @nume_nou = nume AND id_f != @id_firma)
	BEGIN
		SET @mesaj = 'Eroare: Exista deja o alta firma cu numele ' + @nume_nou + '!'
		RETURN
	END

	BEGIN TRY
		UPDATE Firme
		SET nume = @nume_nou, tara_origine = @tara_noua
		WHERE id_f = @id_firma

		SET @mesaj = 'Succes: Datele firmei au fost actualizate!'
	END TRY
	BEGIN CATCH
		SET @mesaj = 'Eroare SQL: ' + ERROR_MESSAGE()
	END CATCH
END
GO

-- DELETE
CREATE OR ALTER PROCEDURE sp_Firme_Delete
	@id_firma INT,
	@mesaj NVARCHAR(255) OUTPUT
AS
BEGIN
	SET NOCOUNT ON

	IF dbo.uf_ExistaFirma(@id_firma) = 0
	BEGIN
		SET @mesaj = 'Eroare: ID-ul firmei nu exista'
		RETURN
	END

	BEGIN TRY
		DELETE FROM Firme WHERE id_f = @id_firma
		SET @mesaj = 'Succes: Firma a fost stearsa'
	END TRY
	BEGIN CATCH
	-- Treubie sa scoatem din publicatii????
		IF ERROR_NUMBER() = 547
			SET @mesaj = 'Eroare: Nu puteti sterge aceasta firma deoarece are filme publicate!'
		ELSE
			SET @mesaj = 'Eroare SQL: ' + ERROR_MESSAGE()
	END CATCH
END
GO


-- =============== Filme ===============
-- CREATE
CREATE OR ALTER PROCEDURE sp_Filme_Create
	@titlu NVARCHAR(100),
	@durata TIME,
	@gen NVARCHAR(100),
	@id_regizor INT = NULL,
	@id_compozitor INT = NULL,
	@mesaj NVARCHAR(255) OUTPUT
AS
BEGIN
	SET NOCOUNT ON

	IF dbo.uf_ValideazaText(@titlu) = 0
	BEGIN
		SET @mesaj = 'Eroare: Titlul filmului este invalid!'
		RETURN
	END

	IF dbo.uf_ValideazaText(@gen) = 0
	BEGIN
		SET @mesaj = 'Eroare: Genul filmului este invalid!'
		RETURN
	END

	IF @id_regizor IS NOT NULL AND NOT EXISTS (SELECT 1 FROM Regizori WHERE id_r = @id_regizor)
	BEGIN
		SET @mesaj = 'Eroare: Regizorul cu ID-ul ' + @id_regizor + ' nu exista!'
		RETURN
	END

	IF @id_compozitor IS NOT NULL AND NOT EXISTS (SELECT 1 FROM Compozitori WHERE id_c = @id_compozitor)
	BEGIN
		SET @mesaj = 'Eroare: Compozitorul cu ID-ul ' + @id_compozitor + ' nu exista!'
	END

	IF EXISTS (SELECT 1 FROM Filme WHERE titlu = @titlu AND id_regizor = @id_regizor)
	BEGIN
		SET @mesaj = 'Eroare: Acest film pare sa existe deja (Titlu + Regizor identic)!'
		RETURN
	END

	BEGIN TRY
		INSERT INTO Filme (titlu, durata, gen, id_regizor, id_compozitor)
		VALUES (@titlu, @durata, @gen, @id_regizor, @id_compozitor)
		
		SET @mesaj = 'Succes: Filmul "' + @titlu + '" a fost adaugat!'
	END TRY
	BEGIN CATCH
		SET @mesaj = 'Eroare SQL: ' + ERROR_MESSAGE()
	END CATCH
END
GO

-- READ
CREATE OR ALTER PROCEDURE sp_Filme_Read
	@id_film INT = NULL
AS
BEGIN
	SET NOCOUNT ON

	IF @id_film IS NOT NULL
	BEGIN
		IF dbo.uf_ExistaFilm(@id_film) = 0
		BEGIN
			PRINT 'Eroare: Nu exista niciun film cu ID-ul ' + CAST(@id_film AS VARCHAR(10)) + '!'
			RETURN
		END
	END

	SELECT * FROM Filme
	WHERE (@id_film IS NULL OR id_f = @id_film)
END
GO

-- UPDATE
CREATE OR ALTER PROCEDURE sp_Filme_Update
	@id_film INT,
	@titlu_nou NVARCHAR(100),
	@durata_noua TIME,
	@gen_nou NVARCHAR(100),
	@id_regizor_nou INT = NULL,
	@id_compozitor_nou INT = NULL,
	@mesaj NVARCHAR(255) OUTPUT
AS
BEGIN
	SET NOCOUNT ON

	IF dbo.uf_ExistaFilm(@id_film) = 0
	BEGIN
		SET @mesaj = 'Eroare: Filmul cu ID-ul ' + CAST(@id_film AS VARCHAR(10)) + ' nu a fost gasit!'
		RETURN
	END

	IF dbo.uf_ValideazaText(@titlu_nou) = 0
	BEGIN
		SET @mesaj = 'Eroare: Titlul nou este invalid!'
		RETURN
	END

	IF dbo.uf_ValideazaText(@gen_nou) = 0
	BEGIN
		SET @mesaj = 'Eroare: Genul nou este invalid!'
		RETURN
	END

	IF @id_regizor_nou IS NOT NULL AND NOT EXISTS (SELECT 1 FROM Regizori WHERE id_r = @id_regizor_nou)
	BEGIN
		SET @mesaj = 'Eroare: Noul Regizor nu exista in baza de date!'
		RETURN
	END

	IF @id_compozitor_nou IS NOT NULL AND NOT EXISTS (SELECT 1 FROM Compozitori WHERE @id_compozitor_nou = id_c)
	BEGIN
		SET @mesaj = 'Eroare: Noul Compozitor nu exista in baza de date!'
		RETURN
	END

	BEGIN TRY
		UPDATE Filme
		SET titlu = @titlu_nou, durata = @durata_noua, gen = @gen_nou, id_regizor = @id_regizor_nou, id_compozitor = @id_compozitor_nou
		WHERE id_f = @id_film

		SET @mesaj = 'Succes: Datele filmului au fost actualizate!'
	END TRY
	BEGIN CATCH
		SET @mesaj = 'Eroare SQL: ' + ERROR_MESSAGE()
	END CATCH
END
GO

-- DELETE
CREATE OR ALTER PROCEDURE sp_Filme_Delete
	@id_film INT,
	@mesaj NVARCHAR(100) OUTPUT
AS
BEGIN
	SET NOCOUNT ON

	IF dbo.uf_ExistaFilm(@id_film) = 0
	BEGIN
		SET @mesaj = 'Eroare: Filmul cu ID-ul ' + CAST(@id_film AS VARCHAR(10)) + ' nu exista!'
		RETURN
	END

	BEGIN TRY
		DELETE FROM Filme WHERE id_f = @id_film
		SET @mesaj = 'Succes: Filmul a fost sters din baza de date!'
	END TRY
	BEGIN CATCH
		IF ERROR_NUMBER() = 547
			SET @mesaj = 'Eroare: Nu puteti sterge acest film! Este folosit in alte tabele.'
		ELSE
			SET @mesaj = 'Eroare SQL: ' + ERROR_MESSAGE()
	END CATCH
END
GO


-- =============== Publicatii ===============
-- CREATE
CREATE OR ALTER PROCEDURE sp_Publicatii_Create
	@id_film INT,
	@id_firma INT,
	@mesaj NVARCHAR(255) OUTPUT
AS
BEGIN
	SET NOCOUNT ON

	IF dbo.uf_ExistaFilm(@id_film) = 0
	BEGIN
		SET @mesaj = 'Eroare: Filmul cu ID-ul ' + CAST(@id_film AS VARCHAR(10)) + ' nu exista!'
		RETURN
	END

	IF dbo.uf_ExistaFirma(@id_firma) = 0
	BEGIN
		SET @mesaj = 'Eroare: Firma cu ID-ul ' + CAST(@id_firma AS VARCHAR(10)) + ' nu exista!'
		RETURN
	END

	IF EXISTS (SELECT 1 FROM Publicatii WHERE id_film = @id_film AND id_firma = @id_firma)
	BEGIN
		SET @mesaj = 'Eroare: Aceasta firma distribuie deja acest film!'
		RETURN
	END

	BEGIN TRY
		INSERT INTO Publicatii (id_film, id_firma)
		VALUES (@id_film, @id_firma)

		SET @mesaj = 'Succes: Relatia de distributie a fost creata!'
	END TRY
	BEGIN CATCH
		SET @mesaj = 'Eroare SQL: ' + ERROR_MESSAGE()
	END CATCH
END
GO

-- READ
CREATE OR ALTER PROCEDURE sp_Publicatii_Read
	@id_film INT = NULL,
	@id_firma INT = NULL
AS
BEGIN
	SET NOCOUNT ON

	IF @id_film IS NOT NULL AND dbo.uf_ExistaFilm(@id_film) = 0
	BEGIN
		PRINT 'Eroare: Filmul cu ID ' + CAST(@id_film AS VARCHAR(10)) + ' nu exista!'
		RETURN
	END

	IF @id_firma IS NOT NULL AND dbo.uf_ExistaFirma(@id_firma) = 0
	BEGIN
		PRINT 'Eroare: Firma cu ID ' + CAST(@id_firma AS VARCHAR(10)) + ' nu exista!'
		RETURN
	END

	IF @id_film IS NOT NULL AND @id_firma IS NOT NULL
	BEGIN
		IF NOT EXISTS (SELECT 1 FROM Publicatii WHERE id_film = @id_film AND id_firma = @id_firma)
		BEGIN
			PRINT 'Eroare: Nu exista o relatie intre Filmul ' + CAST(@id_film AS VARCHAR(10)) + ' si Firma ' + CAST(@id_firma AS VARCHAR(10)) + '!'
			RETURN
		END
	END

	SELECT	F.titlu AS [Nume Film], C.nume AS [Nume Firma], C.tara_origine AS [Tara Firma]
	FROM Publicatii P
	INNER JOIN Filme F ON P.id_film = F.id_f
	INNER JOIN Firme C ON P.id_firma = C.id_f
	WHERE (@id_film IS NULL OR P.id_film = @id_film) AND (@id_firma IS NULL OR p.id_firma = @id_firma)
END
GO

-- UPDATE
CREATE OR ALTER PROCEDURE sp_Publicatii_Update
	@old_id_film INT,
	@old_id_firma INT,
	@new_id_film INT,
	@new_id_firma INT,
	@mesaj NVARCHAR(255) OUTPUT
AS
BEGIN
	SET NOCOUNT ON

	IF dbo.uf_ExistaFilm(@old_id_film) = 0
	BEGIN
		SET @mesaj = 'Eroare: Vechiul Film (ID ' + CAST(@old_id_film AS VARCHAR(10)) + ') nu exista!'
		RETURN
	END

	IF dbo.uf_ExistaFirma(@old_id_firma) = 0
	BEGIN
		SET @mesaj = 'Eroare: Vechea Firma (ID ' + CAST(@old_id_firma AS VARCHAR(10)) + ') nu exista!'
		RETURN
	END

	IF NOT EXISTS (SELECT 1 FROM Publicatii WHERE id_film = @old_id_film AND id_firma = @old_id_firma)
	BEGIN
		SET @mesaj = 'Eroare: Relatia pe care incercati sa o modificati nu exista!'
		RETURN
	END

	IF dbo.uf_ExistaFilm(@new_id_film) = 0
	BEGIN
		SET @mesaj = 'Eroare: Noul Film (ID ' + CAST(@new_id_film AS VARCHAR(10)) + ') nu exista!'
		RETURN
	END

	IF dbo.uf_ExistaFirma(@new_id_firma) = 0
	BEGIN
		SET @mesaj = 'Eroare: Noua Firma (ID ' + CAST(@new_id_firma AS VARCHAR(10)) + ') nu exista!'
		RETURN
	END

	IF EXISTS (SELECT 1 FROM Publicatii
				WHERE id_film = @new_id_film AND id_firma = @new_id_firma
				AND NOT (id_film = @old_id_film AND id_firma = @old_id_firma))
	BEGIN
		SET @mesaj = 'Eroare: Relatia noua deja exista! Nu puteti crea duplicate.'
		RETURN
	END

	BEGIN TRY
		UPDATE Publicatii
		SET id_film = @new_id_film, id_firma = @new_id_firma
		WHERE id_film = @old_id_film AND id_firma = @old_id_firma

		SET @mesaj = 'Succes: Relatia a fost modificata!'
	END TRY
	BEGIN CATCH
		SET @mesaj = 'Eroare SQL: ' + ERROR_MESSAGE()
	END CATCH
END
GO

-- DELETE
CREATE OR ALTER PROCEDURE sp_Publicatii_Delete
	@id_film INT,
	@id_firma INT,
	@mesaj NVARCHAR(255) OUTPUT
AS
BEGIN
	SET NOCOUNT ON

	IF dbo.uf_ExistaFilm(@id_film) = 0
	BEGIN
		SET @mesaj = 'Eroare: Filmul cu ID ' + CAST(@id_film AS VARCHAR(10)) + ' nu exista!'
		RETURN
	END

	IF dbo.uf_ExistaFirma(@id_firma) = 0
	BEGIN
		SET @mesaj = 'Eroare: Firma cu ID ' + CAST(@id_firma AS VARCHAR(10)) + ' nu exista!'
		RETURN
	END

	IF NOT EXISTS (SELECT 1 FROM Publicatii WHERE id_film = @id_film AND id_firma = @id_firma)
	BEGIN
		SET @mesaj = 'Eroare: Aceasta relatie nu exista, deci nu poate fi stearsa!'
		RETURN
	END

	BEGIN TRY
		DELETE FROM Publicatii
		WHERE id_film = @id_film AND id_firma = @id_firma

		SET @mesaj = 'Succes: Relatia a fost stearsa!'
	END TRY
	BEGIN CATCH
		SET @mesaj = 'Eroare SQL: ' + ERROR_MESSAGE()
	END CATCH
END
GO