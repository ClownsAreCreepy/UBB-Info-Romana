-- Creem sinonim pentru tabel separat
Select * From club_cultura.dbo.Autori

CREATE SYNONYM Autori_Miha FOR club_cultura.dbo.Autori

Select * From Autori_Miha


CREATE SYNONYM Teme_Autori_Miha FOR club_cultura.dbo.Teme_autori

SELECT * FROM Teme_Autori_Miha

DROP TABLE Teme_Autori

-- Daca stergem tabelul, avem dangling pointer daca folosim sinonimul