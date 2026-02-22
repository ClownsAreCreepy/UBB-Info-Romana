CREATE DATABASE Spotify;
GO
USE Spotify;

CREATE TABLE Artisti
	(id INT PRIMARY KEY IDENTITY(1,1),
	nume VARCHAR(60) NOT NULL UNIQUE,
	prenume VARCHAR(60)
	);

CREATE TABLE Subscriptions
	(id INT PRIMARY KEY IDENTITY(1,1),
	denumire VARCHAR(30) NOT NULL UNIQUE,
	descriere VARCHAR(100),
	pret INT
	);

CREATE TABLE Genuri
	(id INT PRIMARY KEY IDENTITY(1,1),
	nume VARCHAR(30) NOT NULL UNIQUE,
	an_aparitie INT
	);

CREATE TABLE Albume
	(id INT PRIMARY KEY IDENTITY(1,1),
	denumire VARCHAR(50) NOT NULL,
	descriere VARCHAR(100),
	an_aparitie INT
	);

CREATE TABLE Melodii
	(id INT PRIMARY KEY IDENTITY(1,1),
	denumire VARCHAR(50) NOT NULL,
	an_aparitie INT,
	id_album INT FOREIGN KEY REFERENCES Albume(id)
	);

CREATE TABLE Utilizatori
	(id INT PRIMARY KEY IDENTITY(1,1),
	nume VARCHAR(30) NOT NULL,
	prenume VARCHAR(60) NOT NULL,
	porecla VARCHAR(40) NOT NULL UNIQUE,
	anul_inscrierii INT,
	id_subscription INT FOREIGN KEY REFERENCES Subscriptions(id)
	);

CREATE TABLE Playlists
	(id INT PRIMARY KEY IDENTITY(1,1),
	denumire VARCHAR(40) NOT NULL,
	descriere VARCHAR(120),
	id_utilizator INT FOREIGN KEY REFERENCES Utilizatori(id)
	);

CREATE TABLE Podcasts
	(id INT PRIMARY KEY IDENTITY(1,1),
	denumire VARCHAR(40) NOT NULL,
	descriere VARCHAR(100),
	subiect_principal VARCHAR(50),
	data DATE,
	id_utilizator INT FOREIGN KEY REFERENCES Utilizatori(id)
	);

CREATE TABLE Videoclipuri
	(id_melodie INT FOREIGN KEY REFERENCES Melodii(id),
	lungime INT,
	PRIMARY KEY(id_melodie)
	);

CREATE TABLE Devices
	(id INT PRIMARY KEY IDENTITY(1,1),
	nume_device VARCHAR(40),
	sistem_operare VARCHAR(40),
	id_utilizator INT FOREIGN KEY REFERENCES Utilizatori(id)
	);


CREATE TABLE Melodii_Playlists
	(id_melodie INT FOREIGN KEY REFERENCES Melodii(id),
	id_playlist INT FOREIGN KEY REFERENCES Playlists(id),
	PRIMARY KEY(id_melodie,id_playlist)
	);


CREATE TABLE Melodii_Artisti
	(id_melodie INT FOREIGN KEY REFERENCES Melodii(id),
	id_artist INT FOREIGN KEY REFERENCES Artisti(id),
	PRIMARY KEY(id_melodie,id_artist)
	);

CREATE TABLE Melodii_Genuri
	(id_melodie INT FOREIGN KEY REFERENCES Melodii(id),
	id_gen INT FOREIGN KEY REFERENCES Genuri(id),
	PRIMARY KEY(id_melodie,id_gen)
	);


CREATE TABLE Albume_Artisti
	(id_album INT FOREIGN KEY REFERENCES Albume(id),
	id_artist INT FOREIGN KEY REFERENCES Artisti(id),
	PRIMARY KEY(id_album,id_artist)
	);

CREATE TABLE Artisti_Genuri
	(id_artist INT FOREIGN KEY REFERENCES Artisti(id),
	id_gen INT FOREIGN KEY REFERENCES Genuri(id),
	PRIMARY KEY(id_artist,id_gen)
	);
----NU e FINISAT!!!!!!
