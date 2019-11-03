-- nazive projekata na kojima se radi ukupno vise od 15h
select nap, sum(brc)
from projekat p, radproj rp
where p.spr = rp.spr
group by nap
having sum(brc) > 15;

-- sifre i nazive projekata na kojima radi vise od 2 radnika
---------------------
select p.spr, p.nap
from projekat p
where p.spr in (select spr from radproj group by spr having count(mbr) > 2);

-- ILI

select p.spr, p.nap
from projekat p, radproj rp
where rp.spr = p.spr
group by p.spr, p.nap
having count(mbr) > 2
order by spr;
----------------------

-- sifre i nazive projekata na kojima je prosecno angazovanje vece od
-- prosecnog angazovanja na svim projektima
select p.spr, p.nap
from projekat p, radproj rp
where p.spr = rp.spr
group by p.spr, p.nap
having avg(brc) > (select avg(brc) from radproj);

-- nazive i sifre projekata sa najvecim prosecnim angazovanjem
select p.nap, p.spr
from projekat p, radproj rp
where p.spr = rp.spr
group by p.nap, p.spr
having avg(rp.brc) >= all(select avg(brc) from radproj group by spr);

-- mbr, ime, prz, plt radnika koji zaradjuju vise od radnika sa mbr = 40
select r.mbr, ime, prz, plt
from radnik r
where plt > (select plt from radnik where mbr = 40);

-- ILI

select r.mbr, r.ime, r.prz, r.plt
from radnik r, radnik r1
where r.plt > r1.plt and r1.mbr = 40;
------------------------------------

-- ime, prz i plt radnika koji zaradjuju bar 1000din manje od rukovodioca projekta
-- na kom rade

select r.ime, r.prz, r.plt
from radnik r, radnik r1, radproj rp, projekat p
where r.mbr = rp.mbr and rp.spr = p.spr and r1.mbr = p.ruk and r.plt + 1000 < r1.plt;

-- mbr, ime, prz, plt radnika cije je angazovanje na nekom projektu vece od proseka angazovanja
-- na tom projektu
select r1.mbr, r1.ime, r1.prz, r1.plt, rp1.brc
from radnik r1, radproj rp1
where r1.mbr = rp1.mbr and rp1.brc > (select avg(brc) from radproj rp2 where rp1.spr = rp2.spr);

-- Najstariji radnik preko (not) exists
select r.mbr, r.ime, r.prz, r.god
from radnik r
where not exists (select god from radnik r1 where r1.god < r.god);

-- Izlistati mbr, ime, prz randika koji ne rade na projektu 10
select r.mbr, r.ime, r.prz
from radnik r
where not exists (select * from radproj rp where rp.mbr = r.mbr and rp.spr = 10);

-- Izlistati radnike koji ne rade ni na jednom projektu (ne postoji projekat na kom rade)
select r.mbr, r.ime, r.prz
from radnik r
where not exists (select * from radproj rp where rp.mbr = r.mbr);

-- Radnici koji nisu rukovodioci projekata (ne postoji projekat kojima rukovode)
select r.mbr, r.ime, r.prz
from radnik r
where not exists (select * from projekat p where p.ruk = r.mbr);

-- Najmladji rukovodioc projekata
select distinct r.mbr, r.ime, r.prz, r.god
from radnik r, projekat p
where r.mbr = p.ruk
and not exists(select mbr from radnik r1, projekat p1 where r1.mbr = p1.ruk and r1.god > r.god);

-- mbr, ime, prz radnika koji rade na projektu 20 ili im je plata veca od prosecne
select mbr, ime, prz
from radnik
where mbr in (select mbr from radproj where spr = 20)
union
select mbr, ime, prz
from radnik
where plt > (select avg(plt) from radnik);

-- sa union all (ima duplikate)
select mbr, ime, prz
from radnik
where mbr in (select mbr from radproj where spr = 20)
union all
select mbr, ime, prz
from radnik
where plt > (select avg(plt) from radnik);

-- mbr, ime, prz cije prezime pocinje na M ili R i mbr, ime, prz radnika
-- cije prezime pocinje na M ili P
select mbr, ime, prz
from radnik
where prz like 'M%' or prz like 'R%'
intersect
select mbr, ime, prz
from radnik
where prz like 'M%' or prz like 'P%';

-- mbr, ime, prz radnika cije prezime pocinje na M ili R i mbr, ime, prz radnika
-- cije prezime pocinje na M ili P
select mbr, ime, prz
from radnik
where prz like 'M%' or prz like 'R%'
minus
select mbr, ime, prz
from radnik
where prz like 'M%' or prz like 'P%';

-- ime i prz radnika koji rade na projektu spr = 30
-- NATURAL JOIN vrsi spajanje preko imena kolona
select ime, prz
from radnik natural join radproj
where spr = 30;

select ime, prz
from radnik inner join radproj
on spr = 30;

-- mbr, ime, prz radnika i spr projekata na kojima rade,
-- takodje isto i za radnike koji ne rade ni na jednom projektu,
-- u tom slucaju prikazati nedostajucu vrednost
select r.mbr, ime, prz, spr
from radnik r left outer join radproj rp
on r.mbr = rp.mbr;

-- mbr, ime, prz svih radnika i naziva projekata
-- kojima rukovode, ukoliko ne rukovodi
-- napisati 'Ne rukovodi projektom'
select r.mbr, ime, prz, nvl(nap, 'Ne rukovodi projektom')
from radnik r left outer join projekat p
on r.mbr = p.ruk;

-- prikazati nazive svih projekata i mbr radnika
-- koji rade na njima, ukoliko ne radi ni jedan radnik
-- napisati 0 na mestu mbr
-- (PREKO RIGHT OUTER JOIN)
select p.nap, nvl(rp.mbr, 0)
from radproj rp right outer join projekat p
on rp.spr = p.spr;

-- full outer
select nap, nvl(rp.mbr, 0)
from radproj rp full outer join projekat p
on rp.spr= p.spr;

-- mbr, ime, prz radnika i spr projekata na kojima
-- rade, takodje iste podatke i za radnike
-- koji ne rade ni na jednom projektu, gde u tom slucaju
-- treba prikazati nedostajucu vrednost
-- (Dodao sam jos da ispise i ime projekta na kom rade)
select r.mbr, ime, prz, nvl(rp.spr, 0), nvl(p.nap, 'Ne radi na projektu')
from radnik r left outer join radproj rp 
on r.mbr = rp.mbr
left outer join projekat p
on rp.spr = p.spr;

-- mbr, ime, prz radnika i spr i nap projekta na kom rade
-- sortiranu po mbr
select r.mbr, ime, prz, nvl(rp.spr, 0), nvl(p.nap, 'Ne radi na projektu')
from radnik r left outer join radproj rp 
on r.mbr = rp.mbr
left outer join projekat p
on rp.spr = p.spr
order by mbr asc;

-- ime, prz svih radnika i prezimena sefova ako ih imaju
-- ako nemaju sefa, napisati 'Nema sefa'
select r.ime, r.prz, nvl(r1.prz, 'Nema sefa')
from radnik r left outer join radnik r1
on r.sef = r1.mbr;