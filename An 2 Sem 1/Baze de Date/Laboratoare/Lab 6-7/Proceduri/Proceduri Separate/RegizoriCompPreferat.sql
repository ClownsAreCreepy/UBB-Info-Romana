CREATE OR ALTER PROCEDURE RegizorCompPreferat
AS
ALTER TABLE Regizori
ADD  cod_c INT

ALTER TABLE Regizori
ADD CONSTRAINT fk_CompozitorRegizor FOREIGN KEY (cod_c) REFERENCES Compozitori (id_c)
