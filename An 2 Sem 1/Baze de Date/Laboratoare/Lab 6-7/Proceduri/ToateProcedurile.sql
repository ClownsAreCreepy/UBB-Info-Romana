-- 1.
CREATE OR ALTER PROCEDURE FirmaTaraNull
AS
ALTER TABLE Firme
ALTER COLUMN tara_origine VARCHAR(100) NOT NULL
GO

-- 2.
CREATE OR ALTER PROCEDURE CompDefaultInstrument
AS
ALTER TABLE Compozitori
ADD CONSTRAINT Compozitori_default_instrument_favorit
DEFAULT N'trianglu' FOR instrument_favorit
GO

-- 3.
CREATE OR ALTER PROCEDURE CreareTabelNoutati
AS
CREATE TABLE Noutati
(
	id_n INT PRIMARY KEY IDENTITY(1,1),
	titlu NVARCHAR(100),
	descriere NVARCHAR(1000)
)
GO

-- 4.
CREATE OR ALTER PROCEDURE AdaugaSeveritateCritici
AS
ALTER TABLE Critici_Oficiali
ADD severitate NVARCHAR(100)
GO

-- 5.
CREATE OR ALTER PROCEDURE RegizorCompPreferat
AS
ALTER TABLE Regizori
ADD  cod_c INT

ALTER TABLE Regizori
ADD CONSTRAINT fk_CompozitorRegizor FOREIGN KEY (cod_c) REFERENCES Compozitori (id_c)
GO


-- REVERSED

-- 1.
CREATE OR ALTER PROCEDURE reverseFirmaTaraNull
AS
ALTER TABLE Firme
ALTER COLUMN tara_origine VARCHAR(100)
GO

-- 2.
CREATE OR ALTER PROCEDURE reverseCompDefaultInstrument
AS
ALTER TABLE Compozitori
DROP CONSTRAINT Compozitori_default_instrument_favorit
GO

-- 3.
CREATE OR ALTER PROCEDURE reverseCreareTabelNoutati
AS
DROP TABLE Noutati
GO

-- 4.
CREATE OR ALTER PROCEDURE reverseAdaugaSeveritateCritici
AS
ALTER TABLE Critici_Oficiali
DROP COLUMN severitate
GO

-- 5.
CREATE OR ALTER PROCEDURE reverseRegizorCompPreferat
AS
ALTER TABLE Regizori
DROP CONSTRAINT fk_CompozitorRegizor

ALTER TABLE Regizori
DROP COLUMN cod_c