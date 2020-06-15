#include "halaman_admin.h"
#include "ui_halaman_admin.h"
#include "supplier.h"
#include "barang_masuk.h"
#include "barang_keluar.h"
#include "barang_stok.h"
#include "pinjam_barang.h"
#include "databarang.h"
#include "mainwindow.h"

halaman_admin::halaman_admin(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::halaman_admin)
{
    ui->setupUi(this);
}

halaman_admin::~halaman_admin()
{
    delete ui;
}

void halaman_admin::on_actionSupplier_triggered()
{
    supplier *halaman_supp;
    halaman_supp=new supplier(this);
    halaman_supp->show();
}

void halaman_admin::on_actionBarang_Masuk_triggered()
{
    barang_masuk *brg_msk;
    brg_msk =new barang_masuk(this);
    brg_msk->show();
}

void halaman_admin::on_actionStok_Barang_triggered()
{
    barang_stok *brg_stok;
    brg_stok =new barang_stok(this);
    brg_stok->show();
}

void halaman_admin::on_actionPeminjaman_Barang_triggered()
{
    pinjam_barang *pinjam_brg;
    pinjam_brg =new pinjam_barang(this);
    pinjam_brg->show();
}

void halaman_admin::on_actionBarang_Keluar_triggered()
{
    barang_keluar *brg_keluar;
    brg_keluar =new barang_keluar(this);
    brg_keluar->show();
}

void halaman_admin::on_actionBarang_triggered()
{
    databarang *databrg;
    databrg =new databarang(this);
    databrg->show();
}

void halaman_admin::on_actionKeluar_triggered()
{
    this->close();
    MainWindow *login;
    login =new MainWindow(this);
    login->show();

}
