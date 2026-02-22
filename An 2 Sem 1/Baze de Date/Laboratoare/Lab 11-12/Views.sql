-- Filme
-- 1. Pe genuri
CREATE OR ALTER VIEW vw_Filme_Genuri
AS
SELECT titlu, gen, durata FROM Filme
WHERE gen IS NOT NULL
GO

-- 2. Pe detalii
CREATE OR ALTER VIEW vw_Filme_Detalii
AS
SELECT 
	f.titlu AS [Titlu Film], f.durata AS Durata, f.gen AS Gen,
	ISNULL(r.nume, 'Necunoscut') AS [Nume Regizor],
	ISNULL(c.nume, 'Fara Compozitor') AS [Nume Compozitor]
FROM Filme f
LEFT JOIN Regizori r ON f.id_regizor = r.id_r
LEFT JOIN Compozitori c ON f.id_compozitor = c.id_c
GO


-- Firme
-- 1. Pe tari
CREATE OR ALTER VIEW vw_Firme_Tari
AS
SELECT nume, tara_origine FROM Firme
WHERE tara_origine IS NOT NULL
GO

-- 2. Pe filme
CREATE OR ALTER VIEW vw_Firme_Filme
AS
SELECT c.nume AS [Nume Firma], c.tara_origine AS [Tara Firma], f.titlu as [Film Distribuit]
FROM Firme c
INNER JOIN Publicatii p ON c.id_f = p.id_firma
INNER JOIN Filme f ON p.id_film = f.id_f
GO


-- Publicatii
-- 1. Film count / Firm
CREATE OR ALTER VIEW vw_Publicatii_Statistici_Firme
AS
SELECT c.nume AS [Nume Firma], COUNT(P.id_film) AS [Numar Filme Distribuite] FROM Firme c
INNER JOIN Publicatii p ON c.id_f = p.id_firma
GROUP BY C.nume
GO

-- 2. Film count / Firm
CREATE OR ALTER VIEW vw_Publicatii_Statistici_Filme
AS
SELECT F.titlu AS [Titlu Film], COUNT(p.id_firma) AS [Numar Distribuitori] FROM Filme f
INNER JOIN Publicatii p ON F.id_f = P.id_film
GROUP BY F.titlu
GO