-- Filme
-- 1. Pe genuri
CREATE NONCLUSTERED INDEX idx_Filme_Gen
ON Filme (gen)
INCLUDE (titlu, durata)
GO

-- 2. Pe detalii
CREATE NONCLUSTERED INDEX idx_Filme_Detalii
ON Filme (id_regizor, id_compozitor)
INCLUDE (titlu, durata, gen)
GO


-- Firme
-- 1. Pe tari
CREATE NONCLUSTERED INDEX idx_Firme_Tari
ON Firme (tara_origine)
INCLUDE (nume)
GO

-- 2. Pe filme + Publicatii: 1. Film count / Firm 
CREATE NONCLUSTERED INDEX idx_Publicatii_Firma
ON Publicatii (id_firma)
INCLUDE (id_film)
GO

-- 2. Firm count / Film
CREATE NONCLUSTERED INDEX idx_Publicatii_Film
ON Publicatii (id_film)
INCLUDE (id_firma)
GO