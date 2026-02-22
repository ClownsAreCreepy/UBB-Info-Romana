CREATE TABLE Log_Filme
(
	id_log INT PRIMARY KEY IDENTITY(1,1),
	tip_operatie VARCHAR(10),	-- UPDATE OR DELETE
	data_operatie DATETIME DEFAULT GETDATE(),
	nume_utilizator NVARCHAR(100),
	
	id_f INT,
	titlu NVARCHAR(100),
	durata TIME,
	gen NVARCHAR(100),
	id_regizor INT,
	id_compozitor INT
)

CREATE TABLE Log_Firme
(
	id_log INT PRIMARY KEY IDENTITY (1,1),
	tip_operatie VARCHAR(10),
	data_operatie DATETIME DEFAULT GETDATE(),
	nume_utilizator NVARCHAR(100),
	
	id_f INT,
	nume NVARCHAR(100),
	tara_origine NVARCHAR(100)
)

CREATE TABLE Log_Publicatii
(
	id_log INT PRIMARY KEY IDENTITY(1,1),
	tip_operatie VARCHAR(10),
	data_operatie DATETIME DEFAULT GETDATE(),
	nume_utilizator NVARCHAR(100),

	id_film INT,
	id_firma INT
)
