--inserare date in tabele

INSERT INTO Autori(nume, perioada, tip_opere) VALUES
('Franz Kafka', 'sec XIX', 'proza'),
('Mihai Eminescu', 'Perioada Marilor Clasici', 'poezie'),
('Ion Luca Caragiale', 'Perioada Marilor Clasici', 'drama'),
('Homer', 'Antichitate', 'epopee'),
('Platon',  'Antichitate', 'filozofie'),
('Mircea Eliade', 'Interbelica', 'proza'),
('Evagrie Ponticul', 'Antichitate', 'religie'),
('Andrei Plesu', 'sec XXI', 'filozofie')


INSERT INTO Teme(titlu, descriere) VALUES
('Metamorfoza - dincolo de gandac', 'Discutie pe baza cartii Metamorfoza de Franz Kafka'),
('Este ceva de capul lui Eminecu?', 'Is Eminescu overrated? Haideti sa vedem'),
('Epopeele grecesti', 'O aventura prin operele lui Homer'),
('Parabolele', 'Discutie pe baza a 7 parabole din Biblie'),
('Oceanografie and friends', 'Nu, nu e vorba despre ape.'),
('Banchet dupa Banchetul', 'Descoperim iubirea conform lui Platon.'),
('O doza de filozofie', 'Dialogurile lui Platon, sub lupa.')

INSERT INTO Roluri(denumire, domeniu) VALUES
('Social media manager', 'Media'),
('Fotograf', 'Media'),
('Informatician', 'Tehnic'),
('Website developer', 'Tehnic'),
('Carul cu minciuni', 'Organizare')

INSERT INTO Produse(nume, tip, data_expirare) VALUES
('Chipsuri cu cascaval', 'snack', '2025-12-23'),
('Cookies cu cicolata', 'snack', '2026-01-19'),
('Gin Tanqueray', 'alcool', '2030-09-18'),
('Rom Havana Club', 'alcool', '2029-11-24'),
('Apa Borsec', 'bauturi', '2026-03-22'),
('Suc de aloe vera', 'bauturi', '2025-12-29'),
('Suc de portocale', 'bauturi', '2025-10-14'),
('Saratele',  'snack', '2025-12-07'),
('Jeleuri', 'snack', '2026-02-25')

INSERT INTO Participanti(nume, prenume, data_nastere, id_rol) VALUES
('Rusu', 'Sanziana', '2006-01-26', 5),
('Carari', 'Victor', '2005-08-26', 3),
('Uricaru', 'Miruna', '2005-12-19', 1),
('Covaciu', 'Darius', '2005-04-20', 5),
('Russu', 'Mihaela', '2006-03-11', 1),
('Stoian', 'Tudor', '2005-08-20', 5),
('Cozma', 'Robert', '2005-11-16', 2),
('Pap', 'Diana', '2005-06-17', 1),
('Macri', 'Tudor', '2005-02-16', 4),
('Calugaritoiu', 'Teodora', '2005-08-03', null),
('Craioveanu', 'Graziela', '1976-02-12', null),
('Popescu', 'Petru', '2005-11-18', null),
('Amoraritei', 'Alexandra', '2005-02-18', null),
('Ionescu', 'Marian', '1967-03-15', null)
--('Manea', 'Vlad', )

INSERT INTO Invitati(id_participant, domeniu_interes) VALUES
(10, '10 la analiza matematica'),
(11, 'CSM'), 
(12, 'Filme'), 
(13, 'Arheologie'), 
(14, 'Excursii pe munte')

INSERT INTO Intalniri(id_tema, id_invitat, locatie, data) VALUES
(8, null, 'Casa Rusu', '2025-03-29'),
(5, 10, 'Casa Rusu', '2025-08-19'),
(5, 10, 'Casa Rusu', '2025-08-26'),
(3, null, 'Casa Covaciu', '2024-12-23'),
(4, 11, 'Aer liber', '2024-05-25'),
(2, 12, 'Casa Covaciu', '2024-09-06'),
(6, 14, 'Aer liber', '2023-08-12'),
(7, null, 'Casa Rusu', '2022-10-22'),
(8, 13, 'Casa Covaciu', '2022-11-23')

INSERT INTO Articole(id_autor, id_tema, titlu, tip_articol) VALUES
(5, 2, 'Din stomac despre Metamorfoza', 'review'),
(5, 6, 'Cringe culture si salvari', 'comparatie'),
(3, 4, 'Ahile - un ideal', 'studiu de personaj'),
(6, 2, 'Metamorfoza pe scurt', 'rezumat'),
(1, 2, 'Neconvins de Eminescu', 'review'),
(4, 5, 'Mesajul lui Dumnezeu', 'rezumat')

INSERT INTO Articole(id_autor, id_tema, titlu, tip_articol) VALUES
(1, 7, 'Articol', 'review'),
(3, 5, 'Review', 'review')

Select * from Autori

INSERT INTO Carti(id_autor, titlu, gen) VALUES
(1, 'Metamorfoza', 'Nuvela'),
(1, 'Procesul', 'Roman'),
(2, 'Poesii', 'Poezie'),
(3, 'Momente si schite', 'Schita'),
(3, 'O noapte furtunoasa', 'Comedie'),
(4, 'Iliada', 'Epopee'),
(4, 'Odiseea', 'Epopee'),
(5, 'Operele vol. 1', 'Dialog'),
(6, 'Oceanografie', 'Eseu'),
(7, 'Gnosticul', 'Credinta'),
(8, 'Parabolele lui Iisus', 'Credinta'),
(8, 'Tipuri de trecere', 'Eseu')

select * from Teme
select * from Autori

INSERT INTO Teme_Autori(id_tema, id_autor) VALUES
(2, 1),
(3, 2),
(4, 4),
(5, 7),
(5, 8),
(6, 6),
(7, 7),
(7, 8),
(8, 5),
(5, 5)

INSERT INTO Teme_Carti(id_tema, id_carte) VALUES
(2, 1),
(3, 3),
(4, 6),
(4, 7),
(5, 7), 
(5, 11),
(6, 9),
(7, 5),
(8, 5),
(8, 12)

select * from Intalniri
select * from Participanti

INSERT INTO Participanti_Intalnire(id_intalnire, id_participant) VALUES
(22, 1),
(22, 2),
(22, 3),
(22, 7),
(23, 3),
(23, 4),
(23, 1),
(23, 7),
(23, 10),
(23, 9),
(24, 1),
(24, 7),
(24, 8),
(24, 9),
(24, 6),
(24, 10),
(25, 5),
(25, 6),
(25, 7),
(25, 8),
(25, 9),
(26, 11),
(26, 1),
(26, 7),
(26, 2),
(26, 4),
(27, 12),
(27, 2),
(27, 5),
(27, 6),
(27, 8),
(27, 9),
(28, 14), 
(28, 9),
(28, 7),
(28, 8),
(28, 5),
(28, 6),
(28, 1),
(29, 1),
(29, 5),
(29, 7),
(30, 13),
(30, 1),
(30, 5),
(30, 8),
(30, 2), 
(30, 3),
(30, 4)

select * from Intalniri
select * from Produse

INSERT INTO Stoc_Intalnire(id_intalnire, id_produs, cantitate) VALUES
(22, 1, 2),
(22, 3, 1),
(22, 5, 10),
(23, 2, 3),
(23, 4, 2),
(23, 6, 12),
(24, 1, 3),
(24, 3, 3),
(25, 5, 20),
(26, 4, 3),
(26, 5, 10),
(27, 1, 4),
(27, 6, 12),
(28, 3, 3),
(28, 2, 3),
(29, 1, 1), 
(29, 5, 10),
(30, 1, 1),
(30, 2, 1),
(30, 3, 2), 
(30, 4, 2),
(30, 5, 10),
(30, 6, 8)





--queries 

--temele care au fost discutate la mai mult de o intalnire
SELECT T.titlu, COUNT(*) as numar_aparitii FROM Teme T
INNER JOIN Intalniri I ON  T.id = I.id_tema
GROUP BY T.titlu
HAVING COUNT(*) >= 2

--cate articole s-au scrie despre fiecare tema cu mai multi autori discutati
SELECT COUNT(DISTINCT A.id) as numar_articole, COUNT(DISTINCT TA.id_autor) as numar_autori, TA.id_tema FROM Articole A
INNER JOIN Teme T ON A.id_tema = T.id 
INNER JOIN Teme_Autori TA ON T.id = TA.id_tema
GROUP BY TA.id_tema
HAVING COUNT(DISTINCT TA.id_autor) > 1

--intalnirile si numarul de produse consumate
SELECT I.id, SUM(cantitate) as numar_produse FROM Intalniri I
INNER JOIN Stoc_Intalnire SI ON I.id = SI.id_intalnire
INNER JOIN Produse P ON P.id = SI.id_produs
GROUP BY I.id

-- numele invitatilor care au participat la intalniri in aer liber
SELECT P.prenume, P.nume, IT.id as id_intalnire, IT.locatie FROM Invitati I
INNER JOIN Participanti P ON I.id_participant = P.id 
INNER JOIN Participanti_Intalnire PI ON PI.id_participant = P.id
INNER JOIN Intalniri IT ON IT.id = PI.id_intalnire
WHERE IT.locatie LIKE 'Aer liber'

--toate cartile scrise de un autor care nu a fost discutat la nicio tema
SELECT C.titlu, A.nume, TA.id_tema FROM Carti C 
INNER JOIN Autori A ON C.id_autor = A.id 
LEFT JOIN Teme_Autori TA ON TA.id_autor = A.id
WHERE TA.id_tema is NULL AND TA.id_autor is null

--toti participantii cu rol media care participa la intalniri din anul 2024
SELECT DISTINCT P.nume, P.prenume FROM Participanti P
INNER JOIN Roluri R ON P.id_rol = R.id
INNER JOIN Participanti_Intalnire PIT ON P.id = PIT.id_participant
INNER JOIN Intalniri I ON I.id = PIT.id_intalnire
WHERE R.domeniu like 'Media' AND YEAR(I.data) = 2024

--participantii care au baut alcool underage :)))  
SELECT DISTINCT P.nume, P.prenume FROM Participanti P
INNER JOIN Participanti_Intalnire PIT ON P.id = PIT.id_participant
INNER JOIN Intalniri I ON I.id = PIT.id_intalnire
WHERE DATEDIFF(year,P.data_nastere, I.data) < 18

--varsta participantilor si numarul de articole pentru cei care au scris articole
SELECT P.nume, P.prenume, DATEDIFF(year, P.data_nastere, GETDATE()) as varsta, COUNT(*) as numar_articole FROM Articole A
INNER JOIN Participanti P ON P.id = A.id_autor
GROUP BY P.id, P.nume, P.prenume, P.data_nastere
ORDER BY numar_articole ASC

--intalnirile unde s-au discutat autori din antichitate
SELECT DISTINCT I.id, I.data, I.locatie, T.titlu FROM Intalniri I
INNER JOIN Teme T ON T.id = I.id_tema
INNER JOIN Teme_Autori TI ON I.id_tema = TI.id_tema
INNER JOIN Autori A ON A.id = TI.id_autor
WHERE A.perioada LIKE 'Antichitate'

--numarul de participanti care au rolul dintr-un anumit departament
SELECT R.domeniu, COUNT(*) as numar_participanti FROM Roluri R
INNER JOIN Participanti P ON P.id_rol = R.id
GROUP BY R.domeniu