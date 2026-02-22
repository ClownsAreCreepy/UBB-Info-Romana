CREATE OR ALTER PROCEDURE reverseRegizorCompPreferat
AS
ALTER TABLE Regizori
DROP CONSTRAINT fk_CompozitorRegizor

ALTER TABLE Regizori
DROP COLUMN cod_c