-- Firme
CREATE OR ALTER TRIGGER trg_Firme_Save ON Firme AFTER UPDATE, DELETE
AS
BEGIN
	SET NOCOUNT ON

	DECLARE @tipOperatie VARCHAR(10) = 'DELETE'

	IF EXISTS (SELECT 1 FROM inserted)
		SET @tipOperatie = 'UPDATE'

	INSERT INTO Log_Firme
	(
		tip_operatie,
		nume_utilizator,
		data_operatie,

		id_f,
		nume,
		tara_origine
	) 
	SELECT
		@tipOperatie,
		SYSTEM_USER,
		GETDATE(),
		
		d.id_f,
		d.nume,
		d.tara_origine
	FROM deleted d
END
GO

-- Filme
CREATE OR ALTER TRIGGER trg_Filme_Save ON Filme AFTER UPDATE, DELETE
AS
BEGIN
	SET NOCOUNT ON

	DECLARE @tipOperatie VARCHAR(10) = 'DELETE'

	IF EXISTS (SELECT 1 FROM inserted)
		SET @tipOperatie = 'UPDATE'

	INSERT INTO Log_Filme
	(
		tip_operatie,
		nume_utilizator,
		data_operatie,

		id_f,
		titlu,
		durata,
		gen,
		id_regizor,
		id_compozitor
	)
	SELECT
		@tipOperatie,
		SYSTEM_USER,
		GETDATE(),

		d.id_f,
		d.titlu,
		d.durata,
		d.gen,
		d.id_regizor,
		d.id_compozitor
	FROM deleted d
END
GO

-- Publicatii
CREATE OR ALTER TRIGGER trg_Publicatii_Save ON Publicatii AFTER UPDATE, DELETE
AS
BEGIN
	SET NOCOUNT ON

	DECLARE @tipOperatie VARCHAR(10) = 'DELETE'

	IF EXISTS (SELECT 1 FROM inserted)
		SET @tipOperatie = 'UPDATE'

	INSERT INTO Log_Publicatii
	(
		tip_operatie,
		nume_utilizator,
		data_operatie,

		id_film,
		id_firma
	)
	SELECT
		@tipOperatie,
		SYSTEM_USER,
		GETDATE(),

		d.id_film,
		d.id_firma
	FROM deleted d
END
GO