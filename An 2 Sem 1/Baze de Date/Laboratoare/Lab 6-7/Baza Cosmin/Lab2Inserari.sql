GO
USE Spotify;

INSERT INTO Artisti(nume,prenume) VALUES
	('Collins','Phil'),
	('Led','Zeppelin'),
	('Status','Quo'),
	('Vita','de Vie'),
	('Green','Day'),
	('Rammstein',''),
	('Rob','Zombie');

UPDATE Artisti SET prenume=NULL
WHERE id=6;

SELECT * FROM Artisti;

INSERT INTO Genuri(nume,an_aparitie) VALUES
	('Pop',1955),
	('Progressive Rock',1967),
	('Hard Rock',1965),
	('Heavy Metal',1970),
	('Folk Rock',1965),
	('Alternative Rock',1980),
	('Alternative Metal',1985),
	('Punk Rock',1975),
	('Industrial Metal',1990),
	('Groove Metal',1990);

SELECT * FROM Genuri

INSERT INTO Albume(denumire,descriere,an_aparitie) VALUES
	('...But Seriously','al patrulea album',1989),
	('Led Zeppelin III','al treilea album',1970),
	('Led Zeppelin II','al doilea album',1969),
	('In The Army Now','al saptesprezecelea album',1986),
	('Whatever You Want','al doisprezecelea album',1979),
	('Fenomental','primul album',1999),
	('Exxtra','al treilea album',2001),
	('Dookie','al treilea album',1994),
	('American Idiot','al saptelea album',2004),
	('Sehnsucht','al doilea album',1997),
	('Hellbilly Deluxe','primul album',1998);

SELECT * FROM Albume;

INSERT INTO Subscriptions(denumire,descriere,pret) VALUES
	('Free','este gratuit, are reclame',0),
	('Individual','un cont, fara reclame',26),
	('Student','un cont,reduceri pentru studenti eligibili,fara reclame',14),
	('Duo','doua conturi, fara reclame',35),
	('Family','patru conturi, control asupra continutului explicit, fara reclame',42);

SELECT * FROM Subscriptions;

INSERT INTO Melodii(denumire,an_aparitie,id_album) VALUES
	('Another Day in Paradise',1989,1),
	('Immigrant Song',1970,2),
	('Gallows Pole',1970,2),
	('Whole Lotta Love',1969,3),
	('In The Army Now',1986,4),
	('Whatever You Want',1979,5),
	('Basul Si Cu Toba Mare',1999,6),
	('Iamma',1999,6),
	('Eu Cu Mine',1999,6),
	('Sunetul mai tare',2001,7),
	('Beat mort',2001,7),
	('Basket Case',1994,8),
	('When I Come Around',1994,8),
	('American Idiot',2004,9),
	('Jesus of Suburbia',2004,9),
	('Wake Me up When September Ends',2004,9),
	('Engel',1997,10),
	('Du hast',1997,10),
	('Dragula',1998,11),
	('Superbeast',1998,11),
	('Living Dead Girl',1998,11);

SELECT * FROM Melodii;

INSERT INTO Utilizatori(nume,prenume,porecla,anul_inscrierii,id_subscription) VALUES
	('Pufu','Cosmin','cosmin2444',2020,5),
	('Pop','Ion','ionica',2015,2),
	('Mihaila','Maria','_maria23_',2025,3),
	('Popescu','Lefter','fArAbAnI',2018,1),
	('Raducu','Mihnea','SpartanulHD',2022,3),
	('Smith','John','default:)',2016,2),
	('Armstrong','Neil','#firstonthemoon',1969,2),
	('Pufu','Andra','littlewitch9',2019,5),
	('Hawking','Stephen','InMemoryOf',2018,2),
	('Pufu','Mihai','misu',2023,5),
	('Tacu','Madalina','Mady',2015,2),
	('Pufu','Nicoleta','nichi',2023,5);

SELECT * FROM Utilizatori;

INSERT INTO Playlists(denumire,descriere,id_utilizator) VALUES
	('ROCK/FOLK/DISCO MIX','tot ce e mai bun',1),
	('Alternative/Heavy','mix de alternative si heavy metal',1),
	('Old school rock','epoca de aur',10),
	('Punk/Alternative FOREVER','punk yeah',8),
	('Drum','Playlist pentru drum',1),
	('All I Want','everything I like',6);

SELECT * FROM Playlists;

INSERT INTO Podcasts(denumire,descriere,subiect_principal,data,id_utilizator) VALUES
	('Quantum physics', 'a study of matter and energy','Wave-particle duality','2019-09-23',9),
	('Space adventure', 'how I got to the moon','Apollo 11','1969-07-24',7),
	('Muzica Rock','scurta istorie a muzicii rock','Istoria muzicii Rock','2024-03-27',1),
	('Viata de contabil','experiente personale','Contabilitate','2025-09-01',12),
	('Cum sa faci bani','sfaturi sincere','Business','2019-12-25',4),
	('Preferinte muzicale','despre diferentele de preferinte muzicale','Muzica','2025-06-22',1),
	('Mecanica fina','principii din industria mecanicii fine','Mecanica','2023-10-29',10),
	('Punk is not dead','discussion about punk music','Punk Music','2020-01-20',5);

SELECT * FROM Podcasts;

INSERT INTO Devices(nume_device,sistem_operare,id_utilizator) VALUES
	('S25','Android',1),
	('IonPC','MacOS',2),
	('HP Elitebook','Windows',1),
	('Iphone 15','IOS',3),
	('MariaMAC','MacOS',3),
	('Samsung Series 6','SamsungTV OS',1),
	('NothingPhone','Android',4),
	('LG TV','Android TV',5),
	('S24 Ultra','Android',5),
	('JohnPhone','IOS',6),
	('OldPC','Windows 95',7),
	('Samsung A33','Android',8),
	('Modulator','Voice OS',9),
	('Sony','Android',10),
	('Iphone 14','IOS',11),
	('Samusng A35','Android',12),
	('AndraElitebook','Windows',8),
	('Philips','Philips TV OS',8),
	('Watch4 Classic','WearOS',1);

SELECT * FROM Devices;

INSERT INTO Videoclipuri(id_melodie,lungime) VALUES
	(1,5),
	(7,3),
	(8,4),
	(10,4),
	(12,3),
	(13,3),
	(14,3),
	(15,12),
	(16,7),
	(17,4),
	(18,4),
	(19,4),
	(20,4),
	(21,3);

SELECT * FROM Videoclipuri;

SELECT * FROM Melodii;
SELECT * FROM Artisti;

INSERT INTO Melodii_Artisti(id_melodie,id_artist) VALUES
	(1,1),
	(2,2),
	(3,2),
	(4,2),
	(5,3),
	(6,3),
	(7,4),
	(8,4),
	(9,4),
	(10,4),
	(11,4),
	(12,5),
	(13,5),
	(14,5),
	(15,5),
	(16,5),
	(17,6),
	(18,6),
	(19,7),
	(20,7),
	(21,7);

SELECT * FROM Melodii_Artisti;

SELECT * FROM Melodii;
SELECT * FROM Genuri;

INSERT INTO Melodii_Genuri(id_melodie,id_gen) VALUES
	(1,1),
	(2,3),
	(2,4),
	(3,5),
	(4,3),
	(4,4),
	(5,3),
	(6,2),
	(7,6),
	(8,6),
	(9,6),
	(10,6),
	(11,6),
	(12,8),
	(12,6),
	(13,6),
	(13,8),
	(14,8),
	(15,8),
	(16,6),
	(17,9),
	(18,9),
	(18,7),
	(18,3),
	(18,8),
	(19,4),
	(19,9),
	(19,7),
	(20,4),
	(21,9),
	(21,4);

SELECT * FROM Melodii_Genuri;

SELECT * FROM Melodii;
SELECT * FROM Playlists;

INSERT INTO Melodii_Playlists(id_melodie,id_playlist) VALUES
	(1,1),
	(2,1),
	(4,1),
	(6,1),
	(7,1),
	(10,1),
	(14,1),
	(17,1),
	(18,1),
	(19,1),
	(2,2),
	(3,2),
	(4,2),
	(5,2),
	(6,2),
	(7,3),
	(8,3),
	(10,3),
	(11,3),
	(13,3),
	(14,3),
	(16,3),
	(18,3),
	(20,3),
	(7,4),
	(8,4),
	(10,4),
	(11,4),
	(13,4),
	(14,4),
	(16,4),
	(18,4),
	(20,4),
	(21,4),
	(1,5),
	(2,5),
	(4,5),
	(6,5),
	(7,6),
	(17,6),
	(18,6),
	(19,6),
	(20,6),
	(21,6);

SELECT * FROM Melodii_Playlists;

SELECT * FROM Albume;
SELECT * FROM Artisti;

INSERT INTO Albume_Artisti(id_album,id_artist) VALUES
	(1,1),
	(2,2),
	(3,2),
	(4,3),
	(5,3),
	(6,4),
	(7,4),
	(8,5),
	(9,5),
	(10,6),
	(11,7);

SELECT * FROM Albume_Artisti;

SELECT * FROM Artisti;
SELECT * FROM Genuri;

INSERT INTO Artisti_Genuri(id_artist,id_gen) VALUES
	(1,1),
	(1,2),
	(2,3),
	(2,5),
	(2,4),
	(3,3),
	(4,6),
	(4,7),
	(5,8),
	(5,6),
	(6,9),
	(7,10),
	(7,9),
	(7,7),
	(7,3);

SELECT * FROM Artisti_Genuri;
