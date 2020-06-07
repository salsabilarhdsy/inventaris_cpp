#include "barang_keluar.h"
#include "ui_barang_keluar.h"

barang_keluar::barang_keluar(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::barang_keluar)
{
    ui->setupUi(this);
}

barang_keluar::~barang_keluar()
{
    delete ui;
}
