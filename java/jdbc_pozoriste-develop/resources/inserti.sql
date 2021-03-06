insert into Drzava values (1,'Srbija');
insert into Drzava values (2,'Crna Gora');
insert into Drzava values (3,'Slovenija');
commit;
insert into Mesto values (1,'Novi Sad',1);
insert into Mesto values (2,'Beograd',1);
insert into Mesto values (3,'Nis',1);
insert into Mesto values (4,'Tivat',2);
insert into Mesto values (5,'Ljubljana',3);
insert into Mesto values (6,'Kragujevac',1);
commit;
insert into Pozoriste values (1, 'Jugoslovensko dramsko pozoriste', 'Kralja Milana 50', 'http://jdp.rs',1);
insert into Pozoriste values (2, 'Pozoriste na Terazijama', 'Trg Nikole Pasica 3', 'http://pozoristeterazije.com',2);
insert into Pozoriste values (3, 'Beogradsko dramsko pozoriste', 'Milesevska 64a', 'http://www.bdp.rs',2);
insert into Pozoriste values (4, 'Narodno pozoriste', 'Francuska 3', 'https://www.narodnopozoriste.rs',1);
insert into Pozoriste values (5, 'Knjazevsko-srpski teatar Kragujevac', 'Daniciceva 3', 'http://www.joakimvujic.com',6);
insert into Pozoriste values (6, 'Centar za kulturu Tivat', 'Luke Tomanovica 4', 'http://www.czktivat.me',4);
insert into Pozoriste values (7, 'Slovensko narodno gledalisce Drama', 'Erjavceva 1', 'http://www.drama.si',5);
insert into Pozoriste values (8, 'Narodno pozoriste u Nisu', 'Sindjelicev trg', 'http://www.narodnopozoristenis.rs',3);
insert into Pozoriste values (9, 'Atelje 212', 'Svetogorska 21', 'http://atelje212.rs',2);
commit;
insert into Glumac values (1, 'Natasa', TO_DATE('22.05.1972', 'DD.MM.YYYY'), 'g',34000.00, null,  4);
insert into Glumac values (2, 'Vojislav', TO_DATE('11.05.1949', 'DD.MM.YYYY'),'z', 160000.00, 3000,  1);
insert into Glumac values (3, 'Nikola',  TO_DATE('09.07.1974', 'DD.MM.YYYY'), 'g', 32000.00, null,  null);
insert into Glumac values (4, 'Vojin',  TO_DATE('22.08.1971', 'DD.MM.YYYY'), 'z', 110000.00, 3000.00, 1);
insert into Glumac values (5, 'Branislav',  TO_DATE('25.08.1955', 'DD.MM.YYYY'), 'z',135000.00, 3000.00,  1);
insert into Glumac values (6, 'Sergej',  TO_DATE('02.09.1972', 'DD.MM.YYYY'), 'g', 15000.00, null,  null);
insert into Glumac values (7, 'Vesna',  TO_DATE('23.03.1954', 'DD.MM.YYYY'), 'g',38000.00, null,  3);
insert into Glumac values (8, 'Sloboda',  TO_DATE('21.08.1981', 'DD.MM.YYYY'), 'g',25000.00, null,  4);
insert into Glumac values (9, 'Boris',  TO_DATE('26.11.1971', 'DD.MM.YYYY'), 'g', 30000.00, null,  null);
insert into Glumac values (10, 'Predrag', TO_DATE('24.07.1947', 'DD.MM.YYYY'), 'z', 150000.00, 3000.00,  1);
insert into Glumac values (11, 'Jelisaveta',  TO_DATE('13.06.1942', 'DD.MM.YYYY'), 'g', 50000.00, null,  null);
insert into Glumac values (12, 'Nenad',TO_DATE('12.07.1972', 'DD.MM.YYYY'), 'g',25000.00, null,  9);
insert into Glumac values (13, 'Nikola',  TO_DATE('27.01.1983', 'DD.MM.YYYY'), 'z', 98000.00, 3000.00,  1);
insert into Glumac values (14, 'Ljubomir',  TO_DATE('08.07.1976', 'DD.MM.YYYY'), 'z',  125000.00, 3000.00, 1);
insert into Glumac values (15, 'Milena',  TO_DATE('24.01.1990', 'DD.MM.YYYY'), 'g', 30000.00, null,  2);
insert into Glumac values (16, 'Bogdan',  TO_DATE('01.08.1953', 'DD.MM.YYYY'), 'z',140000.00, 3000.00,  1);
insert into Glumac values (17, 'Goran',  TO_DATE('19.03.1969', 'DD.MM.YYYY'), 'z',10000.00, 3000.00,  1);
insert into Glumac values (18, 'Vesna',  TO_DATE('13.03.1965', 'DD.MM.YYYY'), 'g', 35000.00, null,  null);
insert into Glumac values (19, 'Milena',  TO_DATE('01.01.1972', 'DD.MM.YYYY'), 'g', 10000.00, null,  3);
insert into Glumac values (20, 'Nikola', TO_DATE('05.09.1967', 'DD.MM.YYYY'), 'g', 20000.00, null,  null);
insert into Glumac values (21, 'Milena', TO_DATE('05.10.1940', 'DD.MM.YYYY'), 'g', 27000.00, null,  null);
insert into Glumac values (22, 'Iskra',  TO_DATE('17.11.1987', 'DD.MM.YYYY'),  'g', 17000.00, null, 4);
insert into Glumac values (23, 'Vanja', TO_DATE('11.11.1976', 'DD.MM.YYYY'),  'g', 17000.00, null, 4);
commit;

insert into Scena values (1, 'Ljuba Tadic', 950,1);
insert into Scena values (2, 'Studio JDP', 210,1);
insert into Scena values (3, 'Scena pozorista na Terazijama',500,2);
insert into Scena values (4, 'Rade Markovic', 374,3);
insert into Scena values (5, 'Nova scena', 129,3);
insert into Scena values (6, 'Rasa Plaovic', 297,4);
insert into Scena values (7, 'Velika scena', 544,4);
insert into Scena values (8, 'Scena Joakim Vujic', 240,5);
insert into Scena values (9, 'Ljetnja pozornica - Tivat', 1026,6);
insert into Scena values (10, 'Scena Atrijum', 217,6);
insert into Scena values (11, 'Veliki oder', 327,7);
insert into Scena values (12, 'Scena Narodnog pozorista u Nisu', 513,8);
commit;

insert into Predstava values (10, 'Otelo',  120, 2012);
insert into Predstava values (20, 'Gospodjica', 115, 2013);
insert into Predstava values (30, 'Don Zuan', 125 , 2017);
insert into Predstava values (40, 'Tako je (ako vam se tako cini)', 85 ,2017);
insert into Predstava values (50, 'Zlocin i kazna', 95, 2013);
commit;


insert into Prikazivanje values (1, TO_DATE('05.02.2017','dd-mm-yyyy') , to_date('05.02.2017 8:00','DD.MM.YYYY HH:mi'), 950, 10, 1);
insert into Prikazivanje values (2, TO_DATE('03.03.2017', 'DD.MM.YYYY'),to_date('03.03.2017 8:00','DD.MM.YYYY HH:mi'), 753, 10, 1);
insert into Prikazivanje values (3, TO_DATE('27.03.2017', 'DD.MM.YYYY'),to_date('27.03.2017 8:00','DD.MM.YYYY HH:mi'), 820, 10, 1);
insert into Prikazivanje values (4, TO_DATE('01.05.2017', 'DD.MM.YYYY'),to_date('01.05.2017 8:00','DD.MM.YYYY HH:mi'), 950, 10, 1);
insert into Prikazivanje values (5, TO_DATE('17.05.2017', 'DD.MM.YYYY'),to_date('17.05.2017 8:00','DD.MM.YYYY HH:mi'), 320, 10,11);
insert into Prikazivanje values (6, TO_DATE('01.07.2017', 'DD.MM.YYYY'),to_date('01.07.2017 8:30','DD.MM.YYYY HH:mi'), 1005, 10, 9);
insert into Prikazivanje values (7, TO_DATE('01.10.2017', 'DD.MM.YYYY'),to_date('01.10.2017 8:00','DD.MM.YYYY HH:mi'), 929, 10, 1);
insert into Prikazivanje values (8, TO_DATE('26.10.2017', 'DD.MM.YYYY'),to_date('26.10.2017 8:00','DD.MM.YYYY HH:mi'), 652, 10, 1);
insert into Prikazivanje values (9, TO_DATE('08.04.2017', 'DD.MM.YYYY'),to_date('08.04.2017 7:30','DD.MM.YYYY HH:mi'), 240, 10, 8);
insert into Prikazivanje values (10, TO_DATE('19.11.2017', 'DD.MM.YYYY'),to_date('19.11.2017 7:30','DD.MM.YYYY HH:mi'), 235, 10, 8);
insert into Prikazivanje values (11, TO_DATE('11.02.2018', 'DD.MM.YYYY'),to_date('11.02.2018 8:00','DD.MM.YYYY HH:mi'), 950, 10, 1);
insert into Prikazivanje values (12, TO_DATE('05.03.2018', 'DD.MM.YYYY'),to_date('05.03.2018 8:00','DD.MM.YYYY HH:mi'), 753, 10, 1);
insert into Prikazivanje values (13, TO_DATE('12.05.2018', 'DD.MM.YYYY'),to_date('12.05.2018 8:00','DD.MM.YYYY HH:mi'), 820, 10, 1);
insert into Prikazivanje values (14, TO_DATE('03.01.2018', 'DD.MM.YYYY'),to_date('03.01.2018 8:00','DD.MM.YYYY HH:mi'), 950, 20, 1);
insert into Prikazivanje values (15, TO_DATE('15.03.2018', 'DD.MM.YYYY'),to_date('15.03.2018 8:00','DD.MM.YYYY HH:mi'), 903, 20, 1);
insert into Prikazivanje values (16, TO_DATE('29.03.2018', 'DD.MM.YYYY'),to_date('29.03.2018 8:00','DD.MM.YYYY HH:mi'), 575, 20, 1);
insert into Prikazivanje values (17, TO_DATE('17.05.2018', 'DD.MM.YYYY'),to_date('17.05.2018 8:30','DD.MM.YYYY HH:mi'), 512, 20, 12);
insert into Prikazivanje values (18, TO_DATE('25.07.2018', 'DD.MM.YYYY'),to_date('25.07.2018 9:30','DD.MM.YYYY HH:mi'), 210, 20, 10);
insert into Prikazivanje values (19, TO_DATE('13.11.2017', 'DD.MM.YYYY'),to_date('13.11.2017 8:00','DD.MM.YYYY HH:mi'), 842, 30, 1);
insert into Prikazivanje values (20, TO_DATE('01.12.2017', 'DD.MM.YYYY'),to_date('01.12.2017 8:00','DD.MM.YYYY HH:mi'), 895, 30, 1);
insert into Prikazivanje values (21, TO_DATE('14.01.2018', 'DD.MM.YYYY'),to_date('14.01.2018 8:00','DD.MM.YYYY HH:mi'), 936, 30, 1);
insert into Prikazivanje values (22, TO_DATE('01.03.2018', 'DD.MM.YYYY'),to_date('01.03.2018 8:00','DD.MM.YYYY HH:mi'), 950, 30, 1);
insert into Prikazivanje values (23, TO_DATE('21.05.2018', 'DD.MM.YYYY'),to_date('21.05.2018 8:00','DD.MM.YYYY HH:mi'), 947, 30, 1);
insert into Prikazivanje values (24, TO_DATE('02.06.2018', 'DD.MM.YYYY'),to_date('02.06.2018 8:00','DD.MM.YYYY HH:mi'), 937, 30, 1);
insert into Prikazivanje values (25, TO_DATE('14.02.2018', 'DD.MM.YYYY'),to_date('14.02.2018 8:00','DD.MM.YYYY HH:mi'), 948, 40, 1);
insert into Prikazivanje values (26, TO_DATE('17.04.2018', 'DD.MM.YYYY'),to_date('17.04.2018 8:00','DD.MM.YYYY HH:mi'), 950, 40, 1);
insert into Prikazivanje values (27, TO_DATE('18.05.2018', 'DD.MM.YYYY'),to_date('18.05.2018 8:00','DD.MM.YYYY HH:mi'), 755, 40, 1);
insert into Prikazivanje values (28, TO_DATE('30.01.2017', 'DD.MM.YYYY'),to_date('30.01.2017 8:00','DD.MM.YYYY HH:mi'), 950, 50, 1);
insert into Prikazivanje values (29, TO_DATE('18.03.2017', 'DD.MM.YYYY'),to_date('18.03.2017 8:00','DD.MM.YYYY HH:mi'), 899, 50, 1);
insert into Prikazivanje values (30, TO_DATE('28.01.2018', 'DD.MM.YYYY'),to_date('28.01.2018 8:00','DD.MM.YYYY HH:mi'), 698, 50, 1);
insert into Prikazivanje values (31, TO_DATE('19.11.2018', 'DD.MM.YYYY'),to_date('19.11.2018 7:30','DD.MM.YYYY HH:mi'), 212, 50, 8);
insert into Prikazivanje values(32, TO_DATE('19.11.2020','DD.MM.YYYY'),to_date('19.11.2020 7:30','DD.MM.YYYY HH:mi'),350,50,5);
commit;

insert into Uloga (idul,imeulo,vrstaulo,pol,predstava_idpred) values (1, 'Otelo', 'g', 'm',10);
insert into Uloga (idul,imeulo,vrstaulo,pol,predstava_idpred) values (2, 'Jago', 'g', 'm',10);
insert into Uloga (idul,imeulo,vrstaulo,pol,predstava_idpred) values (3, 'Dezdemona', 'g', 'z',10);
insert into Uloga (idul,imeulo,vrstaulo,pol,predstava_idpred) values (4, 'Brabancio', 'g', 'm',10);
insert into Uloga (idul,imeulo,vrstaulo,pol,predstava_idpred) values (5, 'Rodrigo', 's', 'm',10);
insert into Uloga (idul,imeulo,vrstaulo,pol,predstava_idpred) values (6,'Montano', 's', 'm',10);
insert into Uloga (idul,imeulo,vrstaulo,pol,predstava_idpred) values (7, 'Gracijano', 's', 'm',10);
insert into Uloga (idul,imeulo,vrstaulo,pol,predstava_idpred) values (8, 'Gospodjica', 'g', 'z',20);
insert into Uloga (idul,imeulo,vrstaulo,pol,predstava_idpred) values (9, 'Otac', 'g', 'm',20);
insert into Uloga (idul,imeulo,vrstaulo,pol,predstava_idpred) values (10, 'Jovanka', 'g', 'z',20);
insert into Uloga (idul,imeulo,vrstaulo,pol,predstava_idpred) values (11, 'Dajdza Vlado Hadzi-Vasic', 'g', 'm',20);
insert into Uloga (idul,imeulo,vrstaulo,pol,predstava_idpred) values (12, 'Majka', 's', 'z',20);
insert into Uloga (idul,imeulo,vrstaulo,pol,predstava_idpred) values (13, 'Don Zuan', 'g', 'm',30);
insert into Uloga (idul,imeulo,vrstaulo,pol,predstava_idpred) values (14, 'Zganare', 'g', 'm',30);
insert into Uloga (idul,imeulo,vrstaulo,pol,predstava_idpred) values (15, 'Dona Elvira', 'g', 'z',30);
insert into Uloga (idul,imeulo,vrstaulo,pol,predstava_idpred) values (16, 'Don Luis', 's', 'm',30);
insert into Uloga (idul,imeulo,vrstaulo,pol,predstava_idpred) values (17, 'Don Karlos', 's', 'm',30);
insert into Uloga (idul,imeulo,vrstaulo,pol,predstava_idpred) values (18, 'Lamberto Laudizi', 'g', 'm',40);
insert into Uloga (idul,imeulo,vrstaulo,pol,predstava_idpred) values (19, 'Gospodja Frola', 'g', 'z',40);
insert into Uloga (idul,imeulo,vrstaulo,pol,predstava_idpred) values (20, 'Savetnik Agaci', 'g', 'm',40);
insert into Uloga (idul,imeulo,vrstaulo,pol,predstava_idpred) values (21, 'Gospodin Sireli', 's', 'm',40);
insert into Uloga (idul,imeulo,vrstaulo,pol,predstava_idpred) values (22, 'Rodion Romanovic Raskoljnikov', 'g', 'm',50);
insert into Uloga (idul,imeulo,vrstaulo,pol,predstava_idpred) values (23, 'Porfirij Petrovic', 'g', 'm',50);
insert into Uloga (idul,imeulo,vrstaulo,pol,predstava_idpred) values (24, 'Sonja Marmeladova', 'g', 'z',50);
insert into Uloga (idul,imeulo,vrstaulo,pol,predstava_idpred) values (25, 'Koh', 'g', 'm',50);
commit;


insert into Podela (idpod,uloga_idul,glumac_mbg,honorar,datumd,datump) values (1,1, 4, 20000, TO_DATE('01.08.2012','DD.MM.YYYY'), TO_DATE('01.01.2018','DD.MM.YYYY'));
insert into Podela (idpod, uloga_idul,glumac_mbg,honorar,datumd,datump) values (2,1, 12, 20000, TO_DATE('01.11.2017','DD.MM.YYYY'), TO_DATE('01.01.2018','DD.MM.YYYY'));
insert into Podela (idpod, uloga_idul,glumac_mbg,honorar,datumd,datump) values (3,2, 3, 20000, TO_DATE('01.01.2016','DD.MM.YYYY'), TO_DATE('01.01.2018','DD.MM.YYYY'));
insert into Podela (idpod, uloga_idul,glumac_mbg,honorar,datumd,datump) values (4,2, 20, 15000, TO_DATE('01.08.2012','DD.MM.YYYY'), TO_DATE('01.01.2016','DD.MM.YYYY'));
insert into Podela (idpod, uloga_idul,glumac_mbg,honorar,datumd,datump) values (5,3, 15, 20000, TO_DATE('01.01.2012','DD.MM.YYYY'), TO_DATE('01.01.2018','DD.MM.YYYY'));
insert into Podela (idpod, uloga_idul,glumac_mbg,honorar,datumd,datump) values (6,3, 8, 20000, TO_DATE('01.03.2017','DD.MM.YYYY'), TO_DATE('01.01.2018','DD.MM.YYYY'));
insert into Podela (idpod, uloga_idul,glumac_mbg,honorar,datumd,datump) values (7,4, 5, 20000, TO_DATE('01.08.2012','DD.MM.YYYY'), TO_DATE('01.01.2018','DD.MM.YYYY'));
insert into Podela (idpod, uloga_idul,glumac_mbg,honorar,datumd,datump) values (8,5, 13, 20000, TO_DATE('01.08.2012','DD.MM.YYYY'), TO_DATE('01.01.2018','DD.MM.YYYY'));
insert into Podela (idpod, uloga_idul,glumac_mbg,honorar,datumd,datump) values (9,8, 1, 25000, TO_DATE('01.06.2013','DD.MM.YYYY'), TO_DATE('01.01.2018','DD.MM.YYYY'));
insert into Podela (idpod, uloga_idul,glumac_mbg,honorar,datumd,datump) values (10,8, 19, 15000, TO_DATE('01.06.2015','DD.MM.YYYY'), TO_DATE('01.12.2017','DD.MM.YYYY'));
insert into Podela (idpod, uloga_idul,glumac_mbg,honorar,datumd,datump) values (11,9, 2, 15000, TO_DATE('01.06.2013','DD.MM.YYYY'), TO_DATE('01.01.2018','DD.MM.YYYY'));
insert into Podela (idpod, uloga_idul,glumac_mbg,honorar,datumd,datump) values (12,10, 8, 18000, TO_DATE('01.06.2013','DD.MM.YYYY'), TO_DATE('01.01.2018','DD.MM.YYYY'));
insert into Podela (idpod, uloga_idul,glumac_mbg,honorar,datumd,datump) values (13,10, 15, 15000, TO_DATE('01.06.2013','DD.MM.YYYY'), TO_DATE('01.02.2018','DD.MM.YYYY'));
insert into Podela (idpod, uloga_idul,glumac_mbg,honorar,datumd,datump) values (14,11, 6, 22000, TO_DATE('01.06.2013','DD.MM.YYYY'), TO_DATE('01.01.2018','DD.MM.YYYY'));
insert into Podela (idpod, uloga_idul,glumac_mbg,honorar,datumd,datump) values (15,12, 7, 20000, TO_DATE('01.06.2013','DD.MM.YYYY'), TO_DATE('01.01.2018','DD.MM.YYYY'));
insert into Podela (idpod, uloga_idul,glumac_mbg,honorar,datumd,datump) values (16,13, 4, 20000, TO_DATE('01.01.2017','DD.MM.YYYY'), TO_DATE('01.01.2018','DD.MM.YYYY'));
insert into Podela (idpod, uloga_idul,glumac_mbg,honorar,datumd,datump) values (17,13, 20, 25000, TO_DATE('01.01.2017','DD.MM.YYYY'), TO_DATE('01.01.2018','DD.MM.YYYY'));
insert into Podela (idpod, uloga_idul,glumac_mbg,honorar,datumd,datump) values (18,14, 6, 21000, TO_DATE('01.01.2017','DD.MM.YYYY'), TO_DATE('01.01.2018','DD.MM.YYYY'));
insert into Podela (idpod, uloga_idul,glumac_mbg,honorar,datumd,datump) values (19,15, 8, 20000, TO_DATE('01.01.2017','DD.MM.YYYY'), TO_DATE('01.01.2018','DD.MM.YYYY'));
insert into Podela (idpod, uloga_idul,glumac_mbg,honorar,datumd,datump) values (20,15, 19, 20000, TO_DATE('01.02.2018','DD.MM.YYYY'), TO_DATE('01.06.2018','DD.MM.YYYY'));
insert into Podela (idpod, uloga_idul,glumac_mbg,honorar,datumd,datump) values (21,16, 2, 20000, TO_DATE('01.01.2017','DD.MM.YYYY'), TO_DATE('01.01.2018','DD.MM.YYYY'));
insert into Podela (idpod, uloga_idul,glumac_mbg,honorar,datumd,datump) values (22,17, 13, 20000, TO_DATE('01.01.2017','DD.MM.YYYY'), TO_DATE('01.01.2018','DD.MM.YYYY'));
insert into Podela (idpod, uloga_idul,glumac_mbg,honorar,datumd,datump) values (23,18, 10, 20000, TO_DATE('01.03.2017','DD.MM.YYYY'), TO_DATE('01.01.2018','DD.MM.YYYY'));
insert into Podela (idpod, uloga_idul,glumac_mbg,honorar,datumd,datump) values (24,19, 11, 35000, TO_DATE('01.03.2017','DD.MM.YYYY'), TO_DATE('01.01.2018','DD.MM.YYYY'));
insert into Podela (idpod, uloga_idul,glumac_mbg,honorar,datumd,datump) values (25,19, 21, 35000, TO_DATE('01.03.2017','DD.MM.YYYY'), TO_DATE('01.01.2018','DD.MM.YYYY'));
insert into Podela (idpod, uloga_idul,glumac_mbg,honorar,datumd,datump) values (26,20, 5, 15000, TO_DATE('01.03.2017','DD.MM.YYYY'), TO_DATE('01.01.2018','DD.MM.YYYY'));
insert into Podela (idpod, uloga_idul,glumac_mbg,honorar,datumd,datump) values (27,21, 12, 15000, TO_DATE('01.03.2017','DD.MM.YYYY'), TO_DATE('01.01.2018','DD.MM.YYYY'));
insert into Podela (idpod, uloga_idul,glumac_mbg,honorar,datumd,datump) values (28,22, 13, 20000, TO_DATE('01.03.2013','DD.MM.YYYY'), TO_DATE('01.01.2018','DD.MM.YYYY'));
insert into Podela (idpod, uloga_idul,glumac_mbg,honorar,datumd,datump) values (29,23, 14, 20000, TO_DATE('01.01.2017','DD.MM.YYYY'), TO_DATE('01.01.2018','DD.MM.YYYY'));
insert into Podela (idpod, uloga_idul,glumac_mbg,honorar,datumd,datump)  values (30,23, 20, 23000, TO_DATE('01.03.2013','DD.MM.YYYY'), TO_DATE('01.01.2017','DD.MM.YYYY'));
insert into Podela (idpod, uloga_idul,glumac_mbg,honorar,datumd,datump) values (31,24, 15, 20000, TO_DATE('01.03.2013','DD.MM.YYYY'), TO_DATE('01.01.2017','DD.MM.YYYY'));
insert into Podela (idpod, uloga_idul,glumac_mbg,honorar,datumd,datump) values (32,25, 16, 23000, TO_DATE('01.03.2013','DD.MM.YYYY'), TO_DATE('01.01.2017','DD.MM.YYYY'));
commit;

insert into Sektor values (1, 'Umetnicki sektor', 1);
insert into Sektor values (2, 'Tehnicki sektor', 1);
insert into Sektor values (3, 'Administracija', 1);
insert into Sektor values (4, 'Uprava', 1);
insert into Sektor values (5, 'Nabavka', 1);
commit;





