--
-- File generated with SQLiteStudio v3.2.1 on Thu Apr 16 07:31:03 2020
--
-- Text encoding used: System
--
PRAGMA foreign_keys = off;
BEGIN TRANSACTION;

-- Table: admin
CREATE TABLE admin (id INTEGER PRIMARY KEY NOT NULL, username VARCHAR (30) UNIQUE NOT NULL, password VARCHAR (50) UNIQUE NOT NULL);

-- Table: barang
CREATE TABLE barang (kode_brg INT PRIMARY KEY NOT NULL, nama_brg VARCHAR (200) NOT NULL, spesifikasi TEXT NOT NULL, kategori VARCHAR (100) NOT NULL, lokasi_brg VARCHAR (100) NOT NULL, sumber_dana VARCHAR (100) NOT NULL, stok INT NOT NULL);
INSERT INTO barang (kode_brg, nama_brg, spesifikasi, kategori, lokasi_brg, sumber_dana, stok) VALUES (123, 'aplasx', 'sxa', 'saxdas', 'fgfdv', 'axdsa', 2);

-- Table: keluar_brg
CREATE TABLE keluar_brg (id_keluar INT PRIMARY KEY NOT NULL, kode_brg INT REFERENCES barang (kode_brg) ON DELETE CASCADE ON UPDATE CASCADE MATCH FULL NOT NULL, tgl_keluar DATE NOT NULL, jml_keluar INT NOT NULL, keperluan TEXT (300) NOT NULL, penerima VARCHAR (100) NOT NULL);
INSERT INTO keluar_brg (id_keluar, kode_brg, tgl_keluar, jml_keluar, keperluan, penerima) VALUES (2, 123, '2015/09/15', 3, 'jcnv', 'dsf');

-- Table: masuk_brg
CREATE TABLE masuk_brg (id_masuk INT PRIMARY KEY NOT NULL, kode_brg INT REFERENCES barang (kode_brg) ON DELETE CASCADE ON UPDATE CASCADE NOT NULL, tgl_masuk DATE NOT NULL, jml_masuk INT NOT NULL, kode_supp INT NOT NULL REFERENCES supplier (kode_supp) ON DELETE CASCADE ON UPDATE CASCADE MATCH FULL);
INSERT INTO masuk_brg (id_masuk, kode_brg, tgl_masuk, jml_masuk, kode_supp) VALUES (2, 123, '2019/04/15', 4, 1);
INSERT INTO masuk_brg (id_masuk, kode_brg, tgl_masuk, jml_masuk, kode_supp) VALUES (3, 123, '2019/04/15', 3, 1);

-- Table: pinjam_brg
CREATE TABLE pinjam_brg (id_pinjam INT PRIMARY KEY NOT NULL, kode_brg INT REFERENCES barang (kode_brg) ON DELETE CASCADE ON UPDATE CASCADE MATCH FULL NOT NULL, jml_pinjam INT NOT NULL, tgl_pinjam DATE NOT NULL, tgl_kembali DATE NOT NULL, nama_peminjam VARCHAR (100) NOT NULL, keperluan VARCHAR NOT NULL, status VARCHAR NOT NULL);
INSERT INTO pinjam_brg (id_pinjam, kode_brg, jml_pinjam, tgl_pinjam, tgl_kembali, nama_peminjam, keperluan, status) VALUES (5, 123, 1, '2015/04/15', '0000/00/00', 'fff', 'csdf', 'dipinjam');

-- Table: supplier
CREATE TABLE supplier (kode_supp INT PRIMARY KEY NOT NULL, nama_supp VARCHAR (100) NOT NULL, alamat TEXT NOT NULL, kota VARCHAR (100) NOT NULL, telp INT NOT NULL);
INSERT INTO supplier (kode_supp, nama_supp, alamat, kota, telp) VALUES (1, 'abc', 'hgsh', 'dsa', 99);

-- Trigger: keluar_stok
CREATE TRIGGER keluar_stok AFTER INSERT ON keluar_brg FOR EACH ROW BEGIN UPDATE barang SET stok = stok - NEW.jml_keluar WHERE kode_brg = NEW.kode_brg; END;

-- Trigger: keluar_stok2
CREATE TRIGGER keluar_stok2 AFTER DELETE ON keluar_brg FOR EACH ROW BEGIN UPDATE barang SET stok=stok+OLD.jml_keluar WHERE kode_brg=OLD.kode_brg; END;

-- Trigger: keluar_stok3
CREATE TRIGGER keluar_stok3 AFTER UPDATE OF jml_keluar ON keluar_brg FOR EACH ROW BEGIN UPDATE barang SET stok=stok+OLD.jml_keluar-NEW.jml_keluar WHERE kode_brg=NEW.kode_brg; END;

-- Trigger: masuk_stok
CREATE TRIGGER masuk_stok AFTER INSERT ON masuk_brg BEGIN UPDATE barang SET stok=stok+NEW.jml_masuk WHERE kode_brg=NEW.kode_brg; END;

-- Trigger: masuk_stok2
CREATE TRIGGER masuk_stok2 AFTER DELETE ON masuk_brg BEGIN UPDATE barang SET stok=stok-OLD.jml_masuk WHERE kode_brg=OLD.kode_brg; END;

-- Trigger: masuk_stok3
CREATE TRIGGER masuk_stok3 AFTER UPDATE OF jml_masuk ON masuk_brg FOR EACH ROW BEGIN UPDATE barang SET stok=stok-OLD.jml_masuk+NEW.jml_masuk WHERE kode_brg=NEW.kode_brg; END;

-- Trigger: pinjam_stok
CREATE TRIGGER pinjam_stok AFTER INSERT ON pinjam_brg FOR EACH ROW BEGIN UPDATE barang SET stok = stok - NEW.jml_pinjam WHERE kode_brg = NEW.kode_brg; END;

-- Trigger: pinjam_stok2
CREATE TRIGGER pinjam_stok2 AFTER DELETE ON pinjam_brg BEGIN UPDATE barang SET stok=stok+OLD.jml_pinjam WHERE kode_brg=OLD.kode_brg AND OLD.status="dipinjam"; END;

-- Trigger: pinjam_stok3
CREATE TRIGGER pinjam_stok3 AFTER UPDATE OF jml_pinjam ON pinjam_brg FOR EACH ROW BEGIN UPDATE barang SET stok=stok+OLD.jml_pinjam-NEW.jml_pinjam WHERE kode_brg=NEW.kode_brg AND OLD.status="dipinjam"; END;

COMMIT TRANSACTION;
PRAGMA foreign_keys = on;
