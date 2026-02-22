CREATE DATABASE club_cultura
GO

USE club_cultura
GO

CREATE TABLE Teme(
	id INT PRIMARY KEY IDENTITY(1, 1),
	titlu VARCHAR(50),
	descriere VARCHAR(50)
)

CREATE TABLE Autori(
	id	INT PRIMARY KEY IDENTITY(1, 1),
	nume VARCHAR(50),
	perioada VARCHAR(50),
	tip_opere VARCHAR(50)
)

CREATE TABLE Roluri(
id	INT PRIMARY KEY IDENTITY(1, 1),
denumire VARCHAR(50),
domeniu VARCHAR(50)
)

CREATE TABLE Produse(
	id	INT PRIMARY KEY IDENTITY(1, 1),
	nume VARCHAR(50),
	tip VARCHAR(50),
	data_expirare DATE
)

CREATE TABLE Carti(
	id	INT PRIMARY KEY IDENTITY(1, 1),
	id_autor INT FOREIGN KEY REFERENCES Autori(id),
	titlu VARCHAR(50),
	gen VARCHAR(50)
)

CREATE TABLE Participanti(
id	INT PRIMARY KEY IDENTITY(1, 1),
nume VARCHAR(50),
prenume VARCHAR(50),
data_nastere DATE,
id_rol INT FOREIGN KEY REFERENCES Roluri(id)
)

CREATE TABLE Invitati(
id_participant INT FOREIGN KEY REFERENCES Participanti(id),
domeniu_interes VARCHAR(50),
PRIMARY KEY(id_participant)
)

CREATE TABLE Intalniri(
	id INT PRIMARY KEY IDENTITY(1, 1),
	id_tema INT FOREIGN KEY REFERENCES Teme(id),
	id_invitat INT FOREIGN KEY REFERENCES Invitati(id_participant),
	locatie VARCHAR(50),
	data DATE
)

CREATE TABLE Articole(
	id INT PRIMARY KEY IDENTITY(1, 1),
	id_autor INT FOREIGN KEY REFERENCES Participanti(id),
	id_tema INT FOREIGN KEY REFERENCES Teme(id),
	titlu VARCHAR(50),
	tip_articol VARCHAR(50)
)

CREATE TABLE Teme_Autori(
	id_tema INT FOREIGN KEY REFERENCES Teme(id),
	id_autor INT FOREIGN KEY REFERENCES Autori(id),
	PRIMARY KEY(id_tema, id_autor)
)

CREATE TABLE Teme_Carti(
id_tema INT FOREIGN KEY REFERENCES Teme(id),
id_carte INT FOREIGN KEY REFERENCES Carti(id)
PRIMARY KEY(id_tema, id_carte)
)

CREATE TABLE Participanti_Intalnire(
id_participant INT FOREIGN KEY REFERENCES Participanti(id),
id_intalnire INT FOREIGN KEY REFERENCES Intalniri(id)
PRIMARY KEY(id_participant, id_intalnire)
)

CREATE TABLE Stoc_Intalnire(
id_produs INT FOREIGN KEY REFERENCES Produse(id),
id_intalnire INT FOREIGN KEY REFERENCES Intalniri(id),
cantitate INT,
PRIMARY KEY(id_produs, id_intalnire)
)

