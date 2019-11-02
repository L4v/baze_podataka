-- Minimalna i maksimalna plata radnika
select max(plt), min(plt) from radnik;

-- Broj radnika i ukupna mesecna plata
-- sum ignorise NULL vrednost
select count(mbr), sum(plt)
from radnik;

-- Broj radnika, prosecna plata i ukupna godisnja plata
-- avg ignorise NULL vrednost
select count(mbr), avg(plt) as "Prosecna plata", sum(plt * 12) as "Ukupna godisnja plata"
from radnik;

-- Ukupna premija svih radnika sa mbr > 100
-- rezultat je NULL, sum, avg, max i min vracaju NULL
-- ako su sve vrednosti u skupu NULL
-- jer NULL +/- NULL = NULL
select sum(pre)
from radnik
where mbr > 100;

-- count vraca 0 jer count broji koliko je instanci
-- neke ne NULL vrednosti bilo
select count(pre)
from radnik
where mbr > 100;

-- Prosecna plata svih radnika pomnozena sa 1.41 na 2 decimale
select round(avg(plt * 1.41), 2)
from radnik;

-- 10 radnika koji imaju najvecu platu,
-- sortirani po plati u opadajucem redosledu
select mbr, ime, prz, plt, rownum
from (select * from radnik order by plt desc)
where rownum <= 10;

select plt, (select avg(plt) from radnik) as "Prosecna plata", abs((select avg(plt) from radnik) - plt) as "Razlika"
from radnik;

-- Broj projekata na kojima su radnici sa mbr < 40
select mbr, count(spr)
from radproj
where mbr < 40
group by mbr;

-- Broj radnika na svakom projektu i ukupno angazovanje na tom projektu
select spr, count(mbr) as "Broj radnika", sum(brc) as "Ukupno angazovanje"
from radproj
group by spr;

-- MBR radnika koji rade na vise od 2 projekta i broj projekata na kojima rade
select mbr, count(spr) as "Broj projekata"
from radproj
group by mbr
having count(spr) > 2;

-- mbr, ime, prz, plt u rastucem redosledu onih radnika koji imaju vecu platu od prosecne
select mbr, ime, prz, plt
from radnik
where plt > (select avg(plt) from radnik)
order by plt asc;

-- ime i prz radnika koji rade na projektu 30
select ime, prz
from radnik
where mbr in (select mbr from radproj where spr = 30);

-- ime i prz radnika koji rade na projektu 10, a ne rade na 30
select ime, prz
from radnik
where mbr in (select mbr from radproj where spr = 10) and mbr not in (select mbr from radproj where spr = 30);

-- OVO NE MOZE
-- Selektovace samo one radnike koji imaju spr = 10, posto gleda samo one
-- spr koji su 10 i nisu 30 => ako gleda spr koji je 10, ocigledno da nece biti 30
-- kada naleti na spr != 30, ali da nije ni 10 onda ga nece selektovati
-- efektivno, ovo je isto kao i da smo u where stavili (select mbr from radproj where spr = 10)
select mbr, ime, prz
from radnik
where mbr in (select mbr from radproj where spr = 10 and spr != 30);

-- Ime, prezime i god najstarijeg radnika
select ime, prz, god
from radnik
where god <= all(select god from radnik);

-- mbr, prz, ime i brc radnika koji su na projektu 10
select r.mbr, prz, ime, brc, spr
from radnik r, radproj rp 
where rp.spr = 10 and r.mbr = rp.mbr;

-- mbr, prz, ime, plt rukovodilaca
select mbr, prz, ime, plt
from radnik r, projekat p
where r.mbr = p.ruk;

-- ime, prz svih radnika osim rukovodilaca projekta 10
select ime, prz
from radnik r, projekat p
where r.mbr != p.ruk and p.spr = 10;

-- ime, prz svih radnika osim rukovodilaca projekta 10 sa ugnjezdenim upitom
select ime, prz
from radnik r
where r.mbr != (select ruk from projekat where spr = 10);

-- nap na kojima radi bar 1 radnik koji radi i na spr = 60
select nap
from projekat p1
where p1.spr in (select spr from radproj where mbr in (select mbr from radproj where spr = 60)); 

-- ime i prz rukovodilaca projekta i br projekta kojima rukovode
select ime, prz, count(spr)
from radnik r, projekat p
where r.mbr = p.ruk
group by ime, prz;

-- mbr, ime, prz, ukupan br projekata i ukupno angazovanje na projektima
-- na kojim rade svi radnici
select r.mbr, ime, prz, count(spr) as BROJ_PROJEKATA, sum(brc) as UKUPNO_ANGAZOVANJE
from radnik r, radproj rp
where r.mbr = rp.mbr
group by r.mbr, ime, prz;

-- ime, prz rukovodilaca i broj projekata na kojima rade
select ime, prz, count(distinct rp.spr)
from radnik r, radproj rp
where r.mbr = rp.mbr and r.mbr in (select ruk from projekat)
group by ime, prz;

