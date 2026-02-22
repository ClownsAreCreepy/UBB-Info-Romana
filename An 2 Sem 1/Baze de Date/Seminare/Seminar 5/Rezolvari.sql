-- INDECSI
-- Un index este o structura on-disk asociata unui tabel sau unui view care creste viteza de returnare a inregistrarilor

-- Activam casuta Include Actual Execution Plan (Ctrl+M)
SELECT * FROM Vizitatori

-- Sintaxa pentru a crea index clustered
-- CREATE CLUSTERED INDEX index_name ON table_name
-- (column_name(s) [ASC|DESC])

-- Sintaxa pentru a crea index non-clustered
-- CREATE INDEX index_name ON table_name
-- (column_name(s) [ASC|DESC])

-- Exemplu:
CREATE NONCLUSTERED INDEX ix_Atractii_nume_asc ON Atractii (nume ASC)
-- sau
-- CREATE INDEX ix_Atractii_nume_asc ON Atractii (nume)

-- Constrangere UNIQUE -> Se creeaza index nonclustered unique pe coloana aia


-- Coloane key -> coloane specificate la crearea unui index
-- Coloane nonkey -> coloanele specificate in clauza INCLUDE a unui index nonclustered
-- Sintaxa:
-- CREATE INDEX index_name
-- ON table_name (key_column_name(s) [ASC|DESC])
-- INCLUDE (nonkey_column_name(s))

-- Crearea unui index unique
CREATE UNIQUE INDEX ix_Categorii_nume_desc_uq ON Categorii
(nume DESC)

-- Crearea unui index unique cu optiunea IGNORE_DUP_KEY
CREATE UNIQUE INDEX ix_Vizitatori_email_asc_uq ON Vizitatori
(email ASC) WITH (IGNORE_DUP_KEY=ON)

-- Index-urile de sus sunt single column
-- La multi-column conteaza ordinea, deoarece primul e sortare principala, apoi al doilea etc
CREATE INDEX ix_Atractii_Varsta_min_asc_nume_asc ON Atractii
(varsta_min ASC, nume ASC)

SELECT varsta_min, nume FROM Atractii
ORDER BY varsta_min ASC


-- Index-urile de mai sus sunt full-table
-- Cele filtered contin doar valorile care evalueaza o anumita conditie
CREATE INDEX ix_Atractii_nume_asc_filtered ON Atractii
(nume ASC) WHERE nume > 'C'

-- Dezactivarea/Modificarea/Stergerea unui index
ALTER INDEX ix_Atractii_varsta_min_asc_nume_asc ON Atractii DISABLE
ALTER INDEX ix_Atractii_varsta_min_asc_nume_asc ON Atractii REBUILD
DROP INDEX ix_Atractii_varsta_min_asc_nume_asc ON Atractii