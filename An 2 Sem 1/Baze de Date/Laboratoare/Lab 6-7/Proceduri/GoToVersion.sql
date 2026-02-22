CREATE OR ALTER PROCEDURE GoToVersion @version INT
AS
BEGIN
	DECLARE @current INT = (SELECT TOP 1 versiune FROM Versiuni)
	IF @current = @version
		RETURN

	IF @version >= 6 THROW 50003, N'Nu exista versiunea', 1 

	WHILE @current < @version
	BEGIN
		SET @current = @current + 1
		IF @current = 1		  EXEC FirmaTaraNull
		ELSE IF @current = 2  EXEC CompDefaultInstrument
		ELSE IF @current = 3  EXEC CreareTabelNoutati
		ELSE IF @current = 4  EXEC AdaugaSeveritateCritici
		ELSE IF @current = 5  EXEC RegizorCompPreferat

		UPDATE Versiuni SET versiune = @current
	END

	WHILE @current > @version
	BEGIN
		IF @current = 5 EXEC reverseRegizorCompPreferat
		IF @current = 4 EXEC reverseAdaugaSeveritateCritici
		IF @current = 3 EXEC reverseCreareTabelNoutati
		IF @current = 2 EXEC reverseCompDefaultInstrument
		IF @current = 1 EXEC reverseFirmaTaraNull

		SET @current = @current - 1
		UPDATE Versiuni SET versiune = @current
	END
END

EXEC GoToVersion 2
SELECT * FROM Versiuni
