--Aratam entry-urile dintr-un tabel
SELECT * FROM Actori
SELECT * FROM Filme

--Produs cartezian intre 2 tabele
--Nume_tabel[spatiu]alias
--Punem clauze pentru a le combina legit (cu foreign key)
SELECT * FROM Regizori r, Filme f WHERE r.id_r = f.id_regizor

SELECT * FROM Filme f
INNER JOIN Regizori r ON f.id_regizor = r.id_r

SELECT * FROM Filme f
LEFT JOIN Regizori r ON f.id_regizor = r.id_r

SELECT * FROM Filme f
RIGHT JOIN Regizori r ON f.id_regizor = r.id_r

SELECT * FROM Filme f
FULL JOIN Regizori r ON f.id_regizor = r.id_r

--Gasim regizorii care nu au facut filme
--Where filtreaza randuri
SELECT * FROM Regizori r
LEFT JOIN Filme f ON r.id_r = f.id_regizor WHERE f.id_regizor is NULL

--Reuniune
SELECT * FROM Filme f
RIGHT JOIN Regizori r ON f.id_regizor = r.id_r
UNION
SELECT * FROM Filme f
LEFT JOIN Regizori r ON f.id_regizor = r.id_r

--Interogare care arata toate filmele facute de Besson
SELECT * FROM Filme f
INNER JOIN Regizori r ON r.id_r = f.id_regizor WHERE r.nume = 'Besson'

--Like pentru comparari tip string
--Luam filmele si lui Besson si lui Benini
--Underscore (_) inseamna orice singur caracter
--Procent (%) inseamna orice oricate caractere
SELECT * FROM Filme f
INNER JOIN Regizori r ON r.id_r = f.id_regizor WHERE r.nume LIKE '%Be%'

/* Putem =, <, >
Putem si BETWEEN */
SELECT * FROM Recenzii WHERE nota > 7

--Pentru mai multe alegeri
SELECT * FROM Filme WHERE gen in ('Thriller', 'Horror')

--Pentru suma, avem functii agregate
SELECT sum(nota) FROM Recenzii

/* Calculam suma pe grupe: GROUP BY	(LA FINAL, INAINTE DE HAVING)
   Aratam chestiile care au mai mult de n coloane: HAVING COUNT(*) > n (LA FINAL)
   Luam distincte: DISTINCT (Dupa Select)*/