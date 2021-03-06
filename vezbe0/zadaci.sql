
-- IZLISTATI SADRZAJ SVIH TABELA
SELECT *
FROM RADNIK;

SELECT *
FROM PROJEKAT;

SELECT *
FROM RADPROJ;

-- IZLISTATI IME I PREZIME SVIH RADNIKA
SELECT IME, PRZ
FROM RADNIK;

-- IZLISTATI SAMO JEDINSTVENO IME I PREZIME RADNIKA
SELECT DISTINCT IME, PRZ
FROM RADNIK;

-- IZLISTATI RADNIKE SA PLATOM >25000
SELECT MBR, IME, PRZ, PLT
FROM RADNIK
WHERE PLT > 25000;

-- IZLISTATI GODISNJU PLATU RADNIKA
SELECT MBR, IME, PRZ, PLT, PLT * 12 "Plata na godisnjem nivou"
FROM RADNIK;

-- RADNICI SA SEFOM
SELECT MBR, IME, PRZ
FROM RADNIK
WHERE SEF IS NOT NULL;

-- RADNICI BEZ SEFA
SELECT MBR, IME, PRZ
FROM RADNIK
WHERE SEF IS NULL;

-- RADNICI SA PLATOM [20000, 24000]
SELECT MBR, IME, PRZ, PLT
FROM RADNIK
WHERE PLT BETWEEN 20000 and 24000;

-- RADNICI RODJENI IZMEDJU 1953 i 1975
-- BETWEEN RADI {>= AND <=}, ZATVOREN INTERVAL
SELECT MBR, IME, PRZ, GOD
FROM RADNIK
WHERE GOD BETWEEN '01-JAN-1953' and '31-DEC-1975';

-- RADNICI RODJENI VAN INTERVALA [1953, 1975]
SELECT MBR, IME, PRZ, GOD
FROM RADNIK
WHERE GOD NOT BETWEEN '01-JAN-1953' and '31-DEC-1975';

-- RADNICI CIJE PREZIME POCINJE SA 'M'
SELECT MBR, IME, PRZ
FROM RADNIK
WHERE PRZ LIKE 'M%';

-- RADNICI CIJE PREZIME NE POCINJE SA 'A'
SELECT MBR, IME, PRZ
FROM RADNIK
WHERE PRZ NOT LIKE 'A%';

-- RADNICI CIJE PREZIME SADRZI 'a' NA DRUGOM MESTU
SELECT MBR, IME, PRZ
FROM RADNIK
WHERE PRZ LIKE '_a%';

-- IMENA RADNIKA KOJA POCINJU SA 'E', BEZ PONAVLJANJA
SELECT DISTINCT IME
FROM RADNIK
WHERE IME LIKE 'E%';

-- RADNICI KOJI U IMENU IMAJU SLOVO 'E' ILI 'e'
SELECT MBR, IME, PRZ
FROM RADNIK
WHERE IME LIKE '%E%' OR IME LIKE '%e%';

-- RADNICI KOJI RADE NA PROJEKTIMA 10, 20 ILI 30
SELECT MBR
FROM RADPROJ
WHERE SPR IN (10, 20, 30);

-- RADNICI NA PROJEKTU 10 ILI DA RADE 2, 4 ILI 6H
SELECT MBR
FROM RADPROJ
WHERE SPR = 10 OR BRC IN (2, 4, 6);

-- RADNICI KOJI SE NE ZOVU ANA ILI SANJA
SELECT MBR, IME, PRZ
FROM RADNIK
WHERE IME NOT IN ('Ana', 'Sanja');

-- RADNICI KOJI IMAJU SEFA SORTIRANI PO PREZIMENU
SELECT MBR, IME, PRZ
FROM RADNIK
WHERE SEF IS NOT NULL
ORDER BY PRZ ASC;

-- RADNICI PO OPADAJUCOJ PLATI
SELECT MBR, IME, PRZ, PLT PLATA
FROM RADNIK
ORDER BY Plata DESC;

-- KONKATENIRANJE IMENA I PREZIMENA I UVECANJE PLATE ZA 17%
SELECT MBR, IME || ' ' || PRZ "Ime i prezime", PLT * 1.17 "PLATA POVECANA"
FROM RADNIK;

-- KONKATENIRANJE IMENA I PREZIMENA I UVECANJE PLATE ZA 17% PREKO CONCAT
SELECT MBR, CONCAT(CONCAT(IME, ' '), PRZ) "Ime i prezime", PLT * 1.17 "PLATA POVECANA"
FROM RADNIK;

-- RADNICI CIJE PREZIME SADRZI IME
SELECT MBR, IME, PRZ
FROM RADNIK
WHERE UPPER(PRZ) LIKE('%' || UPPER(IME) || '%');

-- RADNICI KOJI SE ZOVU Pera ILI Moma
SELECT MBR, IME, PRZ, PLT
FROM RADNIK
WHERE IME = ANY('Pera', 'Moma');

-- RADNICI KOJI SE NE ZOVU Pera ILI Moma
SELECT MBR, IME, PRZ, PLT
FROM RADNIK
WHERE IME != ALL('Pera', 'Moma');

-- RADNICI CIJE SU PLATE UVECANE ZA GODISNJU PREMIJU
SELECT MBR, IME, PRZ, PLT + NVL(PRE, 0) "PLATA SA PREMIJOM", PRE
FROM RADNIK;
