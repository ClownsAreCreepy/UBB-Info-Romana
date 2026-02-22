CREATE OR ALTER PROCEDURE CompDefaultInstrument
AS
ALTER TABLE Compozitori
ADD CONSTRAINT Compozitori_default_instrument_favorit
DEFAULT N'trianglu' FOR instrument_favorit
