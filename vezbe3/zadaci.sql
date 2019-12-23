-- mbr, ime, prz, plt radnika ciji je broj sati angazovanja na nekom projektu
-- veci od prosecnog broja sati angazovanja na tom projektu
with angaz as
(
select rp.spr, avg(rp.brc) as ang_avg
from radproj rp
group by spr
)
select distinct r.mbr, r.ime, r.prz, r.plt, an.ang_avg
from radnik r, radproj rp, angaz an
where r.mbr = rp.mbr and rp.spr = an.spr
group by r.mbr, r.ime, r.prz, r.plt, an.ang_avg, an.spr
having avg(rp.brc) > (select ang_avg from angaz an2 where an2.spr = an.spr);
