--Creem baza de date cu nume nebun
CREATE DATABASE CRAZY_SITE_DE_FILME
--Spunem GO pentru ca altcumva nu mere USE fix dupa CREATE pentru ca
GO

--Selectam baza noastra de date ca sa lucram pe ea
USE CRAZY_SITE_DE_FILME

--Creem tabelele de regizori, compozitori si actori (cam clone da nu conteaza)
CREATE TABLE Regizori
(
id_r INT PRIMARY KEY IDENTITY(1,1),
nume NVARCHAR(100) NOT NULL,
varsta INT,
nr_filme_realizate INT NOT NULL
);

CREATE TABLE Compozitori
(
id_c INT PRIMARY KEY IDENTITY(1,1),
nume NVARCHAR(100) NOT NULL,
varsta INT,
instrument_favorit NVARCHAR(100) NOT NULL
);

CREATE TABLE Actori
(
id_a INT PRIMARY KEY IDENTITY(1,1),
nume NVARCHAR(100) NOT NULL,
varsta INT,
interviewuri_date INT
);

--Creem tabel pentru Filme
--Folosim referinte pentru regizori si compozitori
--Constraint pentru ca avem foreign key format din o pereche de campuri
CREATE TABLE Filme
(
id_f INT PRIMARY KEY IDENTITY(1,1),
titlu NVARCHAR(100) NOT NULL,
durata TIME,
gen NVARCHAR(100),
id_regizor INT,
id_compozitor INT, 
CONSTRAINT fk_RegizorFilm FOREIGN KEY (id_regizor) REFERENCES Regizori(id_r),
CONSTRAINT fk_CompozitorFilm FOREIGN KEY (id_compozitor) REFERENCES Compozitori(id_c)
);

--Creem tabel pentru utilizatori
CREATE TABLE Utilizatori
(
id_u INT PRIMARY KEY IDENTITY(1,1),
nume NVARCHAR(100) NOT NULL UNIQUE,
varsta INT,
tara_de_origine NVARCHAR(100)
);

--Creem tabel smecher de legatura pentru recenzii
--Va avea 2 chei externe: filme si utilizatori, care formeaza cheia primara
CREATE TABLE Recenzii
(
id_film INT,
id_utilizator INT,
nota INT NOT NULL,
recenzie_in_sine NVARCHAR(1000),
CONSTRAINT fk_FilmRecenzie FOREIGN KEY (id_film) REFERENCES Filme(id_f),
CONSTRAINT fk_UtilizatorRecenzie FOREIGN KEY (id_utilizator) REFERENCES Utilizatori(id_u),
CONSTRAINT pk_Recenzie PRIMARY KEY (id_film, id_utilizator),
CONSTRAINT ck_Recenzii_Nota CHECK (nota BETWEEN 1 AND 10)
);

--Creem tabelu de critici
CREATE TABLE Critici_Oficiali
(
id_u INT PRIMARY KEY,
reputatie NVARCHAR(50)
CONSTRAINT fk_UtilizatorCritic FOREIGN KEY (id_u) REFERENCES Utilizatori(id_u) ON DELETE CASCADE ON UPDATE CASCADE
);

--Creem tabel pentru relatie unu la unu - oscar
CREATE TABLE Premii_Oscar
(
id_o INT PRIMARY KEY IDENTITY(1,1),
id_film INT FOREIGN KEY REFERENCES Filme(id_f) ON UPDATE CASCADE ON DELETE CASCADE,
tip NVARCHAR(100) NOT NULL,
an INT NOT NULL
);

--Creem tabel de roluri pentru actori in filme
CREATE TABLE Roluri
(
id_film INT,
id_actor INT,
tip NVARCHAR(100) NOT NULL,
nume_personaj NVARCHAR(100) NOT NULL,
CONSTRAINT fk_FilmRol FOREIGN KEY (id_film) REFERENCES Filme(id_f),
CONSTRAINT fk_ActorRol FOREIGN KEY (id_actor) REFERENCES Actori(id_a),
CONSTRAINT pk_Rol PRIMARY KEY (id_film,id_actor)
);

--Creem tabelu pentru firme
--Stabilim o relatie MtoM cu un tabel pur de relatii
CREATE TABLE Firme
(
id_f INT PRIMARY KEY IDENTITY(1,1),
nume NVARCHAR(100) NOT NULL,
tara_origine NVARCHAR(100)
);

CREATE TABLE Publicatii
(
id_film INT,
id_firma INT,
CONSTRAINT fk_FilmPublicatie FOREIGN KEY (id_film) REFERENCES Filme(id_f),
CONSTRAINT fk_FirmaPublicatie FOREIGN KEY (id_firma) REFERENCES Firme(id_f),
CONSTRAINT pk_Publicatie PRIMARY KEY (id_film, id_firma)
);

CREATE TABLE Versiuni
(
versiune INT
);

INSERT INTO Versiuni VALUES (0)