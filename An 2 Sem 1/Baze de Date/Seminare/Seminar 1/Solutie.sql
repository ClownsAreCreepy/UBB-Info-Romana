--Crearea bazei de date cu numele ProblemaFilme
CREATE DATABASE ProblemaFilme;
GO

--Conectare la baza de date
USE ProblemaFilme

--Crearea tabelului Utilizatori
create table Utilizatori
(
cod_u int primary key identity(1,1),
nume_u VARCHAR(100) NOT NULL UNIQUE,
parola VARCHAR(100),
email varchar(100)
);

--Crearea tabelului Companii
create table Companii
(
cod_c INT PRIMARY KEY IDENTITY(1,1),
nume_c NVARCHAR(100),
tara NVARCHAR(100)
);

--Crearea tabelului Filme
CREATE TABLE Filme
(
cod_f INT PRIMARY KEY IDENTITY,
titlu NVARCHAR(100),
durata TIME,
limba NVARCHAR(100),
cod_c INT FOREIGN KEY REFERENCES Companii(cod_c) ON UPDATE CASCADE ON DELETE CASCADE
);

--Crearea tabelului Note
CREATE TABLE Note
(
cod_u INT,
cod_f INT,
nota INT,
CONSTRAINT fk_UtilizatoriNote FOREIGN KEY (cod_u) REFERENCES Utilizatori(cod_u),
CONSTRAINT fk_FilmeNote FOREIGN KEY (cod_f) REFERENCES Filme(cod_f),
CONSTRAINT pk_Note PRIMARY KEY (cod_u, cod_f)
);

ALTER TABLE Utilizatori
ADD CONSTRAINT uq_email UNIQUE (email)

ALTER TABLE Note
ADD CONSTRAINT ck_nota CHECK (nota>=1 AND nota<=10)

ALTER TABLE Note
ADD data_si_ora_adaugarii DATE

ALTER TABLE Note
ADD CONSTRAINT df_data_si_ora_adaugarii DEFAULT GETDATE() FOR data_si_ora_adaugarii

ALTER TABLE Filme
ALTER COLUMN titlu NVARCHAR(220)

ALTER TABLE Note
DROP CONSTRAINT df_data_si_ora_adaugarii

ALTER TABLE Note
DROP COLUMN data_si_ora_adaugarii

ALTER DATABASE ProblemaFilme
MODIFY Name=NoteFilme

DROP TABLE Note

USE master
DROP DATABASE ProblemaFilme