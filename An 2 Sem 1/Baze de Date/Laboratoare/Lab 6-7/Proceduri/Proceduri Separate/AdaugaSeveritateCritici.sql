CREATE OR ALTER PROCEDURE AdaugaSeveritateCritici
AS
ALTER TABLE Critici_Oficiali
ADD severitate NVARCHAR(100)