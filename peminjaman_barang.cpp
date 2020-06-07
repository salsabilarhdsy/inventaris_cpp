#include "peminjaman_barang.h"
#include "ui_peminjaman_barang.h"

peminjaman_barang::peminjaman_barang(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::peminjaman_barang)
{
    ui->setupUi(this);
}

peminjaman_barang::~peminjaman_barang()
{
    delete ui;
}
